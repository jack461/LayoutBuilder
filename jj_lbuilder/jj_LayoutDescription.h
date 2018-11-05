/*
  ==============================================================================

    LayoutDescription.h
    Created: 28 Sep 2018 9:13:25pm
    Author:  Jean-Jacques Girardot

  ==============================================================================
*/

#pragma once
#include <cstring>
#include <ff_layout/ff_layout.h>

#define setError(x) setErrorF ((x), __LINE__, __FILE__)
/**
    This defines the elements of a kind of "bytecode" aimed at
    describing a "simple looking GUI" for plug-ins.
    
    This assumes that an int is at least 32 bits, which will be probably true
    for the next few months on my Mac :-)
*/
static_assert(sizeof(int) >= 4, "Expecting 4 byte ints");

namespace lo {
    // Components ID style
    constexpr int idStyle {1};
    
    // Various opcodes sizes and masks
    constexpr int sizeOP {7}; // 
    constexpr int maskOP {(1<<sizeOP)-1};
    constexpr int sizePar {6};
    constexpr int maskPar {(1<<sizePar)-1};
    constexpr int sizeMod {6};
    constexpr int maskMod {(1<<sizeMod)-1};
    constexpr int sizeValue {12};
    constexpr int maskValue {(1<<sizeValue)-1};
    constexpr int maskXValue {(1<<(sizeValue+sizeMod))-1};
    constexpr int maskXLValue {(1<<(sizeValue+sizeMod+sizePar))-1};
    constexpr int cmptMask { (maskOP << (sizePar+sizeMod+sizeValue)) | maskValue } ;
    
    // The "bytecode" op codes
    enum bytecodesEnum {
        knop=0, kstartCmpt, kendCmpt, kaCol, kendCol, kaRow, kendRow, kaSlider,
        kaLabel, kaTgButton, kaCmpt, kpad, kpad2, kthisCmpt, kframeLab, kaSpace,
        kaCmbBox, kaSplitter, ksetCol, kfontStyle, kfontFace, ksetWidth, ksetHeight, ksetStretch,
        kfixSize, ksetRatio, kaCanvas, kstartDcl, kendDcl, kcolorize, kwithLabel, kaTButton,
        ksetSldPdef, ksetTbtPdef, ksetTgbPdef, kaLine, 
        kdefCol = 112
    };
    
    // Elements classes
    enum eltClassesEnum {
        eltUnknown=0, eltCmpt, eltCol, eltRow, eltSlider, eltLabel, eltTButton, eltTgButton,
        eltCmbBox, eltICmpt, eltSpace, eltSplitter
    };
    
    // Layout directions
    enum directionsEnum {
        topDown, bottomUp, leftToRight, rightToLeft
    };
    
    // Some localizations
    enum localizationsEnum {
        top=1, bottom, left, right, horizontal, vertical, allDirections
    };

    // Default entry marker, none, end...
    constexpr int defaultEntry { 0x7FFE };
    constexpr int none { 0x7FFF };
    

    enum colorsEnum {
        // Alternate numbering for new colors definitions
        c_A=0, c_B, c_C, c_D, c_E, c_F, c_G, c_H, c_I, c_J, c_K, c_L, c_M, c_N, c_O, c_P,
        // some classical JUCE colors
        c_transparentBlack, c_black, c_white, c_red, c_green, c_blue, c_yellow, c_grey,
        c_greenyellow, c_lightblue, c_lightseagreen, c_purple, c_crimson, c_darkblue, c_cyan, c_darkcyan,
        c_orange, c_darkorange, c_darkred, c_turquoise, c_darkturquoise, c_indianred, c_limegreen,
        c_orangered, c_springgreen, c_yellowgreen, c_aquamarine, c_beige, c_brown, c_azure, c_coral,
        c_darkgrey, c_darkslategrey, c_lightgrey, c_lightsteelblue, c_lime, c_slategrey, c_silver, c_tan,
        c_mediumpurple, c_mediumslateblue, c_forestgreen, c_teal, c_aqua, c_skyblue, c_midnightblue, c_sienna

    };
    // Fonts styles
    enum fontStylesEnum {
        s_plain=0, s_bold=1, s_italic=2, s_underlined=4
    };
    
    enum justifStyleEnum {
        j_none=0, j_left, j_right, j_horizontallyCentred, j_top, j_bottom, j_verticallyCentred,
        j_horizontallyJustified, j_centred, j_centredLeft, j_centredRight, j_centredTop,
        j_centredBottom, j_topLeft, j_topRight, j_bottomLeft, j_bottomRight, j_last
    };
    static constexpr Justification::Flags justifStyles[] { Justification::centredLeft, // as default
        Justification::left, Justification::right, Justification::horizontallyCentred, Justification::top, 
        Justification::bottom, Justification::verticallyCentred, Justification::horizontallyJustified, Justification::centred, 
        Justification::centredLeft, Justification::centredRight, Justification::centredTop, Justification::centredBottom, 
        Justification::topLeft, Justification::topRight, Justification::bottomLeft, Justification::bottomRight 
    };
    

    // Components types
    enum compTypesEnum {
        type_main=1, type_stdcmp, type_cnvs, type_grpcmp
    };
    
    // Some useful data
    // Slider related
    static constexpr Slider::SliderStyle sliderTypes[] {  Slider::RotaryHorizontalVerticalDrag, // as default
        Slider::LinearHorizontal, Slider::LinearVertical, Slider::LinearBar, Slider::LinearBarVertical,
        Slider::Rotary, Slider::RotaryVerticalDrag, Slider::RotaryHorizontalDrag,
        Slider::RotaryHorizontalVerticalDrag, Slider::IncDecButtons,
        Slider::TwoValueHorizontal, Slider::TwoValueVertical, Slider::ThreeValueHorizontal,
        Slider::ThreeValueVertical };
    enum sliderStyleEnum { // Aliases for the slider styles
        linH=1, linV, barH, barV, rot, rotVD, rotHD, rotHVD, incDec, lin2H, lin2V, lin3H, lin3V
    };

    static constexpr Slider::TextEntryBoxPosition sliderTxtBoxpos[] { Slider::TextBoxBelow, // as default
        Slider::NoTextBox, Slider::TextBoxLeft, Slider::TextBoxRight, Slider::TextBoxAbove,
        Slider::TextBoxBelow };
    // Aliases for the text box positions
    constexpr int noTB {16};
    constexpr int tBLeft {32};
    constexpr int tBRight {48};
    constexpr int tBAbove {64};
    constexpr int tBBelow {80};
    constexpr int stdDD {15} ; // code for "slider default standard decimal digit count"
    
    constexpr int setSkewCenter { 0x10000 };
    constexpr int setSymSkew { 0x20000 };
    
    // Buttons modes
    constexpr int tgB {0x800}; // set text button as toggle
    
    // Aggregations and extractions
    constexpr int dc(int code, int value=0) { return ((code & maskOP) << (sizePar+sizeMod+sizeValue)) |
        (value & maskXLValue); };
    constexpr int dc(int code, int par, int value) { return ((code & maskOP) << (sizePar+sizeMod+sizeValue)) |
        ((par & maskPar) << (sizeMod+sizeValue)) | (value & maskXValue); };
    constexpr int dc(int code, int par, int mod, int value) {
        return ((code & maskOP) << (sizePar+sizeMod+sizeValue)) |
        ((par & maskPar) << (sizeMod+sizeValue)) | ((mod & maskMod) << (sizeValue)) | (value & maskValue); };
    constexpr int ds(int code, int value1, int value2=0) { return ((code & maskOP) << (sizePar+sizeMod+sizeValue)) |
        ((value1 & maskValue) << sizeValue) | (value2 & maskValue); };
    constexpr int ds(int code, float v1, float v2) { return ds(code, int(0.5f+v1*100.0f), int(0.5f+v2*100.0f)); };
    constexpr int dv(int code, int p1, int p2, int p3, int p4) { return dc(code, p1, p2, ((p3 & maskMod)<<sizeMod)|(p4 & maskMod)); };
    constexpr int defColor(int n, int r, int g, int b) { return ((kdefCol+(n & 0xf)) << 24) | ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff); };
    constexpr int defColor(int n, int val) { return ((kdefCol+(n & 0xf)) << 24) | (val & 0xFFFFFF); };
    
    // Predefined op-codes
    constexpr int startCmpt(int value, int mode=leftToRight) { return dc(kstartCmpt, mode, value); } ;
    constexpr int endCmpt(int value) { return dc(kendCmpt, value); } ;
    constexpr int aRow(int dir=leftToRight, int par2=0) { return dc(kaRow, dir, par2); } ;
    constexpr int endRow(int par=0, int par2=0) { return dc(kendRow, par, par2); } ;
    constexpr int aCol(int dir=topDown, int par2=0) { return dc(kaCol, dir, par2); } ;
    constexpr int endCol(int par=0, int par2=0) { return dc(kendCol, par, par2); } ;
    constexpr int aSlider(int idt, int par1=0, int par2=stdDD, int par3=0) { return dc(kaSlider, par1, par2+par3, idt); } ;
    constexpr int aLabel(int idt, int par1=0, int par2=0) { return dc(kaLabel, par1, par2, idt); } ;
    constexpr int withLabel(int idt, int par1=0, int par2=0) { return dc(kwithLabel, par1, par2, idt); } ;
    constexpr int aTButton(int idt, int par1=0, int par2=0) { return ds(kaTButton, par1+par2, idt); } ;
    constexpr int aCmbBox(int idt, int par1=0, int par2=0) { return ds(kaCmbBox, par1+par2, idt); } ;
    constexpr int theCmpt(int idt, int par1=0, int par2=0) { return dc(kaCmpt, par1, par2, idt); } ;
    constexpr int pad(int wh, int val) { return dc(kpad, wh, 0, val); } ;
    constexpr int pad(int p1, int p2, int p3, int p4=0) { return dv(kpad2, p1, p2, p3, p4); };
    constexpr int thisCmpt() { return dc(kthisCmpt); } ;
    constexpr int frameLab(int idt, int par1=0, int par2=0) { return dc(kframeLab, par1, par2, idt); } ;
    constexpr int setColor(int loc, int col) { return dc(ksetCol, loc, 0, col); } ;
    constexpr int colorize(int p1, int p2=c_transparentBlack, int p3=0, int p4=0) { return dv(kcolorize, p1, p2, p3, p4); };
    constexpr int aTgButton(int idt, int par1=0, int par2=0) { return ds(kaTgButton, par1+par2, idt); } ;
    constexpr int aSpace(float ws=1.0f, float hf=1.0f) { return ds(kaSpace, ws, hf); };
    constexpr int aLine(float ws=1.0f, float hf=1.0f) { return ds(kaLine, ws, hf); };
    constexpr int aSplitter(float ws=0.5f) { return ds(kaSplitter, ws, 0.5f); };
    constexpr int fontStyle(float size=0.0f, int style=0, int just=0) { return dc(kfontStyle, style, just, int(0.5f+size*100.0f)); };
    constexpr int fontFace(int fid) { return dc(kfontFace, fid); };
    constexpr int setWidth(int mi, int ma=0) { return ds(ksetWidth, mi, ma); };
    constexpr int setHeight(int mi, int ma=0) { return ds(ksetHeight, mi, ma); };
    constexpr int fixSize(int w, int h=0) { return ds(kfixSize, w, h); };
    constexpr int setStretch(float mi, float ma=1.0f) { return ds(ksetStretch, mi, ma); };
    constexpr int setRatio(float mi) { return ds(ksetRatio, mi, 0.0f); };
    constexpr int startDcl() { return dc(kstartDcl); } ;
    constexpr int endDcl() { return dc(kendDcl); } ;
    constexpr int setSldPdef(int value) { return dc(ksetSldPdef, value); } ;
    constexpr int setTbtPdef(int value) { return dc(ksetTbtPdef, value); } ;
    constexpr int setTgbPdef(int value) { return dc(ksetTgbPdef, value); } ;
    
    // Access to op-codes parameters
    inline int opcode(int inst) { return inst >> (sizePar+sizeMod+sizeValue); };
    inline int oppar(int inst) { return (inst >> (sizeMod+sizeValue)) & maskPar; };
    inline int opmod(int inst) { return (inst >> sizeValue) & maskMod; };
    inline int opvalue(int inst) { return inst & maskValue; };
    inline int opvalue1(int inst) { return inst & maskValue; };
    inline int opvalue2(int inst) { return (inst >> sizeValue) & maskValue; };
    inline int opvalue3(int inst) { return (inst >> sizePar) & maskPar; };
    inline int opvalue4(int inst) { return inst & maskPar; };
    inline int opXvalue(int inst) { return inst & maskXValue; };
    inline int opXLvalue(int inst) { return inst & maskXLValue; };
    inline float fvalue2(int inst) { return float (inst & maskValue)/100.0f; };
    inline float fvalue1(int inst) { return float ((inst >> sizeValue) & maskValue)/100.0f; };
    
    
    
    
    /** This describes strings that can be used in a plugin
    */
    struct AppStringsDesc {
        int itemId; // An identification
        std::vector<std::string> txts; // A vector of strings
        AppStringsDesc(int pitemId, std::string txt1) :
                    itemId(pitemId), txts({txt1})  { };
        AppStringsDesc(int pitemId, std::string txt1, std::string txt2 ) :
                    itemId(pitemId), txts({txt1,txt2})  { };
        AppStringsDesc(int pitemId, std::string txt1, std::string txt2, std::string txt3 ) :
                    itemId(pitemId), txts({txt1,txt2,txt3})  { };
        AppStringsDesc(int pitemId, std::string txt1, std::string txt2, std::string txt3, std::string txt4 ) :
                    itemId(pitemId), txts({txt1,txt2,txt3,txt4})  { };
        AppStringsDesc(int pitemId, std::vector<std::string> vtxt) :
                    itemId(pitemId), txts(vtxt)  { };
        struct AppStringsDesc& operator=(const struct AppStringsDesc&) = default;
    };
    typedef struct lo::AppStringsDesc ASD;
    
    /** This describes the numeric set of values used in the plugin
     */
     
    struct AppValuesDesc {
        int itemId; // An identification of the parameter
        int itemFlgs; // addt. flags
        float defVal; // default value as float
        NormalisableRange<float> range; // parameter range
        AppValuesDesc(int pitemId, int pitemFlgs, NormalisableRange<float> nrg= NormalisableRange<float>(), float ddefVal=0.0f) :
                    itemId(pitemId), itemFlgs(pitemFlgs), defVal(ddefVal), range(nrg)  { };
        AppValuesDesc(int pitemId, NormalisableRange<float> nrg= NormalisableRange<float>(), float ddefVal=0.0f) :
                    itemId(pitemId), itemFlgs(0), defVal(ddefVal), range(nrg)  { };
        struct AppValuesDesc& operator=(const struct AppValuesDesc&) = default;
    };
    typedef struct lo::AppValuesDesc AVD;

   
    /** The class that can build a layout
    */
    class LayoutBuilder
    {
        
    public:
        LayoutBuilder(AudioProcessorValueTreeState * vts) : pvalueTreeState (vts)
        {
            DBG("****** LayoutBuilder construct -- Version 0.2.1");
            buildAllColors();
            DBG("****** END LayoutBuilder construct");
        };
        ~LayoutBuilder()
        {
            DBG("****** LayoutBuilder destruct");
        };
        
        typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
        typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;
        typedef AudioProcessorValueTreeState::ComboBoxAttachment ComboBoxAttachment;
        
        // Functions transmitting resources references
        void setSliderList(Slider * sL, std::unique_ptr<SliderAttachment> *  sLA, int sLS) {
            sliderList=sL; slAttchList = sLA; sliderListSize=sLS;
        };
        void setSliderCount(int sc=0, int fst=0) { sliderListSize = sc;  sliderFirst = fst; };
        
        void setLabelList(Label * lL, int lLS) {
            labelList=lL; labelListSize=lLS; nextLab=0;
        };
        void setSLabelCount(int ct) { labelListSize = ct;  nextLab=0; };
        
        void setTButtonList(TextButton * li, std::unique_ptr<ButtonAttachment> * tba, int liS) {
            tButtonList=li; tbAttchList=tba; tButtonListSize=liS;
        };
        void setTButtonCount(int ct=0, int fst=0) { tButtonListSize=ct; tbuttonsFirst = fst; };
        
        void setTgButtonList(ToggleButton * li, std::unique_ptr<ButtonAttachment> * tga, int liS) {
            tgButtonList=li; tgAttchList=tga; tgButtonListSize=liS;
        };
        void setTgButtonCount(int ct=0, int fst=0) { tgButtonListSize=ct; tgbuttonsFirst = fst; };
        
        void setCmbBoxList(ComboBox * li, std::unique_ptr<ComboBoxAttachment> * cba, int liS) {
            cmbBoxList=li; cmbBAttchList=cba; cmbBoxListSize=liS;
        };
        void setCmbBoxCount(int ct=0, int fst=0) { cmbBoxListSize=ct; cmbBoxFirst = fst; };
        
        void setStringsSet(std::vector<struct lo::AppStringsDesc> vS);
        
        void setValuesSet(std::vector<struct lo::AppValuesDesc> vS);
        
        void setLayoutDesc(Layout * pl, Component * pe);
        
        void setCompDesc(Component ** cA, int cN) {
            comArray = cA; compCount = cN;
            for (int i=0; i<compCount; i++) comArray[i]=nullptr;
        };
        
        void setCode(std::vector<int> xc);
        void setEditor(Component * me);
        void setProcessor(AudioProcessor * ap) { audioProc = ap; };
        void registerComponent(Component * cmp, int cpnb=-1);
        void setPAddresses(float ** pP, int pc) {
            allParams = pP; ParamCount = pc;
            for (int i=0; i<ParamCount; i++) allParams[i]=nullptr;
        };
        
        // Main entries
        void buildParameters();
        void buildLayout(int cmptNumber);
        
        // Utilities
        int getStrEntry(const int itm, const int def= -1);
        inline std::string getLabel(const int num) { return (stringSetSize > num && num >= 0 && stringSet[num].txts.size() > 0) ? stringSet[num].txts[0] : ""; };
        inline std::string getPName(const int num) { return (stringSetSize > num && num >= 0 && stringSet[num].txts.size() > 0) ? stringSet[num].txts[0] : ""; };
        inline std::string getText(const int num) { return (stringSetSize > num && num >= 0 && stringSet[num].txts.size() > 1) ? stringSet[num].txts[1] : ""; };
        inline std::string getUnits(const int num) { return (stringSetSize > num && num >= 0 && stringSet[num].txts.size() > 2) ? stringSet[num].txts[2] : ""; };
        inline std::vector<std::string> getStrings(const int num) { return (stringSetSize > num && num >= 0) ? stringSet[num].txts : std::vector<std::string>(); };
        inline std::string getString(const int num, const int ns) { return (stringSetSize > num && num >= 0 && stringSet[num].txts.size() > ns) ? stringSet[num].txts[ns] : ""; };
        int getValEntry(const int itm, const int def= -1);
        inline NormalisableRange<float> getRange(const int num) {
            return (valueSetSize > num && num >= 0) ? valueSet[num].range : NormalisableRange<float>(0.0f, 1.0f, 1.0f);
        };
        inline float getFltDef(const int num) { return (valueSetSize > num && num >= 0) ? valueSet[num].defVal : 0.0f; };
        
        int getError() { return firstErrorFound; };
        void clearError() { firstErrorFound = 0; };
        void signalError();
        Colour theColor(int nb) { return ((nb < 0) || (nb >= cSize)) ? colors [0] : colors [nb]; } ;
        void setDefaultDecimalDigits(int d) { if (d >=0 && d < 14) defaultDecimalDigits=d; }
        
    private:
        static constexpr int cSize {64};  // Color table size
        
        void setErrorF (int e, int li=0, const char * fn = nullptr);
        void buildAllColors();
        int findInCode(int pat, int start=0) {
            for (int i=start; i < instructSize ; i++) {
                if ((instructs[i] & cmptMask) == pat) return i;
            }
            return -1;
        }
        
        // All Data
        AudioProcessorValueTreeState * pvalueTreeState;
        
        // Slider set to allocate from
        Slider * sliderList {nullptr};
        std::unique_ptr<SliderAttachment> * slAttchList {nullptr};
        int sliderListSize {0};
        int sliderFirst {0};
        int defSlidEntry {-1}; // default entry for the sliders
        
        // Text buttons
        TextButton * tButtonList {nullptr};
        std::unique_ptr<ButtonAttachment> * tbAttchList {nullptr};
        int tButtonListSize {0};
        int tbuttonsFirst {0};
        int defTBtnEntry {-1}; // default entry for the text buttons
        
        // Toggle buttons
        ToggleButton * tgButtonList {nullptr};
        std::unique_ptr<ButtonAttachment> * tgAttchList {nullptr};
        int tgButtonListSize {0};
        int tgbuttonsFirst {0};
        int defTgBtnEntry {-1}; // default entry for the toggle buttons

        // Combo Boxes
        ComboBox * cmbBoxList {nullptr};
        std::unique_ptr<ComboBoxAttachment> * cmbBAttchList {nullptr};
        int cmbBoxListSize {0};
        int cmbBoxFirst {0};
        int defCmbBoxEntry {-1}; // default entry for the Combo Boxes

        // Label set to allocate from
        Label * labelList {nullptr};
        int labelListSize {0};
        int nextLab {0};  // Labels allocator
        
        // Strings used in the plugin
        int stringSetSize {0};
        std::vector<struct lo::AppStringsDesc> stringSet;
        struct AppStringsDesc itmS {0, ""}; // used for comparisons
        int appSdefEntry {-1};
        
        // Float values used in the plugin
        int valueSetSize {0};
        std::vector<struct lo::AppValuesDesc> valueSet;
        struct AppValuesDesc itmE {0}; // used for comparisons
        int appVdefEntry {-1};
        
        Layout * playout {nullptr};
        Component * edt {nullptr};
        Component * mainEditor {nullptr};
        AudioProcessor * audioProc {nullptr};
        Colour colors [cSize]; // local color table
        
        // const int * instructs {nullptr}; // current byte code
        std::vector<int> instructs;
        int instructSize {0};
        
        Component ** comArray {nullptr};
        int compCount {0};
        
        float ** allParams {nullptr};
        int ParamCount {0};
        
        int firstErrorFound {0};
        int lineErrorFound {0};
        char fileErrorFound [128] ;
        int defaultDecimalDigits {3};
        //
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LayoutBuilder)
    };
};


//==============================================================================

/**
 A virtual class to reference some informations common
 to all layout components
 */
class TypedComponent
{
public:
    virtual ~TypedComponent() { };
    virtual void buildIt()=0;
    inline void setTCFlags(int f) { tcFlags = f; };
protected:
    friend lo::LayoutBuilder;
    lo::LayoutBuilder * layer { nullptr };
    Layout * playout { nullptr };
    int lgcNum {0};  // which group is described
    int lcmp {0}; // kind of component
    int tcFlags {0}; // debug flags
};


/**
   The very basic component, with the typed component interface
*/
class LayedComponent : public Component, public virtual TypedComponent
{
public:
    LayedComponent (lo::LayoutBuilder *, int num);
    ~LayedComponent ();
    void paint (Graphics&) override;
    void paintOverChildren (Graphics&) override;
    void resized() override;
    void buildIt() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LayedComponent)
};


/**
 This class is used to group components like sliders,
 buttons, combobox, etc, inside a GroupComponent
 It receives a description of what it should include,
 and builds it...
 
 It is a standard GroupComponent, with the typed component interface
*/
class LayedGroupComponent : public GroupComponent, public virtual TypedComponent
{
public:
    LayedGroupComponent (lo::LayoutBuilder *, int num);
    ~LayedGroupComponent ();
    void paint (Graphics&) override;
    void paintOverChildren (Graphics&) override;
    void resized() override;
    void buildIt() override;
private:
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LayedGroupComponent)
};

/**
   A simple colored canvas
 */
class LayedCanvas : public Component, public virtual TypedComponent
{
public:
    LayedCanvas (lo::LayoutBuilder *, int num);
    ~LayedCanvas ();
    void paint (Graphics&) override;
    void paintOverChildren (Graphics&) override;
    void resized() override;
    void buildIt() override;
    void setColor(Colour cl) { bgColor = cl; };
    void providePaintMethod(void (*theMethod)(LayedCanvas *, int, Graphics&)) { doPaint = theMethod; } ;
    void provideResizedMethod(void (*theMethod)(LayedCanvas *, int)) { doResized = theMethod; } ;
    Colour bgColor;
private:
    void (*doPaint)(LayedCanvas *, int, Graphics&) = nullptr;
    void (*doResized) (LayedCanvas *, int) = nullptr;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LayedCanvas)
};


