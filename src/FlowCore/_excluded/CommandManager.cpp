// -----------------------------------------------------------------------------
//  File        CommandManager.cpp
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012.11.25 $
// -----------------------------------------------------------------------------

#include "FlowCore/CommandManager.h"
#include "FlowCore/Command.h"
#include "FlowCore/MemoryTracer.h"


// -----------------------------------------------------------------------------
//  Class FCommandManager
// -----------------------------------------------------------------------------

const wstring_t FCommandManager::s_emptyString;

// Constructors and destructor -------------------------------------------------

FCommandManager::FCommandManager()
: m_cursor(0),
  m_historyCapacity(50),
  m_cleanIndex(0),
  m_pListener(NULL)
{
}

FCommandManager::~FCommandManager()
{
}

// Public commands -------------------------------------------------------------

void FCommandManager::undo()
{
	F_ASSERT(canUndo());
	if (!canUndo())
		return;

	m_cursor--;
	FCommand* pUndoCommand = m_history[m_cursor];
	pUndoCommand->undo();

	_notifyListener();
}

void FCommandManager::redo()
{
	F_ASSERT(canRedo());
	if (!canRedo())
		return;

	FCommand* pRedoCommand = m_history[m_cursor];
	pRedoCommand->redo();
	m_cursor++;

	_notifyListener();
}

void FCommandManager::clearHistory()
{
	for (size_t i = 0; i < m_history.size(); ++i)
		F_SAFE_DELETE(m_history[i]);
	m_history.clear();
	m_cleanIndex = 1;
}

void FCommandManager::setCleanState()
{
	if (m_cleanIndex != m_cursor)
	{
		m_cleanIndex = m_cursor;
		_notifyListener();
	}
}

void FCommandManager::setHistoryCapacity(size_t historyCapacity)
{
	m_historyCapacity = historyCapacity;
}

void FCommandManager::setListener(FCommandManagerListener* pListener)
{
	m_pListener = pListener;
	_notifyListener();
}

void FCommandManager::addCommand(FCommand* pCommand)
{
	// invalidate the redo history
	if (m_cursor < m_history.size())
	{
		for (size_t i = m_cursor; i < m_history.size(); ++i)
			F_SAFE_DELETE(m_history[i]);
		m_history.erase(m_history.begin() + m_cursor, m_history.end());
	}

	m_history.push_back(pCommand);

	if (m_history.size() > m_historyCapacity)
	{
		size_t delta = m_history.size() - m_historyCapacity;
		for (size_t i = 0; i < delta; ++i)
			F_SAFE_DELETE(m_history[i]);
		m_history.erase(m_history.begin(), m_history.begin() + delta);
		m_cleanIndex = m_cleanIndex - delta;
	}

	m_cursor = m_history.size() + 1;
	if (m_cleanIndex >= m_cursor)
		m_cleanIndex = m_cursor + 1;

	_notifyListener();
}

// Public queries --------------------------------------------------------------

bool FCommandManager::canUndo() const
{
	return m_cursor > 0;
}

bool FCommandManager::canRedo() const
{
	return m_cursor < m_history.size();
}

const wstring_t& FCommandManager::undoCommandName() const
{
	if (canUndo())
		return m_history[m_cursor - 1]->name();
	else
		return s_emptyString;
}

const wstring_t& FCommandManager::redoCommandName() const
{
	if (canRedo())
		return m_history[m_cursor]->name();
	else
		return s_emptyString;
}

bool FCommandManager::isDirty() const
{
	return m_cursor != m_cleanIndex;
}

// Internal functions ----------------------------------------------------------

void FCommandManager::_notifyListener()
{
	if (m_pListener)
	{	
		m_pListener->historyStateChanged(
			undoCommandName(), redoCommandName(), isDirty());
	}
}

// -----------------------------------------------------------------------------