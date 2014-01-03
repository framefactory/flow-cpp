// -----------------------------------------------------------------------------
//  File        Font.h
//  Project     FlowGraphics
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/30 $
// -----------------------------------------------------------------------------

#ifndef FLOWGRAPHICS_FONT_H
#define FLOWGRAPHICS_FONT_H

#include "FlowGraphics/Library.h"
#include "FlowCore/Object.h"

#include <QString>

class FArchive;

// -----------------------------------------------------------------------------
//  Class FFont
// -----------------------------------------------------------------------------

class FLOWGRAPHICS_EXPORT FFont : public FObject
{
	F_DECLARE_SERIALIZABLE(FFont);
	friend class FFontFactory;

	//  Constructors and destructor ----------------------------------

public:
	/// Virtual destructor.
	virtual ~FFont();

	//  Public commands ----------------------------------------------

	/// Serialization to or from the given archive.
	virtual void serialize(FArchive& ar);

	//  Public queries -----------------------------------------------

#ifdef FLOW_DEBUG
	/// Returns information about the internal state.
	virtual QString dump() const;
#endif

	//  Overridables -------------------------------------------------

protected:

	//  Overrides ----------------------------------------------------

protected:

	//  Internal functions -------------------------------------------

private:

	//  Internal data members ----------------------------------------

private:
	QString m_fontName;
};
	
// -----------------------------------------------------------------------------

#endif // FLOWGRAPHICS_FONT_H