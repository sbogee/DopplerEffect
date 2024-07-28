/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DopplerEffectAudioProcessor::DopplerEffectAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
    ),
#else
    :
#endif
parameters(*this, nullptr,
    juce::Identifier("DopplerEffectPlugin"),
    { std::make_unique<juce::AudioParameterFloat>(
            "cycle_time", "Cycle Time",
            juce::NormalisableRange{0.125f, 10.f, 0.125f, 1.f, false}, 500.f),

        std::make_unique<juce::AudioParameterFloat>(
            "max_distance", "Max Distance",
            juce::NormalisableRange{1.f, 100.f, 1.f, 1.f, false}, 500.f),

        std::make_unique<juce::AudioParameterFloat>(
            "vanishing_point", "Vanishing Point",
            juce::NormalisableRange{1.f, 100.f, 1.f, 1.f, false}, 500.f),

        std::make_unique<juce::AudioParameterBool>(
            "infinite",
            "Infinite",
            false) })
{
    cycleTimeParameter =
        parameters.getRawParameterValue("cycle_time");
    maxDistanceParameter =
        parameters.getRawParameterValue("max_distance");
    vanishingPointParameter =
        parameters.getRawParameterValue("vanishing_point");
    infiniteParameter = parameters.getRawParameterValue("infinite");

}

DopplerEffectAudioProcessor::~DopplerEffectAudioProcessor()
{
}

//==============================================================================
const juce::String DopplerEffectAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DopplerEffectAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool DopplerEffectAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool DopplerEffectAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double DopplerEffectAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DopplerEffectAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int DopplerEffectAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DopplerEffectAudioProcessor::setCurrentProgram(int index)
{
}

const juce::String DopplerEffectAudioProcessor::getProgramName(int index)
{
    return {};
}

void DopplerEffectAudioProcessor::changeProgramName(int index, const juce::String& newName)
{
}

//==============================================================================
void DopplerEffectAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    filter.setSamplingRate(static_cast<float>(sampleRate));
}

void DopplerEffectAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DopplerEffectAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused(layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
#endif
}
#endif

void DopplerEffectAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    // JUCE default code
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());
    // end of the default code

    playHead = this->getPlayHead();
    playHead->getCurrentPosition(currentPositionInfo);
    bpm = currentPositionInfo.bpm;

    const auto cycleTime = cycleTimeParameter->load();
    const auto maxDistance = maxDistanceParameter->load();
    const auto vanishingPoint = vanishingPointParameter->load();

    const auto infinite = *infiniteParameter < 0.5f ? false : true;
    filter.setCycleTime(cycleTime);
    filter.setMaxDistance(maxDistance);
    filter.setVanishingPoint(vanishingPoint);
    filter.setInfinite(infinite);
    filter.setBPM(bpm);

    filter.processBlock(buffer, midiMessages);
}

//==============================================================================
bool DopplerEffectAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* DopplerEffectAudioProcessor::createEditor()
{
    return new DopplerEffectAudioProcessorEditor(*this, parameters);
}

//==============================================================================
void DopplerEffectAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void DopplerEffectAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DopplerEffectAudioProcessor();
}
