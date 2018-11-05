/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/


#include "PluginProcessor.h"
#include "PluginEditor.h"

static void paintItBlack(LayedCanvas * can, int idt, Graphics& g)
{
    g.setColour (can->bgColor);
    g.fillRect (can->getLocalBounds());
    g.setFont (Font (16.0f));
    g.setColour (Colours::white);
    g.drawText (String(idt), can->getLocalBounds(), Justification::centred, true);
}

//==============================================================================
SecondAudioProcessorEditor::SecondAudioProcessorEditor (SecondAudioProcessor& p,
                                                        AudioProcessorValueTreeState& vts,
                                                        lo::LayoutBuilder& lB)
    : AudioProcessorEditor (&p)
    , processor (p)
    , valueTreeState (vts)
    , layout (LayoutItem::LeftToRight, this)
    , lBuilder(lB)
      // The inner components have their own numbering, an need a reference to the builder
    , frame1(&lBuilder, 1) , frame2(&lBuilder, 2) , frame3(&lBuilder, 3) , frame4(&lBuilder, 4)
    , frame5(&lBuilder, 5) , frame6(&lBuilder, 6) , frame7(&lBuilder, 7)

{
    DBG("****** AudioProcessorEditor construct");
    
    // 1) Manage its own TypedComponent infos
    layer = & lBuilder;
    lgcNum = 0;  // The editor is "component 0"
    lcmp = lo::type_main; // its type is "main window"
    playout = & layout;

    
    // Transmit informations to the builder :
    // Those that are available only from the Editor
    lBuilder.setEditor(this); // Declare the Editor
    lBuilder.setCompDesc(comArray, componentCount); // declare the array for all the inner components
    // Register the AudioEditor as component 0
    lBuilder.registerComponent(this);
    // Register other components
    lBuilder.registerComponent(&frame1);
    lBuilder.registerComponent(&frame2);
    lBuilder.registerComponent(&frame3);
    lBuilder.registerComponent(&frame4);
    lBuilder.registerComponent(&frame5); frame5.setColor(Colours::green); frame5.providePaintMethod(paintItBlack);
    lBuilder.registerComponent(&frame6); frame6.setColor(Colours::blue); frame6.providePaintMethod(paintItBlack);
    lBuilder.registerComponent(&frame7);
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
            lBuilder.signalError(); // signal error if any
        }
    }
    
    
    setResizable (true, true);
    setResizeLimits (320, 280, 2000, 1200);
    setSize (560, 360);
    DBG("****** END AudioProcessorEditor construct");
};


SecondAudioProcessorEditor::~SecondAudioProcessorEditor()
{
    playout = nullptr;
    DBG("****** AudioProcessorEditor destruct");
};


void SecondAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    // DBG("SecondAudioProcessorEditor::paint");
    // g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    g.setColour (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    g.fillRect (getLocalBounds());
};


void SecondAudioProcessorEditor::resized()
{
    // DBG("SecondAudioProcessorEditor::resized");
    layout.updateGeometry ();
};


void SecondAudioProcessorEditor::paintOverChildren (Graphics& g)
{
    if (tcFlags & 1)
         layout.paintBounds (g);
};


void SecondAudioProcessorEditor::buildIt()
{
    if (tcFlags & 2)
    {
        DBG("*** Building main component " << lgcNum);
    }
    layer->setLayoutDesc(playout, this);
    layer->buildLayout(lgcNum);
};

