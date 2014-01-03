// -----------------------------------------------------------------------------
//  File        LogType.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/10/17 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_LOGTYPE_H
#define FLOWCORE_LOGTYPE_H

#include "FlowCore/Library.h"

// -----------------------------------------------------------------------------
//  Class FLogType
// -----------------------------------------------------------------------------

class FLogType
{
	//  Public enumerations ------------------------------------------

public:
	enum state_t
	{
		Trace,
		Debug,
		Info,
		Warning,
		Critical,
		Fatal,
		All
	};

	//  Constructors and destructor ----------------------------------

	FLogType() : m_state(Info) { }
	FLogType(state_t state) : m_state(state) { }

	//  Public methods -----------------------------------------------

	operator state_t() const { return m_state; }

	bool operator==(FLogType rhs) const { return m_state == rhs.m_state; }
	bool operator!=(FLogType rhs) const { return m_state != rhs.m_state; }

	bool operator==(state_t state) const { return m_state == state; }
	bool operator!=(state_t state) const { return m_state != state; }

	/// Returns the name of the current state.
	const char* name() const;

	//  Internal data members ----------------------------------------

private:
	state_t m_state;
};

// -----------------------------------------------------------------------------

#endif // FLOWCORE_LOGTYPE_H