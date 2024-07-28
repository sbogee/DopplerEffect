#pragma once
#include <vector>
#include <cmath>
#include <algorithm>
#include "JuceHeader.h"

class DopplerEffect
{
public:
	void setInfinite(bool infinite);
	void setCycleTime(float cycleTime);
	void setMaxDistance(float maxDistance);
	void setVanishingPoint(float vanishingPoint);
	void setSamplingRate(float samplingRate);
	void setBPM(float bpm);

	void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&);

private:
	bool infinite;
	float cycleTime;
	float maxDistance;
	float vanishingPoint;
	float samplingRate;
	float bpm;

	int timeCntr = 0;

	std::vector<float> amp1;
	std::vector<float> time;
	std::vector<float> amp2;
};

