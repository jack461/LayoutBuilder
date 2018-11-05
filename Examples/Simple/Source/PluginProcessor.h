/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

// The Layout module written by Daniel Walz
// see: https://ffAudio.github.io/
#include <ff_layout/ff_layout.h>

// The Layout module itself
#include "../../../jj_lbuilder/jj_lbuilder.h"

/**
  This describes for the plug-in the different components
*/

/**
 This is the set of the "active" components of the plug-in.
 (i.e. components which are associated with a plug-in parameter)
 This includes the sliders count, buttons, etc.
*/

// Active components
static constexpr int sliderCount {3};  // we use 3 sliders
static constexpr int tbuttonsCount {0}; // no text buttons
static constexpr int tgbuttonsCount {0};  // no toggle buttons
static constexpr int comboBoxCount {0};  // no combo box
// etc...

// Total count of "active components"
static constexpr int parCount {sliderCount+tbuttonsCount+tgbuttonsCount+comboBoxCount};

// Positions of active components in the "value array"
static constexpr int sliderFirst {0};
static constexpr int tbuttonsFirst {sliderFirst+sliderCount};
static constexpr int tgbuttonsFirst {tbuttonsFirst+tbuttonsCount};
static constexpr int comboBoxFirst {tgbuttonsFirst+tgbuttonsCount};

// Others components
static constexpr int labelCount {4};
static constexpr int labelFirst {comboBoxFirst+comboBoxCount};

// String are not components
static constexpr int stringCount {4};
static constexpr int stringFirst {1024};

// The windows components do not appear in the "value array"
// There is at least 1, the Editor window
static constexpr int componentCount {1};
static constexpr int pluginEditorWindow {0};

// Components identifications
enum cmptsIdts {
    // sliders
    sl1=sliderFirst, sl2, sl3,
    // text buttons
    // toggle buttons
    // labels
    lab0=labelFirst, lab1, lab2, lab3,
    //  others...
    str0=stringFirst,
};

// Actual items are described in the pluginProcessor.cpp file


//==============================================================================
/**
*/
class SimpleAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    SimpleAudioProcessor();
    ~SimpleAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override  { return true; }

    //==============================================================================
    const String getName() const override { return JucePlugin_Name; }

    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override  { return false; }
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    //==============================================================================
    AudioProcessorValueTreeState parameters;
    lo::LayoutBuilder lBuilder; // the layout builder, unique for all components
    float * pParams[parCount];
    std::vector<int> codeLout;
    std::vector<struct lo::AppStringsDesc> allStrs;
    std::vector<struct lo::AppValuesDesc> allVals;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleAudioProcessor)
};
