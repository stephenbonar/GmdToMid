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

GmdFile::GmdFile(std::string fileName) 
    : stream{ fileName }, bytesRemaining{ 0 } 
{ }

bool GmdFile::Convert(std::string fileName)
{
    MidiFile convertedFile{ fileName };

    stream.Open();
    bytesRemaining = stream.Size();

    if (!ReadFileHeader())
        return false;

    std::cout << "Converting file..." << std::endl << std::endl;
    while (bytesRemaining > 0)
    {
        ChunkHeader nextHeader = ReadChunkHeader();
        if (nextHeader.id.ToString() == "MThd")
        {
            PrintChunkHeader("MIDI Header", nextHeader);
            CopyMidiChunk(convertedFile, nextHeader);
        }
        else if (nextHeader.id.ToString() == "MTrk")
        {
            PrintChunkHeader("MIDI Track", nextHeader);
            CopyMidiChunk(convertedFile, nextHeader);
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
                ReadChunkData(&skippedData);
            }
        }

        std::cout << std::endl << "Bytes remaining: " << bytesRemaining 
                  << std::endl;
    }   

    return true;
}

ChunkHeader GmdFile::ReadChunkHeader()
{
    ChunkHeader header;
    stream.Read(&header.id);
    stream.Read(&header.size);
    bytesRemaining -= ChunkHeader::Size;
    return header;
}

bool GmdFile::ReadFileHeader()
{
    header = ReadChunkHeader();
    if (header.id.ToString() != "GMD ")
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

void GmdFile::ReadChunkData(BinData::RawField* data)
{
    stream.Read(data);
    bytesRemaining -= data->Size();
}

void GmdFile::CopyMidiChunk(MidiFile& file, ChunkHeader header)
{
    file.WriteChunkHeader(header);
    BinData::RawField chunkData{ static_cast<size_t>(header.size.Value()) };
    ReadChunkData(&chunkData);
    file.WriteChunkData(&chunkData);
}

void PrintChunkHeader(std::string title, const ChunkHeader& header)
{
    std::cout << title << std::endl
              << "--------------------" << std::endl
              << "ID    : " << header.id.ToString() << std::endl
              << "Size  : " << header.size.Value() << std::endl
              << std::endl;
}