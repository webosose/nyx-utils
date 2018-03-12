// Copyright (c) 2013-2018 LG Electronics, Inc.
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
#include "nyx_cmd_system_shutdown.h"

#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <getopt.h>

using namespace std;

/*
* Class constructor
*/

NyxCmdSystemShutdown::NyxCmdSystemShutdown()
{
}

/*
* Command usage description as a string.
*/
string NyxCmdSystemShutdown::Description()
{
	return string("Executes system shutdown.\nTakes shutdown reason as an argument.");
}

/*
* Command name as it will be written on the command line.
*/
string NyxCmdSystemShutdown::Name()
{
	return string("system_shutdown");
}

/*
* Execute command.
* Resolves command parameters from the command line arguments.
*/
int NyxCmdSystemShutdown::Execute(const char *deviceId, int argc, char **argv)
{
	nyx_device_handle_t device = NULL;
	nyx_system_shutdown_type_t shutdownReason;
	nyx_error_t error = NYX_ERROR_NONE;

	shutdownReason = resolveArguments(argc, argv);

	if (shutdownReason != -1)
	{
		error = nyx_init();

		if (error == NYX_ERROR_NONE)
		{
			error = nyx_device_open(NYX_DEVICE_SYSTEM, deviceId, &device);

			if (device != NULL)
			{
				error = nyx_system_shutdown(device, shutdownReason, NULL);

				if (error != NYX_ERROR_NONE)
				{
					cerr << "Error: Error in shutting down the device." << endl;
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
nyx_system_shutdown_type_t NyxCmdSystemShutdown::resolveArguments(int argc,
        char **argv)
{
	// defaults to 'NYX_SYSTEM_NORMAL_SHUTDOWN' for cases there isn't any parameters
	// Unknown arguments are still considered invalid.
	nyx_system_shutdown_type_t retVal = NYX_SYSTEM_NORMAL_SHUTDOWN;

	if (optind < argc)
	{
		//Arguments
		char *argumentStr = argv[optind++];

		if (strcmp(argumentStr, "NYX_SYSTEM_NORMAL_SHUTDOWN") == 0)
		{
			retVal = NYX_SYSTEM_NORMAL_SHUTDOWN;
		}
		else if (strcmp(argumentStr, "NYX_SYSTEM_EMERG_SHUTDOWN") == 0)
		{
			retVal = NYX_SYSTEM_EMERG_SHUTDOWN;
		}
		else if (strcmp(argumentStr, "NYX_SYSTEM_TEST_SHUTDOWN") == 0)
		{
			retVal = NYX_SYSTEM_TEST_SHUTDOWN;
		}
		else
		{
			cerr << "Error: Unknown argument" << endl;
			retVal = (nyx_system_shutdown_type_t) - 1;
		}
	}

	return retVal;
}
