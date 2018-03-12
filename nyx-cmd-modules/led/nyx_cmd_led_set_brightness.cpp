// Copyright (c) 2014-2018 LG Electronics, Inc.
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
#include "nyx_cmd_led_set_brightness.h"

#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <getopt.h>
#include <stdlib.h>

using namespace std;

static string nameStr = "led_set_brightness";
static string descriptionStr = "Sets device led brigtness.";

NyxCmdLedSetBrightness::NyxCmdLedSetBrightness()
{
}

string NyxCmdLedSetBrightness::Description()
{
	return descriptionStr;
}

string NyxCmdLedSetBrightness::Name()
{
	return nameStr;
}

int NyxCmdLedSetBrightness::Execute(const char *deviceId, int argc, char **argv)
{
	nyx_device_handle_t device = NULL;
	nyx_error_t error = NYX_ERROR_NONE;
	int brightness;

	brightness = resolveArguments(argc, argv);

	if (brightness != -1)
	{
		error = nyx_init();

		if (error == NYX_ERROR_NONE)
		{
			error = nyx_device_open(NYX_DEVICE_LED, deviceId, &device);

			if (device != NULL)
			{
				error = nyx_led_set_brightness(device, brightness);

				if (error == NYX_ERROR_NONE)
				{
					cout << "Led brightness is set to " << brightness << endl;
				}
				else
				{
					cerr << "Error: Error in setting led brightness." << endl;
				}

				nyx_device_close(device);
			}
			else
			{
				cerr << "Error: Could not open LED device" << endl;
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

int NyxCmdLedSetBrightness::resolveArguments(int argc, char **argv)
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
