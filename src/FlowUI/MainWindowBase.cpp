// -----------------------------------------------------------------------------
//  File        MainWindowBase.h
//  Project     FlowUI
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/09 $
// -----------------------------------------------------------------------------

#include "FlowUI/MainWindowBase.h"
//#include "FlowCore/MemoryTracer.h"

#include <QtWidgets>

// -----------------------------------------------------------------------------
//  Class FMainWindowBase
// -----------------------------------------------------------------------------

// Constructors and destructor -------------------------------------------------

FMainWindowBase
	::FMainWindowBase(QWidget* pParent /* = NULL */,
								 Qt::WindowFlags flags /* = 0 */)
: QMainWindow(pParent, flags)
{
}

FMainWindowBase
	::~FMainWindowBase()
{
}

// Public commands -------------------------------------------------------------

bool FMainWindowBase
	::restoreWindowState()
{
	QString name = objectName().isEmpty() ? QString("mainWindow") : objectName();
	QByteArray state = settings().value(name + "Dockables").toByteArray();
	QRect geometry = settings().value(name + "Location").toRect();

	if (geometry.isEmpty()) {
		return false;
	}

	setGeometry(geometry);

	if (state.isEmpty() || !restoreState(state)) {
		return false;
	}

	return true;
}

bool FMainWindowBase
	::saveWindowState()
{
	QByteArray state = saveState();
	if (state.isEmpty()) {
		return false;
	}

	QString name = objectName().isEmpty() ? QString("mainWindow") : objectName();
	settings().setValue(name + "Dockables", state);
	settings().setValue(name + "Location", this->geometry());

	return true;
}

// Public queries --------------------------------------------------------------

// Overrides -------------------------------------------------------------------

void FMainWindowBase
	::closeEvent(QCloseEvent* pCloseEvent)
{
	QMessageBox::StandardButton result;

	QString appName = QApplication::applicationName();

	result = QMessageBox::question(this, appName, tr("Do you really want to quit?"),
		QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);

	if (result == QMessageBox::Ok) {
		pCloseEvent->accept();
		saveWindowState();
	}
	else {
		pCloseEvent->ignore();
	}
}

// Internal functions ----------------------------------------------------------

void FMainWindowBase
	::initializeUserInterface(const QSize& initialSize /* = QSize */,
		  					  bool resetWindowState /* = false */)
{
	if (!initialSize.isNull()) {
		resize(initialSize);
	}

	setDockNestingEnabled(true);

	QMenu* pViewMenu = onCreateMenu(this->menuBar());
	onCreateDockWidgets(pViewMenu);
	onCreateToolbar();

	if (!resetWindowState) {
		restoreWindowState();
	}
}

QDockWidget* FMainWindowBase
	::addDockWidget(QWidget* pWidget,
 					const QString& name,
					Qt::DockWidgetArea area,
					QMenu* pMenuView /* = NULL */)
{
	QDockWidget* pDockWidget = new QDockWidget(name, this);
	pDockWidget->setObjectName(name);
	pDockWidget->setWidget(pWidget);
	QMainWindow::addDockWidget(area, pDockWidget);

	if (pMenuView) {
		pMenuView->addAction(pDockWidget->toggleViewAction());
	}

	return pDockWidget;
}

// -----------------------------------------------------------------------------