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
 * @file nyx_cmd_query_command.h
 *
 * @brief Base class for nyx-cmd query type commands.
 *
 * Inherit from this class to add new query type commands. If your new\n
 * command queries for strings only, you don't need to implement more\n
 * than pure virtual functions.
 *
 */

#ifndef __NYXCMDQUERYCOMMAND_H__
#define __NYXCMDQUERYCOMMAND_H__

#include <map>
#include "nyx_cmd_command.h"
#include "nyx_cmd_output.h"

class NyxCmdQueryCommand : public NyxCmdCommand
{
	/**
	* @defgroup nyx_cmd_query_command nyx-cmd query type command base class.
	* @ingroup nyx_cmd_base_classes
	* @{
	*/
private:
	static const int RESOLVE_ARGS_INVALID = -200;
	static const int RESOLVE_ARGS_FAILED = -100;
	static const int RESOLVE_ARGS_LIST_ALL_QUERIES = -50;
	static const int RESOLVE_ARGS_EXECUTE_ALL_QUERIES = -25;

	std::map<std::string, commandUsage> commandMap;
	nyx_device_type_t nyxDevType;
	NyxCmdOutput *output;

	/**
	 * List all available query targets.
	 *
	 * For 'listAllQueries' to work, please fill 'commandUsage' structure correctly.
	 *
	 */
	void listAllQueries();

	/**
	 * Resolve arguments given to Execute function.
	 *
	 * @param[in]   argc - number of arguments
	 * @param[in]   argv - list of arguments
	 *
	 * @return valid index from argv or error\n
	 *
	 * Return values:
	 * - RESOLVE_ARGS_INVALID - if resolving arguments not done
	 * - RESOLVE_ARGS_FAILED - if resolving arguments failed
	 * - RESOLVE_ARGS_LIST_ALL_QUERIES - if all query targets should be listed
	 * - RESOLVE_ARGS_EXECUTE_ALL_QUERIES - if 'query all' should be executed
	 * - >0 - if resolving arguments succeeded and contains valid index from argv where\n
	 *        to start parsing queries
	 *
	 */
	int resolveArguments(int argc, char **argv);

protected:
	/**
	 * Executes a single query.
	 *
	 * This virtual function may be implemented by all query type commands.
	 *
	 * Default implementation returns an error 'NYX_ERROR_NOT_IMPLEMENTED'
	 *
	 * @param[in]   device   - Nyx device handle
	 * @param[in]   cmd      - command to be queried
	 * @param[out]  retVal   - Returned string from query
	 *
	 * @return error from Nyx calls. NYX_ERROR_NONE if no error
	 *
	 */
	virtual nyx_error_t nyxQuery(nyx_device_handle_t device,
	                             commandUsage::command_enum_t cmd,
	                             const char **retVal);

	/**
	 * Executes queries.
	 *
	 * This virtual function may be implemented by query type commands.
	 * Default implementation queries for single string.
	 *
	 * @param[in]   deviceId   - device identifier
	 * @param[in]   startIndex - index where to start parsing arguments
	 * @param[in]   argc       - number of arguments
	 * @param[in]   argv       - list of arguments
	 * @param[in]   allQueries - true if a 'query all'
	 *
	 * @return error from Nyx calls. NYX_ERROR_NONE if no error
	 *
	 */
	virtual nyx_error_t executeQueries(const char *deviceId,
	                                   int startIndex,
	                                   int argc, char **argv,
	                                   bool allQueries = false);

public:
	/**
	 * Execute the command. Full argument list is expected.
	 *
	 * @param[in]   deviceId - device identifier
	 * @param[in]   argc     - number of arguments
	 * @param[in]   argv     - list of arguments
	 *
	 * @return -1 if error.
	 *
	 */
	int Execute(const char *deviceId, int argc, char **argv);

	/**
	 * Initializes command map for the command.
	 *
	 * This virtual function must be implemented by all query type commands.
	 *
	 * @param[in]   devType     - Nyx device type
	 * @param[out]  commandMap  - Initialized commandMap
	 *
	 */
	virtual void initCommandMap(nyx_device_type_t &devType,
	                            std::map<std::string, commandUsage> &commandMap) = 0;

	virtual ~NyxCmdQueryCommand() {}
	/** @} */
};

#endif // __NYXCMDQUERYCOMMAND_H__
