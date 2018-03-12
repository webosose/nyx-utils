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

#include "nyx_cmd_keys.h"
#include "nyx_cmd_keys_events.h"
#include <nyx/common/nyx_device.h>

#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

string NyxCmdKeys::Name()
{
	return string("Keys");
}

string NyxCmdKeys::Description()
{
	return string("Nyx 'Keys' device type.");
}

string NyxCmdKeys::Usage()
{

	ostringstream usage;
	usage << "COMMAND" << endl;
	usage << left << setw(30) << "subscribe_key_event" << setw(30)
	      << "Start Capturing key press and release events. Ctrl-C to end." << endl;

	usage << left << setw(30) << "subscribe_power_key_event" << setw(30)
	      << "Start Capturing power key press and release events. Ctrl-C to end." << endl;
	return usage.str();
}

// Returns the command object instance for defined name.
// Implemented command names and their class initiations are added here.
NyxCmdCommand *NyxCmdKeys::getCommand(string commandName)
{
	if (commandName == "subscribe_key_event")
	{
		return new NyxCmdKeysEvents(NYX_DEVICE_KEYS);
	}

	if (commandName == "subscribe_power_key_event")
	{
		return new NyxCmdKeysEvents(NYX_DEVICE_POWERKEY);
	}

	return NULL;
}

extern "C"
{
	NyxCmdDeviceType *getNyxCmdDeviceTypeInstance()
	{
		return new NyxCmdKeys();
	}
}


