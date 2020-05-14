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

#include "nyx_cmd_gps_providers_query.h"

#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <map>

using namespace std;

/*
* Class constructor
*/

NyxCmdGpsProvidersQuery::NyxCmdGpsProvidersQuery()
{
}

/*
* Command usage description as a string.
*/
string NyxCmdGpsProvidersQuery::Description()
{
	return string("Returns GPS Providers information");
}

/*
* Command name as it will be written on the command line.
*/
string NyxCmdGpsProvidersQuery::Name()
{
	return string("queryProviders");
}

void NyxCmdGpsProvidersQuery::initCommandMap(nyx_device_type_t &devType,
                                       std::map<std::string, commandUsage> &commandMap)
{
	devType = NYX_DEVICE_GPS;
	commandMap["provider"] = commandUsage(
	        NYX_GPS_PROVIDER_NAME, "Return GPS provoder name");
	commandMap["status"] = commandUsage(NYX_GPS_PROVIDER_STATUS,
	                             "Return GPS provider status");
}

nyx_error_t NyxCmdGpsProvidersQuery::nyxQuery(nyx_device_handle_t device,
                                        commandUsage::command_enum_t cmd, const char **retVal)
{
	return nyx_gps_providers_query(device, cmd.gps_providers_enum, retVal);
}
