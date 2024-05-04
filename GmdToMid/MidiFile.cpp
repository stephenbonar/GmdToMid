// MidiFile.h - Defines the MidiFile class.
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

#include "MidiFile.h"

MidiFile::MidiFile(std::string fileName, BinData::UInt16Field division) :
    stream{ fileName }
{
    header.id.SetData(midiHeaderID);
    header.size.SetValue(midiHeaderDataSize);

    // We're creating a type 0 MIDI file. GMD files are type 2, but we export
    // each MIDI track from the GMD as a single type 0 track.
    headerData.format.SetValue(midiType0ID);

    // Type 0 MIDI files only have 1 track.
    headerData.numTracks.SetValue(midiType0TrackNum);

    // The only header field we bring over from the GMD file is the division.
    headerData.division.SetValue(division.Value());
}

void MidiFile::WriteChunkHeader(ChunkHeader header)
{
    if (!stream.IsOpen())
        stream.Open(BinData::FileMode::Write);

    stream.Write(&header.id);
    stream.Write(&header.size);
}

void MidiFile::WriteMidiHeaderData(MidiHeaderData data)
{
    stream.Write(&data.format);
    stream.Write(&data.numTracks);
    stream.Write(&data.division);
}

void MidiFile::WriteData(BinData::RawField* data)
{
    stream.Write(data);
}

void MidiFile::WriteTrack(ChunkHeader trackHeader, 
                          BinData::RawField* trackData)
{
    WriteChunkHeader(header);
    WriteMidiHeaderData(headerData);
    WriteChunkHeader(trackHeader);
    WriteData(trackData);
}