// Copyright (c) 2016-2018 LG Electronics, Inc.
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

#ifndef NYX_TOUCH_PANEL_ACTIVESCANRATE_SET_H
#define NYX_TOUCH_PANEL_ACTIVESCANRATE_SET_H

/**
 * @file nyx_cmd_touchpanel_activescanrate_mode.h
 *
 * @brief Implementation class for nyx-cmd TouchPanel device type set mode command.
 *
 */

#include <nyx/nyx_client.h>
#include <string>

class NyxCmdTouchPanelSetActiveScanRate : public NyxCmdCommand
{
	/**
	* @defgroup nyx_cmd_touchpanel_set_mode nyx-cmd TouchPanel device type set mode command
	* @ingroup nyx_cmd_led_module
	* @{
	*/
private:
	/**
	 * Resolve arguments given to Execute function. Parses the command line arguments and
	 * resolves them to proper variables.
	 *
	 * @param[in]   argc - number of arguments
	 * @param[in]   argv - list of arguments
	 *
	 * @return int TouchPanel mode to be set, -1 if error
	 *
	 */
	int32_t resolveArguments(int argc, char **argv);

public:
	/**
	 * Class constructor.
	 *
	 */
	NyxCmdTouchPanelSetActiveScanRate(void);

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

#endif // NYX_TOUCH_PANEL_ACTIVESCANRATE_SET_H
