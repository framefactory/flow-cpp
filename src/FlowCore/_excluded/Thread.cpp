// -----------------------------------------------------------------------------
//  File        Thread.cpp
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/09 $
// -----------------------------------------------------------------------------

#include "FlowCore/Thread.h"
#include "FlowCore/Log.h"
#include "FlowCore/MemoryTracer.h"

#include <boost/thread.hpp>
#include <exception>

// -----------------------------------------------------------------------------
//  Class FThread
// -----------------------------------------------------------------------------

F_IMPLEMENT_ABSTRACT_TYPEINFO(FThread, FObject);

// Constructors and destructor -------------------------------------------------

FThread::FThread(const wstring_t& name)
	: m_pThread(NULL),
	  m_wantExit(false),
	  m_threadName(name)
{
}

FThread::~FThread()
{
	F_SAFE_DELETE(m_pThread);
}

// Public commands -------------------------------------------------------------

void FThread::start()
{
	if (m_pThread)
		return;

	onStart();
	boost::thread::attributes attr;
	m_pThread = new boost::thread(boost::ref(*this));
}

void FThread::stop()
{
	if (!m_pThread)
		return;

	m_wantExit = true;
	m_pThread->join();
	F_SAFE_DELETE(m_pThread);
	onStop();
}

void FThread::operator()(void)
{
	try
	{
		onRun();
	}
	catch(std::exception e)
	{
		F_CRITICAL("FThread") << toString() << " terminated, reason: " << e.what();
	}
}

// Public queries --------------------------------------------------------------

wstring_t FThread::toString() const
{
	return m_threadName;
}

// -----------------------------------------------------------------------------