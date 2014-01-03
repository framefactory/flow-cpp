// -----------------------------------------------------------------------------
//  File        PixelT.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/30 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_PIXELT_H
#define FLOWCORE_PIXELT_H

#include "FlowCore/Library.h"

// -----------------------------------------------------------------------------
//  Class FPixelRGBT
// -----------------------------------------------------------------------------

template <typename T>
struct FPixelRGT
{
	T red;
	T green;
};

typedef FPixelRGT<float> FPixelRGf;
typedef FPixelRGT<double> FPixelRGd;
typedef FPixelRGT<uint8_t> FPixelRGi;

// -----------------------------------------------------------------------------
//  Class FPixelRGBT
// -----------------------------------------------------------------------------

template <typename T>
struct FPixelRGBT
{
	T red;
	T green;
	T blue;
};

typedef FPixelRGBT<float> FPixelRGBf;
typedef FPixelRGBT<double> FPixelRGBd;
typedef FPixelRGBT<uint8_t> FPixelRGBi;

// -----------------------------------------------------------------------------
//  Class FPixelBGRT
// -----------------------------------------------------------------------------

template <typename T>
struct FPixelBGRT
{
	T blue;
	T green;
	T red;
};

typedef FPixelBGRT<float> FPixelBGRf;
typedef FPixelBGRT<double> FPixelBGRd;
typedef FPixelBGRT<uint8_t> FPixelBGRi;

// -----------------------------------------------------------------------------
//  Class FPixelRGBAT
// -----------------------------------------------------------------------------

template <typename T>
struct FPixelRGBAT
{
	T red;
	T green;
	T blue;
	T alpha;
};

typedef FPixelRGBAT<float> FPixelRGBAf;
typedef FPixelRGBAT<double> FPixelRGBAd;
typedef FPixelRGBAT<uint8_t> FPixelRGBAi;

// -----------------------------------------------------------------------------

#endif // FLOWCORE_PIXELT_H