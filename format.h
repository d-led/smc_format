#ifndef FSM_FormatParser_09_20_2013_20_00_04_H
#define FSM_FormatParser_09_20_2013_20_00_04_H
//----------------------------------------------
// format.h
// FSM:       FormatParser
// Context:   FormatContext
// Version:   
// Generated: Freitag 09/20/2013 at 20:00:04 MESZ
//


// Included header files

#include "format_context.h"

///BEGIN FORMAT H///

// Forward Declarations

class FormatParser;

//----------------------------------------------
// FormatParserState: The base state class
//----------------------------------------------
class FormatParserState
{
  public: 
    virtual const char* StateName() const = 0;
    virtual void ReadEqualsSign( FormatParser& );
    virtual void ReadRightBrace( FormatParser& );
    virtual void ReadLeftBrace( FormatParser& );
    virtual void ReadComma( FormatParser& );
};

//----------------------------------------------
// State: ReadingKey
//----------------------------------------------
class FormatParserReadingKeyState : public FormatParserState
{
  public: 
    virtual const char* StateName() const
        { return "ReadingKey"; }
    virtual void ReadComma( FormatParser& );
    virtual void ReadLeftBrace( FormatParser& );
    virtual void ReadEqualsSign( FormatParser& );
    virtual void ReadRightBrace( FormatParser& );
};
//----------------------------------------------
// State: General
//----------------------------------------------
class FormatParserGeneralState : public FormatParserState
{
  public: 
    virtual const char* StateName() const
        { return "General"; }
    virtual void ReadLeftBrace( FormatParser& );
};
//----------------------------------------------
// State: ReadingPlaceholder
//----------------------------------------------
class FormatParserReadingPlaceholderState : public FormatParserState
{
  public: 
    virtual const char* StateName() const
        { return "ReadingPlaceholder"; }
    virtual void ReadRightBrace( FormatParser& );
    virtual void ReadComma( FormatParser& );
    virtual void ReadLeftBrace( FormatParser& );
};
//----------------------------------------------
// State: ReadingValue
//----------------------------------------------
class FormatParserReadingValueState : public FormatParserState
{
  public: 
    virtual const char* StateName() const
        { return "ReadingValue"; }
    virtual void ReadComma( FormatParser& );
    virtual void ReadRightBrace( FormatParser& );
    virtual void ReadLeftBrace( FormatParser& );
};
//----------------------------------------------
// FormatParser: The Finite State Machine class
//----------------------------------------------
class FormatParser: public FormatContext
{
  public: 
    // Static State variables
    static FormatParserReadingKeyState ReadingKey;
    static FormatParserGeneralState General;
    static FormatParserReadingPlaceholderState ReadingPlaceholder;
    static FormatParserReadingValueState ReadingValue;

    FormatParser(); // default Constructor

    // Event functions
    virtual void ReadEqualsSign() { itsState->ReadEqualsSign( *this ); }
    virtual void ReadRightBrace() { itsState->ReadRightBrace( *this ); }
    virtual void ReadLeftBrace() { itsState->ReadLeftBrace( *this ); }
    virtual void ReadComma() { itsState->ReadComma( *this ); }

    // State Accessor functions
    void SetState( FormatParserState& theState ) { itsState = &theState; }
    FormatParserState& GetState() const { return *itsState; }

    const char* GetCurrentStateName() const { return itsState->StateName(); }
    const char* GetVersion() const;

  private: 
    FormatParserState* itsState;
};

///END FORMAT H///

#endif /* FSM_FormatParser_09_20_2013_20_00_04_H */
