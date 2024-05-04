# CMakeLists.txt - CMakeLists for building the GmdToMid project.
#
# Copyright (C) 2024 Stephen Bonar
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http ://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

cmake_minimum_required(VERSION 3.5.0)
project(GmdToMid VERSION 0.81.0 LANGUAGES C CXX)

# Although the project command can natively pass the name and version into
# the program through the configure_file command, there is no native RELEASE
# or COPYRIGHT info, so we define that here to pass to configure_file.
set(PROJECT_RELEASE "Alpha")
set(PROJECT_COPYRIGHT "Copyright (C) 2024 Stephen Bonar")

# Specify the C++ standard.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(GmdToMid)

add_subdirectory(LibCppCmdLine)

add_subdirectory(LibCppBinData)

