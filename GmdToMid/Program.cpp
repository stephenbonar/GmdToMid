// Program.cpp - Defines the main Program class for the console version.
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

#include "Program.h"

Program::Program(std::vector<std::string> args)
{
    CmdLine::ProgParam::Definition progDef;
    progDef.name = "gmdtomid";
    progDef.description = "GMIDI to MIDI Conversion Program";
    progParam = std::make_unique<CmdLine::ProgParam>(progDef);
    
    CmdLine::PosParam::Definition inputFileDef;
    inputFileDef.name = "gmd";
    inputFileDef.description = "The .GMD file to convert";
    inputFileDef.isMandatory = true;
    inputFileParam = std::make_unique<CmdLine::PosParam>(inputFileDef);

    cmdLineParser = std::make_unique<CmdLine::Parser>(progParam.get(), args);
    cmdLineParser->Add(inputFileParam.get());
}

int Program::Run()
{
    std::cout << PROGRAM_NAME << " v" << VERSION_MAJOR << "." << VERSION_MINOR
              << " " << PROGRAM_RELEASE << " " << PROGRAM_BUILD_TYPE
              << std::endl << PROGRAM_COPYRIGHT << std::endl << std::endl;

    if (!ParseArguments())
        return exitCodeInvalidArgs;

    GmdFile gmd{ inputFileParam->Value() };
    if (!gmd.Convert())
        return exitCodeConversionError;
    else
        return exitCodeSuccess;
}

bool Program::ParseArguments()
{
    if (cmdLineParser->Parse() == CmdLine::Parser::Status::Failure)
    {
        std::cout << cmdLineParser->GenerateUsage() << std::endl;
        std::cerr << "Invalid command line arguments, please see usage info."
                  << std::endl;
        return false;
    }
    else if (!inputFileParam->IsSpecified())
    {
        std::cout << cmdLineParser->GenerateUsage() << std::endl;
        std::cerr << "You must specify a file to convert to .mid." 
                  << std::endl;
        return false;
    }
    else if (cmdLineParser->BuiltInHelpOptionIsSpecified())
    {
        std::cout << cmdLineParser->GenerateHelp() << std::endl;
    }

    return true;
}