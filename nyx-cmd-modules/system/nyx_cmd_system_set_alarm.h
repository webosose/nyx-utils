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

#ifndef NYXCMDSYSTEMSETALARM_H
#define NYXCMDSYSTEMSETALARM_H

/**
 * @file nyx_cmd_system_set_alarm.h
 *
 * @brief Implementation class for nyx-cmd System device type set alarm command.
 *
 */

#include <time.h>
#include <nyx/nyx_client.h>
#include <nyx/common/nyx_device.h>

class NyxCmdSetAlarm : public NyxCmdCommand
{
	/**
	* @defgroup nyx_cmd_system_set_alarm nyx-cmd System device type set alarm command
	* @ingroup nyx_cmd_system_module
	* @{
	*/
private:
	char *seconds;
	static const int RESOLVE_ARGS_INVALID = -200;
	static const int RESOLVE_ARGS_FAILED = -100;
	static const int RESOLVE_ARGS_BLOCKING = -50;
	static const int RESOLVE_ARGS_NON_BLOCKING = -25;

	/**
	 * Resolve arguments given to Execute function. Parses the command line arguments and
	 * resolves them to proper variables.
	 *
	 * @param[in]   argc - number of arguments
	 * @param[in]   argv - list of arguments
	 *
	 * @return int The selected option
	 *
	 */
	int resolveArguments(int argc, char **argv);

public:
	/**
	 * Class constructor.
	 *
	 */
	NyxCmdSetAlarm(void);
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
	 * Execute the command. Resolves command parameters from the command line arguments.
	 * Full argument list is expected.
	 *
	 * @param[in]   deviceId - device identifier
	 * @param[in]   argc     - number of arguments
	 * @param[in]   argv     - list of arguments
	 *
	 * @return error value from command. 0 if no error.
	 *
	 */
	int Execute(const char *deviceId, int argc, char **argv);
	/** @} */
};

#endif // NYXCMDSYSTEMSETALARM_H
