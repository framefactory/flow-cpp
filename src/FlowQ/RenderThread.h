// -----------------------------------------------------------------------------
//  File        RenderThread.h
//  Project     FlowQ
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/06/09 $
// -----------------------------------------------------------------------------

#ifndef FLOWQ_RENDERTHREAD_H
#define FLOWQ_RENDERTHREAD_H

#include "FlowQ/Library.h"
#include <QThread>

class FRenderer;

// -----------------------------------------------------------------------------
//  Class FRenderThread
// -----------------------------------------------------------------------------

class FLOWQ_EXPORT FRenderThread : public QThread
{
	Q_OBJECT;

	//  Constructors and destructor ----------------------------------

public:
	/// Default Constructor.
	FRenderThread(QObject* pParent = NULL);
	FRenderThread(FRenderer* pRenderer, QObject* pParent = NULL);
	/// Virtual destructor.
	virtual ~FRenderThread();

	//  Public commands ----------------------------------------------

public:
	void start(QThread::Priority priority = QThread::NormalPriority);
	void stop();

	void setRenderer(FRenderer* pRenderer);

	//  Public queries -----------------------------------------------

	FRenderer* renderer() const { return m_pRenderer; }

	//  Overridables -------------------------------------------------

protected:

	//  Overrides ----------------------------------------------------

protected:
	virtual void run();

	//  Internal functions -------------------------------------------

private:

	//  Internal data members ----------------------------------------

private:
	FRenderer* m_pRenderer;
};
	
// -----------------------------------------------------------------------------

#endif // FLOWQ_RENDERTHREAD_H