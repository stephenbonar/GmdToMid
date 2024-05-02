// MidiFile.h - Declares the MidiFile class.
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

#ifndef MIDI_FILE_H
#define MIDI_FILE_H

#include <string>
#include "BinData.h"
#include "ChunkHeader.h"

class MidiFile
{
public:
    MidiFile(std::string fileName) : stream{ fileName } { }

    void WriteChunkHeader(ChunkHeader header);

    void WriteChunkData(BinData::RawField* data);
private:
    BinData::StdFileStream stream;
};

#endif