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
#include "nyx_cmd_system_set_alarm.h"

#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <getopt.h>
#include <unistd.h>
#include <stdlib.h>
#include <glib.h>

using namespace std;

static string nameStr = "system_set_alarm";
static string descriptionStr =
    "Sets the system alarm.\nTakes alarm time (in \"Mar 01 2013 10:00:00\" format) as an argument.";
int alarm_done = 0;
GMainLoop *mainloop = 0;

NyxCmdSetAlarm::NyxCmdSetAlarm(): seconds(NULL)
{
}

string NyxCmdSetAlarm::Description()
{
	return descriptionStr;
}

string NyxCmdSetAlarm::Name()
{
	return nameStr;
}

void alarm_cb(nyx_device_handle_t device, nyx_callback_status_t status,
              void *ctx)
{
	cout << "Alarm fired" << endl;
	alarm_done = 1;
}

gboolean check_alarm_done_cb(gpointer user_data)
{
	if (alarm_done)
	{
		g_main_loop_quit(mainloop);
		return FALSE;
	}

	return TRUE;
}

int NyxCmdSetAlarm::Execute(const char *deviceId, int argc, char **argv)
{
	nyx_device_handle_t device = NULL;
	nyx_error_t error = NYX_ERROR_NONE;
	seconds = NULL;
	time_t alarm_time = 0;

	int option = resolveArguments(argc, argv);

	switch (option)
	{
		case RESOLVE_ARGS_INVALID:
		case RESOLVE_ARGS_FAILED:
		default:
			cerr << "Error: Error resolving arguments" << endl;
			break;

		case RESOLVE_ARGS_BLOCKING:
		case RESOLVE_ARGS_NON_BLOCKING:
			if (seconds)
			{
				alarm_time = time(NULL) + strtol(seconds, NULL, 10);
			}
			else
			{
				cerr << "Error: Error resolving arguments" << endl;
				break;
			}

			error = nyx_init();

			if (error == NYX_ERROR_NONE)
			{
				error = nyx_device_open(NYX_DEVICE_SYSTEM, deviceId, &device);

				if (device != NULL)
				{
					if (RESOLVE_ARGS_BLOCKING == option)
					{
						error = nyx_system_set_alarm(device, alarm_time, alarm_cb, NULL);

						if (error == NYX_ERROR_NONE)
						{
							mainloop = g_main_loop_new(NULL, FALSE);
							g_timeout_add(100, check_alarm_done_cb, NULL);
							g_main_loop_run(mainloop);
							g_main_loop_unref(mainloop);
						}

						nyx_device_close(device);
					}
					else
					{
						error = nyx_system_set_alarm(device, alarm_time, alarm_cb, NULL);
						nyx_device_close(device);
					}

					if (error != NYX_ERROR_NONE)
					{
						cerr << "Error: Error in setting alarm on the device." << endl;
					}
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
			break;
	}

	return (NYX_ERROR_NONE == error) ? 0 : -1;
}

int NyxCmdSetAlarm::resolveArguments(int argc, char **argv)
{
	int retval = RESOLVE_ARGS_INVALID;
	int c = 0;

	// reset errors and prevent from outputting
	opterr = 0;

	static struct option long_options[] =
	{
		{"block", required_argument, 0, 'b' },
		{0, 0, 0, 0 }
	};

	while (1)
	{
		int option_index = 0;
		c = getopt_long(argc, argv, "b:", long_options, &option_index);

		if (c == -1)
		{
			break;
		}

		switch (c)
		{
			case 'b':
				seconds = optarg;

				if (NULL == seconds)
				{
					retval = RESOLVE_ARGS_FAILED;
				}
				else
				{
					retval = RESOLVE_ARGS_BLOCKING;
				}

				break;

			default:
				retval = RESOLVE_ARGS_FAILED;
				break;
		}
	}

	if (RESOLVE_ARGS_INVALID == retval)
	{
		// check if there is still arguments left
		// If there wasn't an alarm time to set, it's an error
		if (0 == (argc - optind))
		{
			retval = RESOLVE_ARGS_FAILED;
		}
		else
		{
			seconds = argv[optind++];
			retval = RESOLVE_ARGS_NON_BLOCKING;
		}
	}

	if (seconds)
	{
		char *pend = seconds;
		(void) strtol(seconds, &pend, 10);

		if ('\0' != *pend)
		{
			retval = RESOLVE_ARGS_FAILED;
		}
	}

	return retval;
}
