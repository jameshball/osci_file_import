#pragma once
#include <atomic>
#include <functional>
#include <memory>
#include <utility>

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_formats/juce_audio_formats.h>
#include <juce_core/juce_core.h>

class WavParser {
public:
    using SampleRateProvider = std::function<double()>;

    explicit WavParser(SampleRateProvider sampleRateProvider = {});
    ~WavParser();

    void processBlock(juce::AudioBuffer<float>& buffer);

    void setProgress(double progress);
    void setPaused(bool paused);
    bool isPaused();
    void setLooping(bool looping);
    bool isLooping();
    bool parse(std::unique_ptr<juce::InputStream> stream);

    // Offline / utility helpers.
    // By default WavParser follows the processor sample rate for realtime playback.
    // Offline callers can disable following and set a fixed target sample rate.
    void setFollowProcessorSampleRate(bool shouldFollow);
    void setTargetSampleRate(double sampleRate);
    double getFileSampleRate() const;
    int getNumChannels() const;

    void close();
    bool isInitialised();

    std::atomic<double> currentSample = 0;
    std::atomic<long> totalSamples;

private:
    void setSampleRate(double sampleRate);
    double getProcessorSampleRate() const;

    std::atomic<bool> initialised = false;
    std::unique_ptr<juce::AudioFormatReaderSource> afSource;
    std::atomic<bool> looping = true;
    std::unique_ptr<juce::ResamplingAudioSource> source = nullptr;
    juce::AudioBuffer<float> audioBuffer;
    std::atomic<bool> paused = false;
    double fileSampleRate = 0.0;
    double currentSampleRate = 0.0;
    std::atomic<bool> followProcessorSampleRate { true };
    std::atomic<double> targetSampleRate { 0.0 };
    int numChannels = 0;
    SampleRateProvider sampleRateProvider;
};
