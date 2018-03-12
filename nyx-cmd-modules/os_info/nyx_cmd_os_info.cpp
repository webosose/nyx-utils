// Copyright (c) 2013-2018 LG Electronics, Inc.
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

#include "nyx_cmd_os_info.h"
#include "nyx_cmd_os_info_query.h"

#include <getopt.h>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

// Name of the device type
string NyxCmdOSInfo::Name()
{
	return string("OSInfo");
}

// Usage information for the device type.
string NyxCmdOSInfo::Usage()
{
	ostringstream usage;

	usage << "COMMAND" << endl;
	usage << left << "  " << setw(30) << "query [QUERY-OPTIONS] [QUERY]" << setw(
	          30) << "Query OS information" << endl;
	usage << left << setw(32) << "" <<
	      "If [QUERY] not specified, returns all information" << endl;
	usage << "QUERY-OPTIONS" << endl;
	usage << left << "  " << setw(30) << "--format=FORMAT" << setw(
	          30) << "Set output format (e.g. --format=json)" << endl;
	usage << left << setw(32) << "" << "json - output in 'JSON' format" << endl;
	usage << left << setw(32) << "" << "plain - output in 'plain' format" << endl;
	usage << left << setw(32) << "" << "shell - output in 'shell' format" << endl;
	usage << left << setw(32) << "" <<
	      "Defaults to 'plain' if 'format' option is left out" << endl;
	usage << left << "  " << setw(30) << "-l, --list" << setw(
	          30) << "List available command targets" << endl;
	usage << left << setw(32) << "" << "(e.g. nyx-cmd OSInfo query -l)" << endl;
	usage << "QUERY" << endl;

	//os_info query usage
	std::map<string, commandUsage> tempMap;
	nyx_device_type_t tempType;

	NyxCmdOSInfoQuery().initCommandMap(tempType, tempMap);

	for (std::map<string, commandUsage>::const_iterator itr = tempMap.begin();
	        itr != tempMap.end(); ++itr)
	{
		usage << left << "  " << setw(30) <<  itr->first << setw(
		          30) << itr->second.commandStr << endl;
	}

	return usage.str();
}

// Human readable description of the device type.
string NyxCmdOSInfo::Description()
{
	return string("Nyx 'OS Info' device type.");
}

/*
* Returns the command object instance by for defined name.
* Implemented command names and their class initiations are added here.
*/
NyxCmdCommand *NyxCmdOSInfo::getCommand(string commandName)
{
	nyx_error_t error = NYX_ERROR_GENERIC;

	if (commandName == "query")
	{
		return new NyxCmdOSInfoQuery();
	}

	return NULL;
}

extern "C"
{
	NyxCmdDeviceType *getNyxCmdDeviceTypeInstance()
	{
		return new NyxCmdOSInfo();
	}
}
