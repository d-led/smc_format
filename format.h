#ifndef FSM_Format_09_19_2013_21_36_00_H
#define FSM_Format_09_19_2013_21_36_00_H
//----------------------------------------------
// format.h
// FSM:       Format
// Context:   FormatContext
// Version:   
// Generated: Donnerstag 09/19/2013 at 21:36:00 MESZ
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
};
//----------------------------------------------
// Format: The Finite State Machine class
//----------------------------------------------
class Format: public FormatContext
{
  public: 
    // Static State variables
    static FormatGeneralState General;
    static FormatReadingPlaceholderState ReadingPlaceholder;

    Format(); // default Constructor

    // Event functions
    virtual void ReadRightBrace() { itsState->ReadRightBrace( *this ); }
    virtual void ReadLeftBrace() { itsState->ReadLeftBrace( *this ); }

    // State Accessor functions
    void SetState( FormatState& theState ) { itsState = &theState; }
    FormatState& GetState() const { return *itsState; }

    const char* GetCurrentStateName() const { return itsState->StateName(); }
    const char* GetVersion() const;

  private: 
    FormatState* itsState;
};

#endif /* FSM_Format_09_19_2013_21_36_00_H */
