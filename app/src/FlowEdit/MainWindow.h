// -----------------------------------------------------------------------------
//  File        MainWindow.h
//  Project     FlowEdit
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/02 $
// -----------------------------------------------------------------------------

#ifndef FLOWEDIT_MAINWINDOW_H
#define FLOWEDIT_MAINWINDOW_H

#include "FlowEdit/Application.h"

#include "FlowQ/CommonActions.h"
#include "FlowQ/MainWindowBase.h"

// -----------------------------------------------------------------------------
//  Class FMainWindow
// -----------------------------------------------------------------------------

class FMainWindow : public FMainWindowBase
{
	Q_OBJECT;

	//  Constructors and destructor ----------------------------------

public:
	/// Default Constructor.
	FMainWindow(QWidget* pParent = NULL, Qt::WindowFlags flags = 0);
	/// Virtual destructor.
	virtual ~FMainWindow();

	//  Public commands ----------------------------------------------

public:

	//  Public queries -----------------------------------------------

	//  Overrides ----------------------------------------------------

protected:
	virtual QMenu* onCreateMenu(QMenuBar* pMenuBar);
	virtual void onCreateToolbar();
	virtual void onCreateDockWidgets(QMenu* pMenuView);

	//  Internal functions -------------------------------------------

private:

	//  Internal data members ----------------------------------------

private:
	FCommonActions m_commonActions;
};
	
// -----------------------------------------------------------------------------

#endif // FLOWEDIT_MAINWINDOW_H