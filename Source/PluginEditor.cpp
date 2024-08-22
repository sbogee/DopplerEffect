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
    juce::Image background = juce::ImageCache::getFromMemory(BinaryData::schwingen_png, BinaryData::schwingen_pngSize);

    if (!background.isNull())
    {
        myImageComponent.setImage(background, juce::RectanglePlacement::stretchToFit);
    }
    else
    {
        jassert(!background.isNull());
    }

    addAndMakeVisible(myImageComponent);
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

    setSize(550, 400);

    
}

DopplerEffectAudioProcessorEditor::~DopplerEffectAudioProcessorEditor()
{
}

//==============================================================================
void DopplerEffectAudioProcessorEditor::paint(juce::Graphics& g)
{
    //g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    

    //g.drawImageAt(background, 0, 0);

    g.setColour(juce::Colours::white);
    g.setFont(juce::FontOptions(15.0f));

    double lastBPM = audioProcessor.bpm;
    bpmLabel.setText("BPM: " + std::to_string(lastBPM), juce::dontSendNotification);
}

void DopplerEffectAudioProcessorEditor::resized()
{
    cycleTimeSlider.setBounds({ 180, 25, 100, 250 });
    cycleTimeLabel.setBounds({ cycleTimeSlider.getX()+40,
                                    cycleTimeSlider.getY() - 30,
                                    200, 50 });

    maxDistanceSlider.setBounds({ 280, 25, 100, 250 });
    maxDistanceLabel.setBounds({ maxDistanceSlider.getX()+40,
                                    maxDistanceSlider.getY() - 30,
                                    200, 50 });

    vanishingPointSlider.setBounds({ 380, 25, 100, 250 });
    vanishingPointLabel.setBounds({ vanishingPointSlider.getX()+40,
                                    vanishingPointSlider.getY() - 30,
                                    200, 50 });

    infiniteButton.setBounds(
        { cycleTimeSlider.getX(),
          cycleTimeSlider.getY() +
          cycleTimeSlider.getHeight() + 80,
         30, 50 });
    infiniteButtonLabel.setBounds(
        { cycleTimeSlider.getX() + infiniteButton.getWidth() + 5,
         infiniteButton.getY(),
         200,
         infiniteButton.getHeight() });

    bpmLabel.setBounds(
        { infiniteButtonLabel.getX() + 180,
         infiniteButton.getY(),
         200,
         infiniteButton.getHeight() });

    myImageComponent.setBoundsRelative(0.f, 0.f, 1.f, 1.f);
}
