/*
  ==============================================================================

    FilmStripKnob.cpp
    Created: 8 Feb 2016 8:37:16pm
    Author:  pwolfe8

  ==============================================================================
*/

#include "ImageKnob.h"

// Constructor =================================================================
ImageKnob::ImageKnob(const Image& image, const String& name) : Slider(name)
{
	im = image;
	setRotaryStartAndEnd(float_Pi*1.8f, float_Pi*3.2f);
}

// Methods ======================================================================
void ImageKnob::setRotaryStartAndEnd(float startInRadians, float endInRadians)
{
	rotaryStartAngle = startInRadians;
	rotaryEndAngle = endInRadians;
}

void ImageKnob::paint(Graphics& g)
{
	int w = getWidth();
	int h = getHeight() - getTextBoxHeight();
	AffineTransform t1 = RectanglePlacement()
						.getTransformToFit(im.getBounds().toFloat(),Rectangle<int>(0, 0, w, h).toFloat() );

	float sliderValue = (float) (getValue() - getMinimum()) / (getMaximum() - getMinimum());
	float rotaryValue = rotaryStartAngle + sliderValue*(rotaryEndAngle - rotaryStartAngle);
	AffineTransform t2 = AffineTransform::rotation(rotaryValue, w/2 , h/2);

	g.drawImageTransformed(im, t1.followedBy(t2), false);
}
