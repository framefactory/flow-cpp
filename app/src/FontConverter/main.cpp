// -----------------------------------------------------------------------------
//  File        main.h
//  Project     FontConverter
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/02 $
// -----------------------------------------------------------------------------

#include "FontConverter/Application.h"
#include "FontConverter/MainDialog.h"

#include "FlowCore/MemoryTracer.h"

#include <QApplication>
#include <QFile>

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
	F_MEMORY_TRACER_START;
	int retCode = 0;
	{
		QApplication application(argc, argv);
		application.setOrganizationName("Frame Factory GmbH");
		application.setApplicationName("Font Converter");
		application.setApplicationVersion("0.01");

		Q_INIT_RESOURCE(FlowUIResources);
		QFile styleFile(":/style/default.css");
		if (styleFile.open(QIODevice::ReadOnly | QIODevice::Text))
			application.setStyleSheet(styleFile.readAll());

		FMainDialog mainDialog;
		mainDialog.show();

		retCode = application.exec();
	}

	F_MEMORY_TRACER_REPORT;
	return retCode; 
}

// -----------------------------------------------------------------------------
