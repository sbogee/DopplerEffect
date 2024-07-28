/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include <string.h> 

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

    // cycleTime

    juce::Slider cycleTimeSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
        cycleTimeAttachment;
    juce::Label cycleTimeLabel;

    // maxDistance

    juce::Slider maxDistanceSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
        maxDistanceAttachment;
    juce::Label maxDistanceLabel;

    // vanishingPoint

    juce::Slider vanishingPointSlider;
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
