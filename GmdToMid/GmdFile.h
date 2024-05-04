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
#include <sstream>
#include <filesystem>
#include "BinData.h"
#include "ChunkHeader.h"
#include "MidiFile.h"
#include "MidiHeaderData.h"

/// @brief The chunk ID used to indicate the beginning of a .gmd file.
inline const char* gmdHeaderID{ "GMD " };

/// @brief Represents a .GMD file.
///
/// The GmdFile class allows the program to convert a .gmd file to a standard
/// MIDI file (.mid). GMD files are essentially type 2 MIDI files with some
/// additional chunks and MIDI SysEx events specific to the GMD format. The GMD
/// format was used by the iMuse system to generate dynamic MIDI music in
/// several DOS-based LucasArts games.
///
/// Standard MIDI files come in several types / formats. 
/// @see MidiHeaderData
///
/// GMD files are essentially a Type 2 MIDI file, and the MIDI header chunk
/// indicates Type 2. Many .GMD files just contain a single Type 0 track, but
/// some contain multiple tracks, with the first track being the "main" song
/// and subsequent tracks being transitions. This class currently extracts each
/// track as a separate Type 0 MIDI file with the same file name as the GMD
/// file, but with a track number suffix and a .mid extension.
///
/// @todo The first track usually sounds fine, but the transitionary tracks
/// sound like they need initializaiton from the first track and cannot stand
/// on their own. Add logic that identifies "setup" events from the first track
/// and copies those events to the other tracks (at least offer a command line
/// option to do so).
class GmdFile
{
public:
    /// @brief Constructor; creates a new instance of a GmdFile from file name.
    /// @param fileName The file name of the .gmd file to convert.
    /// @todo Define and enforce class invariants.
    GmdFile(std::string fileName) : 
        fileName{ fileName }, stream{ fileName }, bytesRemaining{ 0 } 
    { }

    /// @brief Converts the file to multiple .mid files, one for each track.
    /// @return true if the conversion was successful, otherwise false.
    bool Convert();
private:
    std::string fileName;
    BinData::StdFileStream stream;
    ChunkHeader header;
    MidiHeaderData midiHeaderData;
    size_t bytesRemaining;

    /// @brief Reads the next ChunkHeader from the file.
    /// @return The next ChunkHeader.
    /// @pre The file is open and the stream pointing to a valid ChunkHeader.
    ChunkHeader ReadChunkHeader();

    /// @brief Reads the GMD header and loads it into the file.
    /// @return true if the header was successfuly read, otherwise false.
    /// @pre The file is open and at the beginning of the stream.
    bool ReadFileHeader();

    /// @brief Reads data from the file into the specified BinData::RawField. 
    /// @param data The field to read the data into.
    /// @pre The file is open.
    void ReadData(BinData::RawField* data);

    /// @brief Reads data from the MIDI header and loads it into the file.
    /// @pre The file is open and the stream is pointing to MidiHeaderData.
    void ReadMidiHeaderData();

    /// @brief Exports the current MIDI track as a MIDI file.
    /// @param trackNum Specifies the track number suffix for the MIDI file.
    /// @param trackHeader The header of the current MIDI track.
    /// @pre The file is open and the stream is pointing to MIDI track data.
    void ExportTrack(int trackNum, const ChunkHeader& trackHeader);
};

/// @brief Prints the specified ChunkHeader to standard output.
/// @param title The title to use when printing the chunk.
/// @param header The ChunkHeader to print.
void PrintChunkHeader(std::string title, const ChunkHeader& header);

/// @brief Prints the specified MidiHeaderData to standard output.
/// @param data The MidiHeaderData to print.
void PrintMidiHeaderData(const MidiHeaderData& data);

#endif