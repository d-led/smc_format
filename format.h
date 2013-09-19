#ifndef FSM_Format_09_19_2013_22_02_19_H
#define FSM_Format_09_19_2013_22_02_19_H
//----------------------------------------------
// format.h
// FSM:       Format
// Context:   FormatContext
// Version:   
// Generated: Donnerstag 09/19/2013 at 22:02:19 MESZ
//


// Included header files

#include "format_context.h"

// Forward Declarations

class Format;

//----------------------------------------------
// FormatState: The base state class
//----------------------------------------------
class FormatState
{
  public: 
    virtual const char* StateName() const = 0;
    virtual void ReadEqualsSign( Format& );
    virtual void ReadRightBrace( Format& );
    virtual void ReadLeftBrace( Format& );
    virtual void ReadComma( Format& );
};

//----------------------------------------------
// State: ReadingKey
//----------------------------------------------
class FormatReadingKeyState : public FormatState
{
  public: 
    virtual const char* StateName() const
        { return "ReadingKey"; }
    virtual void ReadComma( Format& );
    virtual void ReadLeftBrace( Format& );
    virtual void ReadEqualsSign( Format& );
    virtual void ReadRightBrace( Format& );
};
//----------------------------------------------
// State: General
//----------------------------------------------
class FormatGeneralState : public FormatState
{
  public: 
    virtual const char* StateName() const
        { return "General"; }
    virtual void ReadLeftBrace( Format& );
};
//----------------------------------------------
// State: ReadingPlaceholder
//----------------------------------------------
class FormatReadingPlaceholderState : public FormatState
{
  public: 
    virtual const char* StateName() const
        { return "ReadingPlaceholder"; }
    virtual void ReadRightBrace( Format& );
    virtual void ReadComma( Format& );
    virtual void ReadLeftBrace( Format& );
};
//----------------------------------------------
// State: ReadingValue
//----------------------------------------------
class FormatReadingValueState : public FormatState
{
  public: 
    virtual const char* StateName() const
        { return "ReadingValue"; }
    virtual void ReadComma( Format& );
    virtual void ReadRightBrace( Format& );
    virtual void ReadLeftBrace( Format& );
};
//----------------------------------------------
// Format: The Finite State Machine class
//----------------------------------------------
class Format: public FormatContext
{
  public: 
    // Static State variables
    static FormatReadingKeyState ReadingKey;
    static FormatGeneralState General;
    static FormatReadingPlaceholderState ReadingPlaceholder;
    static FormatReadingValueState ReadingValue;

    Format(); // default Constructor

    // Event functions
    virtual void ReadEqualsSign() { itsState->ReadEqualsSign( *this ); }
    virtual void ReadRightBrace() { itsState->ReadRightBrace( *this ); }
    virtual void ReadLeftBrace() { itsState->ReadLeftBrace( *this ); }
    virtual void ReadComma() { itsState->ReadComma( *this ); }

    // State Accessor functions
    void SetState( FormatState& theState ) { itsState = &theState; }
    FormatState& GetState() const { return *itsState; }

    const char* GetCurrentStateName() const { return itsState->StateName(); }
    const char* GetVersion() const;

  private: 
    FormatState* itsState;
};

#endif /* FSM_Format_09_19_2013_22_02_19_H */
