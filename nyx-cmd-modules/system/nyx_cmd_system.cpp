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

#include "nyx_cmd_system.h"
#include "nyx_cmd_system_reboot.h"
#include "nyx_cmd_system_shutdown.h"
#include "nyx_cmd_system_erase.h"
#include "nyx_cmd_system_set_alarm.h"
#include "nyx_cmd_system_query_time.h"
#include "nyx_cmd_system_query_alarm.h"
#include "nyx_cmd_system_suspend.h"

#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

string NyxCmdSystem::Name()
{
	return string("System");
}

string NyxCmdSystem::Description()
{
	return string("Nyx 'System' device type.");
}

string NyxCmdSystem::Usage()
{
	const char *const usage =
	    "COMMAND\n"
	    "  system_reboot [ARGS]               Reboots the device\n"
	    "                                     If [ARGS] is not set, defaults to\n"
	    "                                     'NYX_SYSTEM_NORMAL_SHUTDOWN'\n"
	    "  system_shutdown [ARGS]             Shuts down the device\n"
	    "                                     If [ARGS] is not set, defaults to\n"
	    "                                     'NYX_SYSTEM_NORMAL_SHUTDOWN'\n"
	    "  erase_parition TYPE                Mark one or more partitions to be\n"
	    "                                     erased on the next reboot\n"
	    "  set_alarm [ALARM_OPTION] SECONDS   Set the alarm to SECONDS from now.\n"
	    "                                     If 0 or negative, any existing RTC alarm present will be cleared.\n"
	    "  query_rtc_time                     Gets the system RTC time.\n"
	    "  query_next_alarm                   Gets the next system alarm. If no alarm is set, it shows the current time\n"
	    "  system_suspend                     Suspends the machine. Program will exit only once the machine has been re-awoken.\n"
	    "\n"
	    "ARGS\n"
	    "  NYX_SYSTEM_NORMAL_SHUTDOWN    Normal shutdown\n"
	    "  NYX_SYSTEM_EMERG_SHUTDOWN     Emergency shutdown\n"
	    "  NYX_SYSTEM_TEST_SHUTDOWN      Test shutdown\n"
	    "\n"
	    "ALARM_OPTION\n"
	    "  -b, --block                   Block till alarm is fired\n"
	    "\n"
	    "TYPE\n"
	    "  media                         Erase user created files, including photos and videos\n"
	    "  var                           Erase installed apps and all app settings and data\n"
	    "  all                           Full erase (factory reset)\n"
	    "  developer                     Erase developer data\n"
	    ;

	return string(usage);
}

// Returns the command object instance for defined name.
// Implemented command names and their class initiations are added here.
NyxCmdCommand *NyxCmdSystem::getCommand(string commandName)
{
	if (commandName == "system_reboot")
	{
		return new NyxCmdSystemReboot();
	}
	else if (commandName == "system_shutdown")
	{
		return new NyxCmdSystemShutdown();
	}
	else if (commandName == "erase_partition")
	{
		return new NyxCmdSystemErase();
	}
	else if (commandName == "set_alarm")
	{
		return new NyxCmdSetAlarm();
	}
	else if (commandName == "query_next_alarm")
	{
		return new NyxCmdQueryAlarm();
	}
	else if (commandName == "query_rtc_time")
	{
		return new NyxCmdQueryTime();
	}
	else if (commandName == "system_suspend")
	{
		return new NyxCmdSystemSuspend();
	}

	return NULL;
}

extern "C"
{
	NyxCmdDeviceType *getNyxCmdDeviceTypeInstance()
	{
		return new NyxCmdSystem();
	}
}


