// ChunkHeader.h - Declares the ChunkHeader struct.
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

#ifndef CHUNK_HEADER_H
#define CHUNK_HEADER_H

#include "BinData.h"

constexpr int chunkHeaderSize{ 8 };

/// @brief Represents the header of a data chunk in a .gmd or .mid file.
///
/// Both standard MIDI files (.mid) and GMD files (.gmd) are comprised of
/// chunks that have an ID field, a size field, and a data section, similar
/// to RIFF chunks in a .wav file. The chunk header contains the ID and
/// size field and is read by programs to determine how to interpret each
/// chunk. The fields in the struct are layed out in the order they occur in
/// the file.
struct ChunkHeader
{
    /// @brief The 4-byte ID field indicating the type of chunk.
    BinData::StringField id{ 4 };

    /// @brief The 32-bit, big endian unsigned integer representing data size.
    BinData::UInt32Field size{ BinData::FieldEndianness::Big };
};

#endif