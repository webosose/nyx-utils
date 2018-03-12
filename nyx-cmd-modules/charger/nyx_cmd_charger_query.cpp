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
#include "nyx_cmd_charger_query.h"

#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <getopt.h>

using namespace std;

static string nameStr = "charger_query";
static string descriptionStr = "Returns device charger information.";

NyxCmdChargerQuery::NyxCmdChargerQuery()
{
}

string NyxCmdChargerQuery::Description()
{
	return descriptionStr;
}

string NyxCmdChargerQuery::Name()
{
	return nameStr;
}

/*
* Execute command.
* Resolves command parameters from the command line arguments.
*/
int NyxCmdChargerQuery::Execute(const char *deviceId, int argc, char **argv)
{
	nyx_device_handle_t device = NULL;
	nyx_error_t error = NYX_ERROR_NONE;
	string operation;

	operation = resolveArguments(argc, argv);

	if (!operation.empty())
	{
		error = nyx_init();

		if (error == NYX_ERROR_NONE)
		{
			error = nyx_device_open(NYX_DEVICE_CHARGER, deviceId, &device);

			if (device != NULL)
			{
				if ("status" == operation)
				{
					nyx_charger_status_t chargerStatus;
					error = nyx_charger_query_charger_status(device, &chargerStatus);

					if (NYX_ERROR_NONE == error)
					{
						cout << "Charger_charger_max_current=\"" << chargerStatus.charger_max_current <<
						     "\"" << endl;
						cout << "Charger_connected=\"" << chargerStatus.connected << "\"" << endl;
						cout << "Charger_powered=\"" << chargerStatus.powered << "\"" << endl;
						cout << "Charger_is_charging=\"" << chargerStatus.is_charging << "\"" << endl;
					}
					else
					{
						cerr << "Error in getting charger status" << endl;
					}
				}
				else if ("event" == operation)
				{
					nyx_charger_event_t event;
					error = nyx_charger_query_charger_event(device, &event);

					if (NYX_ERROR_NONE == error)
					{
						cout << "Event received is " << event << ":" << endl;

						if (event == NYX_NO_NEW_EVENT)
						{
							cout << "No new event" <<  endl;
						}

						if (event & NYX_CHARGER_CONNECTED)
						{
							cout << "Charger connected" <<  endl;
						}

						if (event & NYX_CHARGER_DISCONNECTED)
						{
							cout << "Charger disconnected" <<  endl;
						}

						if (event & NYX_CHARGER_FAULT)
						{
							cout << "Charger fault" <<  endl;
						}

						if (event & NYX_CHARGE_COMPLETE)
						{
							cout << "Charge complete" <<  endl;
						}

						if (event & NYX_CHARGE_RESTART)
						{
							cout << "Charge restart" <<  endl;
						}

						if (event & NYX_BATTERY_PRESENT)
						{
							cout << "Battery present" <<  endl;
						}

						if (event & NYX_BATTERY_ABSENT)
						{
							cout << "Battery absent" <<  endl;
						}

						if (event & NYX_BATTERY_CRITICAL_VOLTAGE)
						{
							cout << "Battery critical voltage" <<  endl;
						}

						if (event & NYX_BATTERY_TEMPERATURE_LIMIT)
						{
							cout << "Battery temperature limit" <<  endl;
						}
					}
					else
					{
						cerr << "Error in getting charger event" << endl;
					}
				}
				else
				{
					cerr << "Error: Unknown argument" << endl;
					// force return to be -1
					error = NYX_ERROR_INVALID_VALUE;
				}

				nyx_device_close(device);
			}
			else
			{
				cerr << "Error in opening charger device" << endl;
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
string NyxCmdChargerQuery::resolveArguments(int argc, char **argv)
{
	string retVal;

	if (optind < argc)
	{
		retVal = argv[optind++];
	}
	else
	{
		cerr << "Error: Not enough arguments" << endl;
	}

	return retVal;
}
