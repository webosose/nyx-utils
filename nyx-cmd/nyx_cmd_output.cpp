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

#include <sstream>
#include <iostream>

#include "nyx_cmd_output.h"
#include "nyx_cmd_output_json.h"
#include "nyx_cmd_output_shell.h"

using namespace std;

/*
* beginOutput Default won't do anything
*
*/
void NyxCmdOutput::beginOutput(ostringstream &output)
{
}

/*
* printError Default implementation just outputs to cerr.
*
*/
void NyxCmdOutput::printError(std::ostringstream &output,
                              const std::string &errorString)
{
	if (printErrorEnabled)
	{
		cerr << errorString << endl;
	}
}

/*
* printOutput print string to output stream
*
*/
void NyxCmdOutput::printOutput(ostringstream &output,
                               const std::string &query_name,
                               std::string query_value)
{
	if (printOutputEnabled)
	{
		output << query_value << endl;
	}
}

/*
* printOutput print an integer to output stream
*
*/
void NyxCmdOutput::printOutput(ostringstream &output,
                               const std::string &query_name,
                               const int &query_value)
{
	if (printOutputEnabled)
	{
		output << query_value << endl;
	}
}

/*
* finalizeOutput Default implementation just outputs the stream
*
*/
void NyxCmdOutput::finalizeOutput(ostringstream &output)
{
	if (printOutputEnabled)
	{
		cout << output.str();
	}
}

/*
* Searches for 'search' and replaces with 'replace' in place
*
*/
void NyxCmdOutput::ReplaceStringInPlace(string &subject,
                                        const string &search,
                                        const string &replace)
{
	size_t pos = 0;

	while ((pos = subject.find(search, pos)) != string::npos)
	{
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
}

NyxCmdOutput *NyxCmdOutput::createNyxCmdOutput(NyxCmdOutput::output_format_t
        outputFormat)
{
	switch (outputFormat)
	{
		case NyxCmdOutput::PLAIN_OUTPUT:
			return new NyxCmdOutput;
			break;

		case NyxCmdOutput::JSON_OUTPUT:
			return new NyxCmdOutputJson;
			break;

		case NyxCmdOutput::SHELL_OUTPUT:
			return new NyxCmdOutputShell;
			break;

		default:
			return NULL;
			break;
	}
}

NyxCmdOutput *NyxCmdOutput::createNyxCmdOutput(const string &outputFormat)
{
	if ("json" == outputFormat)
	{
		return NyxCmdOutput::createNyxCmdOutput(NyxCmdOutput::JSON_OUTPUT);
	}
	else if ("shell" == outputFormat)
	{
		return NyxCmdOutput::createNyxCmdOutput(NyxCmdOutput::SHELL_OUTPUT);
	}
	else if ("plain" == outputFormat)
	{
		return NyxCmdOutput::createNyxCmdOutput(NyxCmdOutput::PLAIN_OUTPUT);
	}
	else
	{
		return NULL;
	}
}

NyxCmdOutput *NyxCmdOutput::createNyxCmdOutput()
{
	return NyxCmdOutput::createNyxCmdOutput(NyxCmdOutput::PLAIN_OUTPUT);
}
