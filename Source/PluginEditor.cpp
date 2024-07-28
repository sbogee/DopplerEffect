/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DopplerEffectAudioProcessorEditor::DopplerEffectAudioProcessorEditor(DopplerEffectAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    // cycleTime

    addAndMakeVisible(cycleTimeSlider);
    cycleTimeSlider.setSliderStyle(
        juce::Slider::SliderStyle::LinearVertical);
    cycleTimeAttachment.reset(
        new juce::AudioProcessorValueTreeState::SliderAttachment(
            vts, "cycle_time", cycleTimeSlider));

    addAndMakeVisible(cycleTimeLabel);
    cycleTimeLabel.setText("Cycle Time",
        juce::dontSendNotification);

    // maxDistance

    addAndMakeVisible(maxDistanceSlider);
    maxDistanceSlider.setSliderStyle(
        juce::Slider::SliderStyle::LinearVertical);
    maxDistanceAttachment.reset(
        new juce::AudioProcessorValueTreeState::SliderAttachment(
            vts, "max_distance", maxDistanceSlider));

    addAndMakeVisible(maxDistanceLabel);
    maxDistanceLabel.setText("Amplitude",
        juce::dontSendNotification);

    // vanishingPoint

    addAndMakeVisible(vanishingPointSlider);
    vanishingPointSlider.setSliderStyle(
        juce::Slider::SliderStyle::LinearVertical);
    vanishingPointAttachment.reset(
        new juce::AudioProcessorValueTreeState::SliderAttachment(
            vts, "vanishing_point", vanishingPointSlider));

    addAndMakeVisible(vanishingPointLabel);
    vanishingPointLabel.setText("Vanishing point",
        juce::dontSendNotification);

    // infiniteVanishingPoint

    addAndMakeVisible(infiniteButton);
    infiniteAttachment.reset(
        new juce::AudioProcessorValueTreeState::
        ButtonAttachment(vts, "infinite", infiniteButton));

    addAndMakeVisible(infiniteButtonLabel);
    infiniteButtonLabel.setText("Infinite vanishing point", juce::dontSendNotification);

    addAndMakeVisible(bpmLabel);
    bpmLabel.setText("BPM: ", juce::dontSendNotification);

    setSize(480, 400);;
}

DopplerEffectAudioProcessorEditor::~DopplerEffectAudioProcessorEditor()
{
}

//==============================================================================
void DopplerEffectAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    g.setColour(juce::Colours::white);
    g.setFont(juce::FontOptions(15.0f));

    double lastBPM = audioProcessor.bpm;
    bpmLabel.setText("BPM: " + std::to_string(lastBPM), juce::dontSendNotification);
}

void DopplerEffectAudioProcessorEditor::resized()
{
    cycleTimeSlider.setBounds({ 15, 35, 100, 300 });
    cycleTimeLabel.setBounds({ cycleTimeSlider.getX() + 30,
                                    cycleTimeSlider.getY() - 30,
                                    200, 50 });

    maxDistanceSlider.setBounds({ 155, 35, 100, 300 });
    maxDistanceLabel.setBounds({ maxDistanceSlider.getX() + 30,
                                    maxDistanceSlider.getY() - 30,
                                    200, 50 });

    vanishingPointSlider.setBounds({ 295, 35, 100, 300 });
    vanishingPointLabel.setBounds({ vanishingPointSlider.getX() + 30,
                                    vanishingPointSlider.getY() - 30,
                                    200, 50 });

    infiniteButton.setBounds(
        { cycleTimeSlider.getX(),
          cycleTimeSlider.getY() +
          cycleTimeSlider.getHeight() + 15,
         30, 50 });
    infiniteButtonLabel.setBounds(
        { cycleTimeSlider.getX() + infiniteButton.getWidth() + 15,
         infiniteButton.getY(),
         200,
         infiniteButton.getHeight() });

    bpmLabel.setBounds(
        { infiniteButtonLabel.getX() + 200,
         infiniteButton.getY(),
         200,
         infiniteButton.getHeight() });
}
