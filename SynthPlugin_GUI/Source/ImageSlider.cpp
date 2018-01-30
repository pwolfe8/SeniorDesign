/*
  ==============================================================================

    ImageSlider.cpp
    Created: 15 Feb 2016 4:11:40pm
    Author:  Andrew

  ==============================================================================
*/

#include "ImageKnob.h"
#include "ImageSlider.h"

// Constructor =================================================================
ImageSlider::ImageSlider(const Image& image, const Image& imag, const String& name) : Slider(name)
{
	im = image;
	im1 = imag;
	setLinearStartAndEnd(0, 56);

}

// Methods ======================================================================
void ImageSlider::setLinearStartAndEnd(float start, float end)
{
	linearStart = start;
	linearEnd = end;

}

void ImageSlider::paint(Graphics& g)
{
	
	int w = getWidth();
	int h = getHeight() - getTextBoxHeight();
	AffineTransform t1 = RectanglePlacement(RectanglePlacement::stretchToFit)
						.getTransformToFit(im1.getBounds().toFloat(),Rectangle<int>(0, 0, w, h).toFloat());

	//g.drawImageTransformed(im, t1, false);

	int sliderHeight = im1.getHeight();


	float sliderValue = (float) (getValue() - getMinimum()) / (getMaximum() - getMinimum());
	int yPos = (1 - sliderValue) * (h-sliderHeight);
	AffineTransform t2 = RectanglePlacement(RectanglePlacement::stretchToFit)
		.getTransformToFit(im1.getBounds().toFloat(), Rectangle<int>(0, yPos, w, sliderHeight).toFloat());


	
	g.drawImageTransformed(im1, t2, false);
}
