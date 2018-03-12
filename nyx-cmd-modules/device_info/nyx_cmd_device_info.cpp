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

#include "nyx_cmd_device_info.h"
#include "nyx_cmd_device_info_query.h"

#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

// Name of the device type
string NyxCmdDeviceInfo::Name()
{
	return string("DeviceInfo");
}

// Usage information for the device type.
string NyxCmdDeviceInfo::Usage()
{
	ostringstream usage;

	usage << "COMMAND" << endl;
	usage << left << "  " << setw(30) << "query [QUERY-OPTIONS] [QUERY]" << setw(
	          30) << "Query device information" << endl;
	usage << left << setw(32) << "" <<
	      "If [QUERY] not specified, returns all information" << endl;
	usage << "QUERY-OPTIONS" << endl;
	usage << left << "  " << setw(30) << "-f FORMAT, --format=FORMAT" << setw(
	          30) << "Set output format (e.g. -f json)" << endl;
	usage << left << setw(32) << "" << "json - output in 'JSON' format" << endl;
	usage << left << setw(32) << "" << "plain - output in 'plain' format" << endl;
	usage << left << setw(32) << "" << "shell - output in 'shell' format" << endl;
	usage << left << setw(32) << "" <<
	      "Defaults to 'plain' if 'format' option is left out" << endl;
	usage << left << "  " << setw(30) << "-l, --list" << setw(
	          30) << "List available command targets" << endl;
	usage << left << setw(32) << "" << "(e.g. nyx-cmd DeviceInfo query -l)" << endl;
	usage << "QUERY" << endl;

	//device_info query usage
	std::map<string, commandUsage> tempMap;
	nyx_device_type_t tempType;

	NyxCmdDeviceInfoQuery().initCommandMap(tempType, tempMap);

	for (std::map<string, commandUsage>::const_iterator itr = tempMap.begin();
	        itr != tempMap.end(); ++itr)
	{
		usage << left << "  " << setw(30) <<  itr->first << setw(
		          30) << itr->second.commandStr << endl;
	}

	return usage.str();
}


// Human readable description of the device type.
string NyxCmdDeviceInfo::Description()
{
	return string("Nyx 'Device Info' device type.");
}

/*
* Returns the command object instance by for defined name.
* Implemented command names and their class initiations are added here.
*/
NyxCmdCommand *NyxCmdDeviceInfo::getCommand(string commandName)
{
	if (commandName == "query")
	{
		return new NyxCmdDeviceInfoQuery();
	}

	return NULL;
}

extern "C"
{
	NyxCmdDeviceType *getNyxCmdDeviceTypeInstance()
	{
		return new NyxCmdDeviceInfo();
	}
}


