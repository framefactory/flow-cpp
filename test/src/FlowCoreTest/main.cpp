// -----------------------------------------------------------------------------
//  File        main.h
//  Project     FlowCoreTest
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/12/22 $
// -----------------------------------------------------------------------------

#include "FlowCoreTest/ObjectTest.h"
#include "FlowCoreTest/ArchiveTest.h"

#include "FlowCore/TestManager.h"
#include "FlowCore/MemoryTracer.h"

int main(int argc, char *argv[])
{
	int result;
	{
		F_MEMORY_TRACER_START;
		result = FTestManager::instance()->run();
		F_MEMORY_TRACER_REPORT;
	}

	return result;
}
