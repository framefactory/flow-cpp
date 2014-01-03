// -----------------------------------------------------------------------------
//  File        SplineTestWidget.cpp
//  Project     FlowEdit
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/06 $
// -----------------------------------------------------------------------------

#include "FlowEdit/SplineTestWidget.h"
#include "FlowCore/CycleCounter.h"
#include "FlowCore/Log.h"
#include "FlowCore/MemoryTracer.h"

#include <QPainter>
#include <QPaintEvent>
#include <QPainterPath>

// -----------------------------------------------------------------------------
//  Class FSplineTestWidget
// -----------------------------------------------------------------------------

// Constructors and destructor -------------------------------------------------

FSplineTestWidget::FSplineTestWidget(QWidget* pParent /* = NULL */)
	: QWidget(pParent)
{
	m_pt[0] = QPoint(20, 20);
	m_pt[1] = QPoint(620, 20);
	m_pt[2] = QPoint(20, 320);
	m_pt[3] = QPoint(620, 320);

	m_dragIndex = -1;
}

FSplineTestWidget::~FSplineTestWidget()
{
}

// Public commands -------------------------------------------------------------

// Public queries --------------------------------------------------------------

// Overrides -------------------------------------------------------------------

void FSplineTestWidget::mousePressEvent(QMouseEvent* pMouseEvent)
{
	if (pMouseEvent->button() != Qt::LeftButton)
		return;

	for (int i = 0; i < 4; ++i)
	{
		if ((m_pt[i] - pMouseEvent->pos()).manhattanLength() < 5)
		{
			m_dragPos = pMouseEvent->pos();
			m_dragIndex = i;
		}
	}
}

void FSplineTestWidget::mouseMoveEvent(QMouseEvent* pMouseEvent)
{
	if (m_dragIndex >= 0)
	{
		QPoint delta = pMouseEvent->pos() - m_dragPos;
		m_pt[m_dragIndex] += delta;
		m_dragPos = pMouseEvent->pos();
		this->update();
	}
}

void FSplineTestWidget::mouseReleaseEvent(QMouseEvent* pMouseEvent)
{
	m_dragIndex = -1;
}

void FSplineTestWidget::paintEvent(QPaintEvent* pPaintEvent)
{
	QPainter painter(this);
	painter.fillRect(pPaintEvent->rect(), QColor(255, 255, 255));

	QPainterPath path;
	path.moveTo(m_pt[0]);
	path.lineTo(m_pt[1]);
	path.moveTo(m_pt[2]);
	path.lineTo(m_pt[3]);

	painter.setPen(QColor(255, 0, 0));
	painter.drawPath(path);

	QPainterPath bsPath;
	bsPath.moveTo(m_pt[0]);
	bsPath.cubicTo(m_pt[1], m_pt[2], m_pt[3]);
	painter.setPen(QColor(255, 0, 255));
	painter.drawPath(bsPath);

	QPainterPath splinePath;
	splinePath.moveTo(m_pt[0]);

	double t0, t1, t2, t3;
	double ct0, ct1, ct2, ct3, ct22, ct33;
	double v0, v1, v2, v3;
	double cv0, cv1, cv2, cv3;
	double f, df;

	t0 = 0.0;
	t1 = (m_pt[1].x() - m_pt[0].x()) / (double)(m_pt[3].x() - m_pt[0].x());
	t2 = (m_pt[2].x() - m_pt[0].x()) / (double)(m_pt[3].x() - m_pt[0].x());
	t3 = 1.0;

	t1 = fMinMax(t1, 1e-4, 1.0 - 1e-4);
	t2 = fMinMax(t2, 1e-4, 1.0 - 1e-4);

	ct0 = t0;
	ct1 = 3.0 * (t1 - t0);
	ct2 = 3.0 * t0 - 6.0 * t1 + 3.0 * t2;
	ct3 = -t0 + 3.0 * (t1 - t2) + t3;

	ct33 = ct3 * 3.0;
	ct22 = ct2 * 2.0;

	v0 = m_pt[0].y();
	v1 = m_pt[1].y();
	v2 = m_pt[2].y();
	v3 = m_pt[3].y();

	cv0 = v0;
	cv1 = 3.0 * (v1 - v0);
	cv2 = 3.0 * v0 - 6.0 * v1 + 3.0 * v2;
	cv3 = -v0 + 3.0 * (v1 - v2) + v3;

	//F_ALIGN(16) double vct3[2] = { ct3, ct33 };
	//F_ALIGN(16) double vct2[2] = { ct2, ct22 };
	//F_ALIGN(16) double vct1[2] = { ct1, ct1 };

	//__m128d mc3 = _mm_load_pd(vct3);
	//__m128d mc2 = _mm_load_pd(vct2);
	//__m128d mc1 = _mm_load_pd(vct1);

	FCycleCounter cc;
	double cycles = 0.0;

	for (double s = 0.0; s <= 1000.0; ++s)
	{
		double x = s * 0.001;
		double t = x;
		double ct00 = ct0 - x;

		//F_ALIGN(16) double vct0[2] = { ct00, ct00 };
		//__m128d mc0 = _mm_load_pd(vct0);
		//__m128d t0 = _mm_load1_pd(&t);
		//__m128d t1, t2;

		cc.start();

		for (int i = 0; i < 14; ++i)
		{
			// evaluate the polynomial f and its derivative df
			// at t using horner scheme
			f = t * (t * (t * ct3  + ct2 ) + ct1) + ct00;
			df =     t * (t * ct33 + ct22) + ct1;
			t = t - f / df;

			/*
			t1 = _mm_mul_pd(mc3, t0);
			t1 = _mm_add_pd(t1, mc2);
			t1 = _mm_mul_pd(t1, t0);
			t1 = _mm_add_pd(t1, mc1);
			t1 = _mm_mul_sd(t1, t0);
			t1 = _mm_add_sd(t1, mc0);
			t2 = _mm_unpackhi_pd(t1, t1);
			t1 = _mm_div_sd(t1, t2);
			t1 = _mm_sub_sd(t0, t1);
			t0 = _mm_unpacklo_pd(t1, t1);
			*/
		}

		//_mm_store_sd(&t, t0);
		cc.stop();

		double y = t * ( t * ( t * cv3 + cv2) + cv1) + cv0;

		cycles += cc.cycles();

		x = m_pt[0].x() + x * (m_pt[3].x() - m_pt[0].x());
		splinePath.lineTo(x, y);
	}

	painter.setPen(QColor(0, 128, 255));
	painter.drawPath(splinePath);

	for (int i = 0; i < 4; ++i)
		painter.fillRect(m_pt[i].x() - 2, m_pt[i].y() - 2, 5, 5, QColor(255, 128, 0));

	F_TRACE << "Cycles: " << (cycles / 1000.0) << std::endl;
}

// Internal functions ----------------------------------------------------------

// -----------------------------------------------------------------------------