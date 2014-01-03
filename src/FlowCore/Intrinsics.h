// -----------------------------------------------------------------------------
//  File        Intrinsics.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/19 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_INTRINSICS_H
#define FLOWCORE_INTRINSICS_H

#include "FlowCore/Library.h"

#include <xmmintrin.h> // SSE
#include <pmmintrin.h> // SSE3
#include <emmintrin.h> // SSE2
#include <smmintrin.h> // SSE4_1

static F_ALIGN(16) const unsigned int _fSignPNPN[4] = {0x00000000, 0x80000000, 0x00000000, 0x80000000};
static F_ALIGN(16) const unsigned int _fSignNNNN[4] = {0x80000000, 0x80000000, 0x80000000, 0x80000000};
static F_ALIGN(16) const unsigned int _fSignNPNP[4] = {0x80000000, 0x00000000, 0x80000000, 0x00000000};
static F_ALIGN(16) const unsigned int _fMaskFFF0[4] = {0xffffffff, 0xffffffff, 0xffffffff, 0x00000000};

#define F_MM_GET_ELEM(__m128, index) (*(((float*)&(__m128)) + (index)))
#define F_MM_SET_ELEM(__m128, index, val) (*(((float*)&(__m128)) + (index))) = (val)

// required because of the memory layout of our matrix implementation
#define F_MM_SHUFFLE4(a,b,c,d) _MM_SHUFFLE(d,c,b,a)

#endif // FLOWCORE_INTRINSICS_H