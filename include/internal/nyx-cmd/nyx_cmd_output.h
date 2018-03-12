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
 * @file nyx_cmd_output.h
 *
 * @brief Base class for nyx-cmd output.
 *
 */

#ifndef __NYXCMDOUTPUT_H__
#define __NYXCMDOUTPUT_H__

#include <string>
#include <nyx/nyx_client.h>
#include <nyx/common/nyx_device.h>

class NyxCmdOutput
{
	/**
	* @defgroup nyx_cmd_output_module nyx-cmd output modules
	* @ingroup nyx_cmd_base_classes
	* @defgroup nyx_cmd_output_base nyx-cmd output base class.
	* @ingroup nyx_cmd_output_module
	* @{
	*/
	/**
	 * Output style used for 'printOutput'
	 */
public:
	bool printErrorEnabled;
	bool printOutputEnabled;

public:
	enum output_format_t
	{
		NO_OUTPUT,
		PLAIN_OUTPUT,
		JSON_OUTPUT,
		SHELL_OUTPUT
	};
	/**
	 * Begin output operation to stream.
	 *
	 * @param[in]   output - stream where output is done
	 *
	 */
	virtual void beginOutput(std::ostringstream &output);

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
	virtual void printOutput(std::ostringstream &output,
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
	virtual void printOutput(std::ostringstream &output,
	                         const std::string &query_name,
	                         const int &query_value);

	/**
	 * Print Error to stream.
	 *
	 * Default implementation just prints out to cerr
	 *
	 * @param[in]   output      - stream where output is done
	 * @param[in]   errorString - Error string to be printed
	 *
	 */
	virtual void printError(std::ostringstream &output,
	                        const std::string &errorString);

	/**
	 * Finalize output operation and print.
	 *
	 * Default implementation will just print the stream to cout.
	 *
	 * @param[in]   output - stream where output is done
	 *
	 */
	virtual void finalizeOutput(std::ostringstream &output);

	/**
	 * Default constructor.
	 *
	 * Enables error and normal output.
	 *
	 */
	NyxCmdOutput(void): printOutputEnabled(true), printErrorEnabled(true) {};

	/**
	 * Factory function to create NyxCmdOutput.
	 *
	 * This version creates a default output.
	 *
	 */
	static NyxCmdOutput *createNyxCmdOutput();

	/**
	 * Factory function to create NyxCmdOutput.
	 *
	 * This version creates specified output.
	 *
	 * @param[in]   outputFormat - Enumeration specifying output type
	 *
	 */
	static NyxCmdOutput *createNyxCmdOutput(output_format_t outputFormat);

	/**
	 * Factory function to create NyxCmdOutput.
	 *
	 * This version creates specified output.
	 *
	 * @param[in]   outputFormat - String specifying output type
	 *
	 */
	static NyxCmdOutput *createNyxCmdOutput(const std::string &outputFormat);

protected:

	/**
	 * Replaces strings in-place.
	 *
	 * Searches for a string from 'subject' and if found replaces it in-place.
	 *
	 * @param[in,out] subject   - String where search and replace happens
	 * @param[in]     search    - String used as search key
	 * @param[in]     replace   - String used to replace 'search'
	 *
	 */
	void ReplaceStringInPlace(std::string &subject, const std::string &search,
	                          const std::string &replace);
	/** @} */
};

#endif // __NYXCMDOUTPUT_H__
