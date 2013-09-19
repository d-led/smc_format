#ifndef FSM_Format_09_19_2013_21_48_54_H
#define FSM_Format_09_19_2013_21_48_54_H
//----------------------------------------------
// format.h
// FSM:       Format
// Context:   FormatContext
// Version:   
// Generated: Donnerstag 09/19/2013 at 21:48:54 MESZ
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
    virtual void ReadLeftBrace( Format& );
    virtual void ReadRightBrace( Format& );
    virtual void ReadComma( Format& );
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

    Format(); // default Constructor

    // Event functions
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

#endif /* FSM_Format_09_19_2013_21_48_54_H */
