// -----------------------------------------------------------------------------
//  File        MainWindowBase.h
//  Project     FlowUI
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/09 $
// -----------------------------------------------------------------------------

#ifndef FLOWUI_MAINWINDOWBASE_H
#define FLOWUI_MAINWINDOWBASE_H

#include "FlowUI/Library.h"

#include <QMainWindow>
#include <QSettings>

// -----------------------------------------------------------------------------
//  Class FMainWindowBase
// -----------------------------------------------------------------------------

class FLOWUI_EXPORT FMainWindowBase : public QMainWindow
{
	Q_OBJECT;

	//  Constructors and destructor ----------------------------------

public:
	/// Default Constructor.
	FMainWindowBase(QWidget* pParent = NULL, Qt::WindowFlags flags = 0);
	/// Virtual destructor.
	virtual ~FMainWindowBase();

	//  Public commands ----------------------------------------------

public:
	/// Saves the current state of the window and all dockable widgets.
	/// Called automatically by the default implementation of closeEvent().
	bool saveWindowState();
	/// Restores the state of the window and all dockable widgets.
	/// Called automatically at the end of initializeUserInterface().
	bool restoreWindowState();

	//  Public queries -----------------------------------------------

	/// Returns an object for reading and writing persistent settings.
	QSettings& settings() { return m_settings; }

	//  Overridables -------------------------------------------------

protected:
	/// Override to initialize the main menu. If a menu is returned,
	/// it is later populated with the view state of the dockable widgets.
	virtual QMenu* onCreateMenu(QMenuBar* pMenuBar) { return NULL; }
	/// Override to initialize the tool and status bars.
	virtual void onCreateToolbar() { }
	/// Override to initialize the dockable widgets. If a menu is given,
	/// it can be passed to addDockWidget() to automatically add view entries
	/// for each dockable.
	virtual void onCreateDockWidgets(QMenu* pMenuView = NULL) { }

	//  Overrides ----------------------------------------------------

	virtual void closeEvent(QCloseEvent* pCloseEvent);

	//  Internal functions -------------------------------------------

	/// Creates and initializes all UI components. The main window
	/// is resized to the given size. If resetWindowState is true, the
	/// geometry of all windows is reset to their default values.
	void initializeUserInterface(const QSize& initialSize = QSize(),
		bool resetWindowState = false);

	/// Adds a dockable widget. The widget initially is in docked state.
	QDockWidget* addDockWidget(QWidget* pWidget, const QString& name,
		Qt::DockWidgetArea area, QMenu* pMenuView = NULL);

	//  Internal data members ---------------------------------------

private:
	QSettings m_settings;
};
	
// -----------------------------------------------------------------------------

#endif // FLOWUI_MAINWINDOWBASE_H
