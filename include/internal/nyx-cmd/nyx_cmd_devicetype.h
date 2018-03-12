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

#ifndef __NYXCMDDEVICETYPE_H__
#define __NYXCMDDEVICETYPE_H__

/**
 * @file nyx_cmd_devicetype.h
 *
 * @brief Base class for nyx-cmd device types that instantiates and holds all
 * commands for a specific device type. This class is inherited by actual
 * nyx-cmd device type implementations.
 *
 */

#include <map>

#include "nyx_cmd_command.h"

class NyxCmdDeviceType
{
	/**
	* @defgroup nyx_cmd_device_type nyx-cmd DeviceType base class.
	* @ingroup nyx_cmd_base_classes
	* @{
	*/
private:
	/**
	 * Resolve arguments given to executeCommand function.
	 *
	 * @param[in]   argc - number of arguments
	 * @param[in]   argv - list of arguments
	 *
	 * @return Command name or NULL if fails
	 *
	 */
	char *resolveArguments(int argc, char **argv);

public:
	/**
	 * Class constructor.
	 *
	 */
	NyxCmdDeviceType(void);

	/**
	 * Get the device type specific name.
	 * This virtual function needs to be implemented by all nyx-cmd device type plugins (e.g. system)
	 *
	 * @return Name for the device type
	 *
	 */
	virtual std::string Name() = 0;

	/**
	 * Get the device type specific usage information.
	 * Note that generic part of usage information is provided so plugins should start with COMMAND
	 * part.
	 *
	 * This virtual function may be implemented by all nyx-cmd device type plugins (e.g. system)
	 *
	 * @return Usage information for the device type
	 *
	 * Example
	 * @snippet nyx_cmd_system.cpp Usage info
	 *
	 */
	virtual std::string Usage();


	/**
	 * Get the device type specific version information.
	 * This virtual function may be implemented by all nyx-cmd device type plugins (e.g. system)
	 *
	 * @return Version information for the device type
	 *
	 */
	virtual std::string Version();

	/**
	 * Get the device type specific options.
	 * This virtual function may be implemented by all nyx-cmd device type plugins (e.g. system)
	 *
	 * @return Options for the device type
	 *
	 */
	virtual std::string Options();

	/**
	 * Get the device type specific description.
	 * This virtual function needs to be implemented by all nyx-cmd device type plugins (e.g. system)
	 *
	 * @return Description for the device type
	 *
	 */
	virtual std::string Description() = 0;

	/**
	 * Execute command defined in the command line arguments.
	 * Throws an exception if command is not found.
	 *
	 * @param[in]   deviceId - device identifier
	 * @param[in]   argc     - number of arguments
	 * @param[in]   argv     - list of arguments
	 *
	 * @return return value from command or -1 if command is not found
	 *
	 */
	int executeCommand(const char *deviceId, int argc, char **argv);

	/**
	 * Get the correct command based on input string.
	 * This virtual function needs to be implemented by all nyx-cmd device type plugins (e.g. system)
	 *
	 * @param[in]   cmdName - command name
	 *
	 * @return pointer to the command
	 *
	 */
	virtual NyxCmdCommand *getCommand(std::string cmdName) = 0;
	/** @} */
};

extern "C"
{
	/**
	 * 'Entrypoint' to the nyx_cmd device type library. Called first to get the correct
	 * device type.
	 *
	 * @return Pointer to the NyxCmdDeviceType instance.
	 *
	 */
	NyxCmdDeviceType *getNyxCmdDeviceTypeInstance();
}

#endif // __NYXCMDDEVICETYPE_H__
