// -----------------------------------------------------------------------------
//  File        FontTestWidget.cpp
//  Project     FlowEdit
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/30 $
// -----------------------------------------------------------------------------

#include "FlowEdit/FontTestWidget.h"
#include "FlowGraphics/BitmapFontFactory.h"
#include "FlowCore/MemoryTracer.h"

#include <QPainter>
#include <QImage>

// -----------------------------------------------------------------------------
//  Class FFontTestWidget
// -----------------------------------------------------------------------------

// Constructors and destructor -------------------------------------------------

FFontTestWidget::FFontTestWidget(QWidget* pParent /* = NULL */)
	: QWidget(pParent),
	  m_pFontFactory(NULL),
	  m_bitmapIndex(-1)
{
	m_pFontFactory = new FBitmapFontFactory();
	m_pFontFactory->setFontFile(L"C:\\Windows\\Fonts\\Arial.ttf");
	bool success = m_pFontFactory->createFont();
}

FFontTestWidget::~FFontTestWidget()
{
	F_SAFE_DELETE(m_pFontFactory);
}

// Public commands -------------------------------------------------------------

// Public queries --------------------------------------------------------------

// Overrides -------------------------------------------------------------------

void FFontTestWidget::mouseReleaseEvent(QMouseEvent* pMouseEvent)
{
	m_bitmapIndex++;
	if (m_bitmapIndex >= m_pFontFactory->m_bitmaps.size())
		m_bitmapIndex = 0;
	update();
}

void FFontTestWidget::paintEvent(QPaintEvent* pPaintEvent)
{
	if (m_bitmapIndex >= 0)
	{
		//int width = m_pFontFactory->m_bitmaps[m_bitmapIndex].width;
		//int height = width;
		int width = 1024;
		uint8_t* pData = m_pFontFactory->m_bitmaps[m_bitmapIndex].data();

		QImage image(pData, width, width, QImage::Format_Indexed8);
		image.setColorCount(256);
		for (size_t i = 0; i < 256; ++i)
			image.setColor(i, qRgb(i, i, i));

		QPainter painter(this);
		painter.drawImage(0, 0, image);
	}
}

// Internal functions ----------------------------------------------------------

// -----------------------------------------------------------------------------