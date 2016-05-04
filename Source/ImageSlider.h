/*
  ==============================================================================

    ImageSlider.h
    Created: 15 Feb 2016 4:11:40pm
    Author:  Andrew

  ==============================================================================
*/

#ifndef IMAGESLIDER_H_INCLUDED
#define IMAGESLIDER_H_INCLUDED
#include "JuceHeader.h"

class ImageSlider : public juce::Slider
{
public:
	ImageSlider(const Image& image, const Image& imag, const String& name);
	~ImageSlider() {};

	void paint(Graphics& g) override;
	void setLinearStartAndEnd(float start, float end);

private:
	Image im;
	Image im1;
	float linearStart, linearEnd;
};

#endif  // FILMSTRIPKNOB_H_INCLUDED