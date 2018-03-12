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

#include "nyx_cmd_charger.h"
#include "nyx_cmd_charger_query.h"
#include "nyx_cmd_charger_register.h"

#include <string>
#include <sstream>

using namespace std;

static string nameStr = "Charger";
static string descriptionStr = "Nyx 'Charger' device type.";

string NyxCmdCharger::Name()
{
	return nameStr;
}

string NyxCmdCharger::Usage()
{
	ostringstream usage;
	usage << "COMMAND" << endl;
	usage << "  query GROUP_ARGS" << endl;
	usage << "  register REGISTER_ARGS" << endl;
	usage << "GROUP_ARGS" << endl;
	usage << "  status\t\t\tQuery charger status" << endl;
	usage << "  event\t\t\t\tQuery charging event" << endl;
	usage << "REGISTER_ARGS" << endl;
	usage << "  status\t\t\tRegister for charger status change" << endl;
	usage << "  state\t\t\t\tRegister for charger state change" << endl;

	return usage.str();
}

string NyxCmdCharger::Description()
{
	return descriptionStr;
}

/*
* Returns the command object instance by for defined name.
* Implemented command names and their class initiations are added here.
*/
NyxCmdCommand *NyxCmdCharger::getCommand(string commandName)
{
	if (commandName == "query")
	{
		return new NyxCmdChargerQuery();
	}
	else if (commandName == "register")
	{
		return new NyxCmdChargerRegister();
	}

	return NULL;
}

extern "C"
{
	NyxCmdDeviceType *getNyxCmdDeviceTypeInstance()
	{
		return new NyxCmdCharger();
	}
}
