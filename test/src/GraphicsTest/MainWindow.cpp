
#include <QtGui>
#include <QtWidgets>

#include "GraphicsTest/MainWindow.h"

#include "FlowQ/LogWidget.h"
#include "FlowQ/NativeWidget.h"

#include "FlowCore/Log.h"
#include "FlowCore/MemoryTracer.h"

// -----------------------------------------------------------------------------
//  Class FMainWindow
// -----------------------------------------------------------------------------

// Constructors and destructor -------------------------------------------------

FMainWindow::FMainWindow(QWidget* pParent /* = NULL */,
						 Qt::WindowFlags flags /* = 0 */)
: FMainWindowBase(pParent, flags)
{
	initializeUserInterface(QSize(), true);
	//initializeUserInterface();

	
	m_pRenderWidget = new FNativeWidget(this);
	m_pRenderWidget->setSizeHint(QSize(640, 480));
	setCentralWidget(m_pRenderWidget);
	
	QSurfaceFormat format;
	format.setProfile(QSurfaceFormat::CoreProfile);
	format.setRenderableType(QSurfaceFormat::OpenGL);
	format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);

	m_pContext = new QOpenGLContext(this);
	m_pContext->setFormat(format);
	m_pContext->setScreen(QGuiApplication::primaryScreen());
	bool success = m_pContext->create();
	F_ASSERT(m_pContext->isValid());
	F_INFO("MainWindow") << (success ? "Successfully created OpenGL context" : "Failed to create OpenGL context");

	connect(m_pRenderWidget, SIGNAL(redraw()), this, SLOT(redraw()));
	
}

FMainWindow::~FMainWindow()
{
}

// Public commands -------------------------------------------------------------

void FMainWindow::redraw()
{
	QWindow* pNativeWindow = m_pRenderWidget->nativeWindow();
	F_ASSERT(pNativeWindow);

	m_pContext->makeCurrent(pNativeWindow);
	glViewport(0, 0, 1024, 768);
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_pContext->swapBuffers(pNativeWindow);
}

// Public queries --------------------------------------------------------------

// Overrides -------------------------------------------------------------------

void FMainWindow::resizeEvent(QResizeEvent* pResizeEvent)
{
}

QMenu* FMainWindow::onCreateMenu(QMenuBar* pMenuBar)
{
	pMenuBar->setAttribute(Qt::WA_NativeWindow, true);

	QMenu* pMenuFile = pMenuBar->addMenu("File");
	pMenuFile->addAction("Quit");

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
