// Copyright (c) 2013-2021 LG Electronics, Inc.
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

#include "nyx_cmd_os_info_query.h"

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

NyxCmdOSInfoQuery::NyxCmdOSInfoQuery()
{
}

/*
* Command usage description as a string.
*/
string NyxCmdOSInfoQuery::Description()
{
	return string("Returns OS information");
}

/*
* Command name as it will be written on the command line.
*/
string NyxCmdOSInfoQuery::Name()
{
	return string("query");
}

void NyxCmdOSInfoQuery::initCommandMap(nyx_device_type_t &devType,
                                       std::map<std::string, commandUsage> &commandMap)
{
	devType = NYX_DEVICE_OS_INFO;
	commandMap["core_os_kernel_version"] = commandUsage(
	        NYX_OS_INFO_CORE_OS_KERNEL_VERSION, "Return Core OS kernel version info");
	commandMap["core_os_name"] = commandUsage(NYX_OS_INFO_CORE_OS_NAME,
	                             "Return Core OS name");
	commandMap["core_os_release"] = commandUsage(NYX_OS_INFO_CORE_OS_RELEASE,
	                                "Return Core OS release info");
	commandMap["core_os_release_codename"] = commandUsage(
	            NYX_OS_INFO_CORE_OS_RELEASE_CODENAME, "Return Core OS release codename");
	commandMap["webos_build_id"] = commandUsage(NYX_OS_INFO_WEBOS_BUILD_ID,
	                               "Return webOS build ID");
	commandMap["webos_imagename"] = commandUsage(NYX_OS_INFO_WEBOS_IMAGENAME,
	                                "Return webOS imagename");
	commandMap["webos_name"] = commandUsage(NYX_OS_INFO_WEBOS_NAME,
	                                        "Return webOS name");
	commandMap["webos_prerelease"] = commandUsage(NYX_OS_INFO_WEBOS_PRERELEASE,
	                                 "Return webOS prerelease info");
	commandMap["webos_release"] = commandUsage(NYX_OS_INFO_WEBOS_RELEASE,
	                              "Return webOS release info");
	commandMap["webos_release_codename"] = commandUsage(
	        NYX_OS_INFO_WEBOS_RELEASE_CODENAME, "Return webOS release codename");

#ifdef NYX_OS_INFO_WEBOS_RELEASE_PLATFORMCODE
	commandMap["webos_release_platformcode"] = commandUsage(
            NYX_OS_INFO_WEBOS_RELEASE_PLATFORMCODE, "Return webOS value to evaluate platform version");
#endif

	commandMap["webos_manufacturing_version"] = commandUsage(
	            NYX_OS_INFO_WEBOS_MANUFACTURING_VERSION, "Return webOS manufacturing version");
	commandMap["encryption_key_type"] = commandUsage(
	                                        NYX_OS_INFO_ENCRYPTION_KEY_TYPE, "Return encryption key type");
	commandMap["webos_build_datetime"] = commandUsage(
	        NYX_OS_INFO_WEBOS_BUILD_DATETIME, "Return the time stamp for the build");
}

nyx_error_t NyxCmdOSInfoQuery::nyxQuery(nyx_device_handle_t device,
                                        commandUsage::command_enum_t cmd, const char **retVal)
{
	return nyx_os_info_query(device, cmd.os_info_enum, retVal);
}
