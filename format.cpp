//----------------------------------------------
// format.cpp
// FSM:       Format
// Context:   FormatContext
// Version:   
// Generated: Donnerstag 09/19/2013 at 22:32:09 MESZ
//


static char _versID[]  = "";

#include "format.h"

//----------------------------------------------
// Definitions of static state objects

//----------------------------------------------
FormatReadingKeyState Format::ReadingKey;
FormatGeneralState Format::General;
FormatReadingPlaceholderState Format::ReadingPlaceholder;
FormatReadingValueState Format::ReadingValue;

//----------------------------------------------
// Default Event Functions

//----------------------------------------------

void FormatState::ReadEqualsSign(Format& s)
  { s.FSMError("ReadEqualsSign", s.GetState().StateName()); }

void FormatState::ReadRightBrace(Format& s)
  { s.FSMError("ReadRightBrace", s.GetState().StateName()); }

void FormatState::ReadLeftBrace(Format& s)
  { s.FSMError("ReadLeftBrace", s.GetState().StateName()); }

void FormatState::ReadComma(Format& s)
  { s.FSMError("ReadComma", s.GetState().StateName()); }

//----------------------------------------------
// The States and their Transitions
//----------------------------------------------

//----------------------------------------------
// ReadingKey Actions and Transitions
//----------------------------------------------

// Starting State: ReadingKey
// Event:          ReadEqualsSign
//
void FormatReadingKeyState::ReadEqualsSign( Format& s )
{

    s.AddKeyAndStartAddingValue();

    // Change the state
    s.SetState(Format::ReadingValue);
}

// Starting State: ReadingKey
// Event:          ReadComma
//
void FormatReadingKeyState::ReadComma( Format& s )
{

    s.AddKeyAndContinue();

    // Change the state
    s.SetState(Format::ReadingKey);
}

// Starting State: ReadingKey
// Event:          ReadLeftBrace
//
void FormatReadingKeyState::ReadLeftBrace( Format& s )
{

    s.LeftBrace();

    // Change the state
    s.SetState(Format::ReadingPlaceholder);
}

// Starting State: ReadingKey
// Event:          ReadRightBrace
//
void FormatReadingKeyState::ReadRightBrace( Format& s )
{

    s.RightBrace();

    // Change the state
    s.SetState(Format::General);
}

//----------------------------------------------
// General Actions and Transitions
//----------------------------------------------

// Starting State: General
// Event:          ReadLeftBrace
//
void FormatGeneralState::ReadLeftBrace( Format& s )
{

    s.LeftBrace();

    // Change the state
    s.SetState(Format::ReadingPlaceholder);
}

//----------------------------------------------
// ReadingPlaceholder Actions and Transitions
//----------------------------------------------

// Starting State: ReadingPlaceholder
// Event:          ReadLeftBrace
//
void FormatReadingPlaceholderState::ReadLeftBrace( Format& s )
{

    s.LeftBrace();

    // Change the state
    s.SetState(Format::ReadingPlaceholder);
}

// Starting State: ReadingPlaceholder
// Event:          ReadRightBrace
//
void FormatReadingPlaceholderState::ReadRightBrace( Format& s )
{

    s.ParsePlaceholder();
    s.RightBrace();

    // Change the state
    s.SetState(Format::General);
}

// Starting State: ReadingPlaceholder
// Event:          ReadComma
//
void FormatReadingPlaceholderState::ReadComma( Format& s )
{

    s.ParsePlaceholder();
    s.StartKey();

    // Change the state
    s.SetState(Format::ReadingKey);
}

//----------------------------------------------
// ReadingValue Actions and Transitions
//----------------------------------------------

// Starting State: ReadingValue
// Event:          ReadRightBrace
//
void FormatReadingValueState::ReadRightBrace( Format& s )
{

    s.AddValue();
    s.RightBrace();

    // Change the state
    s.SetState(Format::General);
}

// Starting State: ReadingValue
// Event:          ReadLeftBrace
//
void FormatReadingValueState::ReadLeftBrace( Format& s )
{

    s.LeftBrace();

    // Change the state
    s.SetState(Format::ReadingPlaceholder);
}

// Starting State: ReadingValue
// Event:          ReadComma
//
void FormatReadingValueState::ReadComma( Format& s )
{

    s.AddValue();

    // Change the state
    s.SetState(Format::ReadingKey);
}

//----------------------------------------------
// State Machine Constructor: Format
//  set Initial State to: General
//
//----------------------------------------------
Format::Format() : itsState(&General)
{
    // Entry functions for: General
}

//  Get version information
//
const char* Format::GetVersion() const
{ return _versID; }

