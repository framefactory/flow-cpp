// -----------------------------------------------------------------------------
//  File        Font.cpp
//  Project     FlowGraphics
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/30 $
// -----------------------------------------------------------------------------

#include "FlowGraphics/Font.h"

#include "FlowCore/Archive.h"
#include "FlowCore/MemoryTracer.h"

#include <QTextStream>

// -----------------------------------------------------------------------------
//  Class FFont
// -----------------------------------------------------------------------------

F_IMPLEMENT_SERIALIZABLE(FFont, FObject, 1);

// Constructors and destructor -------------------------------------------------

FFont::~FFont()
{
}

// Public commands -------------------------------------------------------------

void FFont::serialize(FArchive& ar)
{
	FObject::serialize(ar);

	if (ar.isWriting())
	{
	}
	else // is reading
	{
	}
}

// Public queries --------------------------------------------------------------

#ifdef FLOW_DEBUG
QString FFont::dump() const
{
	QString text;
	QTextStream stream(&text);
	stream << FObject::dump();
	stream << "\n--- FFont ---";
	return text;
}
#endif

// Overrides -------------------------------------------------------------------

// Internal functions ----------------------------------------------------------

// -----------------------------------------------------------------------------