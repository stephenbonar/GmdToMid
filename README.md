# GMD to MIDI Converter

GMD to MIDI Converter is a cross-platform program that converts .gmd files to standard MIDI files (.mid). The GMD format was prevalent in games that used the iMuse system to dynamically generate MIDI music.

The program accepts a .gmd file and converts it to multiple type 0 MIDI files, one per track contained within the GMD.

# Pre-release Version

This program is a pre-release version (0.81 alpha) but is mostly functional.
The first track in the .gmd file converts correctly, but the subsequent tracks are missing context from the first track. I suspect there's initialization events in the first track the subsequent tracks depend on.
It is command-line only at this point, but the final release is planned to support both GUI and command line.

You can compile and run the program from source using CMake on Windows, macOS, or Linux. 
It has only been compiled and functionally tested on Windows using .gmd files from one game, so your mileage may vary.