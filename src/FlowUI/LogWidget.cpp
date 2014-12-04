// -----------------------------------------------------------------------------
//  File        LogWidget.h
//  Project     FlowQ
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/09 $
// -----------------------------------------------------------------------------

#include "FlowUI/LogWidget.h"
#include "FlowCore/MemoryTracer.h"

#include <QEvent>
#include <QResizeEvent>
#include <QTreeWidget>
#include <QApplication>

// -----------------------------------------------------------------------------
//  Class FLogWidget
// -----------------------------------------------------------------------------

int FLogWidget::s_updateEvent = QEvent::registerEventType();

// Constructors and destructor -------------------------------------------------

FLogWidget::FLogWidget(QWidget* pParent, Qt::WindowFlags flags /* = 0 */)
: QWidget(pParent, flags)
{
	m_pLogList = new QTreeWidget(this);
	m_pLogList->setIndentation(0);
	m_pLogList->setWordWrap(true);
	m_pLogList->setRootIsDecorated(false);

	QStringList headerLabels;
	headerLabels << tr("Time") << tr("Level") << tr("Module") << tr("Message");
	m_pLogList->setHeaderLabels(headerLabels);

	m_pLogList->setColumnWidth(0, 120);
	m_pLogList->setColumnWidth(1, 70);
	m_pLogList->setColumnWidth(2, 120);

	FLogManager* pLogManager = FLogManager::instance();
	pLogManager->addListener(this);

	std::vector<FLogMessage> messages = pLogManager->getMessages();
	for (size_t i = 0; i < messages.size(); ++i) {
		_addEntry(messages[i]);
	}
}

FLogWidget::~FLogWidget()
{
	FLogManager::instance()->removeListener(this);
}

// Public commands -------------------------------------------------------------


// Public queries --------------------------------------------------------------


// Overrides -------------------------------------------------------------------

void FLogWidget::logMessage(const FLogMessage& message)
{
	FSectionLock lock(&m_queueLock);
	m_messageQueue.push(message);
	QApplication::postEvent(this, new QEvent((QEvent::Type)s_updateEvent));
}

QSize FLogWidget::sizeHint() const
{
	return m_pLogList->sizeHint();
}

void FLogWidget::resizeEvent(QResizeEvent* pResize)
{
	m_pLogList->setGeometry(QRect(QPoint(0, 0), pResize->size()));
}

bool FLogWidget::event(QEvent* pEvent)
{
	if (pEvent->type() != (QEvent::Type)s_updateEvent)
		return QWidget::event(pEvent);

	FSectionLock lock(&m_queueLock);

	while (!m_messageQueue.empty())
	{
		_addEntry(m_messageQueue.front());
		m_messageQueue.pop();
	}

	return true;
}

// Internal functions ----------------------------------------------------------

void FLogWidget::_addEntry(const FLogMessage& message)
{
	int n = m_pLogList->topLevelItemCount();
	if (n > 100)
	{
		for (int i = 0; i < (n - 100); i++)
			delete m_pLogList->takeTopLevelItem(i);
	}

	static bool lineEven = false;
	lineEven = !lineEven;

	QString typeText;
	QBrush foreBrush;
	bool setForeColor = false;

	switch (message.type())
	{
	case FLogType::Debug:
		typeText = tr("Debug");
		foreBrush = QBrush(QRgb(0x909090));
		setForeColor = true;
		break;
	case FLogType::Info:
		typeText = tr("Info");
		break;
	case FLogType::Warning:
		typeText = tr("Warning");
		foreBrush = QBrush(QRgb(0x95c0ec));
		setForeColor = true;
		break;
	case FLogType::Critical:
		typeText = tr("Critical");
		foreBrush = QBrush(QRgb(0xedda80));
		setForeColor = true;
		break;
	case FLogType::Fatal:
		typeText = tr("Fatal");
		foreBrush = QBrush(QRgb(0xff6666));
		setForeColor = true;
		break;
	default:
		typeText = tr("Unknown");
		break;
	}

	QStringList itemText;
	itemText << message.dateTime().toString("dd.MM.yyyy hh:mm:ss");
	itemText << typeText;
	itemText << message.module();
	itemText << message.text();

	QTreeWidgetItem* pItem = new QTreeWidgetItem(itemText);

	if (setForeColor)
		for (int i = 0; i < 4; i++)
			pItem->setForeground(i, foreBrush);

	m_pLogList->addTopLevelItem(pItem);
	m_pLogList->setCurrentItem(pItem);
}

// -----------------------------------------------------------------------------