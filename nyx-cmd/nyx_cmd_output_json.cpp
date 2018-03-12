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

#include "nyx_cmd_output_json.h"

using namespace std;

/*
* beginOutput begins JSON style output
*
*/
void NyxCmdOutputJson::beginOutput(ostringstream &output)
{
	if (printOutputEnabled)
	{
		output << "{" << endl;
	}
}

/*
* finalizeOutput finalizes JSON output and prints out to cout
*
*/
void NyxCmdOutputJson::finalizeOutput(ostringstream &output)
{
	if (printOutputEnabled)
	{
		//remove final ','
		string tempCpy = output.str();
		tempCpy.erase(tempCpy.rfind(","));
		cout << tempCpy;

		cout << endl << "}" << endl;
	}
}

/*
* printOutput print string to output stream
*
*/
void NyxCmdOutputJson::printOutput(ostringstream &output,
                                   const std::string &query_name,
                                   std::string query_value)
{
	if (printOutputEnabled)
	{
		ReplaceStringInPlace(query_value, "\n", "\\n");
		ReplaceStringInPlace(query_value, "\"", "\\\"");
		output << "    \"" << query_name << "\": \"" << query_value
		       << "\"," << endl;
	}
}

/*
* printOutput print an integer to output stream
*
*/
void NyxCmdOutputJson::printOutput(ostringstream &output,
                                   const std::string &query_name,
                                   const int &query_value)
{
	if (printOutputEnabled)
	{
		output << "    \"" << query_name << "\": " << query_value << endl;
	}
}
