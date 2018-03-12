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

#include "nyx_cmd_led.h"
#include "nyx_cmd_led_set_brightness.h"
#include "nyx_cmd_led_get_brightness.h"
#include "nyx_cmd_led_set_mode.h"

#include <string>
#include <sstream>


using namespace std;

static string nameStr = "Led";
static string descriptionStr = "Nyx 'Led' device type.";


string NyxCmdLed::Name()
{
	return nameStr;
}

string NyxCmdLed::Usage()
{
	ostringstream usage;
	usage << "COMMAND" << endl;
	usage << "  set_mode [VALUE]\t\tSet mode" << endl;
	usage << "  invert_colour_off\t\t invert colour off" << endl;
	usage << "  invert_colour_on\t\t invert colour on" << endl;
	usage << "  ambient_off\t\t\t ambient mode off" << endl;
	usage << "  ambient_on\t\t\t ambient mode on" << endl;
	usage << "  dnd_off\t\t\t dnd mode off" << endl;
	usage << "  dnd_on\t\t\t dnd mode on" << endl;
	usage << "  outdoor_mode\t\t\t outdoor mode" << endl;
	usage << "  get_brightness\t\t Get LED brightness" << endl;
	usage << "  set_brightness VALUE\t\t Set LED brightness" << endl;

	return usage.str();
}

string NyxCmdLed::Description()
{
	return descriptionStr;
}

// Returns the command object instance for defined name.
// Implemented command names and their class initiations are added here.
NyxCmdCommand *NyxCmdLed::getCommand(string commandName)
{
	if (commandName == "set_brightness")
	{
		return new NyxCmdLedSetBrightness();
	}
	else if (commandName == "get_brightness")
	{
		return new NyxCmdLedGetBrightness();
	}
	else if (commandName == "set_mode")
	{
		return new NyxCmdLedSetMode();
	}
	else
	{
	}

	return NULL;
}

extern "C"
{
	NyxCmdDeviceType *getNyxCmdDeviceTypeInstance()
	{
		return new NyxCmdLed();
	}
}
