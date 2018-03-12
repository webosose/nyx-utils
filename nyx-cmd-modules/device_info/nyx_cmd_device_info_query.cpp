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


#include "nyx_cmd_device_info_query.h"

#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <map>
#include <getopt.h>

using namespace std;

/*
* Class constructor
*/

NyxCmdDeviceInfoQuery::NyxCmdDeviceInfoQuery()
{
}

/*
* Command usage description as a string.
*/
string NyxCmdDeviceInfoQuery::Description()
{
	return string("Returns device info.");
}

/*
* Command name as it will be written on the command line.
*/
string NyxCmdDeviceInfoQuery::Name()
{
	return string("query");
}

void NyxCmdDeviceInfoQuery::initCommandMap(nyx_device_type_t &devType,
        std::map<std::string, commandUsage> &commandMap)
{
	devType = NYX_DEVICE_DEVICE_INFO;
	commandMap["board_type"] = commandUsage(NYX_DEVICE_INFO_BOARD_TYPE,
	                                        "Return board type");
	commandMap["bt_addr"] = commandUsage(NYX_DEVICE_INFO_BT_ADDR,
	                                     "Return Bluetooth address");
	commandMap["device_name"] = commandUsage(NYX_DEVICE_INFO_DEVICE_NAME,
	                            "Return device name");
	commandMap["hardware_id"] = commandUsage(NYX_DEVICE_INFO_HARDWARE_ID,
	                            "Return hardware ID");
	commandMap["hardware_revision"] = commandUsage(
	                                      NYX_DEVICE_INFO_HARDWARE_REVISION, "Return hardware revision");
	commandMap["installer"] = commandUsage(NYX_DEVICE_INFO_INSTALLER,
	                                       "Return installer");
	commandMap["keyboard_type"] = commandUsage(NYX_DEVICE_INFO_KEYBOARD_TYPE,
	                              "Return keyboard type");
	commandMap["modem_present"] = commandUsage(NYX_DEVICE_INFO_MODEM_PRESENT,
	                              "Return modem availability");
	commandMap["nduid"] = commandUsage(NYX_DEVICE_INFO_NDUID, "Return NDUID");
	commandMap["product_id"] = commandUsage(NYX_DEVICE_INFO_PRODUCT_ID,
	                                        "Return product ID");
	commandMap["radio_type"] = commandUsage(NYX_DEVICE_INFO_RADIO_TYPE,
	                                        "Return radio type");
	commandMap["ram_size"] = commandUsage(NYX_DEVICE_INFO_RAM_SIZE,
	                                      "Return RAM size");
	commandMap["serial_number"] = commandUsage(NYX_DEVICE_INFO_SERIAL_NUMBER,
	                              "Return serial number");
	commandMap["storage_free"] = commandUsage(NYX_DEVICE_INFO_STORAGE_FREE,
	                             "Return free storage size");
	commandMap["storage_size"] = commandUsage(NYX_DEVICE_INFO_STORAGE_SIZE,
	                             "Return storage size");
	commandMap["wifi_addr"] = commandUsage(NYX_DEVICE_INFO_WIFI_ADDR,
	                                       "Return WiFi MAC address");
	commandMap["wired_addr"] = commandUsage(NYX_DEVICE_INFO_WIRED_ADDR,
	                                        "Return Wired MAC address");
}

nyx_error_t NyxCmdDeviceInfoQuery::nyxQuery(nyx_device_handle_t device,
        commandUsage::command_enum_t cmd, const char **retVal)
{
	return nyx_device_info_query(device, cmd.device_info_enum, retVal);
}
