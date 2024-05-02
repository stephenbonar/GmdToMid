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

    CmdLine::PosParam::Definition outputFileDef;
    outputFileDef.name = "mid";
    outputFileDef.description = "The .MID file to output";
    outputFileDef.isMandatory = true;
    outputFileParam = std::make_unique<CmdLine::PosParam>(outputFileDef);

    cmdLineParser = std::make_unique<CmdLine::Parser>(progParam.get(), args);
    cmdLineParser->Add(inputFileParam.get());
    cmdLineParser->Add(outputFileParam.get());
}

int Program::Run()
{
    if (!ParseArguments())
        return 1;

    GmdFile gmd{ inputFileParam->Value() };
    if (!gmd.Convert(outputFileParam->Value()))
        return 1;
    else
        return 0;
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
    else if (!inputFileParam->IsSpecified() || !outputFileParam->IsSpecified())
    {
        std::cout << cmdLineParser->GenerateUsage() << std::endl;
        std::cerr << "You must specify both an input and output filename." 
                  << std::endl;
        return false;
    }
    else if (cmdLineParser->BuiltInHelpOptionIsSpecified())
    {
        std::cout << cmdLineParser->GenerateHelp() << std::endl;
    }

    return true;
}