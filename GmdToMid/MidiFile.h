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
#include "MidiHeaderData.h"

/// @brief The chunk ID used to indicate the beginning of a MIDI header.
inline const char* midiHeaderID{ "MThd" };

/// @brief The chunk ID used to indicate the beginning of a MIDI track.
inline const char* midiTrackID{ "MTrk" };

/// @brief The integer value representing MIDI type 0.
inline constexpr int midiType0ID{ 0 };

/// @brief The number of tracks a type 0 MIDI file should contain.
inline constexpr int midiType0TrackNum{ 1 };

/// @brief Represents a MIDI (.mid) file.
///
/// This class supports writing an individual type 0 MIDI track encapsulated
/// within an entire type 0 MIDI file.
class MidiFile
{
public:
    /// @brief Constructor; creates a new MidiFile instance of type 0.
    /// @param fileName The file name of the .mid file. 
    /// @param division The division value the type 0 MIDI track should use.
    MidiFile(std::string fileName, BinData::UInt16Field division); 

    /// @brief Writes the specified track header and data as a new MIDI file.
    /// @param trackHeader The header of the track to write.
    /// @param trackData The track data to write.
    void WriteTrack(ChunkHeader trackHeader, 
                    BinData::RawField* trackData);
private:
    BinData::StdFileStream stream;
    ChunkHeader header;
    MidiHeaderData headerData;

    /// @brief Writes the specified chunk header to the file.
    /// @param header The header to write at the current position.
    /// @pre The file is open.
    void WriteChunkHeader(ChunkHeader header);

    /// @brief Writes the specified MidiHeaderData to the file.
    /// @param data The data to write to the file.
    /// @pre The file is open.
    void WriteMidiHeaderData(MidiHeaderData data);

    /// @brief Writes the specified data to the file.
    /// @param data The data to write to the file.
    void WriteData(BinData::RawField* data);
};

#endif