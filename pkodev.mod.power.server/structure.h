#pragma once

namespace pkodev
{
    // Parameters ending flag for CParser::DoString() call
    const unsigned int DOSTRING_PARAM_END = 999999999;

    // Parameters types for CParser::DoString() call
    enum EScriptParamType
    {
        enumSCRIPT_PARAM_NUMBER = 1,
        enumSCRIPT_PARAM_NUMBER_UNSIGNED,
        enumSCRIPT_PARAM_LIGHTUSERDATA,
        enumSCRIPT_PARAM_STRING,
        enumSCRIPT_PARAM_NUMBER_LONG64,
    };

    // Returns types for CParser::DoString() call
    enum EScriptReturnType
    {
        enumSCRIPT_RETURN_NONE,
        enumSCRIPT_RETURN_NUMBER,
        enumSCRIPT_RETURN_STRING,
    };

    // Power structure
    struct Power
    {
        // Power amount
        unsigned int power;

        // Color (0xFFRRGGBB)
        unsigned int color;


        // Default constructor
        Power() :
            power(0), color(0xFFFFFFFF) { }

        // Constructor
        Power(unsigned int power_, unsigned int color_) :
            power(power_), color(color_) { }
    };
}