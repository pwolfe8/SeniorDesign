# Senior Design Project Folder
Project folder for the synthesizer plugin GUI and the Mbed DAC controller used to interface to the analog synthesizer on the Field Programmable Analog Array(FPAA).


## Mbed FPAA Interface:
- parses serial messsages from our GUI to control DACs using SPI. The DACs drive the FPAA inputs to control parameters like volume, pitch, etc.
- located in folder "Mbed_Serial_DAC_Interface"
- [Mbed project link](https://os.mbed.com/users/pwolfe8/code/serialPCtoSPItoDAC/wiki/Mbed-Serial-Relay-to-control-DACs)


## Synthesizer Plugin GUI:
- GUI for controlling our analog synthesizer. It's formatted as a VST plugin that is compatible with most digital audio workstations.
- located in folder "SynthPlugin_GUI". The C++ project file is under Builds=>VisualStudio2015=>Plugin2.sln

- Prereqs:
    - install JUCE at https://www.juce.com/get-juce, 
    - install Visual Studio 2015 with C++
