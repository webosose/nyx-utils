// Copyright (c) 2012-2018 LG Electronics, Inc.
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

#include "nyx_cmd_battery.h"
#include "nyx_cmd_battery_read.h"
#include "nyx_cmd_battery_register_status.h"

#include <string>
#include <sstream>

using namespace std;

static string nameStr = "Battery";
static string descriptionStr = "Nyx 'Battery' device type.";

string NyxCmdBattery::Name()
{
	return nameStr;
}

string NyxCmdBattery::Usage()
{
	ostringstream usage;
	usage << "COMMAND" << endl;
	usage << "  readall [GROUP_ARGS]\t\tRead all values" << endl;
	usage << "  register_status\t\tRegister to battery status change" << endl;
	usage << "GROUP_ARGS" << endl;
	usage << "  status\t\t\tBattery status" << endl;
	usage << "  ctia\t\t\t\tCTIA parameters" << endl;

	return usage.str();
}

string NyxCmdBattery::Description()
{
	return descriptionStr;
}

/*
* Returns the command object instance by for defined name.
* Implemented command names and their class initiations are added here.
*/
NyxCmdCommand *NyxCmdBattery::getCommand(string commandName)
{
	if (commandName == "readall")
	{
		return new NyxCmdBatteryRead();
	}
	else if (commandName == "register_status")
	{
		return new NyxCmdBatteryRegisterStatus();
	}

	return NULL;
}

extern "C"
{
	NyxCmdDeviceType *getNyxCmdDeviceTypeInstance()
	{
		return new NyxCmdBattery();
	}
}
