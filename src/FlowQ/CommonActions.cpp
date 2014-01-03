// -----------------------------------------------------------------------------
//  File        CommonActions.cpp
//  Project     FlowQ
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/02 $
// -----------------------------------------------------------------------------

#include <QAction>

#include "FlowQ/CommonActions.h"
#include "FlowCore/CommandManager.h"
#include "FlowCore/MemoryTracer.h"



// -----------------------------------------------------------------------------
//  Class FCommonActions
// -----------------------------------------------------------------------------

// Constructors and destructor -------------------------------------------------

FCommonActions::FCommonActions(QWidget* pParent)
	: m_pParent(pParent)
{
	F_ASSERT(pParent);
	_createCommonActions();
	
	FCommandManager::instance()->setListener(this);
}

FCommonActions::~FCommonActions()
{
	FCommandManager::instance()->setListener(NULL);

	F_SAFE_DELETE(m_pActUndo);
	F_SAFE_DELETE(m_pActRedo);
	F_SAFE_DELETE(m_pActCut);
	F_SAFE_DELETE(m_pActCopy);
	F_SAFE_DELETE(m_pActPaste);
	F_SAFE_DELETE(m_pActDuplicate);
	F_SAFE_DELETE(m_pActDelete);
}

// Public commands -------------------------------------------------------------




// Overrides -------------------------------------------------------------------

void FCommonActions::historyStateChanged(const wstring_t& undoCommand,
	const wstring_t& redoCommand, bool isDirty)
{
	if (!undoCommand.empty())
	{
		m_pActUndo->setText(QString("Undo ") + QString::fromStdWString(undoCommand));
		m_pActUndo->setEnabled(true);
	}
	else
	{
		m_pActUndo->setText("Undo");
		m_pActUndo->setEnabled(false);
	}

	if (!redoCommand.empty())
	{
		m_pActRedo->setText(QString("Redo ") + QString::fromStdWString(redoCommand));
		m_pActRedo->setEnabled(true);
	}
	else
	{
		m_pActRedo->setText("Redo");
		m_pActRedo->setEnabled(false);
	}
}

// Slots -----------------------------------------------------------------------

void FCommonActions::onUndo()
{
	FCommandManager::instance()->undo();
}

void FCommonActions::onRedo()
{
	FCommandManager::instance()->redo();
}

void FCommonActions::onCut()
{
}

void FCommonActions::onCopy()
{
}

void FCommonActions::onPaste()
{
}

void FCommonActions::onDuplicate()
{
}

void FCommonActions::onDelete()
{
}

// Internal functions ----------------------------------------------------------

void FCommonActions::_createCommonActions()
{
	m_pActUndo = new QAction("Undo", m_pParent);
	m_pActUndo->setShortcut(QKeySequence::Undo);
	m_pActUndo->setEnabled(false);
	connect(m_pActUndo, SIGNAL(triggered()), SLOT(onUndo()));

	m_pActRedo = new QAction("Redo", m_pParent);
	m_pActRedo->setShortcut(QKeySequence::Redo);
	m_pActRedo->setEnabled(false);
	connect(m_pActRedo, SIGNAL(triggered()), SLOT(onUndo()));

	m_pActCut = new QAction("Cut", m_pParent);
	m_pActCut->setShortcut(QKeySequence::Cut);
	m_pActCut->setEnabled(false);
	connect(m_pActCut, SIGNAL(triggered()), SLOT(onUndo()));

	m_pActCopy = new QAction("Copy", m_pParent);
	m_pActCopy->setShortcut(QKeySequence::Copy);
	m_pActCopy->setEnabled(false);
	connect(m_pActCopy, SIGNAL(triggered()), SLOT(onUndo()));

	m_pActPaste = new QAction("Paste", m_pParent);
	m_pActPaste->setShortcut(QKeySequence::Paste);
	m_pActPaste->setEnabled(false);
	connect(m_pActPaste, SIGNAL(triggered()), SLOT(onUndo()));

	m_pActDuplicate = new QAction("Duplicate", m_pParent);
	m_pActDuplicate->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_D));
	m_pActDuplicate->setEnabled(false);
	connect(m_pActDuplicate, SIGNAL(triggered()), SLOT(onUndo()));
	
	m_pActDelete = new QAction("Delete", m_pParent);
	m_pActDelete->setShortcut(QKeySequence(Qt::Key_Delete));
	m_pActDelete->setEnabled(false);
	connect(m_pActDelete, SIGNAL(triggered()), SLOT(onUndo()));
}

// -----------------------------------------------------------------------------