// Copyright (c) 2020 LG Electronics, Inc.
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
#include "nyx_cmd_gps_enable_mock.h"

#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <getopt.h>
#include <stdlib.h>

using namespace std;

static string nameStr = "gps_enable_mock";
static string descriptionStr = "Enable device gps mock";

NyxCmdGpsEnableMock::NyxCmdGpsEnableMock()
{
}

string NyxCmdGpsEnableMock::Description()
{
	return descriptionStr;
}

string NyxCmdGpsEnableMock::Name()
{
	return nameStr;
}

int NyxCmdGpsEnableMock::Execute(const char *deviceId, int argc, char **argv)
{
	nyx_device_handle_t device = NULL;
	nyx_error_t error = NYX_ERROR_NONE;
	int mock;

	mock = resolveArguments(argc, argv);

	if (mock != -1)
	{
		error = nyx_init();

		if (error == NYX_ERROR_NONE)
		{
			error = nyx_device_open(NYX_DEVICE_GPS, "Mock" , &device);

			if (device != NULL)
			{
				error = nyx_gps_enable_mock(device, mock);

				if ((error == NYX_ERROR_NONE) && (mock == 1))
				{
					cout << "Gps mock is enable to " << mock << endl;
				}
				else if ((error == NYX_ERROR_NONE) && (mock == 0))
				{
					cout << "Gps mock is disable to " << mock << endl;
				}
				else
				{
					cerr << "Error: Error in setting gps mock." << endl;
				}

				nyx_device_close(device);
			}
			else
			{
				cerr << "Error: Could not open GPS device" << endl;
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

int NyxCmdGpsEnableMock::resolveArguments(int argc, char **argv)
{
	int retval = -1;

	if (optind < argc)
	{
		std::string input = argv[optind++];
		retval = atoi(input.c_str());
	}
	else
	{
		cerr << "Error: Not enough arguments" << endl;
	}

	return retval;
}
