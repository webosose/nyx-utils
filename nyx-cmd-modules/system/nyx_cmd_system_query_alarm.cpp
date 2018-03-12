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
#include "nyx_cmd_system_query_alarm.h"

#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <getopt.h>
#include <unistd.h>

using namespace std;

static string nameStr = "query_next_alarm";
static string descriptionStr = "Gets the next rtc alarm.";

NyxCmdQueryAlarm::NyxCmdQueryAlarm()
{
}

string NyxCmdQueryAlarm::Description()
{
	return descriptionStr;
}

string NyxCmdQueryAlarm::Name()
{
	return nameStr;
}

int NyxCmdQueryAlarm::Execute(const char *deviceId, int argc, char **argv)
{
	nyx_device_handle_t device = NULL;
	time_t alarm_time;
	nyx_error_t error = NYX_ERROR_NONE;

	error = nyx_init();

	if (error == NYX_ERROR_NONE)
	{
		error = nyx_device_open(NYX_DEVICE_SYSTEM, deviceId, &device);

		if (device != NULL)
		{
			error = nyx_system_query_next_alarm(device, &alarm_time);

			if (error == NYX_ERROR_NONE)
			{
				cout << "Next alarm time is " << ctime(&alarm_time) << endl;
			}
			else
			{
				cerr << "Error: Error in getting next alarm on the device." << endl;
			}

			nyx_device_close(device);
		}
		else
		{
			cerr << "Error: Could not open System device" << endl;
		}
	}
	else
	{
		cerr << "Error: Error initializing Nyx" << endl;
	}

	nyx_deinit();

	return (NYX_ERROR_NONE == error) ? 0 : -1;
}
