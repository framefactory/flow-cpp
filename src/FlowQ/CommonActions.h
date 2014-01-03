// -----------------------------------------------------------------------------
//  File        CommonActions.h
//  Project     FlowQ
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/02 $
// -----------------------------------------------------------------------------

#ifndef FLOWQ_COMMONACTIONS_H
#define FLOWQ_COMMONACTIONS_H

#include "FlowQ/Library.h"

#include "FlowCore/String.h"
#include "FlowCore/CommandManagerListener.h"

#include <QObject>

class QWidget;
class QAction;

// -----------------------------------------------------------------------------
//  Class FCommonActions
// -----------------------------------------------------------------------------

class FLOWQ_EXPORT FCommonActions
	: public QObject, public FCommandManagerListener
{
	Q_OBJECT;

	//  Constructors and destructor ----------------------------------

public:
	/// Default Constructor.
	FCommonActions(QWidget* pParent);
	/// Virtual destructor.
	virtual ~FCommonActions();

	//  Public commands ----------------------------------------------

public:

	//  Public queries -----------------------------------------------

	QAction* actionUndo() const { return m_pActUndo; }
	QAction* actionRedo() const { return m_pActRedo; }
	QAction* actionCut() const { return m_pActCut; }
	QAction* actionCopy() const { return m_pActCopy; }
	QAction* actionPaste() const { return m_pActPaste; }
	QAction* actionDuplicate() const { return m_pActDuplicate; }
	QAction* actionDelete() const { return m_pActDelete; }

	//  Overrides (FCommandManagerListener) --------------------------

public:
	virtual void historyStateChanged(const wstring_t& undoCommand,
		const wstring_t& redoCommand, bool isDirty);

	//  Slots --------------------------------------------------------

protected slots:
	void onUndo();
	void onRedo();
	void onCut();
	void onCopy();
	void onPaste();
	void onDuplicate();
	void onDelete();

	//  Internal functions -------------------------------------------

private:
	void _createCommonActions();

	//  Internal data members ----------------------------------------

	QWidget* m_pParent;

	QAction* m_pActUndo;
	QAction* m_pActRedo;
	QAction* m_pActCut;
	QAction* m_pActCopy;
	QAction* m_pActPaste;
	QAction* m_pActDuplicate;
	QAction* m_pActDelete;
};
	
// -----------------------------------------------------------------------------

#endif // FLOWQ_COMMONACTIONS_H