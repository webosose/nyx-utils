// Copyright (c) 2012-2018 LG Electronics, Inc.
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

#include <string>
#include <sstream>

#include <nyx/nyx_client.h>

#include "nyx_cmd_command.h"

using namespace std;

/*
* Default implementation for Version()
*
*/
string NyxCmdCommand::Version()
{
	int32_t major = nyx_get_api_version_major();
	int32_t minor = nyx_get_api_version_minor();

	ostringstream version;
	version << "NyxLib " << major << "." << minor;
	return version.str();
}

