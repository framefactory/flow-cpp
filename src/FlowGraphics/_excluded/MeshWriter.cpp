// -----------------------------------------------------------------------------
//  File        MeshWriter.cpp
//  Project     FlowGraphics
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/09/24 $
// -----------------------------------------------------------------------------

#include "FlowGraphics/MeshWriter.h"
#include "FlowCore/MemoryTracer.h"

// -----------------------------------------------------------------------------
//  Class FMeshWriter
// -----------------------------------------------------------------------------

// Static members --------------------------------------------------------------

// Constructors and destructor -------------------------------------------------

FMeshWriter::FMeshWriter()
{
}

FMeshWriter::~FMeshWriter()
{
}

// Public commands -------------------------------------------------------------

bool FMeshWriter::open(const wstring_t& filePath)
{
	return false;
}

void FMeshWriter::close()
{

}

bool FMeshWriter::writeMesh(const FMesh& mesh)
{
	return false;
}

// Public queries --------------------------------------------------------------

// Overrides -------------------------------------------------------------------

// Internal functions ----------------------------------------------------------

// -----------------------------------------------------------------------------