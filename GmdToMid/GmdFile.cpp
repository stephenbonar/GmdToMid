// GmdFile.cpp - Defines the GmdFile class.
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

#include "GmdFile.h"

bool GmdFile::Convert()
{
    stream.Open();
    bytesRemaining = stream.Size();

    if (!ReadFileHeader())
        return false;

    int trackNum{ 0 };
    std::cout << "Converting file..." << std::endl << std::endl;
    while (bytesRemaining > 0)
    {
        ChunkHeader nextHeader = ReadChunkHeader();
        if (nextHeader.id.ToString() == midiHeaderID)
        {
            PrintChunkHeader("MIDI Header", nextHeader);
            ReadMidiHeaderData();
            PrintMidiHeaderData(midiHeaderData);
        }
        else if (nextHeader.id.ToString() == midiTrackID)
        {
            PrintChunkHeader("MIDI Track", nextHeader);
            ExportTrack(trackNum, nextHeader);
            trackNum++;
        }
        else
        {
            PrintChunkHeader("Skipped Chunk", nextHeader);

            // Believe it or not, there are some chunks that have a size of
            // zero. In that case, we simply ignore the chunk.
            if (nextHeader.size.Value() > 0)
            {
                BinData::RawField skippedData
                { 
                    static_cast<size_t>(nextHeader.size.Value()) 
                };
                ReadData(&skippedData);
            }
        }

        std::cout << "Bytes remaining: " << bytesRemaining << std::endl 
                  << std::endl;
    }   

    return true;
}

ChunkHeader GmdFile::ReadChunkHeader()
{
    ChunkHeader header;
    stream.Read(&header.id);
    stream.Read(&header.size);
    bytesRemaining -= chunkHeaderSize;
    return header;
}

bool GmdFile::ReadFileHeader()
{
    header = ReadChunkHeader();
    if (header.id.ToString() != gmdHeaderID)
    {
        std::cerr << "Input file does not appear to be in the GMD format."
                  << std::endl;
        return false;
    }
    else if (header.size.Value() != (bytesRemaining))
    {
        std::cerr << "GMD file appears corrupt due to file size mismatch."
                  << std::endl << "Expected Size : " << header.size.Value()
                  << std::endl << "Actual Size   : " << bytesRemaining
                  << std::endl;
        return false;
    }
    else
    {
        PrintChunkHeader("File Header", header);
        return true;
    }
}

void GmdFile::ReadData(BinData::RawField* data)
{
    stream.Read(data);
    bytesRemaining -= data->Size();
}

void GmdFile::ReadMidiHeaderData()
{
    stream.Read(&midiHeaderData.format);
    stream.Read(&midiHeaderData.numTracks);
    stream.Read(&midiHeaderData.division);
    bytesRemaining -= midiHeaderDataSize;
}

void GmdFile::ExportTrack(int trackNum, const ChunkHeader& trackHeader)
{
    auto trackSize = static_cast<size_t>(trackHeader.size.Value());
    BinData::RawField trackData{ trackSize };
    ReadData(&trackData);

    // The exported file takes the same name as the .gmd, but we add a track
    // number prefix that increases with each successive track so we can tell
    // each track / .mid file apart.
    std::filesystem::path gmdPath{ fileName };
    std::stringstream exportFileName;
    exportFileName << gmdPath.stem().string() << "-" << trackNum << ".mid";

    unsigned int division = midiHeaderData.division.Value();
    MidiFile exportFile{ exportFileName.str(), division };
    exportFile.WriteTrack(trackHeader, &trackData);
}

void PrintChunkHeader(std::string title, const ChunkHeader& header)
{
    std::cout << title << std::endl
              << "--------------------" << std::endl
              << "ID       : " << header.id.ToString() << std::endl
              << "Size     : " << header.size.Value() << std::endl
              << std::endl;
}

void PrintMidiHeaderData(const MidiHeaderData& data)
{
    std::cout << "Format   : " << data.format.ToString() << std::endl
              << "Tracks   : " << data.numTracks.Value() << std::endl
              << "Division : " << data.division.Value() << std::endl
              << std::endl;
}