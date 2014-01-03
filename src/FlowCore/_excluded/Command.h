// -----------------------------------------------------------------------------
//  File        Command.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012.11.25 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_COMMAND_H
#define FLOWCORE_COMMAND_H

#include "FlowCore/Library.h"
#include "FlowCore/Object.h"
#include "FlowCore/Archive.h"
#include "FlowCore/String.h"

#include <ostream>
#include <string>

// -----------------------------------------------------------------------------
//  Class FCommand
// -----------------------------------------------------------------------------

class FLOWCORE_EXPORT FCommand : public FObject
{
	F_DECLARE_ABSTRACT_SERIALIZABLE(FCommand);
	friend class FCommandManager;
	typedef FObject base_t;

	//  Constructors and destructor ----------------------------------

public:
	/// Creates a command with the given name.
	FCommand(const wstring_t& name);
	/// Virtual destructor.
	virtual ~FCommand();

	//  Public commands ----------------------------------------------

public:
	/// Records all state needed for undo and executes the command.
	/// Returns true if the execution operation has been completed successfully.
	bool execute();

	/// Serialization to or from the given archive.
	virtual void serialize(FArchive& ar);

	//  Public queries -----------------------------------------------

	/// Returns the name of the command.
	const wstring_t& name() const { return m_name; }
	/// Returns true if the command has been executed successfully.
	bool isExecuted() const { return m_isExecuted; }
	/// Returns true if the command has been undone successfully.
	bool isUndone() const { return m_isUndone; }
	/// Returns true if the command can be undone. Only undoable commands
	/// are recorded in the command history. Execution of a command that
	/// can't be undone clears the history.
	virtual bool canUndo() const { return true; }

#ifdef FLOW_DEBUG
	/// Writes information about the internal state to the given stream.
	virtual void dump(std::wostream& stream) const;
#endif

	//  Protected (FCommandManager) ----------------------------------

protected:
	/// Reverts the command. Returns true if the undo operation
	/// has been completed successfully.
	bool undo();
	/// Executes the command again after it has been undone.
	bool redo();

	//  Overridables -------------------------------------------------

	/// Called when the command needs to be executed.
	virtual bool onExecute() = 0;
	/// Called when the already executed command needs to be undone.
	virtual bool onUndo() = 0;
	/// Called when a previously undone command needs to be
	/// executed again. The default implementation calls onExecute().
	virtual bool onRedo() { return onExecute(); }

	//  Internal data members ----------------------------------------

private:
	wstring_t m_name;
	bool m_isExecuted;
	bool m_isUndone;
};
	
// -----------------------------------------------------------------------------

#endif // FLOWCORE_COMMAND_H