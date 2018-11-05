/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SimpleAudioProcessor::SimpleAudioProcessor()
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
        We describe here as an "AppStringsDesc" the set of labels, strings, etc, used by the plugin
        */
        allStrs = * new std::vector<struct AppStringsDesc> {
            { none, "Error 80", "error" }, // [a reference to the PL 1600 compiler, back in 1972, that had just this error message :]
            { lab0, "A very simple plugin" },
            { lab1, "Gain"},
            { lab2, "Pan"},
            { lab3, "Volume" },
        };
    
        /**
        We describe here the float values used by the various sliders, buttons, etc.
        The first number (an integer) is the item identification, the second represents
        some flags, and the others values are what is required to declare the parameter :
        the range (typically, min value, max value, step) and the default value
        */
        allVals = * new std::vector<struct AppValuesDesc> {
            { sl1, {0.0f, 2.0f, 0.01f}, 1.0f },
            { sl2, {-1.0f, 1.0f, 0.01f}, 0.0f },
            { sl3, {0.0f, 100.0f, 0.001f, 0.25f}, 0.0f},
        
        };

        /**
         We describe here the GUI of the plugin
        */
        codeLout = * new std::vector<int> {
            //The main window is component "0"
            startCmpt(pluginEditorWindow),
                aCol(),
                    aRow(),
                        aLabel(lab0), pad(bottom, 15), colorize(c_orange,c_transparentBlack),
                    endRow(), setStretch(1.0, 0.35),
                    aRow(),
                        aSlider(sl1,rotVD), withLabel(lab1),
                        aSlider(sl2,rotVD), withLabel(lab2),
                        aSlider(sl3,rotVD), withLabel(lab3),
                    endRow(),
                endCol(),
            endCmpt(pluginEditorWindow)
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
    
    DBG("**** Giving the value tree its state.");
    parameters.state = ValueTree (Identifier ("OrangeV02"));
    
    DBG("****** END AudioProcessor construct");
}

SimpleAudioProcessor::~SimpleAudioProcessor()
{
    DBG("****** AudioProcessor destruct");
}

//==============================================================================

double SimpleAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SimpleAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SimpleAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SimpleAudioProcessor::setCurrentProgram (int index)
{
}

const String SimpleAudioProcessor::getProgramName (int index)
{
    return {};
}

void SimpleAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void SimpleAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void SimpleAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SimpleAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void SimpleAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
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

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    
    /*
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
     */
}

//==============================================================================

AudioProcessorEditor* SimpleAudioProcessor::createEditor()
{
    return (AudioProcessorEditor*) new SimpleAudioProcessorEditor (*this, parameters, lBuilder);
}

//==============================================================================
void SimpleAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
        MemoryOutputStream stream(destData, false);
        parameters.state.writeToStream (stream);
}

void SimpleAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
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
    return new SimpleAudioProcessor();
}
