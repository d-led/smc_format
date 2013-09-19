//----------------------------------------------
// format.cpp
// FSM:       Format
// Context:   FormatContext
// Version:   
// Generated: Donnerstag 09/19/2013 at 21:36:00 MESZ
//


static char _versID[]  = "";

#include "format.h"

//----------------------------------------------
// Definitions of static state objects

//----------------------------------------------
FormatGeneralState Format::General;
FormatReadingPlaceholderState Format::ReadingPlaceholder;

//----------------------------------------------
// Default Event Functions

//----------------------------------------------

void FormatState::ReadRightBrace(Format& s)
  { s.FSMError("ReadRightBrace", s.GetState().StateName()); }

void FormatState::ReadLeftBrace(Format& s)
  { s.FSMError("ReadLeftBrace", s.GetState().StateName()); }

//----------------------------------------------
// The States and their Transitions
//----------------------------------------------

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

    s.RightBrace();

    // Change the state
    s.SetState(Format::General);
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

