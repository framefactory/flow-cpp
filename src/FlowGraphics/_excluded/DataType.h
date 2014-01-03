// -----------------------------------------------------------------------------
//  File        DataType.h
//  Project     FlowGraphics
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/05/21 $
// -----------------------------------------------------------------------------

#ifndef FLOWGRAPHICS_DATATYPE_H
#define FLOWGRAPHICS_DATATYPE_H

#include "FlowGraphics/Library.h"

#include <iosfwd>
class FArchive;

// -----------------------------------------------------------------------------
//  Class FDataType
// -----------------------------------------------------------------------------

struct FLOWGRAPHICS_EXPORT FDataType
{
	typedef uint8_t value_type;

	enum enum_type : value_type
	{
		Float,
		Float2,
		Float3,
		Float4,
		Double,
		Double2,
		Double3,
		Double4,
		UByte,
		UByte2,
		UByte3,
		UByte4,
		UShort,
		UInt
	};

	/// Returns the size of the type in bytes.
	size_t size() const;
	/// Returns the number of components of the type.
	size_t components() const;

	F_DECLARE_ENUM(FLOWGRAPHICS_EXPORT, FDataType, Float);
};
	
// -----------------------------------------------------------------------------

#endif // FLOWGRAPHICS_DATATYPE_H