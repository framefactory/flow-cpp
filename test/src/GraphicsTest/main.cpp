// -----------------------------------------------------------------------------
//  File        main.cpp
//  Project     GraphicsTest
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/06/02 $
// -----------------------------------------------------------------------------

#include "GraphicsTest/Application.h"
#include "GraphicsTest/MainWindow.h"

#include "FlowCore/MemoryTracer.h"

#include <QApplication>
#include <QFile>

// -----------------------------------------------------------------------------
//  Application main entry
// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
	F_MEMORY_TRACER_START;
	int retCode = 0;
	{
		QApplication application(argc, argv);
		application.setOrganizationName("Frame Factory GmbH");
		application.setApplicationName("Graphics Test");
		application.setApplicationVersion("0.01");

		Q_INIT_RESOURCE(FlowQResources);
		QFile styleFile(":/style/default.css");
		if (styleFile.open(QIODevice::ReadOnly | QIODevice::Text))
			application.setStyleSheet(styleFile.readAll());

		FMainWindow mainWindow;
		mainWindow.show();

		retCode = application.exec();
	}

	F_MEMORY_TRACER_REPORT;
	return retCode; 
}

// -----------------------------------------------------------------------------
