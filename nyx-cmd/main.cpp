// Copyright (c) 2012-2018 LG Electronics, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0

#include <stdio.h>
#include <getopt.h>
#include <dlfcn.h>
#include <dirent.h>
#include <errno.h>

#include <cstdlib>
#include <map>
#include <string>
#include <cstring>
#include <list>
#include <iostream>

#include "nyx_cmd_devicetype.h"

#include <nyx/nyx_client.h>
#include <nyx/common/nyx_device.h>

#ifndef NYX_CMD_MODULE_DIR
#error "NYX_CMD_MODULE_DIR not defined!"
#endif

#ifndef NYX_CMD_MODULE_PREFIX
#error "NYX_CMD_MODULE_PREFIX not defined!"
#endif

#ifndef NYX_CMD_VERSION_INFO
#error "NYX_CMD_VERSION_INFO not defined!"
#endif

using namespace std;

static char *deviceId = NULL;
static const char *defaultDevId = "Main";

static bool versionQuery = false;
static bool usageInfo = false;

static nyx_device_handle_t device = NULL;
static nyx_system_shutdown_type_t argument;

static void usage(void);
static void printVersion();
static char *resolveArguments(int argc, char **argv);
static void searchLibraries(string libPath, list<string> &files);
static void listImplementations(void);

static void usage(void)
{
	printf("usage:\n");
	printf("nyx-cmd [OPTIONS] [DEVICE-TYPE [COMMAND [ARGS]...]]\n");
	printf("OPTIONS\n");
	printf("  -v, --version\t\t\tDisplay version of nyx-cmd when no other\n");
	printf("\t\t\t\targuments are present.\n");
	printf("\t\t\t\tDisplay version of device type module when DEVICE-TYPE\n");
	printf("\t\t\t\tis specified.\n");
	printf("  -i, --id\t\t\tSet the device identifier (e.g. -iMyDevId).\n");
	printf("\t\t\t\tUnless specified, uses 'Main'.\n");
	printf("  -h, --help\t\t\tUsage guidance.\n");
	printf("\t\t\t\tDisplay usage guidance of device type module when\n");
	printf("\t\t\t\tDEVICE-TYPE is specified.\n");
	printf("  -l, --list\t\t\tList installed device type modules.\n");
	printf("DEVICE-TYPE\n");
	printf("  E.g. System\n");
	printf("COMMAND\n");
	printf("  Maps onto one of the functions within the API for the specified DEVICE-TYPE.\n");
	printf("  Requires a value for DEVICE-TYPE.\n");
	printf("ARGS\n");
	printf("  COMMAND specific argument lists.\n");
	exit(EXIT_SUCCESS);
}

static void printVersion()
{
	printf("%s\n", NYX_CMD_VERSION_INFO);
}

static char *resolveArguments(int argc, char **argv)
{
	int c;
	char *devType = NULL;

	opterr = 0;

	static struct option long_options[] =
	{
		{"version", optional_argument, 0, 'v' },
		{"id", required_argument, 0, 'i' },
		{"help", optional_argument, 0, 'h' },
		{"list", no_argument, 0, 'l' },
		{0, 0, 0, 0 }
	};

	if (argc < 2) // Not enough arguments, minimum command is "nyx-cmd [OPTION]"
	{
		// calling usage exits the program
		usage();
	}

	while (1)
	{
		int option_index = 0;

		// Note that the + prevents getopt from permuting the contents of argv and it also stops processing as soon as
		// a nonoption argument is met. This allows for the device types to have separate option values from the main options.
		c = getopt_long(argc, argv, "+lvi:h", long_options, &option_index);

		if (c == -1)
		{
			break;
		}

		switch (c)
		{
			case 'i':
				deviceId = optarg;
				break;

			case 'v':
				versionQuery = true;
				break;

			case 'h':
				usageInfo = true;
				break;

			case 'l':
				listImplementations();
				break;

			default:
				cerr << "Error: Error resolving options" << endl;
				exit(1);
		}

	} //while(1)

	if (optind < argc)
	{
		//Device type
		devType = argv[optind++];
	}

	// initialize 'deviceId' if not found in parameters
	if (NULL == deviceId)
	{
		deviceId = const_cast<char *>(defaultDevId);
	}

	return devType;
}


int main(int argc, char **argv)
{
	int retVal = -1;
	char *devType = resolveArguments(argc, argv);

	if (versionQuery && usageInfo)
	{
		// both version query and usage info was wanted, just print usage
		cout << "Both version query and usage defined, only usage is shown" << endl;
		versionQuery = false;
	}

	if (devType)
	{
		char *error;
		void *lib_handle;
		NyxCmdDeviceType *devTypeInstance = NULL;
		NyxCmdDeviceType* (*initialize)(void);

		//create the plugin path and name
		string libName(NYX_CMD_MODULE_DIR);
		libName.append("/");
		libName.append("lib" NYX_CMD_MODULE_PREFIX);
		libName.append(devType);
		libName.append(".so");

		lib_handle = dlopen(libName.c_str(), RTLD_LAZY);

		if (lib_handle)
		{
			//Clear the error log
			dlerror();

			// Get pointer to Instance creation function.
			// The funtion name is used to identify that we are dealing with
			// the type of plugin we are interested in.
			initialize = (NyxCmdDeviceType * (*)(void)) dlsym(lib_handle,
			             "getNyxCmdDeviceTypeInstance");

			if (initialize)
			{
				try
				{
					devTypeInstance = (*initialize)();

					if (versionQuery)
					{
						cout << devTypeInstance->Version() << endl;
						retVal = 0;
					}
					else if (usageInfo)
					{
						// print out the generic guidance so there's no need to have it in each plugin
						cout << "Usage for " << devTypeInstance->Description() << endl;
						cout << "nyx-cmd [OPTIONS] " << devTypeInstance->Name() <<
						     " [COMMAND [ARGS]...]]" << endl;
						cout << "OPTIONS" << endl << devTypeInstance->Options() << endl;
						cout << devTypeInstance->Usage() << endl;

						retVal = 0;
					}
					else
					{
						retVal = devTypeInstance->executeCommand(deviceId, argc, argv);
					}
				}
				catch (...)
				{
					cout << "Error: Error executing command." << endl;
				}

				if (devTypeInstance)
				{
					delete devTypeInstance;
				}
			}
			else
			{
				cerr << error << endl;
			}

			dlclose(lib_handle);
		}
		else
		{
			cerr << "Error: Error opening the plugin" << endl;
		}
	}
	else
	{
		if (versionQuery)
		{
			printVersion();
		}
		else if (usageInfo)
		{
			usage();
		}
		else
		{
			cout << "Error: No available device types" << endl;
		}
	}

	return (0 == retVal) ? EXIT_SUCCESS : EXIT_FAILURE;
}

/*
* Searches for libraries in the defined path
*/
static void searchLibraries(string libPath, list<string> &files)
{
	DIR *libDirectory;
	struct dirent *dirp;
	string filenameComparator("lib" NYX_CMD_MODULE_PREFIX);

	if ((libDirectory  = opendir(libPath.c_str())) == NULL)
	{
		cout << "Error: Error(" << errno << ") opening plugins directory: " << libPath
		     << endl;
	}

	while ((dirp = readdir(libDirectory)) != NULL)
	{
		if (!strcmp(dirp->d_name, "."))
		{
			continue;
		}

		if (!strcmp(dirp->d_name, ".."))
		{
			continue;
		}

		if (dirp->d_name[0] == '.')
		{
			continue;
		}

		string filename(dirp->d_name);

		// search for libraries starting with nyx-cmd module naming convention
		if (filename.find(filenameComparator) != -1 &&
		        filename.substr(filename.find_last_of(".") + 1) == "so")
		{
			string name(dirp->d_name);
			files.push_back(name);
		}
	}

	closedir(libDirectory);
}

/*
* Lists all device types available
*/
static void listImplementations(void)
{
	list<string> files;
	void *lib_handle;
	char *error;

	searchLibraries(NYX_CMD_MODULE_DIR, files);

	NyxCmdDeviceType* (*initialize)(void);
	NyxCmdDeviceType *deviceInstance = NULL;
	string nameStr;

	for (list<string>::iterator it = files.begin(); it != files.end(); ++it)
	{
		lib_handle = dlopen(it->c_str(), RTLD_LAZY);

		if (lib_handle)
		{
			//Clear the error log
			dlerror();

			initialize = (NyxCmdDeviceType * (*)(void)) dlsym(lib_handle,
			             "getNyxCmdDeviceTypeInstance");

			if (initialize != NULL && (error = dlerror()) == NULL)
			{
				deviceInstance = (*initialize)();
				nameStr = deviceInstance->Name();
				// print out the name
				cout << nameStr << endl;
				delete deviceInstance;
			}

			dlclose(lib_handle);
		}
	}

	exit(EXIT_SUCCESS);
}
