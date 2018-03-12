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

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <list>
#include <string>
#include <iostream>
#include <cstring>
#include <dlfcn.h>
#include <stdlib.h>
#include <getopt.h>
#include <sstream>

#include "nyx_cmd_devicetype.h"

using namespace std;

NyxCmdDeviceType::NyxCmdDeviceType()
{
}

/*
* Default implementation for Version()
*
*/
string NyxCmdDeviceType::Version()
{
	int32_t major = nyx_get_api_version_major();
	int32_t minor = nyx_get_api_version_minor();

	ostringstream version;
	version << "NyxLib " << major << "." << minor;
	return version.str();
}

/*
* Default implementation for Options()
*
*/
string NyxCmdDeviceType::Options()
{
	ostringstream options;
	options << "  -i, --id\t\t\tSet the device identifier (e.g. -iMyDevId)" << endl;
	options << "\t\t\t\tUnless specified, uses 'Main'" << endl;
	options << "  -h, --help\t\t\tUsage guidance";
	return options.str();
}

/*
* Default implementation for Usage()
*
*/
string NyxCmdDeviceType::Usage()
{
	// output empty string
	return string("");
}

/*
* Executes the command defined in command line.
*
* Resolve command line and use map find to find right file name.
* Get the lib class initiator.
* Cast to proper base class type.
* Call execute comand.
*/
int NyxCmdDeviceType::executeCommand(const char *deviceId, int argc,
                                     char **argv)
{
	int err = -1;
	char *command = resolveArguments(argc, argv);

	if (command != NULL)
	{
		NyxCmdCommand *targetCommand = getCommand(command);

		if (targetCommand)
		{
			err = targetCommand->Execute(deviceId, argc, argv);
			delete targetCommand;
		}
		else
		{
			cout << "Error: Unknown command" << endl;
		}
	}
	else
	{
		throw (1);
	}

	return err;
}

/*
* Parses the command line arguments and resolves them to proper variables.
*/
char *NyxCmdDeviceType::resolveArguments(int argc, char **argv)
{
	char *commandStr = NULL;
	//Check that there are arguments left

	if (optind < argc)
	{
		//Command
		commandStr = argv[optind++];
	}

	return commandStr;
}
