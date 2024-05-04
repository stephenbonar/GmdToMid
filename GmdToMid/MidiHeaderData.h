// MidiHeaderData.h - Declares the MidiHeaderData struct.
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

#ifndef MIDI_HEADER_DATA_H
#define MIDI_HEADER_DATA_H

#include "BinData.h"

/// @brief The size of the data in a MIDI header chunk.
///
/// The MIDI header chunk data should always be 6-bytes wide as the data is
/// comprised of 3, 16-bit (2 byte) fields.
constexpr int midiHeaderDataSize{ 6 };

/// @brief Represents the data contained within a MIDI header.
struct MidiHeaderData
{
    /// @brief Determines the format of the MIDI file, 0, 1, or 2.
    ///
    /// Type 0: All the midi events are contained within a single track
    /// Type 1: Each instrument / part is on its own track
    /// Type 2: Each track is essentially a separate Type 0 track.
    BinData::UInt16Field format{ BinData::FieldEndianness::Big };

    /// @brief Determines the number of tracks contained in the MIDI file.
    BinData::UInt16Field numTracks{ BinData::FieldEndianness::Big };

    /// @brief The division of the MIDI file.
    ///
    /// The division represents the Pulses Per Quarter Note (PPQN) the time
    /// stamps are based on.
    BinData::UInt16Field division{ BinData::FieldEndianness::Big };
};

#endif