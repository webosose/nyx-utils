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
#include "nyx_cmd_touchpanel_get_active_scan_rate.h"

#include <iostream>
#include <sstream>
#include <cstring>
#include <getopt.h>
#include <stdlib.h>

using namespace std;

static string nameStr = "activescanrate_get_mode";
static string descriptionStr = "Gets device activescanrate mode.";

NyxCmdTouchPanelGetActiveScanRate::NyxCmdTouchPanelGetActiveScanRate()
{
}

string NyxCmdTouchPanelGetActiveScanRate::Description()
{
	return descriptionStr;
}

string NyxCmdTouchPanelGetActiveScanRate::Name()
{
	return nameStr;
}

int NyxCmdTouchPanelGetActiveScanRate::Execute(const char *deviceId, int argc,
        char **argv)
{
	nyx_device_handle_t device = NULL;
	nyx_error_t error = NYX_ERROR_NONE;
	uint32_t activeScanRate = 0;

	error = nyx_init();

	if (error == NYX_ERROR_NONE)
	{
		error = nyx_device_open(NYX_DEVICE_TOUCHPANEL, deviceId, &device);

		if (device != NULL)
		{
			error = nyx_touchpanel_get_active_scan_rate(device, &activeScanRate);

			if (error == NYX_ERROR_NONE)
			{
				cout << "set to " << activeScanRate << endl;
			}
			else if (error == NYX_ERROR_NOT_IMPLEMENTED)
			{
				cout << "Command Not Implemented " << endl;
			}
			else
			{
				cerr << "Error: Error in getting active scan rate." << activeScanRate <<  endl;
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

	return (NYX_ERROR_NONE == error) ? 0 : -1;
}
