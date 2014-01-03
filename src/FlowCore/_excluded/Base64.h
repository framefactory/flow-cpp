// -----------------------------------------------------------------------------
//  File        Base64.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/10/20 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_BASE64_H
#define FLOWCORE_BASE64_H

#include "FlowCore/Library.h"
#include "FlowCore/String.h"

// -----------------------------------------------------------------------------
//  Class FBase64
// -----------------------------------------------------------------------------

class FLOWCORE_EXPORT FBase64
{
	//  Constructors and destructor ----------------------------------

private:
	/// Private constructor. Class provides only static methods.
	FBase64();

	//  Static methods -----------------------------------------------

public:
	static string_t encode(const uint8_t* pData, size_t length, int lineSize = 256);
	static bool decode(const string_t encodedData, uint8_t* pBuffer, size_t bufLength);
};
	
// -----------------------------------------------------------------------------

#endif // FLOWCORE_BASE64_H