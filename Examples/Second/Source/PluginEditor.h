/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"


class SecondAudioProcessorEditor; // For the forward reference


#include "PluginProcessor.h"
//==============================================================================
/**
*/

class SecondAudioProcessorEditor  : public AudioProcessorEditor, public virtual TypedComponent
{
    friend LayedGroupComponent;
    friend LayedComponent;
    
public:
    SecondAudioProcessorEditor (SecondAudioProcessor&, AudioProcessorValueTreeState&, lo::LayoutBuilder&);
    ~SecondAudioProcessorEditor();

    typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;
    typedef AudioProcessorValueTreeState::ComboBoxAttachment ComboBoxAttachment;


    //==============================================================================
    void paint (Graphics&) override;
    void paintOverChildren (Graphics& g) override;
    void resized() override;
    void buildIt() override;
 
private:
    SecondAudioProcessor& processor;
    AudioProcessorValueTreeState& valueTreeState;
    Layout layout; // The layout for the editor window
    lo::LayoutBuilder& lBuilder; // the layout builder, from the plugin processor
    
    //  The various GroupComponents
    LayedComponent frame1;
    LayedGroupComponent frame2, frame3;
    LayedComponent frame4;
    LayedCanvas frame5;
    LayedCanvas frame6;
    LayedComponent frame7;
    
    // The local ressources :
    Label allLabels [labelCount];
    
    // interaction objects [some arrays empty...]
    Slider allSliders [sliderCount];
    TextButton allTButtons[tbuttonsCount];
    ToggleButton allTgButtons[tgbuttonsCount];
    ComboBox allComboBox[comboBoxCount];
    
     // The actual components list
    Component * comArray[componentCount];

    // Finally, the various attachments, so they a deleted first
    std::unique_ptr<SliderAttachment> slAttachment[sliderCount];
    std::unique_ptr<ButtonAttachment> tbAttachment[tbuttonsCount];
    std::unique_ptr<ButtonAttachment> tgAttachment[tgbuttonsCount];
    std::unique_ptr<ComboBoxAttachment> cmbBAttachment[comboBoxCount];
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SecondAudioProcessorEditor)
};

