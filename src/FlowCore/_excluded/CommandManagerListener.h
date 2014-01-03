// -----------------------------------------------------------------------------
//  File        CommandManagerListener.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/02 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_COMMANDMANAGERLISTENER_H
#define FLOWCORE_COMMANDMANAGERLISTENER_H

#include "FlowCore/Library.h"

// -----------------------------------------------------------------------------
//  Interface FCommandManagerListener
// -----------------------------------------------------------------------------

class FCommandManagerListener
{
public:
	virtual ~FCommandManagerListener() { }

	virtual void historyStateChanged(const wstring_t& undoCommand,
		const wstring_t& redoCommand, bool isDirty) = 0;
};

// -----------------------------------------------------------------------------

#endif // FLOWCORE_COMMANDMANAGERLISTENER_H