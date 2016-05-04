/*
  ==============================================================================

    FilmStripKnob.h
    Created: 8 Feb 2016 8:37:16pm
    Author:  pwolfe8

  ==============================================================================
*/

#ifndef FILMSTRIPKNOB_H_INCLUDED
#define FILMSTRIPKNOB_H_INCLUDED
#include "JuceHeader.h"

class ImageKnob : public juce::Slider
{
public:
	ImageKnob(const Image& image, const String& name);
	~ImageKnob() {};

	void paint(Graphics& g) override;
	void setRotaryStartAndEnd(float startInRadians, float endInRadians);

private:
	Image im;
	float rotaryStartAngle, rotaryEndAngle;
};

#endif  // FILMSTRIPKNOB_H_INCLUDED
