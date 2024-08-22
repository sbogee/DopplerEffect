/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include <string.h> 
#include "Knob.h"

//==============================================================================
/**
*/
class DopplerEffectAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    DopplerEffectAudioProcessorEditor(DopplerEffectAudioProcessor&, juce::AudioProcessorValueTreeState& vts);
    ~DopplerEffectAudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;

private:
    DopplerEffectAudioProcessor& audioProcessor;

    juce::ImageComponent myImageComponent;
    juce::Image filmStrip = juce::ImageCache::getFromMemory(BinaryData::knobstrip_bmp, BinaryData::knobstrip_bmpSize);

    // cycleTime

    Knob cycleTimeSlider = Knob(filmStrip);
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
        cycleTimeAttachment;
    juce::Label cycleTimeLabel;

    // maxDistance

    Knob maxDistanceSlider = Knob(filmStrip);
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
        maxDistanceAttachment;
    juce::Label maxDistanceLabel;

    // vanishingPoint

    Knob vanishingPointSlider = Knob(filmStrip);
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
        vanishingPointAttachment;
    juce::Label vanishingPointLabel;

    // infiniteVanishingPoint

    juce::ToggleButton infiniteButton;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment>
        infiniteAttachment;
    juce::Label infiniteButtonLabel;

    juce::Label bpmLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(
        DopplerEffectAudioProcessorEditor)
};
