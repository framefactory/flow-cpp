// -----------------------------------------------------------------------------
//  File        GLWidget.h
//  Project     FlowQ
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/06/02 $
// -----------------------------------------------------------------------------

#ifndef FLOWQ_GLWIDGET_H
#define FLOWQ_GLWIDGET_H

#include "FlowQ/Library.h"
#include <QWidget>

// -----------------------------------------------------------------------------
//  Class FGLWidget
// -----------------------------------------------------------------------------

class FLOWQ_EXPORT FGLWidget : public QWidget
{
	//  Constructors and destructor ----------------------------------

public:
	/// Default Constructor.
	FGLWidget(QWidget* pParent);
	/// Virtual destructor.
	virtual ~FGLWidget();

	//  Public commands ----------------------------------------------

public:

	//  Public queries -----------------------------------------------

	//  Overridables -------------------------------------------------

protected:

	//  Overrides ----------------------------------------------------

protected:

	//  Internal functions -------------------------------------------

private:

	//  Internal data members ----------------------------------------

private:

};
	
// -----------------------------------------------------------------------------

#endif // FLOWQ_GLWIDGET_H