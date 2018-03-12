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
#include "nyx_cmd_battery_register_status.h"

#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <getopt.h>
#include <glib.h>

using namespace std;

static string nameStr = "battery_register_status";
static string descriptionStr =
    "Registers to device battery status changes and invokes callback.";
int cb_fired = 0;
GMainLoop *mainloop = 0;

NyxCmdBatteryRegisterStatus::NyxCmdBatteryRegisterStatus()
{
}

string NyxCmdBatteryRegisterStatus::Description()
{
	return descriptionStr;
}

string NyxCmdBatteryRegisterStatus::Name()
{
	return nameStr;
}

void status_cb(nyx_device_handle_t device, nyx_callback_status_t status,
               void *ctx)
{
	cout << "Status change callback fired, status = " << status << endl;
	nyx_battery_status_t battStatus;
	nyx_error_t error = NYX_ERROR_NONE;
	error = nyx_battery_query_battery_status(device, &battStatus);

	if (NYX_ERROR_NONE == error)
	{
		cout << "Battery status is: " << endl;
		cout << "Battery_present=\"" << battStatus.present << "\"" << endl;
		cout << "Battery_charging=\"" << battStatus.charging << "\"" << endl;
		cout << "Battery_percentage=\"" << battStatus.percentage << "\"" << endl;
		cout << "Battery_temperature=\"" << battStatus.temperature << "\"" << endl;
		cout << "Battery_current=\"" << battStatus.current << "\"" << endl;
		cout << "Battery_voltage=\"" << battStatus.voltage << "\"" << endl;
		cout << "Battery_capacity=\"" << battStatus.capacity << "\"" << endl;
		cout << "Battery_avg_current=\"" << battStatus.avg_current << "\"" << endl;
		cout << "Battery_capacity_raw=\"" << battStatus.capacity_raw << "\"" << endl;
		cout << "Battery_capacity_full40=\"" << battStatus.capacity_full40 << "\"" <<
		     endl;
		cout << "Battery_age=\"" << battStatus.age << "\"" << endl;
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
int NyxCmdBatteryRegisterStatus::Execute(const char *deviceId, int argc,
        char **argv)
{
	nyx_device_handle_t device = NULL;
	nyx_error_t error = NYX_ERROR_NONE;

	error = nyx_init();

	if (error == NYX_ERROR_NONE)
	{
		error = nyx_device_open(NYX_DEVICE_BATTERY, deviceId, &device);

		if (device != NULL)
		{
			error = nyx_battery_register_battery_status_callback(device, status_cb, NULL);

			if (error == NYX_ERROR_NONE)
			{
				mainloop = g_main_loop_new(NULL, FALSE);
				g_timeout_add(100, check_cb_fired, NULL);
				g_main_loop_run(mainloop);
				g_main_loop_unref(mainloop);
			}
			else
			{
				cerr << "Error in registering for battery status change" << endl;
			}

			nyx_device_close(device);
		}
		else
		{
			cerr << "Error in opening battery device" << endl;
		}
	}
	else
	{
		cerr << "Error: Error initializing Nyx" << endl;
	}

	nyx_deinit();
	return (NYX_ERROR_NONE == error) ? 0 : -1;
}
