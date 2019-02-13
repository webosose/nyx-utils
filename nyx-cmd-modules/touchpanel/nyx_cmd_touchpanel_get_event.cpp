// Copyright (c) 2016-2019 LG Electronics, Inc.
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
#include "nyx_cmd_touchpanel_get_event.h"
#include <nyx/common/nyx_device.h>

#include <iostream>
#include <sstream>
#include <cstring>
#include <getopt.h>
#include <stdlib.h>
#include <poll.h>
using namespace std;

static string nameStr = "get_touch_event";
static string descriptionStr = "Touch panel get event.";

NyxCmdTouchPanelGetEvent::NyxCmdTouchPanelGetEvent()
{
}

string NyxCmdTouchPanelGetEvent::Description()
{
	return descriptionStr;
}

string NyxCmdTouchPanelGetEvent::Name()
{
	return nameStr;
}

bool NyxCmdTouchPanelGetEvent::readTouchEventData(nyx_device_handle_t
        deviceTouchId)
{
	nyx_error_t error = NYX_ERROR_NONE;
	nyx_event_handle_t eventHandle = NULL;
	nyx_touchpanel_event_type_t touchPanelType = NYX_TOUCHPANEL_EVENT_TYPE_INVALID;
	nyx_touchpanel_event_item_t *touchPanelItem = NULL;
	int32_t count = 0;

	do
	{
		error = nyx_device_get_event(deviceTouchId, &eventHandle);

		if (error != NYX_ERROR_NONE || eventHandle == NULL)
		{
			return false;
		}

		nyx_touchpanel_event_get_type(eventHandle, &touchPanelType);
		nyx_touchpanel_event_get_touches(eventHandle, &touchPanelItem, &count);

	}
	while (count <= 0);

	for (auto i = 0; i < count; i++)
	{
		nyx_touchpanel_event_item_t *touchItem = touchPanelItem++;
		cout << " x coordinate =" << touchItem->x << "  y coordinate =" << touchItem->y
		     << endl;
	}

	if (eventHandle)
	{
		error = nyx_device_release_event(deviceTouchId, eventHandle);
	}

	if (error != NYX_ERROR_NONE)
	{
		cerr << "failed to release event";
		return false;
	}

	return true;

}

int NyxCmdTouchPanelGetEvent::Execute(const char *deviceId, int argc,
                                      char **argv)
{
	nyx_device_handle_t device = NULL;
	nyx_error_t error = NYX_ERROR_NONE;
	int touchPanelFD;
	int poll_ret_val = -1;

	error = nyx_init();

	if (error == NYX_ERROR_NONE)
	{
		error = nyx_device_open(NYX_DEVICE_TOUCHPANEL, deviceId, &device);

		if (device != NULL)
		{
			error = nyx_device_get_event_source(device, &touchPanelFD);

			if (error == NYX_ERROR_NONE)
			{
				struct pollfd ufds[1];
				ufds[0].fd = touchPanelFD;
				ufds[0].events = POLLIN;
				ufds[0].revents = 0;
				cout << "Touch the screen to get X,Y coordinates or Press Ctrl+C to exit" <<
				     endl;

				while (1)
				{
					poll_ret_val = poll(ufds, 1, -1);

					if ((poll_ret_val != -1) && ufds[0].revents && POLLIN)
					{
						readTouchEventData(device);
					}
					else
					{
						cerr << "poll system call error" << endl;
					}
				}

			}
			else if (error == NYX_ERROR_NOT_IMPLEMENTED)
			{
				cout << "Command Not Implemented " << endl;
			}
			else
			{
				cerr << "error getting event source" << endl;
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
