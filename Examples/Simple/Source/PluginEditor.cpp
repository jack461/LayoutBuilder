/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/


#include "PluginProcessor.h"
#include "PluginEditor.h"



//==============================================================================
SimpleAudioProcessorEditor::SimpleAudioProcessorEditor (SimpleAudioProcessor& p,
                                                        AudioProcessorValueTreeState& vts,
                                                        lo::LayoutBuilder& lB)
    : AudioProcessorEditor (&p)
    , processor (p)
    , valueTreeState (vts)
    , layout (LayoutItem::LeftToRight, this)
    , lBuilder(lB)

{
    DBG("****** AudioProcessorEditor construct");
    
    // Manage its own TypedComponent infos
    layer = & lBuilder;
    lgcNum = 0;  // The editor is "component 0"
    lcmp = lo::type_main; // its type is "main window"
    playout = & layout;

    
    
    // Transmit informations to the builder :
    // Those that are available only from the Editor
    lBuilder.setEditor(this); // Declare the Editor
    lBuilder.setCompDesc(comArray, componentCount); // declare the array for the inner components
    // Register the AudioEditor as component 0
    lBuilder.registerComponent(this);
    lBuilder.setSliderList(allSliders, slAttachment, sliderCount); // declare the sliders and their attachments
    lBuilder.setTButtonList(allTButtons, tbAttachment, tbuttonsCount); // declare the text buttons and their attachments
    lBuilder.setTgButtonList(allTgButtons, tgAttachment, tgbuttonsCount); // declare the toggle buttons and their attachments
    lBuilder.setCmbBoxList(allComboBox, cmbBAttachment, comboBoxCount); // declare the combo boxes and their attachments
    lBuilder.setLabelList(allLabels, labelCount); // declare the labels

    // Set trace/show flags [default is 0]
    // tcFlags = 0;
    // frame1.setTCFlags(0);
    // lBuilder.setDefaultDecimalDigits(2); // change the number of default decimal digis
    
    // Prepare to build main window layout and other components
    for (int i = 0; i < componentCount; i++)
    {
        TypedComponent * tc = dynamic_cast<TypedComponent *> (comArray[i]);
        if (tc != nullptr)
        {
            lBuilder.clearError();
            tc->buildIt(); // This calls the builder for this component
            DBG("*** return code [" << i << "] : " << lBuilder.getError());
        }
    }
    
    
    setResizable (true, true);
    setResizeLimits (160, 120, 1500, 900);
    setSize (300, 200);
    DBG("****** END AudioProcessorEditor construct");
};


SimpleAudioProcessorEditor::~SimpleAudioProcessorEditor()
{
    playout = nullptr;
    DBG("****** AudioProcessorEditor destruct");
};


void SimpleAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    // DBG("SimpleAudioProcessorEditor::paint");
    g.setColour (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    g.fillRect (getLocalBounds());
};


void SimpleAudioProcessorEditor::resized()
{
    // DBG("SimpleAudioProcessorEditor::resized");
    layout.updateGeometry ();
};


void SimpleAudioProcessorEditor::paintOverChildren (Graphics& g)
{
    if (tcFlags & 1)
         layout.paintBounds (g);
};


void SimpleAudioProcessorEditor::buildIt()
{
    if (tcFlags & 2)
    {
        DBG("*** Building main component " << lgcNum);
    }
    layer->setLayoutDesc(playout, this);
    layer->buildLayout(lgcNum);
};

