nyx-utils
========

Summary
-------
Utility to invoke nyx library device type commands.

Description
-----------
Nyx-utils provides a command line tool 'nyx-cmd' to call the nyx library
device types and commands within them.
To see command line options call 'nyx-cmd' without parameters.

How to extend
=============

## Adding stream output modules

- inherit new module from NyxCmdOutput and override virtual functions
  you need. Base class has two variables to control output ('printErrorEnabled'
  and 'printOutputEnabled'). Please support those in all new modules.
- add an enumeration for your new module to nyx/_cmd/_output.h
- add your new module to factory function in nyx/_cmd/_output.cpp
- add your new files to nyx-cmd/CMakeLists.txt

## Adding new command modules

- add your new files to nyx-cmd-modules/<module>/CMakeLists.txt

### Query only type module

- inherit from NyxCmdQueryCommand
- if your module only queries for strings you need to implement pure virtual
  functions only
- if your module queries for other type of data too, you need to implement
  other virtual functions as well
- add Nyx specific enumeration type to union in nyx/_cmd/_command.h
- add a new constructor to struct in nyx/_cmd/_command.h

### Other types of modules

- inherit from NyxCmdCommand
- implement all virtual functions
- handle argument parsing in 'Execute' function
- consider using 'commandUsage' struct from nyx/_cmd/_command.h

## Adding new Device types

- inherit from NyxCmdDeviceType
- implement all virtual functions
- add new command modules as specified in 2)
- add your new files to nyx-cmd-modules/<module>/CMakeLists.txt
- add your new module to nyx-cmd-modules/CMakeLists.txt

How to build on linux
=====================

## Dependencies

Below are the tools and libraries (and their minimum versions) required
to build _nyx-utils_:

* cmake (version required by cmake-modules-webos)
* cmake-modules-webos 1.0.0
* gcc 4.6.3
* glib-2.0 2.32.1
* nyx-lib 7.0.0
* pkg-config 0.26

## Building

Once you have downloaded the source, enter the following to build it (after
changing into the directory under which it was downloaded):

    $ mkdir BUILD
    $ cd BUILD
    $ cmake ..
    $ make
    $ sudo make install

The directory under which the files are installed defaults to `/usr/local/webos`.
You can install them elsewhere by supplying a value for `WEBOS_INSTALL_ROOT`
when invoking `cmake`. For example:

    $ cmake -D WEBOS_INSTALL_ROOT:PATH=$HOME/projects/webosose ..
    $ make
    $ make install

will install the files in subdirectories of `$HOME/projects/webosose`.

Specifying `WEBOS_INSTALL_ROOT` also causes `pkg-config` to look in that tree
first before searching the standard locations. You can specify additional
directories to be searched prior to this one by setting the `PKG_CONFIG_PATH`
environment variable.

If not specified, `WEBOS_INSTALL_ROOT` defaults to `/usr/local/webos`.

To configure for a debug build, enter:

    $ cmake -D CMAKE_BUILD_TYPE:STRING=Debug ..

To see a list of the make targets that `cmake` has generated, enter:

    $ make help

## Uninstalling

From the directory where you originally ran `make install`, enter:

    $ [sudo] make uninstall

You will need to use `sudo` if you did not specify `WEBOS_INSTALL_ROOT`.

# Copyright and License Information

Unless otherwise specified, all content, including all source code files and
documentation files in this repository are:

Copyright (c) 2012-2018 LG Electronics, Inc.

Unless otherwise specified or set forth in the NOTICE file, all content,
including all source code files and documentation files in this repository are:
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this content except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

SPDX-License-Identifier: Apache-2.0
