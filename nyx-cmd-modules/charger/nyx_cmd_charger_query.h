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

#ifndef NYXCMDCHARGERQUERY_H
#define NYXCMDCHARGERQUERY_H

/**
 * @file nyx_cmd_charger_query.h
 *
 * @brief Implementation class for nyx-cmd Charger device type query command.
 *
 */

#include <nyx/nyx_client.h>

class NyxCmdChargerQuery : public NyxCmdCommand
{
	/**
	* @defgroup nyx_cmd_charger_query nyx-cmd Charger device type query command
	* @ingroup nyx_cmd_charger_module
	* @{
	*/
private:
	/**
	 * Resolve arguments given to Execute function.
	 *
	 * @param[in]   argc - number of arguments
	 * @param[in]   argv - list of arguments
	 *
	 * @return Charger query operation, empty string if error
	 *
	 */
	std::string resolveArguments(int argc, char **argv);
public:
	/**
	 * Class constructor.
	 *
	 */
	NyxCmdChargerQuery(void);
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
	 * Execute the command. Full argument list is expected.
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

#endif // NYXCMDCHARGERQUERY_H
