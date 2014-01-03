// -----------------------------------------------------------------------------
//  File        TokenRegistry.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012.12.30 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_TOKENREGISTRY_H
#define FLOWCORE_TOKENREGISTRY_H

#include "FlowCore/Library.h"
#include "FlowCore/SingletonT.h"
#include "FlowCore/String.h"

#include <boost/thread/mutex.hpp>
#include <map>

struct FTokenEntry;

// -----------------------------------------------------------------------------
//  Class FTokenRegistry
// -----------------------------------------------------------------------------

class FLOWCORE_EXPORT FTokenRegistry : public FSingletonAutoT<FTokenRegistry>
{
	friend class FSingletonAutoT<FTokenRegistry>;
	friend class FToken;

	//  Constructors and destructor ----------------------------------

protected:
	FTokenRegistry();
	virtual ~FTokenRegistry();

	//  Protected members (accessed by FToken) -----------------------

protected:
	FTokenEntry* add(const wstring_t& text);
	void addRef(FTokenEntry* pEntry);
	void removeRef(FTokenEntry* pEntry);
	const wstring_t& text(const FTokenEntry* pEntry) const;

	//  Internal data members ----------------------------------------

private:
	typedef std::map<wstring_t, FTokenEntry*> tokenMap_t;
	tokenMap_t m_tokens;
	boost::mutex m_mutex;
};
	
// -----------------------------------------------------------------------------


#endif // FLOWCORE_TOKENREGISTRY_H