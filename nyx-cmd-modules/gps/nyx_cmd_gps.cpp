// Copyright (c) 2020 LG Electronics, Inc.
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

#include "nyx_cmd_gps.h"
#include "nyx_cmd_gps_enable_mock.h"
#include "nyx_cmd_gps_set_mock_latency.h"

#include <string>
#include <sstream>


using namespace std;

static string nameStr = "Gps";
static string descriptionStr = "Nyx 'Gps' device type.";


string NyxCmdGps::Name()
{
	return nameStr;
}

string NyxCmdGps::Usage()
{
	ostringstream usage;
	usage << "COMMAND" << endl;
	usage << "  enablemock [VALUE]\t\tEnable GPS mock ( 0 = disable, 1 = Enable)" << endl;

	return usage.str();
}

string NyxCmdGps::Description()
{
	return descriptionStr;
}

// Returns the command object instance for defined name.
// Implemented command names and their class initiations are added here.
NyxCmdCommand *NyxCmdGps::getCommand(string commandName)
{
	if (commandName == "enablemock")
	{
		return new NyxCmdGpsEnableMock();
	}
	else if (commandName == "setmocklatency")
	{
		return new NyxCmdGpsSetMockLatency();
	}

	return NULL;
}

extern "C"
{
	NyxCmdDeviceType *getNyxCmdDeviceTypeInstance()
	{
		return new NyxCmdGps();
	}
}
