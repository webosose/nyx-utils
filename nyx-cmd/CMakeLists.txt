# Copyright (c) 2012-2018 LG Electronics, Inc.
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

set(CMAKE_INSTALL_RPATH ${NYX_CMD_MODULE_DIR})

add_executable(nyx-cmd ${SRC} main.cpp
                              nyx_cmd_devicetype.cpp
                              nyx_cmd_command.cpp
                              nyx_cmd_output.cpp
                              nyx_cmd_output_json.cpp
                              nyx_cmd_output_shell.cpp
                              nyx_cmd_query_command.cpp)

target_link_libraries(nyx-cmd dl ${NYXLIB_LDFLAGS})

webos_config_build_doxygen(doc nyx_cmd.doxy)
webos_build_program(NAME nyx-cmd)
