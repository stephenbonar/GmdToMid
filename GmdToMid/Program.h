// Program.h - Declares the main program class for the console version.
//
// Copyright (C) 2024 Stephen Bonar
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http ://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef PROGRAM_H
#define PROGRAM_H

#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include "CmdLine.h"
#include "BinData.h"
#include "GmdFile.h"
#include "Version.h"

/// @brief Indicates the program ran successfully.
inline constexpr int exitCodeSuccess{ 0 };

/// @brief Indicates invalid command line arguments were specified.
inline constexpr int exitCodeInvalidArgs{ 1 };

/// @brief Indicates conversion failed.
inline constexpr int exitCodeConversionError{ 2 };

/// @brief This class encasulates the main program logic.
class Program
{
public:
    /// @brief Constructor; creates a new instance of Program.
    /// @param args The program command line arguments.
    Program(std::vector<std::string> args);

    /// @brief Runs the program.
    /// @return The exit status of the program.
    int Run();
private:
    std::unique_ptr<CmdLine::ProgParam> progParam;
    std::unique_ptr<CmdLine::PosParam> inputFileParam;
    std::unique_ptr<CmdLine::Parser> cmdLineParser;

    /// @brief Parses the command line arguments.
    /// @return true if arguments were successfully parsed, otherwise false.
    bool ParseArguments();
};

#endif