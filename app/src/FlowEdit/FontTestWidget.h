// -----------------------------------------------------------------------------
//  File        FontTestWidget.h
//  Project     FlowEdit
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/30 $
// -----------------------------------------------------------------------------

#ifndef FLOWEDIT_FONTTESTWIDGET_H
#define FLOWEDIT_FONTTESTWIDGET_H

#include "FlowEdit/Application.h"
#include <QWidget>

class FBitmapFontFactory;

// -----------------------------------------------------------------------------
//  Class FFontTestWidget
// -----------------------------------------------------------------------------

class FFontTestWidget : public QWidget
{
	Q_OBJECT;

	//  Constructors and destructor ----------------------------------

public:
	/// Default Constructor.
	FFontTestWidget(QWidget* pParent = NULL);
	/// Virtual destructor.
	virtual ~FFontTestWidget();

	//  Public commands ----------------------------------------------

public:

	//  Public queries -----------------------------------------------


	//  Overrides ----------------------------------------------------

protected:
	virtual void mouseReleaseEvent(QMouseEvent* pMouseEvent);
	virtual void paintEvent(QPaintEvent* pPaintEvent);

	//  Internal functions -------------------------------------------

private:

	//  Internal data members ----------------------------------------

private:
	FBitmapFontFactory* m_pFontFactory;
	int m_bitmapIndex;
};
	
// -----------------------------------------------------------------------------

#endif // FLOWEDIT_FONTTESTWIDGET_H