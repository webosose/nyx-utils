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
#include "nyx_cmd_keys_events.h"

#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <getopt.h>

#include <poll.h>
#include <linux/input.h>

using namespace std;

static string nameStr = "Keys";
static string descriptionStr =
    "Register to poll key press events";

/*
* Class constructor
*/

NyxCmdKeysEvents::NyxCmdKeysEvents(nyx_device_type_t deviceType): mDeviceType(
	    deviceType),mDevice(NULL)
{

}

/*
* Command usage description as a string.
*/
string NyxCmdKeysEvents::Description()
{
	return descriptionStr;
}

/*
* Command name as it will be written on the command line.
*/
string NyxCmdKeysEvents::Name()
{
	return nameStr;
}

typedef struct key_map
{
	int keyCode;
	const char *keyString;
} key_map_t;

static const key_map_t customKeys[] =
{
	{NYX_KEYS_CUSTOM_KEY_UNDEFINED, "undefined"},
	{NYX_KEYS_CUSTOM_KEY_VOL_UP, "volume_up"},
	{NYX_KEYS_CUSTOM_KEY_VOL_DOWN, "volume_down"},
	{NYX_KEYS_CUSTOM_KEY_POWER_ON, "power"},
	{NYX_KEYS_CUSTOM_KEY_HOME, "home"},
	{NYX_KEYS_CUSTOM_KEY_RINGER_SW, "ringer"},
	{NYX_KEYS_CUSTOM_KEY_SLIDER_SW, "slider"},
	{NYX_KEYS_CUSTOM_KEY_HEADSET_BUTTON, "headset_button"},
	{NYX_KEYS_CUSTOM_KEY_HEADSET_PORT, "headset"},
	{NYX_KEYS_CUSTOM_KEY_HEADSET_PORT_MIC, "headset-mic"},
	{NYX_KEYS_CUSTOM_KEY_MEDIA_PLAY, "play"},
	{NYX_KEYS_CUSTOM_KEY_MEDIA_PAUSE, "pause"},
	{NYX_KEYS_CUSTOM_KEY_MEDIA_STOP, "stop"},
	{NYX_KEYS_CUSTOM_KEY_MEDIA_NEXT, "next"},
	{NYX_KEYS_CUSTOM_KEY_MEDIA_PREVIOUS, "prev"},
	{NYX_KEYS_CUSTOM_KEY_MEDIA_REPEAT_ALL, "repeat-all"},
	{NYX_KEYS_CUSTOM_KEY_MEDIA_REPEAT_TRACK, "repeat-track"},
	{NYX_KEYS_CUSTOM_KEY_MEDIA_REPEAT_NONE, "repeat-none"},
	{NYX_KEYS_CUSTOM_KEY_MEDIA_SHUFFLE_ON, "shuffle-on"},
	{NYX_KEYS_CUSTOM_KEY_MEDIA_SHUFFLE_OFF, "shuffle-off"},
	{NYX_KEYS_CUSTOM_KEY_MEDIA_PLAYPAUSE, "pause"},
	{NYX_KEYS_CUSTOM_KEY_BACK, "f2"},
	{NYX_KEYS_CUSTOM_KEY_HOT, "f1"}
};

static const key_map_t standardKeys [] =
{
	{KEY_BACK, "back"},
	{KEY_PLAYCD, "play"},
	{KEY_PAUSECD, "pause"},
	{KEY_NEXTSONG, "next"},
	{KEY_PREVIOUSSONG, "previous"},
	{KEY_FASTFORWARD, "fastforward"},
	{KEY_REWIND, "rewind"},
	{KEY_STOPCD, "stop"}
};

std::string  NyxCmdKeysEvents::keyToString(int key, nyx_key_type_t key_type)
{
	int arraySizeCust = sizeof(customKeys) / sizeof(customKeys[0]);
	int arraySizeStd = sizeof(standardKeys) / sizeof(standardKeys[0]);

	switch (key_type)
	{
		case NYX_KEY_TYPE_CUSTOM:
			for (int cnt = 0; cnt < arraySizeCust; cnt++)
			{
				if (key == customKeys[cnt].keyCode)
				{
					return customKeys[cnt].keyString;

				}
			}

			break;

		case NYX_KEY_TYPE_STANDARD:

			for (int cnt = 0; cnt < arraySizeStd; cnt++)
			{
				if (key == standardKeys[cnt].keyCode)
				{
					return standardKeys[cnt].keyString;

				}
			}

			break;

		default :
			break;
	}

	return "wrong_key";
}


void NyxCmdKeysEvents::readKeyData()
{
	int keycode = 0;
	bool is_auto_repeat = false;
	bool is_pressed = false;
	nyx_error_t error = NYX_ERROR_NONE;
	nyx_event_handle_t event_handle = NULL;
	nyx_key_type_t key_type;

	error = nyx_device_get_event(mDevice, &event_handle);

	if (error != NYX_ERROR_NONE)
	{
		cerr << "Error getting event" ;
	}

	nyx_keys_event_get_key(event_handle, &keycode);
	nyx_keys_event_get_key_type(event_handle, &key_type);
	nyx_keys_event_get_key_is_auto_repeat(event_handle, &is_auto_repeat);
	nyx_keys_event_get_key_is_press(event_handle, &is_pressed);

	if (key_type == NYX_KEY_TYPE_STANDARD || key_type == NYX_KEY_TYPE_CUSTOM)
	{
		string keyString = keyToString(keycode, key_type);
		cout << keyString << (is_pressed ? " pressed" : " released");
		cout << (is_auto_repeat ? " AutoRepeat" : "") << endl;
	}
	else if (key_type == NYX_KEY_TYPE_UNDEFINED)
	{
		cerr << "Error: key type is undefined" << endl;
	}
	else
	{
		cerr << "Invalid key " << key_type << endl;
	}

}

void NyxCmdKeysEvents::waitForEvent()
{
	int eventSrc = -1;
	struct pollfd ufds[1];
	int maxfds = 0;
	int ready = 0;

	nyx_error_t error = nyx_device_get_event_source(mDevice, &eventSrc);

	if (error != NYX_ERROR_NONE)
	{
		cerr << "Error: Failed to obtain key event_source successfully!\n";
		return;
	}

	ufds[0].fd = eventSrc;
	ufds[0].events = POLLIN;
	ufds[0].revents = 0;

	//poll and read key press events until program termination(Ctrl-C)
	while (1)
	{
		ready = poll(ufds, maxfds + 1, -1);

		if (ufds[0].revents & POLLIN)
		{
			readKeyData();
		}
	}

}

/*
* Execute command.
* Resolves command parameters from the command line arguments.
*/
int NyxCmdKeysEvents::Execute(const char *deviceId, int argc, char **argv)
{
	mDevice = NULL;
	nyx_error_t error = nyx_init();

	if (error == NYX_ERROR_NONE)
	{
		error = nyx_device_open(mDeviceType, deviceId, &mDevice);

		if (mDevice != NULL)
		{
			waitForEvent();
		}
		else
		{
			cerr << "Error: Failed to open device Keys" << endl ;
		}

		nyx_device_close(mDevice);
	}
	else
	{
		cerr << "Error: Error initializing Nyx" << endl;
	}

	nyx_deinit();
	return (NYX_ERROR_NONE == error) ? 0 : -1;
}

