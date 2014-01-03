// -----------------------------------------------------------------------------
//  File        LogWidget.h
//  Project     FlowQ
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/09 $
// -----------------------------------------------------------------------------

#ifndef FLOWUI_LOGWIDGET_H
#define FLOWUI_LOGWIDGET_H

#include "FlowUI/Library.h"
#include "FlowCore/LogManager.h"
#include "FlowCore/CriticalSection.h"

#include <QWidget>
#include <queue>

class QEvent;
class QTreeWidget;
class QResizeEvent;

// -----------------------------------------------------------------------------
//  Class FLogWidget
// -----------------------------------------------------------------------------

class FLOWUI_EXPORT FLogWidget : public QWidget, public FLogListener
{
	Q_OBJECT;

	//  Constructors and destructor ----------------------------------

public:
	/// Default constructor.
	FLogWidget(QWidget* pParent = NULL, Qt::WindowFlags flags = 0);
	/// Virtual destructor.
	virtual ~FLogWidget();

	//  Public commands ----------------------------------------------


	//  Public queries -----------------------------------------------


	//  Overrides ----------------------------------------------------

	virtual void logMessage(const FLogMessage& message);

protected:
	virtual QSize sizeHint() const;
	virtual void resizeEvent(QResizeEvent* pResize);
	virtual bool event(QEvent* pEvent);

	//  Internal functions -------------------------------------------

private:
	void _addEntry(const FLogMessage& message);

	//  Internal data members ----------------------------------------

	QTreeWidget* m_pLogList;
	std::queue<FLogMessage> m_messageQueue;
	FCriticalSection m_queueLock;
	static int s_updateEvent;
};
	
// -----------------------------------------------------------------------------

#endif // FLOWUI_LOGWIDGET_H
