#pragma once
#include <JuceHeader.h>

class Knob : public juce::Slider
{
public:
    Knob(juce::Image stripToShow) : filmStrip(stripToShow)
    {
        // careful with empty images (zero division) and/or non-square images.
        // also, strips with one image wont work as well.
        // strips are vertical stacked images of the same size.
        sideLength = filmStrip.getHeight();
        numFrames = filmStrip.getWidth() / sideLength;
    }
    void paint(juce::Graphics& g) override
    {
        std::size_t imageNumber = static_cast<std::size_t>(0.5 + (getValue() - getMinimum()) / (getMaximum() - getMinimum()) * (numFrames - 1));
        g.drawImage(filmStrip, 0, 0, sideLength, sideLength, imageNumber * sideLength, 0, sideLength, sideLength);
    }
private:
    std::size_t numFrames, sideLength;
    juce::Image filmStrip;
};