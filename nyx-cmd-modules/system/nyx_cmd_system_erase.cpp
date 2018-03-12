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

#include "nyx_cmd_command.h"
#include "nyx_cmd_system_erase.h"

#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <getopt.h>

using namespace std;

static string nameStr = "erase_partition";
static string descriptionStr =
    "Marks one or more logical partitions to be erased on the next reboot";

/*
* Class constructor
*/

NyxCmdSystemErase::NyxCmdSystemErase()
{
}

/*
* Command usage description as a string.
*/
string NyxCmdSystemErase::Description()
{
	return descriptionStr;
}

/*
* Command name as it will be written on the command line.
*/
string NyxCmdSystemErase::Name()
{
	return nameStr;
}

/*
* Execute command.
* Resolves command parameters from the command line arguments.
*/
int NyxCmdSystemErase::Execute(const char *deviceId, int argc, char **argv)
{
	nyx_device_handle_t device = NULL;
	nyx_system_erase_type_t eraseType;
	nyx_error_t error = NYX_ERROR_NONE;

	eraseType = resolveArguments(argc, argv);

	if (eraseType != -1)
	{
		error = nyx_init();

		if (error == NYX_ERROR_NONE)
		{
			error = nyx_device_open(NYX_DEVICE_SYSTEM, deviceId, &device);

			if (device != NULL)
			{
				error = nyx_system_erase_partition(device, eraseType);

				if (error != NYX_ERROR_NONE)
				{
					cerr << "Error: Error in rebooting the device." << endl;
				}

				nyx_device_close(device);
			}
		}
		else
		{
			cerr << "Error: Error initializing Nyx" << endl;
		}

		nyx_deinit();
	}

	return (NYX_ERROR_NONE == error) ? 0 : -1;
}

/*
* Parses the command line arguments and resolves them to proper variables.
*/
nyx_system_erase_type_t NyxCmdSystemErase::resolveArguments(int argc,
        char **argv)
{
	// No default is allowed given the nature of the command
	nyx_system_erase_type_t retVal = (nyx_system_erase_type_t) - 1;

	if (optind < argc)
	{
		//Arguments
		char *argumentStr = argv[optind++];

		if (strcmp(argumentStr, "var") == 0)
		{
			retVal = NYX_SYSTEM_ERASE_VAR;
		}
		else if (strcmp(argumentStr, "media") == 0)
		{
			retVal = NYX_SYSTEM_ERASE_MEDIA;
		}
		else if (strcmp(argumentStr, "all") == 0)
		{
			retVal = NYX_SYSTEM_ERASE_ALL;
		}
		else if (strcmp(argumentStr, "developer") == 0)
		{
			retVal = NYX_SYSTEM_ERASE_DEVELOPER;
		}
		else
		{
			cerr << "Error: Unknown argument - " << argumentStr << endl;
		}
	}
	else
	{
		cerr << "Error: No default value is defined" << endl;
	}

	return retVal;
}
