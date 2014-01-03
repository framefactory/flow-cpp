// -----------------------------------------------------------------------------
//  File        CommandManager.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012.11.25 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_COMMANDMANAGER_H
#define FLOWCORE_COMMANDMANAGER_H

#include "FlowCore/Library.h"
#include "FlowCore/SingletonT.h"
#include "FlowCore/String.h"
#include "FlowCore/CommandManagerListener.h"

class FCommand;


// -----------------------------------------------------------------------------
//  Class FCommandManager
// -----------------------------------------------------------------------------

class FLOWCORE_EXPORT FCommandManager : public FSingletonAutoT<FCommandManager>
{
	friend class FSingletonAutoT<FCommandManager>;
	friend class FCommand;

	//  Constructors and destructor ----------------------------------

protected:
	/// Default Constructor.
	FCommandManager();
	/// Virtual destructor.
	virtual ~FCommandManager();

	//  Public commands ----------------------------------------------

public:
	void undo();
	void redo();
	void clearHistory();
	void setCleanState();
	void setHistoryCapacity(size_t historyCapacity);
	void setListener(FCommandManagerListener* pListener);

	//  Public queries -----------------------------------------------

	bool canUndo() const;
	bool canRedo() const;
	const wstring_t& undoCommandName() const;
	const wstring_t& redoCommandName() const;
	bool isDirty() const;

	//  Protected (FCommand) -----------------------------------------

	void addCommand(FCommand* pCommand);

	

	//  Internal functions -------------------------------------------

private:
	void _notifyListener();

	//  Internal data members ----------------------------------------

private:
	typedef std::vector<FCommand*> commandVec_t;
	commandVec_t m_history;
	size_t m_cursor;
	size_t m_historyCapacity;
	size_t m_cleanIndex;

	FCommandManagerListener* m_pListener;

	static const wstring_t s_emptyString;
};
	
// -----------------------------------------------------------------------------

#endif // FLOWCORE_COMMANDMANAGER_H