// -----------------------------------------------------------------------------
//  File        Command.cpp
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012.11.25 $
// -----------------------------------------------------------------------------

#include "FlowCore/Command.h"
#include "FlowCore/CommandManager.h"
#include "FlowCore/MemoryTracer.h"

// -----------------------------------------------------------------------------
//  Class FCommand
// -----------------------------------------------------------------------------

F_IMPLEMENT_ABSTRACT_SERIALIZABLE(FCommand, base_t);

// Constructors and destructor -------------------------------------------------

FCommand::FCommand(const wstring_t& name)
: m_name(name),
  m_isExecuted(false),
  m_isUndone(false)
{
}

FCommand::~FCommand()
{
}

// Public commands -------------------------------------------------------------

bool FCommand::execute()
{
	F_ASSERT(!m_isExecuted && !m_isUndone);

	m_isExecuted = onExecute();

	if (m_isExecuted && canUndo())
		FCommandManager::instance()->addCommand(this);
	else
		FCommandManager::instance()->clearHistory();

	return m_isExecuted;
}

bool FCommand::undo()
{
	F_ASSERT(canUndo());
	F_ASSERT(m_isExecuted && !m_isUndone);

	bool result = onUndo();
	if (result)
	{
		m_isExecuted = false;
		m_isUndone = true;
	}

	return result;
}

bool FCommand::redo()
{
	F_ASSERT(m_isUndone && !m_isExecuted);
	
	bool result = onRedo();
	if (result)
	{
		m_isExecuted = true;
		m_isUndone = false;
	}

	return result;
}

void FCommand::serialize(FArchive& ar)
{
	// base_t::serialize(ar);

	if (ar.isWriting())
	{
		ar << m_name;
		ar << m_isExecuted;
	}
	else // is reading
	{
		ar >> m_name;
		ar >> m_isExecuted;
	}
}

// Public queries --------------------------------------------------------------

#ifdef FLOW_DEBUG
void FCommand::dump(std::wostream& stream) const
{
	base_t::dump(stream);
	stream << "\n--- FCommand ---";
	stream << "\n     Name:     " << m_name;
	stream << "\n     Executed: " << m_isExecuted;
	stream << "\n     Can Undo: " << canUndo();
}
#endif

// -----------------------------------------------------------------------------