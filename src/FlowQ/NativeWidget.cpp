// -----------------------------------------------------------------------------
//  File        NativeWidget.cpp
//  Project     FlowQ
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/06/02 $
// -----------------------------------------------------------------------------

#include "FlowQ/NativeWidget.h"
#include "FlowCore/Log.h"

#include <QResizeEvent>
#include <QPaintEvent>
#include <QWindow>

// -----------------------------------------------------------------------------
//  Class FNativeWidget
// -----------------------------------------------------------------------------

// Constructors and destructor -------------------------------------------------

FNativeWidget::FNativeWidget(QWidget* pParent /* = NULL */)
: QWidget(pParent),
  m_paintEngineEnabled(false)
{
	setAttribute(Qt::WA_PaintOnScreen, true);
	setAttribute(Qt::WA_NativeWindow, true);
	setFocusPolicy(Qt::StrongFocus);

	QWindow* pNativeWindow = windowHandle();
	F_ASSERT(pNativeWindow);

	pNativeWindow->setSurfaceType(QSurface::OpenGLSurface);
	pNativeWindow->destroy();
	pNativeWindow->create();
}

FNativeWidget::~FNativeWidget()
{
}

// Public commands -------------------------------------------------------------

void FNativeWidget::setPaintEngineEnabled(bool state)
{
	m_paintEngineEnabled = state;
}

void FNativeWidget::setSizeHint(const QSize& size)
{
	m_sizeHint = size;
}

// Public queries --------------------------------------------------------------

bool FNativeWidget::paintEngineEnabled() const
{
	return m_paintEngineEnabled;
}

QWindow* FNativeWidget::nativeWindow() const
{
	return windowHandle();
}

// Overrides -------------------------------------------------------------------

QPaintEngine* FNativeWidget::paintEngine() const
{
	if (m_paintEngineEnabled)
		return QWidget::paintEngine();

	return NULL;
}

QSize FNativeWidget::sizeHint() const
{
	return m_sizeHint;
}

void FNativeWidget::paintEvent(QPaintEvent* pPaintEvent)
{
	emit redraw();
}

void FNativeWidget::resizeEvent(QResizeEvent* pResizeEvent)
{
	emit sizeChanged(pResizeEvent->size());
}

// -----------------------------------------------------------------------------