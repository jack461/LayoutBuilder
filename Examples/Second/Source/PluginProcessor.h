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

// The Layout module builder
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
static constexpr int sliderCount {28};  // we use some sliders
static constexpr int tbuttonsCount {4}; //  text buttons
static constexpr int tgbuttonsCount {4};  //  toggle buttons
static constexpr int comboBoxCount {2};  //  combo box
// etc...

// Total count of "active components"
static constexpr int parCount {sliderCount+tbuttonsCount+tgbuttonsCount+comboBoxCount};

// Positions of active components in the "value pointer array"
// We put them (arbitrarily) in the order : sliders, buttons, combo boxes
static constexpr int sliderFirst {0};
static constexpr int tbuttonsFirst {sliderFirst+sliderCount};
static constexpr int tgbuttonsFirst {tbuttonsFirst+tbuttonsCount};
static constexpr int comboBoxFirst {tgbuttonsFirst+tgbuttonsCount};

// Others components
static constexpr int labelCount {12};
static constexpr int labelFirst {comboBoxFirst+comboBoxCount};

// String are not components
static constexpr int stringCount {4};
static constexpr int stringFirst {1024};

// The windows components do not appear in the "value array"
// and have their own numbering
// There is at least 1, the Editor window
static constexpr int componentCount {8};
static constexpr int pluginEditorWindow {0};

// Active components identifications
// this is also the parameters identification
enum cmptsIdts {
    // sliders
    b1s1=sliderFirst, b1s2, b1s3, b1s4,
        b2s1a, b2s1b, b2s1c, b2s1d,
        b2s2a, b2s2b, b2s2c, b2s3, b2s4,
        b3s1, b3s2, b3s3, b3s4, b4s1, b4s2, b4s3, b4s4,
        b4s5, b4s6, b4s7, b4s8,
    // text buttons
    tbt1=tbuttonsFirst, tbt2, tbt3,
    // toggle buttons
    tgbt1=tgbuttonsFirst, tgbt2, tgbt3, tgbt4,
    // Combo boxes
    cb1=comboBoxFirst,
    // labels
    lab0=labelFirst, lab1, lab2, lab3, lab4, lab5, lab6, lab7,
    //  others...
    str0=stringFirst, cb1itms, font1, font2,
    //
    dfSl=2048, // default entry for any slider
    dfTB,     // idem for Text Buttons and Toggle buttons
};

// Actual items are described in the pluginProcessor.cpp file

class SecondAudioProcessorEditor; // For the forward reference
//==============================================================================
/**
*/
class SecondAudioProcessor  : public AudioProcessor,
                              public ValueTree::Listener
{
public:
    //==============================================================================
    SecondAudioProcessor();
    ~SecondAudioProcessor();

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
    // The ValueTree::Listener interface - we just care about properties changing
    void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property) override;
    void valueTreeChildAdded (ValueTree &parentTree, ValueTree &childWhichHasBeenAdded) override {};
    void valueTreeChildRemoved (ValueTree &parentTree, ValueTree &childWhichHasBeenRemoved, int indexFromWhichChildWasRemoved) override{};
    void valueTreeChildOrderChanged (ValueTree &parentTreeWhoseChildrenHaveMoved, int oldIndex, int newIndex) override{};
    void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged) override{};
    void valueTreeRedirected (ValueTree &treeWhichHasBeenChanged) override{};
    SecondAudioProcessorEditor * editor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SecondAudioProcessor)
};
