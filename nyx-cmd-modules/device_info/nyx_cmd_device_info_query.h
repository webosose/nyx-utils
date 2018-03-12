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

#ifndef __NYXCMDDEVICEINFOQUERY_H__
#define __NYXCMDDEVICEINFOQUERY_H__

/**
 * @file nyx_cmd_device_info_query.h
 *
 * @brief Implementation class for nyx-cmd Device info device type query command.
 *
 */

#include <string>
#include <map>
#include <nyx/nyx_client.h>
#include <nyx/common/nyx_device.h>

#include "nyx_cmd_query_command.h"
#include "nyx_cmd_device_info.h"

class NyxCmdDeviceInfoQuery : public NyxCmdQueryCommand
{
	/**
	* @defgroup nyx_cmd_device_info_query nyx-cmd Device info device type query command
	* @ingroup nyx_cmd_device_info_module
	* @{
	*/
protected:
	/**
	 * Executes a single query.
	 *
	 * @param[in]   device   - Nyx device handle
	 * @param[in]   cmd      - command to be queried
	 * @param[out]  retVal   - Returned string from query
	 *
	 * @return error from Nyx calls. NYX_ERROR_NONE if no error
	 *
	 */
	nyx_error_t nyxQuery(nyx_device_handle_t device,
	                     commandUsage::command_enum_t cmd, const char **retVal);

public:
	/**
	 * Class constructor.
	 *
	 */
	NyxCmdDeviceInfoQuery(void);
	/**
	 * Get the description of the command functionality.
	 *
	 * @return String containing description of the functionality.
	 *
	 */
	std::string Description();

	/**
	 * Get the name for command. This will be compared against the command line arguments
	 *
	 * @return String containing command name.
	 *
	 */
	std::string Name();

	/**
	 * Initializes command map for the command.
	 *
	 * @param[in]   devType     - Nyx device type
	 * @param[out]  commandMap  - Initialized commandMap
	 *
	 */
	void initCommandMap(nyx_device_type_t &devType,
	                    std::map<std::string, commandUsage> &commandMap);
	/** @} */
};

#endif // __NYXCMDDEVICEINFOQUERY_H__
