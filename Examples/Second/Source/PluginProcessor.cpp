/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SecondAudioProcessor::SecondAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
#endif
    parameters (*this, nullptr),
    lBuilder(&parameters)
{
    DBG("****** AudioProcessor construct");
    
    

    /**
         We work inside the namespace "lo" to be able to use the various
         operations, structures, and constants definitions
    */
    {
        using namespace lo;
        /**
        We describe here as an "AppStringsDesc" vector the set of labels, strings, etc, used by the plugin
        */
        allStrs = * new std::vector<struct AppStringsDesc> {
            { none, "error", "Error 80" }, // [a nostalgic reference to the PL 1600 compiler, back in 1972, that had just this unique error message :]
            { lab0, "The second plugin" },
            { lab1, "By Colored Black Boxes" },
            { lab2, "Delay X"},
            { lab3, "Lock"},
            { lab4, "Start"},
            { lab5, "Write"},
            { lab6, "Label" },
            { lab7, "Gain" },
            { tbt1, "Good"},
            { tgbt1, "With"},
            { b1s2, "length" },
            { cb1, "Choice"},
            { cb1itms, { "-", "first", "second", "third", "fourth", "fifth"}},
            { font1, "Arial", "Italic", "26.0" },
            { font2, "Charter", "Bold Italic", "30.0" },
        };
    
        /**
        We describe here the float values used by the various sliders, buttons, etc.
        The first number (an integer) is the item identification, the second [optional] represents
        some flags, and the others values are what is required to declare the parameter :
        the range (typically, min value, max value, step) and the default value
        */
        allVals = * new std::vector<struct AppValuesDesc> {
            { b1s1, {0.0f, 2.0f, 0.01f}, 1.0f },
            { b1s2, {0.0f, 100.0f, 0.0001f, 0.25f}, 1.0f },
            { b1s3, {0.0f, 100.0f, 0.1f}, 0.0f},
            { b2s3, {0.0f, 100.0f}},
            { b4s2, {0.0f, 24.0f, 1.0f}},
            //------------------------------
            { tbt1, {0.0f, 1.0f, 1.0f}, 0.0f},
            //------------------------------
            { tgbt1, {0.0f, 1.0f, 1.0f}, 0.0f},
            //------------------------------
            { cb1, {0.0f, 10.0f, 1.0f}, 1.0f},
            //------------------------------
            { dfSl, {0.0f, 10.0f, 0.1f}}, // default entry for a slider
            { dfTB, {0.0f, 1.0f, 1.0f}}, // default entry for a button
        };

        /**
         We describe here the GUI of the plugin
        */
        // "cheap" look & feel for items
        constexpr int stdsSlColors { colorize(c_orange, c_green, c_grey) };
        
        codeLout = * new std::vector<int> {
            // Global declarations
            setSldPdef(dfSl), setTbtPdef(dfTB), setTgbPdef(dfTB),
            // First define some common declarations
            startDcl(),
                setColor(c_A, c_orange),  // chose a default main color (orange) for the frames
            endDcl(),
            //The main window contains a label and 5 components
            startCmpt(pluginEditorWindow),
                aCol(),
                    aRow(), aRow(),
                        aLabel(lab0), fontFace(font2), fontStyle(0, 0, j_centred), colorize(c_orange,c_transparentBlack), setStretch(3.5),
                        aCmbBox(cb1, cb1itms), pad(vertical, 5), setStretch(1.5),
                    endRow(), endRow(), setStretch(1.0, 0.1),
                    aRow(),
                        theCmpt(1),
                        theCmpt(2),
                        aSplitter(0.4),
                        theCmpt(3),
                        theCmpt(7), setStretch(0.5),
                        theCmpt(4), setStretch(1.5),
                    endRow(),
                endCol(),
            endCmpt(pluginEditorWindow),
            // Component 1
            startCmpt(1, topDown),
                aSlider(b1s1,0), stdsSlColors,
                aSlider(b1s2,linH),
                aSlider(b1s3,linV), stdsSlColors,
            endCmpt(1),
            // Component 2
            startCmpt(2),
                aCol(),
                    aCol(),
                        aSlider(b2s1a,barH), stdsSlColors,
                        aSlider(b2s1b,barH), stdsSlColors,
                        aSlider(b2s1c,barH), stdsSlColors,
                        aSlider(b2s1d,barH), stdsSlColors,
                    endCol(),
                    aRow(),
                        aSlider(b2s2a,barV), stdsSlColors,
                        aSlider(b2s2b,barV), stdsSlColors,
                        aSlider(b2s2c,barV), stdsSlColors,
                    endRow(),
                    aSpace(), setHeight(20,20),
                    aSlider(b2s3,rot,2), withLabel(lab7), stdsSlColors,
                endCol(), pad(15,10,5,5),
                frameLab(lab2, c_orange), // Build the frame and label
            endCmpt(2),
            // Component 3
            startCmpt(3),
                aCol(),
                    aLabel(lab1), setHeight(35,55), pad(vertical, 10), colorize(c_orange,c_transparentBlack), fontStyle(9.5, s_underlined),
                    aSlider(b3s1,rotVD,noTB), stdsSlColors, setHeight(50,150), setWidth(45,140),
                    aSlider(b3s2,rotHD), stdsSlColors,
                    aTButton(tbt1,tgB), setHeight(25,55), pad(allDirections, 10), colorize(c_lightseagreen),
                    aTgButton(tgbt1), setHeight(35,55), colorize(c_lightseagreen),
                endCol(), pad(allDirections, 10),
                frameLab(lab6, c_orange, c_green),
            endCmpt(3),
            // Component 4
            startCmpt(4, topDown),
                aRow(),
                    aSlider(b4s1,rotHVD), stdsSlColors,
                    aSlider(b4s2,incDec), stdsSlColors,
                endRow(),
                aRow(),
                    aSlider(b4s3,linV), stdsSlColors,
                    aSlider(b4s4,linV),
                    aSlider(b4s5,lin3V), stdsSlColors,
                endRow(),
                aSpace(), setHeight(20,20),
                aSlider(b4s6,linH), stdsSlColors, withLabel(lab5),
                aSlider(b4s7,lin3H), stdsSlColors,
                aSlider(b4s8,linH,tBLeft,2), stdsSlColors,
            endCmpt(4),
            // Component 7
            startCmpt(7, topDown),
                theCmpt(5),
                aSlider(b1s4,0),
                theCmpt(6),
            endCmpt(7),
        };
        
        // end using "lo"
    };
    
    // Transmitt a first set of informations to the layout builder :
    // those that are available in the AudioProcessor part
    lBuilder.setProcessor(this);
    lBuilder.setCode(codeLout);
    lBuilder.setStringsSet(allStrs);
    lBuilder.setValuesSet(allVals);
    lBuilder.setPAddresses(pParams, parCount);
    lBuilder.setSliderCount(sliderCount, sliderFirst);
    lBuilder.setTButtonCount(tbuttonsCount, tbuttonsFirst);
    lBuilder.setTgButtonCount(tgbuttonsCount, tgbuttonsFirst);
    lBuilder.setCmbBoxCount(comboBoxCount, comboBoxFirst);
    
    // All parameters are ready to be created.
    lBuilder.buildParameters();
    
    lBuilder.signalError(); // signal error if any
    
    DBG("**** Giving the value tree its state.");
    parameters.state = ValueTree (Identifier ("OrangeV04"));
    parameters.state.addListener(this);
    DBG("****** END AudioProcessor construct");
}

SecondAudioProcessor::~SecondAudioProcessor()
{
    DBG("****** AudioProcessor destruct");
}

//==============================================================================

double SecondAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SecondAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SecondAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SecondAudioProcessor::setCurrentProgram (int index)
{
}

const String SecondAudioProcessor::getProgramName (int index)
{
    return {};
}

void SecondAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
// Let's create some trace of parameters changes
// This is how we can be aware that a parameter has changed
void SecondAudioProcessor::valueTreePropertyChanged (ValueTree &tree,
                                                     const Identifier &property)
{
    const var val = tree.getProperty (property);
    jassert (tree.getNumProperties() == 2); // we expect 2 properties, "id" and "value"
    Value pname = tree.getPropertyAsValue("id", nullptr);
    int pnum = pname.getValue().toString().getTrailingIntValue(); // our parameter number
    float pv = float(val); // the actual parameter value
    jassert(pv == * pParams[pnum]); // check that pParams addresses remain valid
    DBG("   " << pname.getValue().toString() << " " << pnum << " ==> " << String(float(val)));
}

//==============================================================================
void SecondAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void SecondAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SecondAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void SecondAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

}

//==============================================================================

AudioProcessorEditor* SecondAudioProcessor::createEditor()
{
    editor = new SecondAudioProcessorEditor (*this, parameters, lBuilder);
    return (AudioProcessorEditor*) editor;
}

//==============================================================================
void SecondAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    MemoryOutputStream stream(destData, false);
    parameters.state.writeToStream (stream);
}

void SecondAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    ValueTree tree = ValueTree::readFromData (data, size_t (sizeInBytes));
    if (tree.isValid()) {
        parameters.state = tree;
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SecondAudioProcessor();
}
