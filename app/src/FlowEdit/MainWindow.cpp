// -----------------------------------------------------------------------------
//  File        MainWindow.cpp
//  Project     FlowEdit
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/02 $
// -----------------------------------------------------------------------------

#include <QtGui>
#include <QtWidgets>

#include "FlowEdit/MainWindow.h"
#include "FlowEdit/SplineTestWidget.h"
#include "FlowEdit/FontTestWidget.h"

#include "FlowQ/LogWidget.h"
#include "FlowCore/MemoryTracer.h"

// -----------------------------------------------------------------------------
//  Class FMainWindow
// -----------------------------------------------------------------------------

// Constructors and destructor -------------------------------------------------

FMainWindow::FMainWindow(
	QWidget* pParent /* = NULL */, Qt::WindowFlags flags /* = 0 */)
: FMainWindowBase(pParent, flags),
  m_commonActions(this)
{
	initializeUserInterface();

	FSplineTestWidget* pWidget = new FSplineTestWidget(this);
	//FFontTestWidget* pWidget = new FFontTestWidget(this);
	setCentralWidget(pWidget);
}

FMainWindow::~FMainWindow()
{
}

// Public commands -------------------------------------------------------------

// Public queries --------------------------------------------------------------

// Overrides -------------------------------------------------------------------

QMenu* FMainWindow::onCreateMenu(QMenuBar* pMenuBar)
{
	QMenu* pMenuFile = pMenuBar->addMenu("File");
	pMenuFile->addAction("Quit");

	QMenu* pMenuEdit = pMenuBar->addMenu("Edit");
	pMenuEdit->addAction(m_commonActions.actionUndo());
	pMenuEdit->addAction(m_commonActions.actionRedo());
	pMenuEdit->addSeparator();
	pMenuEdit->addAction(m_commonActions.actionCut());
	pMenuEdit->addAction(m_commonActions.actionCopy());
	pMenuEdit->addAction(m_commonActions.actionPaste());
	pMenuEdit->addSeparator();
	pMenuEdit->addAction(m_commonActions.actionDuplicate());
	pMenuEdit->addAction(m_commonActions.actionDelete());

	QMenu* pMenuView = pMenuBar->addMenu("View");
	return pMenuView;
}

void FMainWindow::onCreateToolbar()
{
}

void FMainWindow::onCreateDockWidgets(QMenu* pMenuView)
{
	FLogWidget* pLogWidget = new FLogWidget(this);
	addDockWidget(pLogWidget, "Log", Qt::BottomDockWidgetArea, pMenuView);
}

// Internal functions ----------------------------------------------------------

// -----------------------------------------------------------------------------