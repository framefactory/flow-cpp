#ifndef GRAPHICSTEST_MAINWINDOW_H
#define GRAPHICSTEST_MAINWINDOW_H

#include "GraphicsTest/Application.h"
#include "FlowQ/MainWindowBase.h"

#include <QOpenGLContext>

class FNativeWidget;

// -----------------------------------------------------------------------------
//  Class FMainWindow
// -----------------------------------------------------------------------------

class  FMainWindow : public FMainWindowBase
{
	Q_OBJECT;

	//  Constructors and destructor ----------------------------------

public:
	/// Default Constructor.
	FMainWindow(QWidget* pParent = NULL, Qt::WindowFlags flags = 0);
	/// Virtual destructor.
	virtual ~FMainWindow();

	//  Public commands ----------------------------------------------

public slots:
	void redraw();

	//  Public queries -----------------------------------------------


	//  Overrides ----------------------------------------------------

protected:
	virtual void resizeEvent(QResizeEvent* pResizeEvent);

	virtual void onCreateDockWidgets(QMenu* pMenuView);
	virtual QMenu* onCreateMenu(QMenuBar* pMenuBar);
	virtual void onCreateToolbar();

	//  Internal functions -------------------------------------------

private:

	//  Internal data members ----------------------------------------

private:
	FNativeWidget* m_pRenderWidget;
	QOpenGLContext* m_pContext;
};
	
// -----------------------------------------------------------------------------


#endif // GRAPHICSTEST_MAINWINDOW_H