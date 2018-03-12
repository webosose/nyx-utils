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

/**
 * @file nyx_cmd_command.h
 *
 * @brief Base class for nyx-cmd commands.
 *
 */

#ifndef __NYXCMDCOMMAND_H__
#define __NYXCMDCOMMAND_H__

#include <string>
#include <nyx/nyx_client.h>
#include <nyx/common/nyx_device.h>

/**
 * Structure for different nyx-cmd commands.
 *
 * Has an union for command enums (from Nyx API) and usage string.
 * If you add support for a new Nyx device type, consider adding specific
 * enum type also to this union and a constructor for commandUsage struct.
 *
 */
struct commandUsage
{
	union command_enum_t
	{
		nyx_device_info_type_t device_info_enum;
		nyx_os_info_query_t os_info_enum;
	};

	command_enum_t commandEnum;
	std::string commandStr;

	// default constructor
	commandUsage() {};
	commandUsage(nyx_device_info_type_t cmd, const std::string &str)
		: commandStr(str)
	{
		commandEnum.device_info_enum = cmd;
	};
	commandUsage(nyx_os_info_query_t cmd, const std::string &str)
		: commandStr(str)
	{
		commandEnum.os_info_enum = cmd;
	};
};

class NyxCmdCommand
{
	/**
	* @defgroup nyx_cmd_base_classes nyx-cmd base classes
	* @ingroup nyx_cmd_modules
	* @defgroup nyx_cmd_command nyx-cmd command base class.
	* @ingroup nyx_cmd_base_classes
	* @{
	*/

public:

	/**
	 * Get the description of the command functionality.
	 * This virtual function needs to be implemented by command classes (e.g. reboot)
	 *
	 * @return String containing description of the functionality.
	 *
	 */
	virtual std::string Description() = 0;

	/**
	 * Get the name for command. This will be compared against the command line arguments
	 * This virtual function needs to be implemented by command classes (e.g. reboot)
	 *
	 * @return String containing command name.
	 *
	 */
	virtual std::string Name() = 0;

	/**
	 * Execute the command. Full argument list is expected.
	 * This virtual function needs to be implemented by command classes (e.g. reboot)
	 *
	 * @param[in]   deviceId - device identifier
	 * @param[in]   argc     - number of arguments
	 * @param[in]   argv     - list of arguments
	 *
	 * @return error value from command. 0 if no error.
	 *
	 */
	virtual int Execute(const char *deviceId, int argc, char **argv) = 0;

	/**
	 * Get the command version information.
	 * This virtual function may be implemented by command classes (e.g. reboot)
	 *
	 * @return String containing version information.
	 *
	 */
	virtual std::string Version();

	virtual ~NyxCmdCommand() {}
	/** @} */
};

#endif // __NYXCMDCOMMAND_H__
