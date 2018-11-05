/*
  ==============================================================================

    LayoutDescription.cpp
    Created: 28 Sep 2018 9:36:23pm
    Author:  Jean-Jacques Girardot

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"

#include "jj_LayoutDescription.h"

/**
  Various utilities implementation
 */

namespace lo {
    // This is for the sort & find operations
    bool cmpAVD(AVD a, AVD b) { return a.itemId < b.itemId; };

    // Provide a swap operation because we are doing a sort
    void swap(struct AppValuesDesc& a, struct AppValuesDesc& b)
    {
        int itemId = a.itemId;
        int itemFlgs = a.itemFlgs;
        float defVal = a.defVal;
        NormalisableRange<float> range = a.range;
        a.itemId = b.itemId;
        a.itemFlgs = b.itemFlgs;
        a.defVal = b.defVal;
        a.range = b.range;
        b.itemId = itemId;
        b.itemFlgs = itemFlgs;
        b.defVal = defVal;
        b.range = range;
    };

    
    // This is for the sort & find operations
    bool cmpASD(ASD a, ASD b) { return a.itemId < b.itemId; };
    
    // Provide a swap operation because we are doing a sort
    void swap(struct AppStringsDesc& a, struct AppStringsDesc& b)
    {
        int itemId = a.itemId;
        std::vector<std::string> v = a.txts;
        a.itemId = b.itemId;
        a.txts = b.txts;
        b.itemId = itemId;
        b.txts = v;
    };
    
    void LayoutBuilder::setEditor(Component * me)
    {
        mainEditor = me;
        // Reset some values, because the editor can be built more than once
        nextLab = 0;
    }
    
    void LayoutBuilder::setCode(std::vector<int> xc)
    {
        instructs = xc;
        instructSize = (int) instructs.size();
    }
    
    void LayoutBuilder::setLayoutDesc(Layout * pl, Component * pe)
    {
        playout = pl;
        edt = pe;
    }
    
    void LayoutBuilder::setStringsSet(std::vector<struct lo::AppStringsDesc> vS)
    {
        stringSet=vS;
        std::sort(stringSet.begin(), stringSet.end(), cmpASD); // sort the array
        stringSetSize = (int)stringSet.size(); // now a constant
        // Build def entry
        appSdefEntry = getStrEntry(defaultEntry); // look for the default entry
        DBG("----  Sorted ; size : " << stringSetSize << " ; default : " << appSdefEntry);
        
    }
    
    // Look for item # itm, if not found return entry "defent", or "appVdefEntry"
    int LayoutBuilder::getStrEntry(const int itm, const int defent)
    {
        if (stringSetSize > 0)
        {
            itmS.itemId = itm;
            auto ps = std::lower_bound(stringSet.begin(), stringSet.end(), itmS, cmpASD);
            if (ps != stringSet.end() && ps->itemId == itm)
            {
                // return element position
                return (int)std::distance(stringSet.begin(), ps);
            }

        }
        if (defent >= 0 && defent < stringSetSize)
            return defent;
        return appSdefEntry;
    }
    
    // Look for item # itm, if not found return entry "defent", or "appVdefEntry"
    int LayoutBuilder::getValEntry(const int itm, const int defent)
    {
        if (valueSetSize > 0)
        {
            itmE.itemId = itm;
            auto ps = std::lower_bound(valueSet.begin(), valueSet.end(), itmE, cmpAVD);
            if (ps != valueSet.end() && ps->itemId == itm)
            {
                // return element position
                return (int)std::distance(valueSet.begin(), ps);
            }
        }
        if (defent >= 0 && defent < valueSetSize)
            return defent;
        return appVdefEntry;
    };

    
    void LayoutBuilder::setValuesSet(std::vector<struct lo::AppValuesDesc> vS)
    {
        valueSet=vS;
        std::sort(valueSet.begin(), valueSet.end(), cmpAVD); // sort the array
        valueSetSize = (int)valueSet.size(); // now a constant
        // Build def entry
        appVdefEntry = getValEntry(defaultEntry); // look for the default entry
        DBG("----  Sorted ; size : " << valueSetSize << " ; default : " << appVdefEntry);

    }
    
    void LayoutBuilder::registerComponent(Component * cmp, int cpnb)
    {
        if (cmp != nullptr && comArray != nullptr)
        {
            TypedComponent * tc = dynamic_cast<TypedComponent *> (cmp);
            if (tc != nullptr)
            {
                int c = tc->lgcNum;
                jassert(c >= 0 && c < compCount);
                if (c >= 0 && c < compCount)
                    comArray[c] = cmp;
                DBG("* dcl cmp " << tc->lgcNum << " as type " << tc->lcmp);
            }
            else
            {
                if (cpnb >= 0 && cpnb < compCount)
                {
                    comArray[cpnb] = cmp;
                }
            }
        }
    };

    void LayoutBuilder::setErrorF (int e, int li, const char * fn) {
        if (firstErrorFound == 0) {
            firstErrorFound = e;
            lineErrorFound = li;
            fileErrorFound [0]=0;
            if (fn != nullptr) {
                strncpy(fileErrorFound, fn, 127);
                fileErrorFound [127]=0;
            }
        }
    } ;
    
    void LayoutBuilder::signalError()
    {
        if (firstErrorFound != 0)
        {
            DBG("LayoutBuilder error " << firstErrorFound << " [[line " << lineErrorFound << ", file "
                << fileErrorFound << "]]");
            jassertfalse;
        }
    }
    
    /**
      A small choice of colors
     */
    void LayoutBuilder::buildAllColors()
    {
        for (int i=0; i < cSize; i++) {
            colors[i] = Colours::white;
        }
        colors[c_transparentBlack] = Colours::transparentBlack;
        colors[c_black] = Colours::black; colors[c_white] = Colours::white;
        colors[c_blue] = Colours::blue; colors[c_grey] = Colours::grey;
        colors[c_green] = Colours::green; colors[c_red] = Colours::red;
        colors[c_yellow] = Colours::yellow; colors[c_greenyellow] = Colours::greenyellow;
        colors[c_lightblue] = Colours::lightblue; colors[c_lightseagreen] = Colours::lightseagreen;
        colors[c_orange] = Colours::orange; colors[c_purple] = Colours::purple;
        colors[c_crimson] = Colours::crimson; colors[c_darkblue] = Colours::darkblue;
        colors[c_cyan] = Colours::cyan; colors[c_darkcyan] = Colours::darkcyan;
        colors[c_darkorange] = Colours::darkorange; colors[c_darkred] = Colours::darkred;
        colors[c_turquoise] = Colours::turquoise; colors[c_darkturquoise] = Colours::darkturquoise;
        colors[c_indianred] = Colours::indianred; colors[c_limegreen] = Colours::limegreen;
        colors[c_orangered] = Colours::orangered; colors[c_springgreen] = Colours::springgreen;
        colors[c_yellowgreen] = Colours::yellowgreen; colors[c_aquamarine] = Colours::aquamarine;
        colors[c_beige] = Colours::beige; colors[c_brown] = Colours::brown;
        colors[c_azure] = Colours::azure; colors[c_coral] = Colours::coral;
        colors[c_darkgrey] = Colours::darkgrey; colors[c_darkslategrey] = Colours::darkslategrey;
        colors[c_lightgrey] = Colours::lightgrey; colors[c_lightsteelblue] = Colours::lightsteelblue;
        colors[c_lime] = Colours::lime; colors[c_slategrey] = Colours::slategrey;
        colors[c_silver] = Colours::silver; colors[c_tan] = Colours::tan;
        colors[c_mediumpurple] = Colours::mediumpurple; colors[c_mediumslateblue] = Colours::mediumslateblue;
        colors[c_forestgreen] = Colours::forestgreen; colors[c_teal] = Colours::teal;
        colors[c_aqua] = Colours::aqua; colors[c_skyblue] = Colours::skyblue;
        colors[c_midnightblue] = Colours::midnightblue; colors[c_sienna] = Colours::sienna;
    };
    
    /**
     Build the Application parameters from the GUIPAR description
     */
    void LayoutBuilder::buildParameters()
    {
        if (firstErrorFound != 0) {
            DBG("buildParameters cancelled because of previous error " << firstErrorFound);
            return;
        }
        DBG("buildParameters" );
        
        if (instructs.size() == 0) { setError(1001); return; } // code ressource missing
        if (pvalueTreeState == nullptr )  { setError(1002); return; } // code ressource missing
        if (allParams == nullptr )  { setError(1003); return; } // code ressource missing
        
        int currSlider, currTButton, currTgButton, currCmbBox;
        
        /** Loop on all "instructions" to find active components
          corresponding to parameters we need to declare
        */
        for (int i=0; i<instructSize; i++)
        {
            int inst = instructs[i];
            int opr = opcode(inst);
            int v = opvalue(inst);
            int vent, lent, pn;
            String componentID;
            switch (opr)
            {
                case kaSlider :
                    if (sliderListSize == 0) { setError(1041); break; } // ressource missing
                    currSlider = (pn = v) - sliderFirst;
                    if (currSlider < 0 || currSlider >= sliderListSize) { setError(104); break; } // invalid slider ID
                    if (pn < 0 || pn >= ParamCount || allParams[pn] != nullptr)
                    {
                        setError(1051); return; // invalid parameter number
                    }
                    componentID = (idStyle == 0) ? String(v) : "Slider" + String(v);
                    DBG("*** Building slider " << componentID << " at : " << i << "    " << currSlider);
                    // Find the param range for this component
                    // DBG("--> 0)");
                    vent = getValEntry(v, defSlidEntry);
                    lent = getStrEntry(v);
                    DBG("--> 0) " << v << " => vent " << vent << " => lent " << lent);
                    // DBG("--> 1) " << getRange(vent).start << " " << getRange(vent).end << " " << getRange(vent).interval << " " << getRange(vent).skew );
                    pvalueTreeState->createAndAddParameter (componentID,   // parameterID
                                                            (lent < 0 ? componentID : getLabel(lent)),   // parameter name
                                                            {},            // parameter label
                                                            getRange(vent), // a NormalisableRange<float>
                                                            getFltDef(vent),  // default value
                                                            nullptr, nullptr); 
                    // DBG("--> 2)");
                    // Create a pointer to the raw value
                    allParams[pn] = pvalueTreeState->getRawParameterValue (componentID);
                    // DBG("--> 3)");
                    DBG("--> 4) " << (long int)(allParams[pn]));
                    break;
                    
                case kaTButton :
                    if (tButtonListSize == 0) { setError(1042); break; } // ressource missing
                    currTButton = (pn = v) - tbuttonsFirst;
                    if (currTButton < 0 || currTButton >= tButtonListSize) { setError(107); break; } // invalid id
                    if (pn < 0 || pn >= ParamCount || allParams[pn] != nullptr)
                    {
                        setError(1052); return; // invalid parameter number
                    }
                    componentID = (idStyle == 0) ? String(v) : "TButtn" + String(v);
                    DBG("*** Building tbutton " << componentID << " at : " << i << "    " << currTButton);
                    vent = getValEntry(v, defTBtnEntry);
                    lent = getStrEntry(v);
                    DBG("--> 0) " << v << " => vent " << vent << " => lent " << lent);
                    pvalueTreeState->createAndAddParameter (componentID,   // parameterID
                                                            (lent < 0 ? componentID : getLabel(lent)),   // parameter name
                                                            {},            // parameter label
                                                            getRange(vent), // a NormalisableRange<float>
                                                            getFltDef(vent),  // default value
                                                            nullptr, nullptr);
                    allParams[pn] = pvalueTreeState->getRawParameterValue (componentID);
                    DBG("--> 4) " << (long int)(allParams[pn]));
                    break;
                    
                case kaTgButton :
                    if (tgButtonListSize == 0) { setError(1043); break; } // ressource missing
                    currTgButton = (pn = v) - tgbuttonsFirst;
                    if (currTgButton < 0 || currTgButton >= tgButtonListSize) { setError(107); break; } // invalid Id
                    if (pn < 0 || pn >= ParamCount || allParams[pn] != nullptr)
                    {
                        setError(1053); return; // invalid parameter number
                    }
                    componentID = (idStyle == 0) ? String(v) : "TgBttn" + String(v);
                    DBG("*** Building tgbutton " << componentID << " at : " << i << "    " << currTgButton);
                    vent = getValEntry(v, defTgBtnEntry);
                    lent = getStrEntry(v);
                    DBG("--> 0) " << v << " => vent " << vent << " => lent " << lent);
                    pvalueTreeState->createAndAddParameter (componentID,   // parameterID
                                                            (lent < 0 ? componentID : getLabel(lent)),   // parameter name
                                                            {},            // parameter label
                                                            getRange(vent), // a NormalisableRange<float>
                                                            getFltDef(vent),  // default value
                                                            nullptr, nullptr);
                    allParams[pn] = pvalueTreeState->getRawParameterValue (componentID);
                    DBG("--> 4) " << (long int)(allParams[pn]));
                    break;
                    
                case kaCmbBox :
                    if (cmbBoxListSize == 0) { setError(1044); break; } // ressource missing
                    currCmbBox = (pn = v) - cmbBoxFirst;
                    if (currCmbBox < 0 || currCmbBox >= cmbBoxListSize) { setError(108); break; } // invalid Id
                    if (pn < 0 || pn >= ParamCount || allParams[pn] != nullptr)
                    {
                        setError(1054); return; // invalid parameter number
                    }
                    componentID = (idStyle == 0) ? String(v) : "CmbBox" + String(v);
                    DBG("*** Building comboBox " << componentID << " at : " << i << "    " << currCmbBox);
                    vent = getValEntry(v, defTgBtnEntry);
                    lent = getStrEntry(v);
                    DBG("--> 0) " << v << " => vent " << vent << " => lent " << lent);
                    pvalueTreeState->createAndAddParameter (componentID,   // parameterID
                                                            (lent < 0 ? componentID : getLabel(lent)),   // parameter name
                                                            {},            // parameter label
                                                            getRange(vent), // a NormalisableRange<float>
                                                            getFltDef(vent),  // default value
                                                            nullptr, nullptr);
                    allParams[pn] = pvalueTreeState->getRawParameterValue (componentID);
                    DBG("--> 4) " << (long int)(allParams[pn]));
                    break;
                    
                case ksetSldPdef :
                    defSlidEntry = getValEntry(v);
                    break;
                    
                case ksetTbtPdef :
                    defTBtnEntry = getValEntry(v);
                    break;
                    
                case ksetTgbPdef :
                    defTgBtnEntry = getValEntry(v);
                    break;
                    
                default :
                    break;
                    
            }
            if (firstErrorFound != 0) {
                DBG("buildParameters cancelled at : " << i << " because of error " << firstErrorFound);
                return;
            }
            
        }
    };
    /**
     Build an interface 
    */
    void LayoutBuilder::buildLayout(int cmptNumber)
    {
        if (firstErrorFound != 0) {
            DBG("buildLayout cancelled at : " << cmptNumber << " because of previous error " << firstErrorFound);
            return;
        }
        DBG("buildLayout : " << cmptNumber);

        if (cmptNumber < 0 || cmptNumber >= compCount) { setError(1021); return; } // invalid cmpt number
        if (comArray == nullptr || compCount == 0) { setError(1022); return; } // component ressource missing
        Component * currComponent = comArray[cmptNumber];
        if (currComponent == nullptr) { setError(1023); return; } // undefined component
        TypedComponent * tc = dynamic_cast<TypedComponent *> (currComponent);
        if (tc == nullptr) { setError(1025); return; } // component is not a Typed Component
        int cmptType = tc->lcmp;
        switch (cmptType) {
            case type_main :
            case type_stdcmp :
            case type_grpcmp :
                setLayoutDesc(tc->playout, currComponent);
                break;
            case type_cnvs :
                return;
            default :
                setError(1026); return; // unmanaged component
        }
        if (playout == nullptr || instructs.size() == 0) { setError(1031); return; } // layout or code ressource missing
        // Check we have a main LayoutItem for the component
        LayoutItem lyItem = playout->state;
        if (!lyItem.isValid()) { setError(1028); return; } // invalid component Layout Item
        if (playout->getOwningComponent() == nullptr) { setError(1029); return; } // invalid Layout
        int index {-1}, indexmax{-1};
        
        // Detect start and end codes for the object we are looking for
        // DBG("buildLayout 1 " << cmptNumber);
        int cmptStart = findInCode(dc(kstartCmpt, cmptNumber));
        if (cmptStart < 0) { setError(101); return; } // can't fin cmpt start
        int cmptEnd = findInCode(dc(kendCmpt, cmptNumber), cmptStart);
        if (cmptEnd < 0) { setError(102); return; } // can't find cmpt end
        // Do we have a common declarative ?
        int doLoop = 0;
        int dclEnd = -1;
        int dclStart = findInCode(dc(kstartDcl));
        if (dclStart >= 0) dclEnd = findInCode(dc(kendDcl), dclStart);
        if (dclStart >= 0 && dclEnd > 0) doLoop = 1;
        
        // Not sure we need this additional complexity...
        constexpr int locColorsNbr {cSize};
        int curColors[locColorsNbr];
        for (int i=0; i<locColorsNbr; i++)
            curColors[i] = i; // which color to use ?
        
        // We accept some levels of nesting
        constexpr int locItemStack {8};
        LayoutItem lItem[locItemStack] {
            {LayoutItem::Unknown}, {LayoutItem::Unknown},
            {LayoutItem::Unknown}, {LayoutItem::Unknown},
            {LayoutItem::Unknown}, {LayoutItem::Unknown},
            {LayoutItem::Unknown}, {LayoutItem::Unknown}
        };
        LayoutItem currItem {LayoutItem::Unknown};
        LayoutItem cmptItem {LayoutItem::Unknown};
        
        // State of the "machine"
        int lItemlev {0};
        lItem[0] = playout->state; // initialize the base Item
        int inst {0};
        int opr, p1, p2, p3, p4, v, s, k;
        int currSlider {0};
        int currLabel {0};
        int currTButton {0};
        int currTgButton {0};
        int currCmbBox {0};
        int currTy {0};
        int currSubTy {0};
        float fv1 {0.0f};
        float fv2 {0.0f};
        String componentID;

        
        for (; doLoop >= 0; doLoop--)
        {
            // We handle common declarations first, then the requested cmpt
            int i;
            if (doLoop != 0) {
                index = dclStart; indexmax = dclEnd;
            } else {
                index = cmptStart; indexmax = cmptEnd;
            }
            for (i = index; i <= indexmax && firstErrorFound==0; i++)
            {
                inst = instructs[i];
                opr = opcode(inst);
                p1 = oppar(inst);
                p2 = opmod(inst);
                v = opvalue(inst);
                // DBG("--> OP. [" << i << "]  " << opr << " " << p1 << " " << p2 << " " << v << " ");
                switch(opr)
                {
                    case kstartCmpt : // Currently equivalent to aRow
                        if (lItemlev != 0) { setError(122); break; } // cmpt description not allowed inside a cmpt
                        if (cmptNumber != v) { setError(123); break; }  // cmpt numbering error
                        ++lItemlev;
                        if (lItemlev >= locItemStack) { setError(132); return; }
                        switch (p1) {
                            case topDown :
                                cmptItem = LayoutItem::makeSubLayout (lItem[lItemlev-1].state, LayoutItem::TopDown);
                                break;
                            case bottomUp :
                                cmptItem = LayoutItem::makeSubLayout (lItem[lItemlev-1].state, LayoutItem::BottomUp);
                                break;
                            case rightToLeft :
                                cmptItem = LayoutItem::makeSubLayout (lItem[lItemlev-1].state, LayoutItem::RightToLeft);
                                break;
                            default :
                                cmptItem = LayoutItem::makeSubLayout (lItem[lItemlev-1].state, LayoutItem::LeftToRight);
                                break;
                        }
                        lItem[lItemlev] = currItem = cmptItem ;
                        currTy = eltCmpt;
                        break;
                        
                    case kendCmpt :
                        lItemlev--;
                        if (lItemlev != 0) { setError(136); return; } // cmpt not allowed inside a cmpt
                        playout->realize (currComponent); //
                        break;
                        
                    case kthisCmpt : // Just to provide a reference to the component being worked on
                        currItem = cmptItem; currTy = eltCmpt;
                        break;
                        
                    case kaCol : // aCol
                        ++lItemlev;
                        if (lItemlev >= locItemStack) { setError(133); return; } // stack full
                        if (p1 == bottomUp)
                            currItem = LayoutItem::makeSubLayout (lItem[lItemlev-1].state, LayoutItem::BottomUp);
                        else
                            currItem = LayoutItem::makeSubLayout (lItem[lItemlev-1].state, LayoutItem::TopDown);
                        lItem[lItemlev] = currItem;  currTy = eltCol;
                        break;
                        
                    case kendCol :
                        currItem = lItem[lItemlev]; currTy = eltCol;
                        lItemlev--;
                        if (lItemlev <= 0) { setError(137); return; } // stack empty
                        break;
                        
                    case kaRow :
                        ++lItemlev;
                        if (lItemlev >= locItemStack) { setError(134); return; } // stack full
                        if (p1 == rightToLeft)
                            currItem = LayoutItem::makeSubLayout (lItem[lItemlev-1].state, LayoutItem::RightToLeft);
                        else
                            currItem = LayoutItem::makeSubLayout (lItem[lItemlev-1].state, LayoutItem::LeftToRight);
                        lItem[lItemlev] = currItem; currTy = eltRow;
                        break;
                        
                    case kendRow :
                        currItem = lItem[lItemlev]; currTy = eltRow;
                        lItemlev--;
                        if (lItemlev <= 0) { setError(138); return; } // stack empty
                        break;
                        
                    case kaSpace :
                        currItem = LayoutItem::makeChildSpacer (lItem[lItemlev].state, fvalue1(inst), fvalue2(inst));
                        currTy = eltSpace;
                        break;
                        
                    case kaLine :
                        setError(139); // Not available
                        break;
                        
                    case kaSplitter :
                        currItem = LayoutItem::makeChildSplitter (lItem[lItemlev].state, fvalue1(inst));
                        currTy = eltSplitter;
                        break;
                        
                    case kaSlider :
                        // "allocate a slider" and initialize it
                        if (sliderList == nullptr || sliderListSize == 0) { setError(1032); break; } // ressource missing
                        currSlider = v - sliderFirst;
                        if (currSlider < 0 || currSlider >= sliderListSize) { setError(104); break; } // invalid slider ID
                        componentID = (idStyle == 0) ? String(v) : "Slider" + String(v);
                        if (p1 < 0 || p1 >= sizeof(sliderTypes)) p1 = 0;
                        p3 = p2 & 0xf ; // last 4 bits are digit decimal count (0 to 14, 15 means "use default" which is 3)
                        DBG("*** Building Slider " << currSlider << " as " << componentID);
                        sliderList[currSlider].setComponentID (componentID);
                        sliderList[currSlider].setSliderStyle (sliderTypes[p1]);
                        p4 = (p2 >> 4) & 0xf ; p4 = p4 > 5 ? 0 : p4;
                        sliderList[currSlider].setTextBoxStyle (sliderTxtBoxpos[p4], false, 80, 16);
                        // DBG("       DD = " << (p3 == stdDD ? defaultDecimalDigits : p3) << "  [" << p3 << "," << defaultDecimalDigits << "]");
                        sliderList[currSlider].setNumDecimalPlacesToDisplay(p3 == stdDD ? defaultDecimalDigits : p3);
                        currComponent->addAndMakeVisible (sliderList[currSlider]);
                        currItem = LayoutItem::makeChildComponent (lItem[lItemlev].state, &sliderList[currSlider]);
                        currTy = eltSlider;
                        currSubTy = p1;
                        // Set Min & Max values for 2/3 values sliders
                        if (p1 == lin2H || p1 == lin2V || p1 == lin3H || p1 == lin3V)
                        {
                            double mv = sliderList[currSlider].getMaximum();
                            sliderList[currSlider].setMaxValue(mv, NotificationType::dontSendNotification, false);
                            DBG("       Slider2/3V " << mv);
                        }   
                        // Should we attach the slider in the value tree ?
                        if (slAttchList != nullptr && pvalueTreeState != nullptr)
                        {
                            DBG("*** Attaching slider " << componentID);
                            slAttchList[currSlider].reset (new SliderAttachment (* pvalueTreeState, componentID, sliderList[currSlider]));
                        }
                        break;
                        
                    case kwithLabel : // Attach a label to a component -- for now, just for sliders...
                        if (currTy != eltSlider) { setError(144); break; } // wrong sequence
                        if (labelList == nullptr || labelListSize == 0) { setError(1035); break; } // ressource missing
                        if (nextLab >= labelListSize) { setError(105); break; } // ressource exhausted
                        currLabel = nextLab++;
                        labelList[currLabel].setComponentID ("Label" + String(v));
                        labelList[currLabel].setText(getLabel(getStrEntry(v)), dontSendNotification);
                        currComponent->addAndMakeVisible (labelList[currLabel]);
                        labelList[currLabel].attachToComponent (&sliderList[currSlider], false);
                        DBG("==> Label " << v << " to slider "  << currSlider);
                        break;
                        
                    case kaLabel :
                        // "allocate a label" and initialize it
                        if (labelList == nullptr || labelListSize == 0) { setError(1036); break; } // ressource missing
                        if (nextLab >= labelListSize) { setError(106); break; } // ressource exhausted
                        currLabel = nextLab++;
                        componentID = (idStyle == 0) ? String(v) : "Label" + String(currLabel);
                        labelList[currLabel].setComponentID (componentID);
                        labelList[currLabel].setText(getLabel(getStrEntry(v)), dontSendNotification);
                        currComponent->addAndMakeVisible (labelList[currLabel]);
                        currItem = LayoutItem::makeChildComponent (lItem[lItemlev].state, &labelList[currLabel]);
                        currTy = eltLabel;
                        DBG("*** Building Label " << currLabel);
                        break;
                        
                    case kfontFace :
                        //
                        k = getStrEntry(v);
                        if (k <= 0) { setError(1040); break;  }
                        {
                            std::vector<std::string> fd = getStrings(k);
                            if (fd.size() < 3) { setError(1050); break;  }
                            // ex: { "Charter", "Bold Italic", "24.0" }
                            Font ft {fd[0], fd[1], String(fd[2]).getFloatValue()};
                            if (currTy != eltLabel) { setError(1056); break; }
                            labelList[currLabel].setFont(ft);
                            DBG("*** Label " << currLabel << " set to " << fd[0] + " " + fd[1]);
                        }
                        break;
                        
                    case kfontStyle :
                        if (currTy != eltLabel) { setError(1057); break; }
                        {
                            Font ft = labelList[currLabel].getFont(); // get current font
                            if (p1 != 0) {
                                ft.setBold((p1 & s_bold) != 0);
                                ft.setItalic((p1 & s_italic) != 0);
                                ft.setUnderline((p1 & s_underlined) != 0);
                            }
                            if (p2 > 0 && p2 < j_last) {
                                labelList[currLabel].setJustificationType(justifStyles[p2]);
                            }
                            if (v != 0) { ft.setHeight(fvalue2(inst)); }
                            labelList[currLabel].setFont(ft);
                        }
                        break;
                        
                    case kaTButton :
                        // "allocate a text button" and initialize it
                        if (tButtonList == nullptr || tButtonListSize == 0) { setError(1037); break; } // ressource missing
                        currTButton = v - tbuttonsFirst;
                        if (currTButton < 0 || currTButton >= tButtonListSize) { setError(107); break; } // invalid id
                        componentID = (idStyle == 0) ? String(v) : "TButtn" + String(v);
                        tButtonList[currTButton].setComponentID(componentID);
                        tButtonList[currTButton].setButtonText(getLabel(getStrEntry(v)));
                        if (opvalue2(inst) & tgB) // set button as "toggle"
                            tButtonList[currTButton].setClickingTogglesState(true);
                        currComponent->addAndMakeVisible (tButtonList[currTButton]);
                        currItem = LayoutItem::makeChildComponent (lItem[lItemlev].state, &tButtonList[currTButton]);
                        currTy = eltTButton;
                        DBG("*** Building TB Label " << currTButton);
                        // Should we attach the button in the value tree ?
                        if (tbAttchList != nullptr && pvalueTreeState != nullptr)
                        {
                            DBG("*** Attaching TButton " << componentID);
                            tbAttchList[currTButton].reset (new ButtonAttachment (* pvalueTreeState, componentID, tButtonList[currTButton]));
                        }
                        break;
                        
                    case kaTgButton :
                        // "allocate a toggle button" and initialize it
                        if (tgButtonList == nullptr || tgButtonListSize == 0) { setError(1038); break; } // ressource missing
                        currTgButton = v - tgbuttonsFirst;
                        if (currTgButton < 0 || currTgButton >= tgButtonListSize) { setError(108); break; } // invalid ID
                        componentID = (idStyle == 0) ? String(v) : "TgBttn" + String(v);
                        tgButtonList[currTgButton].setButtonText(getLabel(getStrEntry(v)));
                        currComponent->addAndMakeVisible (tgButtonList[currTgButton]);
                        currItem = LayoutItem::makeChildComponent (lItem[lItemlev].state, &tgButtonList[currTgButton]);
                        currTy = eltTgButton;
                        DBG("*** Building TgB Label " << currTgButton);
                        // Should we attach the button in the value tree ?
                        if (tgAttchList != nullptr && pvalueTreeState != nullptr)
                        {
                            DBG("*** Attaching TgButton " << componentID);
                            tgAttchList[currTgButton].reset (new ButtonAttachment (* pvalueTreeState, componentID, tgButtonList[currTgButton]));
                        }
                    break;
                    
                    case kaCmbBox :
                        if (cmbBoxList == nullptr || cmbBoxListSize == 0) { setError(1039); break; } // ressource missing
                        currCmbBox = v - cmbBoxFirst;
                        if (currCmbBox < 0 || currCmbBox >= cmbBoxListSize) { setError(109); break; } // invalid ID
                        componentID = (idStyle == 0) ? String(v) : "CmbBox" + String(v);
                        cmbBoxList[currCmbBox].setTextWhenNothingSelected(getLabel(getStrEntry(v)));
                        currComponent->addAndMakeVisible (cmbBoxList[currCmbBox]);
                        s = opvalue2(inst);
                        k = getStrEntry(s);
                        if (k > 0)
                        {
                            DBG("*** Building ComboBox menu from " << k);
                            int i=1;
                            for (auto str : getStrings(k))
                            {
                                cmbBoxList[currCmbBox].addItem (str, i++);
                            }
                        }
                        currItem = LayoutItem::makeChildComponent (lItem[lItemlev].state, &cmbBoxList[currCmbBox]);
                        currTy = eltCmbBox;
                        DBG("*** Building ComboBox Label " << currCmbBox << " " << getLabel(getStrEntry(v)));
                        if (cmbBAttchList != nullptr && pvalueTreeState != nullptr)
                        {
                            DBG("*** Attaching ComboBox " << componentID);
                            cmbBAttchList[currCmbBox].reset (new ComboBoxAttachment (* pvalueTreeState, componentID, cmbBoxList[currCmbBox]));
                        }
                        break;
                        
                    case kaCmpt :
                      {
                        // We add the cmpt as a new child component
                        DBG("-- inserting component " << v);
                        if (v < 0 || v >= compCount) { setError(1041); return; } // incorrect cmpt number
                        Component * theCmpt = comArray[v];
                        if (theCmpt == nullptr) { setError(1043); return; } // cmpt not defined
                        DBG("building component at level" << lItemlev);
                        currComponent->addAndMakeVisible(theCmpt);
                        currItem = LayoutItem::makeChildComponent (lItem[lItemlev].state, theCmpt);
                        currTy = eltICmpt;
                      }
                        break;
                        
                    case kframeLab :
                      {
                        if (tc -> lcmp != type_grpcmp) { setError(1033); break;  } // ressource missing
                        LayedGroupComponent * grcp = dynamic_cast<LayedGroupComponent *> (currComponent);
                        if (grcp == nullptr) { setError(1034); break; } // ressource missing
                        p1 = (p1 == 0) ? curColors[c_A] : p1;
                        p2 = (p2 == 0) ? p1 : p2;
                        if (v != 0)
                        {
                            grcp->setTextLabelPosition (Justification::centred);
                            if (stringSetSize != 0) {
                                grcp->setText (getLabel(getStrEntry(v)));
                            }
                            grcp->setColour (GroupComponent::textColourId, theColor(p1)); // text color
                        }
                        grcp->setColour (GroupComponent::outlineColourId, theColor(p2));  // frame color
                      }
                        break;
                        
                    case ksetCol :
                        // Select a different local color
                        if (v >= 0 && v < cSize && p1 >= 0 && p1 < locColorsNbr) {
                            curColors[p1] = v; // choose "v" as current color "c_x"
                        }
                        break;
                        
                    case kdefCol : case kdefCol+1 : case kdefCol+2 : case kdefCol+3 :
                    case kdefCol+4 : case kdefCol+5 : case kdefCol+6 : case kdefCol+7 :
                    case kdefCol+8 : case kdefCol+9 : case kdefCol+10 : case kdefCol+12 :
                    case kdefCol+13 : case kdefCol+14 : case kdefCol+15 : case kdefCol+16 :
                        colors[opr & 0xF] = Colour(0xFF000000 | (inst & 0xFFFFFF));
                        break;
                        
                    case kpad :
                        if (p1 == top || p1 == vertical || p1 == allDirections)
                            currItem.setPaddingTop(v);
                        if (p1 == bottom || p1 == vertical || p1 == allDirections)
                            currItem.setPaddingBottom(v);
                        if (p1 == left || p1 == horizontal || p1 == allDirections)
                            currItem.setPaddingLeft(v);
                        if (p1 == right || p1 == horizontal || p1 == allDirections)
                            currItem.setPaddingRight(v);
                        break;
                        
                    case kpad2 :
                        currItem.setPaddingTop(p1);
                        currItem.setPaddingBottom(p2);
                        currItem.setPaddingLeft(opvalue3(inst));
                        currItem.setPaddingRight(opvalue4(inst));
                        break;
                        
                    case ksetHeight :
                        if (v > 0) { currItem.setMaximumHeight(v); }
                        v = opvalue2(inst);
                        if (v > 0) { currItem.setMinimumHeight(v); }
                        break;
                        
                    case ksetWidth :
                        if (v > 0) { currItem.setMaximumWidth(v); }
                        v = opvalue2(inst);
                        if (v > 0) { currItem.setMinimumWidth(v); }
                        break;
                        
                    case kfixSize :
                        if (v > 0) { currItem.setMaximumHeight(v); currItem.setMinimumHeight(v); }
                        v = opvalue2(inst);
                        if (v > 0) { currItem.setMaximumWidth(v); currItem.setMinimumWidth(v); }
                        break;
                        
                    case ksetStretch :
                        fv1 = fvalue1(inst); fv1 = (fv1 >= 0.01f) ? fv1 : 1.0f;
                        fv2 = fvalue2(inst); fv2 = (fv2 >= 0.01f) ? fv2 : 1.0f;
                        currItem.setStretch(fv1, fv2);
                        break;
                        
                    case kcolorize :
                        // Colorize the last used element
                        p3 = opvalue3(inst);
                        p4 = opvalue4(inst);
                        switch (currTy) {
                            case eltTButton : // colorize a button
                                if (p1 != 0)
                                    tButtonList[currTButton].setColour (TextButton::textColourOffId, theColor(p1));
                                if (p2 != 0)
                                    tButtonList[currTButton].setColour (TextButton::buttonColourId, theColor(p2));
                                if (p3 != 0)
                                    tButtonList[currTButton].setColour (TextButton::textColourOnId, theColor(p3));
                                if (p4 != 0)
                                    tButtonList[currTButton].setColour (TextButton::buttonOnColourId, theColor(p4));
                                break;
                            case eltSlider :
                                switch (currSubTy) {
                                    default :
                                        if (p1 != 0) // Thumb color
                                            sliderList[currSlider].setColour (Slider::thumbColourId, theColor(p1));
                                        if (p2 != 0) // "active" part of the track
                                            sliderList[currSlider].setColour (Slider::rotarySliderFillColourId, theColor(p2));
                                        if (p3 != 0) // "inactive" part of the track
                                            sliderList[currSlider].setColour (Slider::rotarySliderOutlineColourId, theColor(p3));
                                        if (p4 != 0) // "background" of the text
                                            sliderList[currSlider].setColour (Slider::textBoxBackgroundColourId /* trackColourId */, theColor(p4));
                                        break;
                                    case linH : case linV :
                                    case lin2H : case lin2V :
                                    case lin3H : case lin3V :
                                        if (p1 != 0)
                                            sliderList[currSlider].setColour (Slider::thumbColourId, theColor(p1));
                                        if (p2 != 0)
                                            sliderList[currSlider].setColour (Slider::trackColourId, theColor(p2));
                                        if (p3 != 0)
                                            sliderList[currSlider].setColour (Slider::backgroundColourId, theColor(p3));
                                        if (p4 != 0)
                                            sliderList[currSlider].setColour (Slider::textBoxBackgroundColourId /* trackColourId */, theColor(p4));
                                        break;
                                }
                                break;
                            case eltLabel :
                                if (p1 != 0)
                                    labelList[currLabel].setColour (Label::textColourId, theColor(p1));
                                if (p2 != 0)
                                    labelList[currLabel].setColour (Label::backgroundColourId, theColor(p2));
                                if (p3 != 0)
                                    labelList[currLabel].setColour (Label::textWhenEditingColourId, theColor(p3));
                                if (p4 != 0)
                                    labelList[currLabel].setColour (Label::outlineColourId, theColor(p4));
                                break;
                                
                        }
                        break;
                        
                    case ksetSldPdef :
                        defSlidEntry = getValEntry(v);
                        break;
                        
                    case ksetTbtPdef :
                        defTBtnEntry = getValEntry(v);
                        break;
                        
                    case ksetTgbPdef :
                        defTgBtnEntry = getValEntry(v);
                        break;
                        
                    case knop : // some "do nothing" op codes
                    case kstartDcl :
                    case kendDcl :
                        break;
                        
                    default :
                        setError(111); break; // unknown op code
                }
            }
            if (lItemlev != 0)
            {
                setError(1055);  // invalid code
            }
            if (firstErrorFound != 0)
            {
                DBG("buildLayout error " << firstErrorFound << " ["<< i << " " << inst << "],  at line " << lineErrorFound << " of " << fileErrorFound);
                return;
            }
        }
        // DBG("buildLayout 4 " << i);
    };
};


//==============================================================================


/** Simple component
 */
LayedComponent::LayedComponent (lo::LayoutBuilder * e, int num)
{
    layer = e;
    lgcNum = num;
    lcmp = lo::type_stdcmp;
    playout = new Layout(LayoutItem::LeftToRight, this);
};

LayedComponent::~LayedComponent ()
{
    if (playout != nullptr)
    {
        delete playout;
        playout = nullptr;
    }
};

/**
 This actually builds the contents of the LayedComponent
 It is dissociated from the ctor because somme parameters transmission
 is usually needed before we can use it, and should be executed from the AudioEditor
 */
void LayedComponent::buildIt()
{
    if (tcFlags & 2)
    {
        DBG("*** Building component " << lgcNum);
    }
    if (layer == nullptr)
    {
        DBG("*** undefined component builder"); return;
    }
    layer->setLayoutDesc(playout, this);
    layer->buildLayout(lgcNum);
};


void LayedComponent::paint (Graphics& g)
{
    // DBG("LayedGroupComponent::paint");
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    Component::paint(g); // For whatever is needed by the parent
}

void LayedComponent::paintOverChildren (Graphics& g)
{
    if (tcFlags & 1 && playout != nullptr)
        playout->paintBounds (g);
};

void LayedComponent::resized()
{
    // DBG("LayedGroupComponent::resized");
    if (playout != nullptr)
        playout->updateGeometry ();
}


//==============================================================================


/** A component that do not contains items managed by
  the layout manager.
  The paint and resized methods can be provided by external functions
 */
LayedCanvas::LayedCanvas (lo::LayoutBuilder * e, int num)
{
    layer = e;
    lgcNum = num;
    lcmp = lo::type_cnvs;
    playout = nullptr;
    bgColor = Colours::black;
};

LayedCanvas::~LayedCanvas ()
{
    if (playout != nullptr)
    {
        delete playout;
        playout = nullptr;
    }
};

/**
 This actually builds the contents of the LayedCanvas
 It is dissociated from the ctor because somme parameters transmission
 is usually needed before we can use it, and should be executed from the AudioEditor
 */
void LayedCanvas::buildIt()
{
    if (tcFlags & 2)
    {
        DBG("*** Building LayedCanvas component " << lgcNum);
    }
    if (layer == nullptr)
    {
        DBG("*** undefined LayedCanvas component builder"); return;
    }
    layer->setLayoutDesc(playout, this);
    layer->buildLayout(lgcNum);
};


void LayedCanvas::paint (Graphics& g)
{
    // DBG("LayedCanvas::paint");
    // Call the provided paint function if any
    if (doPaint != nullptr) (*doPaint)(this, lgcNum, g);
}

void LayedCanvas::paintOverChildren (Graphics& g)
{
    if (tcFlags & 1 && playout != nullptr)
        playout->paintBounds (g);
};

void LayedCanvas::resized()
{
    // DBG("LayedCanvas::resized");
    // call the provided resized function if any
    if (doResized != nullptr) (*doResized)(this, lgcNum);
}




//==============================================================================


LayedGroupComponent::LayedGroupComponent (lo::LayoutBuilder * e, int num)
{
    layer = e;
    lgcNum = num;
    lcmp = lo::type_grpcmp;
    playout = new Layout(LayoutItem::LeftToRight, this);
};


LayedGroupComponent::~LayedGroupComponent ()
{
    if (playout != nullptr)
    {
        delete playout;
        playout = nullptr;
    }
};


/**
 This actually builds the contents of the GroupComponent
 It is dissociated from the ctor because somme parameters transmission
 is needed before we can use it
 */
void LayedGroupComponent::buildIt()
{
    if (tcFlags & 2)
    {
        DBG("*** Building group component " << lgcNum);
    }
    if (layer == nullptr)
    {
        DBG("*** undefined component builder"); return;
    }
    layer->setLayoutDesc(playout, this);
    layer->buildLayout(lgcNum);
};


void LayedGroupComponent::paint (Graphics& g)
{
    // DBG("LayedGroupComponent::paint");
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    GroupComponent::paint(g); // For drawing the border and whatever is needed
}

void LayedGroupComponent::paintOverChildren (Graphics& g)
{
    if (tcFlags & 1 && playout != nullptr)
        playout->paintBounds (g);
};


void LayedGroupComponent::resized()
{
    // DBG("LayedGroupComponent::resized");
    if (playout != nullptr)
        playout->updateGeometry ();
}



//==============================================================================


