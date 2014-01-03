// -----------------------------------------------------------------------------
//  File        MeshWriter.h
//  Project     FlowGraphics
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/09/24 $
// -----------------------------------------------------------------------------

#ifndef FLOWGRAPHICS_MESHWRITER_H
#define FLOWGRAPHICS_MESHWRITER_H

#include "FlowGraphics/Library.h"
#include "FlowGraphics/Mesh.h"

// -----------------------------------------------------------------------------
//  Class FMeshWriter
// -----------------------------------------------------------------------------

class FLOWGRAPHICS_EXPORT FMeshWriter
{
	//  Constructors and destructor ----------------------------------

public:
	/// Default Constructor.
	FMeshWriter();
	/// Virtual destructor.
	virtual ~FMeshWriter();

	//  Public commands ----------------------------------------------

public:
	bool open(const wstring_t& filePath);
	void close();

	bool writeMesh(const FMesh& mesh);

	//  Public queries -----------------------------------------------



	//  Internal functions -------------------------------------------

private:

	//  Internal data members ----------------------------------------

private:

};
	
// -----------------------------------------------------------------------------

#endif // FLOWGRAPHICS_MESHWRITER_H