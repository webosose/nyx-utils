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

#include <iostream>
#include <sstream>
#include <getopt.h>
#include "nyx_cmd_query_command.h"
#include "nyx_cmd_output.h"

using namespace std;

/*
* Parses the command line arguments and resolves them to proper variables.
*
* RESOLVE_ARGS_INVALID              Resolving arguments not done
* RESOLVE_ARGS_FAILED               Resolving arguments failed
* RESOLVE_ARGS_LIST_ALL_QUERIES     Resolving arguments succeeded with list
*                                   all queries action
* RESOLVE_ARGS_EXECUTE_ALL_QUERIES  Resolving arguments succeeded with
*                                   execute all queries action
* >0                                Resolving arguments succeeded and
*                                   contains valid index from argv where
*                                   to start parsing queries
*/
int NyxCmdQueryCommand::resolveArguments(int argc, char **argv)
{
	int retVal = RESOLVE_ARGS_INVALID;
	int c = 0;

	// reset errors and prevent from outputting
	opterr = 0;

	static struct option long_options[] =
	{
		{"format", required_argument, 0, 'f' },
		{"list", no_argument, 0, 'l' },
		{0, 0, 0, 0 }
	};

	while (1)
	{
		int option_index = 0;

		c = getopt_long(argc, argv, "lf:", long_options, &option_index);

		if (c == -1)
		{
			break;
		}

		switch (c)
		{
			// format is a long option only and in index 0
			case 'f':
				output = NyxCmdOutput::createNyxCmdOutput(optarg);

				if (NULL == output)
				{
					retVal = RESOLVE_ARGS_FAILED;
				}

				break;

			case 'l':
				retVal = RESOLVE_ARGS_LIST_ALL_QUERIES;
				break;

			// all that are not recognized make the function fail
			default:
				retVal = RESOLVE_ARGS_FAILED;
				break;
		}
	}

	if (RESOLVE_ARGS_INVALID == retVal)
	{
		// check if there is still arguments left
		// there wasn't so it's a query for all
		if (0 == (argc - optind))
		{
			retVal = RESOLVE_ARGS_EXECUTE_ALL_QUERIES;
		}
		else
		{
			retVal = optind;
		}
	}

	return retVal;
}

/*
* Execute command.
* Resolves command parameters from the command line arguments.
*/
int NyxCmdQueryCommand::Execute(const char *deviceId, int argc, char **argv)
{
	nyx_error_t error = NYX_ERROR_GENERIC;

	// initialize output to NULL
	output = NULL;

	// initialize command specific enums and usage strings if it is empty
	if (commandMap.empty())
	{
		initCommandMap(nyxDevType, commandMap);
	}

	int argIndex = resolveArguments(argc, argv);

	// initialize a default output if not initialized from arguments
	if (NULL == output)
	{
		output = NyxCmdOutput::createNyxCmdOutput();
	}

	switch (argIndex)
	{
		case RESOLVE_ARGS_INVALID:
		case RESOLVE_ARGS_FAILED:
			cerr << "Error: Error resolving arguments" << endl;
			break;

		case RESOLVE_ARGS_LIST_ALL_QUERIES:
			listAllQueries();
			error = NYX_ERROR_NONE;
			break;

		case RESOLVE_ARGS_EXECUTE_ALL_QUERIES:
			error = executeQueries(deviceId, argIndex, argc, argv, true);
			break;

		default:
			error = executeQueries(deviceId, argIndex, argc, argv, false);
			break;
	}

	// clean up
	delete output;

	commandMap.clear();

	return (NYX_ERROR_NONE == error) ? 0 : -1;
}

/*
* List all query targets.
*/
void NyxCmdQueryCommand::listAllQueries()
{
	for (std::map<string, commandUsage>::const_iterator itr = commandMap.begin();
	        itr != commandMap.end(); ++itr)
	{
		cout << itr->first << endl;
	}
}

/*
* Executes a Nyx query. Default implementation will return 'NYX_ERROR_NOT_IMPLEMENTED'
*/
nyx_error_t NyxCmdQueryCommand::nyxQuery(nyx_device_handle_t device,
        commandUsage::command_enum_t cmd,
        const char **retVal)
{
	*retVal = "";
	return NYX_ERROR_NOT_IMPLEMENTED;
}

/*
* Executes queries. Default implementation queries for single strings
*/
nyx_error_t NyxCmdQueryCommand::executeQueries(const char *deviceId,
        int startIndex, int argc,
        char **argv,
        bool allQueries)
{
	nyx_device_handle_t device = NULL;
	nyx_os_info_query_t infoType;
	nyx_error_t error = NYX_ERROR_GENERIC;
	nyx_error_t finalError = NYX_ERROR_GENERIC;

	error = nyx_init();

	if (NYX_ERROR_NONE == error && NULL != output)
	{
		error = nyx_device_open(nyxDevType, deviceId, &device);

		if (NULL != device)
		{
			ostringstream outputStream;
			const char *retVal;
			bool keepPrinting = true;
			int failCount = 0;
			std::map<string, commandUsage>::const_iterator iter = commandMap.begin();

			if (allQueries)
			{
				output->printErrorEnabled = false;
			}

			output->beginOutput(outputStream);

			while (keepPrinting)
			{
				// 'allQueries' controls how the iterator is fetched
				// when it's false then you find the iterator based on strings
				if (false == allQueries)
				{
					iter = commandMap.find(string(argv[startIndex++]));

					// when there is no more arguments, stop printing
					if (0 == (argc - startIndex))
					{
						keepPrinting = false;
					}
				}

				if (commandMap.end() != iter)
				{
					error = nyxQuery(device, iter->second.commandEnum, &retVal);

					switch (error)
					{
						case NYX_ERROR_NONE:
							output->printOutput(outputStream, iter->first, retVal);
							finalError = NYX_ERROR_NONE;
							break;

						case NYX_ERROR_NOT_IMPLEMENTED:
							output->printError(outputStream, "Error: Query not implemented");
							break;

						case NYX_ERROR_DEVICE_UNAVAILABLE:
							output->printError(outputStream, "Error: Device or value not available");
							break;

						default:
							ostringstream tempError;
							tempError << "Error: Error " << error << " in executing query";
							output->printError(outputStream, tempError.str());
							break;
					}

					// when 'allQueries' is true, iterator is looped
					if (allQueries)
					{
						// stop outputting if final
						if (commandMap.end() == ++iter)
						{
							keepPrinting = false;
						}
					}
				}
				else
				{
					if (false == allQueries)
						// increment failcount for all other cases than 'query all'
					{
						failCount++;
					}
				}
			}

			// don't finalize output if there wasn't even one successful query
			if (NYX_ERROR_NONE == finalError)
			{
				output->finalizeOutput(outputStream);
			}

			// if there were queries that were not found print the
			// number of failed queries
			// NOTE: this is not printed when doing 'query all'
			if (failCount)
			{
				cerr << "Error: " << failCount << " query/queries not found" << endl;
			}

			nyx_device_close(device);
		}
	}
	else
	{
		cerr << "Error: Error initializing Nyx" << endl;
	}

	nyx_deinit();

	return finalError;
}
