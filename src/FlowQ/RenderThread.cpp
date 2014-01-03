// -----------------------------------------------------------------------------
//  File        RenderThread.cpp
//  Project     FlowQ
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/06/09 $
// -----------------------------------------------------------------------------

#include "FlowQ/RenderThread.h"
#include "FlowCore/MemoryTracer.h"

// -----------------------------------------------------------------------------
//  Class FRenderThread
// -----------------------------------------------------------------------------

// Constructors and destructor -------------------------------------------------

FRenderThread::FRenderThread(QObject* pParent /* = NULL */)
: QThread(pParent),
  m_pRenderer(NULL)
{
}

FRenderThread::FRenderThread(FRenderer* pRenderer, QObject* pParent /* = NULL */)
: QThread(pParent),
  m_pRenderer(pRenderer)
{
}

FRenderThread::~FRenderThread()
{
}

// Public commands -------------------------------------------------------------

// Public queries --------------------------------------------------------------

// Overrides -------------------------------------------------------------------

// Internal functions ----------------------------------------------------------

// -----------------------------------------------------------------------------