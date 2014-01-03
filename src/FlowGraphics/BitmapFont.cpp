// -----------------------------------------------------------------------------
//  File        BitmapFont.cpp
//  Project     FlowGraphics
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/30 $
// -----------------------------------------------------------------------------

#include "FlowGraphics/BitmapFont.h"

#include "FlowCore/Archive.h"
#include "FlowCore/MemoryTracer.h"

#include <QTextStream>

// -----------------------------------------------------------------------------
//  Class FBitmapFont
// -----------------------------------------------------------------------------

F_IMPLEMENT_SERIALIZABLE(FBitmapFont, FFont, 1);

// Constructors and destructor -------------------------------------------------

FBitmapFont::~FBitmapFont()
{
}

// Public commands -------------------------------------------------------------

void FBitmapFont::serialize(FArchive& ar)
{
	FFont::serialize(ar);

	if (ar.isWriting())
	{
	}
	else // is reading
	{
	}
}

// Public queries --------------------------------------------------------------

#ifdef FLOW_DEBUG
QString FBitmapFont::dump() const
{
	QString text;
	QTextStream stream(&text);
	stream << FFont::dump();
	stream << "\n--- FBitmapFont ---";
	return text;
}
#endif

// Overrides -------------------------------------------------------------------

// Internal functions ----------------------------------------------------------

// -----------------------------------------------------------------------------