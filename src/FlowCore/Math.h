// -----------------------------------------------------------------------------
//  File        Math.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/09 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_MATH_H
#define FLOWCORE_MATH_H

#include "FlowCore/Library.h"
#include <cmath>

// -----------------------------------------------------------------------------
//  Macro definitions
// -----------------------------------------------------------------------------

#define F_PI		3.1415926535897932384626433832795
#define F_2PI		6.283185307179586476925286766559
#define F_PI2		1.5707963267948966192313216916398
#define F_PI4		0.78539816339744830961566084581988
#define F_EULER		2.7182818284590452353602874713526624977572
#define F_R2D		57.295779513082320876798154814114
#define F_D2R		0.017453292519943295769236907684883

// -----------------------------------------------------------------------------
//  Class FMath
// -----------------------------------------------------------------------------

class FLOWCORE_EXPORT FMath
{
private:
	/// Private constructor. Class contains only static members.
	FMath();

	//  Public static constants --------------------------------------

public:
	// Mathematical constant pi.
	static const double pi;
	// Pi times 2.
	static const double pi2;
	// Pi divided by 2.
	static const double piHalf;
	// Pi divided by 4.
	static const double piQuarter;

	/// Euler's number.
	static const double e;

	/// Multiplication constant for radian to degree conversion.
	static const double r2d;
	/// Multiplication constant for degree to radian conversion.
	static const double d2r;

	//  Public static methods ---------------------------------------

	template <typename REAL>
	inline static REAL rad2deg(REAL rad)
	{
		return rad * (REAL)57.295779513082320876798154814114;
	}

	template <typename REAL>
	inline static REAL deg2rad(REAL deg)
	{
		return deg * (REAL)0.017453292519943295769236907684883;
	}

	template <typename REAL>
	inline static REAL gaussian(REAL x, REAL sigma)
	{
		REAL sigmaSquare = sigma * sigma;
		return REAL(1.0) / sqrt(REAL(F_2PI) * sigmaSquare) * exp(-x*x / (REAL(2.0)*sigmaSquare));
	}

	template <typename REAL>
	inline static REAL lerp(REAL f, REAL outMin, REAL outMax)
	{
		return outMin + f * (outMax - outMin);
	}

	template <typename REAL>
	inline static REAL limitedLerp(REAL f, REAL outMin, REAL outMax)
	{
		f = fMax(REAL(0.0), fMin(REAL(1.0), f));
		return outMin + f * (outMax - outMin);
	}

	template <typename REAL>
	inline static REAL lerp(REAL f, REAL inMin, REAL inMax, REAL outMin, REAL outMax)
	{
		f = (f - inMin) / (inMax - inMin);
		return outMin + f * (outMax - outMin);
	}

	template <typename REAL>
	inline static REAL limitedLerp(REAL f, REAL inMin, REAL inMax, REAL outMin, REAL outMax)
	{
		f = (f - inMin) / (inMax - inMin);
		f = fMax(REAL(0.0), fMin(REAL(1.0), f));
		return outMin + f * (outMax - outMin);
	}
};
	
// -----------------------------------------------------------------------------

#endif // FMATH_H
