// GmdFile.h - Declares the GmdFile class.
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

#ifndef GMD_FILE_H
#define GMD_FILE_H

#include <string>
#include "BinData.h"
#include "ChunkHeader.h"
#include "MidiFile.h"

class GmdFile
{
public:
    GmdFile(std::string fileName);

    bool Convert(std::string fileName);
private:
    BinData::StdFileStream stream;
    ChunkHeader header;
    size_t bytesRemaining;

    ChunkHeader ReadChunkHeader();

    bool ReadFileHeader();

    void ReadChunkData(BinData::RawField* data);

    void CopyMidiChunk(MidiFile& file, ChunkHeader header);
};

void PrintChunkHeader(std::string title, const ChunkHeader& header);

#endif