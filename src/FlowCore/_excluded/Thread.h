// -----------------------------------------------------------------------------
//  File        Thread.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/09 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_THREAD_H
#define FLOWCORE_THREAD_H

#include "FlowCore/Library.h"
#include "FlowCore/Object.h"

#include <iosfwd>

namespace boost { class thread; }

// -----------------------------------------------------------------------------
//  Class FThread
// -----------------------------------------------------------------------------

class FLOWCORE_EXPORT FThread : public FObject
{
	F_DECLARE_ABSTRACT_TYPEINFO(FThread);

	//  Constructors and destructor ----------------------------------

public:
	/// Default constructor.
	FThread(const wstring_t& name);
	/// Virtual destructor.
	virtual ~FThread();

	//  Public commands ----------------------------------------------

	/// Starts the thread.
	void start();
	/// Stops the thread.
	void stop();

	/// Entry function for the thread.
	void operator()(void);

	//  Public queries -----------------------------------------------

	/// Returns a text representation of the thread.
	virtual wstring_t toString() const;

	//  Protected members --------------------------------------------

	bool wantExit() const { return m_wantExit; }

	//  Overridables -------------------------------------------------

	virtual void onStart() { }
	virtual void onRun() = 0;
	virtual void onStop() { }

	//  Internal data members ----------------------------------------

private:
	boost::thread* m_pThread;
	bool m_wantExit;
	wstring_t m_threadName;
};
	
// -----------------------------------------------------------------------------

#endif // FLOWCORE_THREAD_H