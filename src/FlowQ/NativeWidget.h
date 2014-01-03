// -----------------------------------------------------------------------------
//  File        NativeWidget.h
//  Project     FlowQ
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/06/02 $
// -----------------------------------------------------------------------------

#ifndef FLOWQ_NATIVEWIDGET_H
#define FLOWQ_NATIVEWIDGET_H

#include "FlowQ/Library.h"
#include <QWidget>
#include <QWindow>

// -----------------------------------------------------------------------------
//  Class FNativeWidget
// -----------------------------------------------------------------------------

class FLOWQ_EXPORT FNativeWidget : public QWidget
{
	Q_OBJECT;

	//  Constructors and destructor ----------------------------------

public:
	/// Default Constructor.
	FNativeWidget(QWidget* pParent = NULL);
	/// Virtual destructor.
	virtual ~FNativeWidget();

	//  Public commands ----------------------------------------------

public:
	void setPaintEngineEnabled(bool state);
	void setSizeHint(const QSize& size);

	//  Public queries -----------------------------------------------

	bool paintEngineEnabled() const;
	QWindow* nativeWindow() const;

	//  Signals ------------------------------------------------------

signals:
	void redraw();
	void sizeChanged(QSize size); 

	//  Overrides ----------------------------------------------------

protected:
	virtual QPaintEngine* paintEngine() const;
	virtual QSize sizeHint() const;

	virtual void paintEvent(QPaintEvent* pPaintEvent);
	virtual void resizeEvent(QResizeEvent* pResizeEvent);

	//  Internal data members ----------------------------------------

private:
	bool m_paintEngineEnabled;
	QSize m_sizeHint;
};
	
// -----------------------------------------------------------------------------

#endif // FLOWQ_NATIVEWIDGET_H