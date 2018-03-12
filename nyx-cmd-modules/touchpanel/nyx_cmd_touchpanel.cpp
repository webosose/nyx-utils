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

#include "nyx_cmd_touchpanel.h"
#include "nyx_cmd_touchpanel_set_mode.h"
#include "nyx_cmd_touchpanel_get_mode.h"
#include "nyx_cmd_touchpanel_get_active_scan_rate.h"
#include "nyx_cmd_touchpanel_set_active_scan_rate.h"
#include "nyx_cmd_touchpanel_get_event.h"

#include <string>
#include <sstream>
#include <iostream>

using namespace std;

static string nameStr = "TouchPanel";
static string descriptionStr = "Nyx 'TouchPanel' device type.";


string NyxCmdTouchPanel::Name()
{
	return nameStr;
}

string NyxCmdTouchPanel::Usage()
{
	static ostringstream usage;
	usage << "COMMAND" << endl;
	usage << "  set_mode [VALUE]\t\tSet mode" << endl;
	usage << "  get_mode\t\t\tGet mode" << endl;
	usage << "  set_active_scan_rate[VALUE]\tset_active_scan_rate" << endl;
	usage << "  get_active_scan_rate\t\tget_active_scan_rate" << endl;
	usage << "  get_touch_events\t\tget_touch_events" << endl;
	return usage.str();
}

string NyxCmdTouchPanel::Description()
{
	return descriptionStr;
}

// Returns the command object instance for defined name.
// Implemented command names and their class initiations are added here.
NyxCmdCommand *NyxCmdTouchPanel::getCommand(string commandName)
{
	if (commandName == "set_mode")
	{
		return new NyxCmdTouchPanelSetMode();
	}
	else if (commandName == "get_mode")
	{
		return new NyxCmdTouchPanelGetMode();
	}
	else if (commandName == "set_active_scan_rate")
	{
		return new NyxCmdTouchPanelSetActiveScanRate();
	}
	else if (commandName == "get_active_scan_rate")
	{
		return new NyxCmdTouchPanelGetActiveScanRate();
	}
	else if (commandName == "get_touch_events")
	{
		return new NyxCmdTouchPanelGetEvent();
	}

	return NULL;
}

extern "C"
{
	NyxCmdDeviceType *getNyxCmdDeviceTypeInstance()
	{
		return new NyxCmdTouchPanel();
	}
}
