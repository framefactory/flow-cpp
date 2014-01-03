// -----------------------------------------------------------------------------
//  File        SplineTestWidget.h
//  Project     FlowEdit
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/06 $
// -----------------------------------------------------------------------------

#ifndef FLOWEDIT_SPLINETESTWIDGET_H
#define FLOWEDIT_SPLINETESTWIDGET_H

#include "FlowEdit/Application.h"
#include <QWidget>
#include <QPoint>

// -----------------------------------------------------------------------------
//  Class FSplineTestWidget
// -----------------------------------------------------------------------------

class FSplineTestWidget : public QWidget
{
	Q_OBJECT;

	//  Constructors and destructor ----------------------------------

public:
	/// Default Constructor.
	FSplineTestWidget(QWidget* pParent = NULL);
	/// Virtual destructor.
	virtual ~FSplineTestWidget();

	//  Public commands ----------------------------------------------

public:

	//  Public queries -----------------------------------------------



	//  Overrides ----------------------------------------------------

protected:
	virtual void mousePressEvent(QMouseEvent* pMouseEvent);
	virtual void mouseMoveEvent(QMouseEvent* pMouseEvent);
	virtual void mouseReleaseEvent(QMouseEvent* pMouseEvent);
	virtual void paintEvent(QPaintEvent* pPaintEvent);

	//  Internal functions -------------------------------------------

private:

	//  Internal data members ----------------------------------------

private:
	QPoint m_pt[4];
	QPoint m_dragPos;
	int m_dragIndex;
};
	
// -----------------------------------------------------------------------------

#endif // FLOWEDIT_SPLINETESTWIDGET_H