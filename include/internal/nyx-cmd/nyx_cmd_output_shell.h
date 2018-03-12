// Copyright (c) 2013-2018 LG Electronics, Inc.
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
 * @file nyx_cmd_output_shell.h
 *
 * @brief Base class for nyx-cmd shell output.
 *
 */

#ifndef __NYXCMDOUTPUTSHELL_H__
#define __NYXCMDOUTPUTSHELL_H__

#include <string>
#include "nyx_cmd_output.h"

class NyxCmdOutputShell : public NyxCmdOutput
{
	/**
	* @defgroup nyx_cmd_output_shell nyx-cmd shell output class.
	* @ingroup nyx_cmd_output_module
	* @{
	*/
public:
	/**
	 * Print string to stream.
	 *
	 * @param[in]   output      - stream where output is done
	 * @param[in]   query_name  - query name that is printed to stream
	 * @param[in]   query_value - query_value that is printed to stream.
	 *                            Copy is made as it might be formatted before
	 *                            printing is done
	 *
	 */
	void printOutput(std::ostringstream &output,
	                 const std::string &query_name,
	                 std::string query_value);

	/**
	 * Print an integer to stream.
	 *
	 * @param[in]   output      - stream where output is done
	 * @param[in]   query_name  - query name that is printed to the stream
	 * @param[in]   query_value - integer that is printed to the stream
	 *
	 */
	void printOutput(std::ostringstream &output,
	                 const std::string &query_name,
	                 const int &query_value);

	/** @} */
};
#endif // __NYXCMDOUTPUTSHELL_H__
