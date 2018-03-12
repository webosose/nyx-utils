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

#ifndef NYXCMDCHARGER_H
#define NYXCMDCHARGER_H

/**
 * @file nyx_cmd_charger.h
 *
 * @brief Implementation class for nyx-cmd Charger device type.
 *
 */

#include "nyx_cmd_devicetype.h"

#include <string>

class NyxCmdCharger : public NyxCmdDeviceType
{
	/**
	* @defgroup nyx_cmd_charger_module nyx-cmd Charger module
	* @ingroup nyx_cmd_modules
	* @defgroup nyx_cmd_charger_devicetype nyx-cmd Charger device type implementation
	* @ingroup nyx_cmd_charger_module
	* @{
	*/
protected:
	/**
	 * Get the correct command based on input string.
	 *
	 * @param[in]   cmdName - command name
	 *
	 * @return Pointer to the command
	 *
	 */
	NyxCmdCommand *getCommand(std::string cmdName);

public :
	/**
	 * Get the device type specific usage.
	 *
	 * @return Usage info for the device type
	 *
	 */
	std::string Usage(void);

	/**
	 * Get the device type specific name.
	 *
	 * @return Name for the device type
	 *
	 */
	std::string Name(void);

	/**
	 * Get the device type specific description.
	 *
	 * @return Description for the device type
	 *
	 */
	std::string Description(void);
	/** @} */
};

#endif // NYXCMDCHARGER_H
