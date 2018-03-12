// Copyright (c) 2016-2018 LG Electronics, Inc.
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
#include "nyx_cmd_led_set_mode.h"
#include <iostream>
#include <sstream>
#include <cstring>
#include <getopt.h>
#include <stdlib.h>

using namespace std;

static string nameStr = "led_set_mode";
static string descriptionStr = "Sets device led mode.";
static std::unordered_map<std::string, nyx_led_controller_mode_t>controllerModeMap
=
{
	{"invert_colour_off", NYX_LED_CONTROLLER_INVERT_COLOUR_OFF},
	{"invert_colour_on", NYX_LED_CONTROLLER_INVERT_COLOUR_ON},
	{"ambient_on", NYX_LED_CONTROLLER_AMBIENT_MODE_ON},
	{"ambient_off", NYX_LED_CONTROLLER_AMBIENT_MODE_OFF},
	{"dnd_on", NYX_LED_CONTROLLER_DND_MODE_ON},
	{"dnd_off", NYX_LED_CONTROLLER_DND_MODE_OFF},
	{"outdoor_mode", NYX_LED_CONTROLLER_OUTDOOR_MODE}
};

NyxCmdLedSetMode::NyxCmdLedSetMode()
{
}

string NyxCmdLedSetMode::Description()
{
	return descriptionStr;
}

string NyxCmdLedSetMode::Name()
{
	return nameStr;
}

int NyxCmdLedSetMode::Execute(const char *deviceId, int argc, char **argv)
{
	nyx_device_handle_t device = NULL;
	nyx_error_t error = NYX_ERROR_NONE;
	string commandType;

	commandType = resolveArguments(argc, argv);

	if (!commandType.empty())
	{
		error = nyx_init();

		if (error == NYX_ERROR_NONE)
		{
			error = nyx_device_open(NYX_DEVICE_LED_CONTROLLER, deviceId, &device);

			if (device != NULL)
			{
				auto iter = controllerModeMap.find(commandType);

				if (iter != controllerModeMap.end())
				{
					error = nyx_led_controller_set_mode(device, controllerModeMap[commandType]);

					if (error == NYX_ERROR_NONE)
					{
						cout << "set to " << commandType << endl;
					}
					else
					{
						cerr << "Error in setting led mode" << commandType;
					}
				}
				else
				{
					error = NYX_ERROR_INVALID_VALUE;
					cerr << "Error: invalid set_mode option." << commandType <<  endl;
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

std::string NyxCmdLedSetMode::resolveArguments(int argc, char **argv)
{
	std::string retval = "";

	if (optind < argc)
	{
		retval = argv[optind++];
	}
	else
	{
		cerr << "Error: Not enough arguments" << endl;
	}

	return retval;
}
