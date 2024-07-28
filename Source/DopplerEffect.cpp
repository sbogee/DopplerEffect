#include "DopplerEffect.h"

void DopplerEffect::setInfinite(bool infinite) {
    this->infinite = infinite;
}

void DopplerEffect::setCycleTime(float cycleTime) {
    this->cycleTime = cycleTime;
}

void DopplerEffect::setMaxDistance(float maxDistance) {
    this->maxDistance = maxDistance;
}

void DopplerEffect::setVanishingPoint(float vanishingPoint) {
    this->vanishingPoint = vanishingPoint;
}

void DopplerEffect::setSamplingRate(float samplingRate) {
    this->samplingRate = samplingRate;
}

void DopplerEffect::setBPM(float bpm) {
    this->bpm = bpm;
}

void DopplerEffect::processBlock(juce::AudioBuffer<float>& buffer,
    juce::MidiBuffer&)
{
    constexpr auto PI = 3.14159265359f;

    float periodTime = cycleTime / (bpm / 60) * samplingRate;
    float circleFreq = (2 * PI) / periodTime;

    auto channelSamples1 = buffer.getWritePointer(0);
    auto channelSamples2 = buffer.getWritePointer(1);

    for (auto i = 0; i < buffer.getNumSamples(); ++i) {

        float distance = (sin(circleFreq * timeCntr - PI / 2.0f) + 1.0f) * 0.5f * maxDistance;

        if (timeCntr == 0)
        {
            amp1.push_back(channelSamples1[i]);
            amp2.push_back(channelSamples2[i]);
            time.push_back(0);
        }
        else
        {
            float delayTime = samplingRate * (distance / 343.0f); // hangsebesség

            time.push_back(delayTime + timeCntr);
            amp1.push_back(channelSamples1[i]);
            amp2.push_back(channelSamples2[i]);

            //interpoláció
            int lowerIdx = (std::lower_bound(time.begin(), time.end(), timeCntr) - time.begin()) - 1;
            channelSamples1[i] = (((amp1[lowerIdx + 1] - amp1[lowerIdx]) * (timeCntr - time[lowerIdx])) / (time[lowerIdx + 1] - time[lowerIdx])) + amp1[lowerIdx];
            channelSamples2[i] = (((amp2[lowerIdx + 1] - amp2[lowerIdx]) * (timeCntr - time[lowerIdx])) / (time[lowerIdx + 1] - time[lowerIdx])) + amp2[lowerIdx];

            //hangerõ
            float volume = 1;
            if (!infinite)
            {
                if (distance <= vanishingPoint)
                {
                    volume = (vanishingPoint - distance) / vanishingPoint;
                }
            }

            channelSamples1[i] *= volume;
            channelSamples2[i] *= volume;

            amp1.erase(amp1.begin(), amp1.begin() + lowerIdx);
            amp2.erase(amp2.begin(), amp2.begin() + lowerIdx);
            time.erase(time.begin(), time.begin() + lowerIdx);
        }

        timeCntr++;
        if (timeCntr > periodTime)
        {
            timeCntr = 0;
            amp1.clear();
            time.clear();
            amp2.clear();
        }
    }
}

