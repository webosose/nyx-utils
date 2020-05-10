# Copyright (c) 2012-2020 LG Electronics, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# SPDX-License-Identifier: Apache-2.0

include_directories(${CMAKE_SOURCE_DIR}/include/internal/nyx-cmd)

# macro to install nyx-cmd device type libraries into correct place
#
# All module names must start with ${NYX_CMD_MODULE_PREFIX} and end with the
# device type identifier.
#
# As the device type identifier is used for opening the module, case MUST be
# followed
macro(nyx_cmd_install_library module)
	if(${module} MATCHES ^${NYX_CMD_MODULE_PREFIX})
		install(TARGETS ${module} DESTINATION ${NYX_CMD_MODULE_DIR})
	else()
		message(FATAL_ERROR "Module is not named according to naming convention")
	endif()
endmacro()

add_subdirectory(system)
add_subdirectory(device_info)
add_subdirectory(battery)
add_subdirectory(os_info)
add_subdirectory(led)
add_subdirectory(charger)
add_subdirectory(touchpanel)
add_subdirectory(keys)
add_subdirectory(gps)
