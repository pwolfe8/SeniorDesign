/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 4.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_FFE5A64DBF6C2868__
#define __JUCE_HEADER_FFE5A64DBF6C2868__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "ImageKnob.h"
#include "ImageSlider.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class Plugin2AudioProcessorEditor  : public AudioProcessorEditor,
                                     public SliderListener,
                                     public MenuBarModel,
                                     public ComboBoxListener,
                                     public ButtonListener
{
public:
    //==============================================================================
    Plugin2AudioProcessorEditor (Plugin2AudioProcessor& p);
    ~Plugin2AudioProcessorEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	Plugin2AudioProcessor* getProcessor() const
    {
        return static_cast <Plugin2AudioProcessor*>(getAudioProcessor());
    }

    void sliderValueChanged(Slider* sliderThatWasMoved);

	void LoadFile();
	void SaveFile();

	StringArray getMenuBarNames();
	PopupMenu getMenuForIndex(int index, const String& name);
	void menuItemSelected(int menuID, int index);

	enum MenuIDs {
		Save = 1000,
		Load

	};

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void buttonClicked (Button* buttonThatWasClicked);

    // Binary resources:
    static const char* background_vst_png;
    static const int background_vst_pngSize;
    static const char* slider_background_vst_png;
    static const int slider_background_vst_pngSize;
    static const char* slider_front_png;
    static const int slider_front_pngSize;
    static const char* vst_knob_png;
    static const int vst_knob_pngSize;
    static const char* resized_knob_png;
    static const int resized_knob_pngSize;
    static const char* resized_knob2_png;
    static const int resized_knob2_pngSize;
    static const char* final_knob_png;
    static const int final_knob_pngSize;
    static const char* slider_front2_png;
    static const int slider_front2_pngSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	Plugin2AudioProcessor& processor; // also add it to initializer if you use this
	ScopedPointer<ImageKnob> knob1;
	ScopedPointer<ImageKnob> knob2;
	ScopedPointer<ImageKnob> knob3;
	ScopedPointer<ImageSlider> slider1;
	ScopedPointer<ImageSlider> slider2;


	MenuBarComponent menuBar;


	//variables to hold data from the GUI
	double tune;
	double shape;
	double volume;
	double attack;
	double release;

	double vout;
	double vref;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> label;
    ScopedPointer<ComboBox> comboBox;
    ScopedPointer<ToggleButton> toggleButton;
    Image cachedImage_background_vst_png_1;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Plugin2AudioProcessorEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_FFE5A64DBF6C2868__
