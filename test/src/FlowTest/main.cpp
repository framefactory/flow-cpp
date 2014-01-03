
#include "FlowUI/MainWindowBase.h"

#include <QApplication>
#include <QFile>
#include <QDebug>


int main(int argc, char *argv[])
{
	//MEMORY_TRACER_START;
	int retCode = 0;
	{
		Q_INIT_RESOURCE(FlowUIResources);

		QApplication application(argc, argv);
		application.setOrganizationName("Frame Factory GmbH");
		application.setApplicationName("Application Name");
		application.setApplicationVersion("0.01");

		QFile styleFile(":/style/default.css");
		if (styleFile.open(QIODevice::ReadOnly | QIODevice::Text))
			application.setStyleSheet(styleFile.readAll());
		
		FMainWindowBase mainWindow;
		mainWindow.show();

		retCode = application.exec();
	}

	//MEMORY_TRACER_REPORT;
	return retCode;
}