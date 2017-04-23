/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include <unistd.h>
#include <iostream>
#include <sstream>>
#include <string>

//////////////////commands
const char _p = 'p'; //play file
const char _f = 'f'; //perform fft
const char _e = 'e';//exit
const char _i = 'i'; //get info




void printFileInfo(ScopedPointer<AudioFormatReader> reader)
{
    std::cout << "Format: " << reader->getFormatName() << std::endl;
    std::cout << "Channels: " << reader->numChannels << std::endl;
    std::cout << "Sample Rate: " << reader->sampleRate << std::endl;
    std::cout << "Bit depth: " <<  reader->bitsPerSample << std::endl;
}

//==============================================================================
int main (int argc, char* argv[])
{
    juce::String testfilepath = "/home/armen/Documents/testfile.wav";
    File audiofile(testfilepath);
    AudioFormatManager manager;
    manager.registerBasicFormats();

    ScopedPointer<AudioFormatReader> reader(manager.createReaderFor(audiofile));
    if (reader != nullptr)
    {
        std::string input;
		while (true)
        {
            std::cout << "Enter a command: " << std::endl;
            getline(std::cin, input);

            switch (input[0])
            {
            case  _p:
                {
                    std::cout << "Playing file" << std::endl;
                    AudioSampleBuffer fileBuffer;
                    fileBuffer.setSize(reader->numChannels, reader->lengthInSamples);
                    reader->read(&fileBuffer, 0, reader->lengthInSamples, 0, true, true);
                    ScopedPointer<AudioFormatReaderSource> newSource = new AudioFormatReaderSource (reader, true);

                    AudioTransportSource transport;
                    transport.setSource (newSource, 0, nullptr, reader->sampleRate);
                    transport.prepareToPlay(fileBuffer.getNumSamples(), reader->sampleRate);
                    transport.start();

                    break;
                }

            case _f:
                {
                    std::cout << "Doing an FFT"<< std::endl;
                    break;
                }

            case _i:
                {
                    printFileInfo(reader);
                    break;
                }

            case _e:
                {

                    return 0;
                }

            }

        }

    }
    std::cout << "hit enter to exit" << std::endl;
    std::cin;
    return 0;
}
