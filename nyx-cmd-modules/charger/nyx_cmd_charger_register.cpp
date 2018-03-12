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
#include "nyx_cmd_charger_register.h"

#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <getopt.h>
#include <glib.h>

using namespace std;

static string nameStr = "charger_register";
static string descriptionStr =
    "Registers to device charger status/state changes and invokes callback.";
int cb_fired = 0;
GMainLoop *mainloop = 0;

NyxCmdChargerRegister::NyxCmdChargerRegister()
{
}

string NyxCmdChargerRegister::Description()
{
	return descriptionStr;
}

string NyxCmdChargerRegister::Name()
{
	return nameStr;
}

void status_cb(nyx_device_handle_t device, nyx_callback_status_t status,
               void *ctx)
{
	cout << "Status change callback fired, status=" << status << endl;
	nyx_charger_status_t chargerStatus;
	nyx_error_t error = NYX_ERROR_NONE;
	error = nyx_charger_query_charger_status(device, &chargerStatus);

	if (NYX_ERROR_NONE == error)
	{
		cout << "Charger status is: " << endl;
		cout << "Charger_charger_max_current=\"" << chargerStatus.charger_max_current <<
		     "\"" << endl;
		cout << "Charger_connected=\"" << chargerStatus.connected << "\"" << endl;
		cout << "Charger_powered=\"" << chargerStatus.powered << "\"" << endl;
		cout << "Charger_is_charging=\"" << chargerStatus.is_charging << "\"" << endl;
	}

	cb_fired = 1;
}

void state_cb(nyx_device_handle_t device, nyx_callback_status_t status,
              void *ctx)
{
	cout << "State change callback fired, status = " << status << endl;
	nyx_charger_event_t event;
	nyx_error_t error = NYX_ERROR_NONE;
	error = nyx_charger_query_charger_event(device, &event);

	if (NYX_ERROR_NONE == error)
	{
		cout << "Event is " << event << ":" << endl;

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

	cb_fired = 1;
}

gboolean check_cb_fired(gpointer user_data)
{
	if (cb_fired)
	{
		g_main_loop_quit(mainloop);
		return FALSE;
	}

	return TRUE;
}

/*
* Execute command.
* Resolves command parameters from the command line arguments.
*/
int NyxCmdChargerRegister::Execute(const char *deviceId, int argc, char **argv)
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
					error = nyx_charger_register_charger_status_callback(device, status_cb, NULL);

					if (error == NYX_ERROR_NONE)
					{
						mainloop = g_main_loop_new(NULL, FALSE);
						g_timeout_add(100, check_cb_fired, NULL);
						g_main_loop_run(mainloop);
						g_main_loop_unref(mainloop);
					}
					else
					{
						cerr << "Error in registering for charger status change" << endl;

					}
				}
				else if ("state" == operation)
				{
					error = nyx_charger_register_state_change_callback(device, state_cb, NULL);

					if (error == NYX_ERROR_NONE)
					{
						mainloop = g_main_loop_new(NULL, FALSE);
						g_timeout_add(100, check_cb_fired, NULL);
						g_main_loop_run(mainloop);
						g_main_loop_unref(mainloop);
					}
					else
					{
						cerr << "Error in registering for charger state change" << endl;
					}
				}
				else
				{
					cerr << "Error: Unknown argument" << endl;
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
string NyxCmdChargerRegister::resolveArguments(int argc, char **argv)
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
