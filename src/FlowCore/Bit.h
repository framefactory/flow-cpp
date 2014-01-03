// -----------------------------------------------------------------------------
//  File        Bit.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/02/08 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_BIT_H
#define FLOWCORE_BIT_H

#include "FlowCore/Library.h"

// -----------------------------------------------------------------------------
//  Class FBit
// -----------------------------------------------------------------------------

class FLOWCORE_EXPORT FBit
{
	//  Constructors and destructor ----------------------------------

private:
	/// Private constructor. Class provides only static methods.
	FBit();

	//  Static methods -----------------------------------------------

public:
	/// Sets the bit at pos in val and returns the modified value.
	template <typename T>
	static inline T set(T val, T pos) { return val | (1 << pos); }
	/// Clears the bit at pos in val and returns the modified value.
	template <typename T>
	static inline T clear(T val, T pos) { return val & ~(1 << pos); }
	/// Toggles the bit at pos in val and returns the modified value.
	template <typename T>
	static inline T toggle(T val, T pos) { return val ^ (1 << pos); }
	/// Tests the bit at pos in val and returns a non-zero value if the bit is set.
	template <typename T>
	static inline T test(T val, T pos) { return val & (1 << pos); }

	/// Rounds the value up to the nearest multiple of 2.
	template <typename T>
	static inline T ceil2(T val) { return ((val - 1) | 0x01) + 1; }
	/// Rounds the value up to the nearest multiple of 4.
	template <typename T>
	static inline T ceil4(T val) { return ((val - 1) | 0x03) + 1; }
	/// Rounds the value up to the nearest multiple of 8.
	template <typename T>
	static inline T ceil8(T val) { return ((val - 1) | 0x07) + 1; }

	/// Rounds the value up to the next power of 2.
	static inline unsigned int ceilPow2(unsigned int val) {
		// Source: http://acius2.blogspot.com/2007/11/calculating-next-power-of-2.html
		val--;
		val = (val >> 1) | val;
		val = (val >> 2) | val;
		val = (val >> 4) | val;
		val = (val >> 8) | val;
		val = (val >> 16) | val;
		val++;
		return val;
	}
};

// -----------------------------------------------------------------------------

#endif // FLOWCORE_BIT_H