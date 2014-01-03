// -----------------------------------------------------------------------------
//  File        Time.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/05 $
// -----------------------------------------------------------------------------

#include "FlowCore/Time.h"
#include "FlowCore/Archive.h"

#include <QTime>
#include <QRegExp>
#include <QStringList>
#include <vector>

// -----------------------------------------------------------------------------
//  Class FTime
// -----------------------------------------------------------------------------

const double FTime::s_eps = 1e-10;

FTime FTime::now()
{
	QTime time = QTime::currentTime();
	return FTime(time.hour(), time.minute(), time.second());
}

// Internal functions ----------------------------------------------------------

void FTime::_setTimecode(const QString& timecode, int fps)
{
	QStringList parts = timecode.split(QRegExp("[.,:;-\\s]"), QString::KeepEmptyParts);
	int n = parts.size();

	int hours = (n - 4 < 0) ? 0 : parts[n - 4].toInt();
	int minutes = (n - 3 < 0) ? 0 : parts[n - 3].toInt();
	int seconds = (n - 2 < 0) ? 0 : parts[n - 2].toInt();
	int frames = (n - 1 < 0) ? 0 : parts[n - 1].toInt();

	set(hours, minutes, seconds, frames, fps);
}

QString FTime::_getTimecode(int fps) const
{
	if (fps < 0) {
		return QString("%1:%2:%3")
			.arg(hour(), 2, 10, QLatin1Char('0'))
			.arg(minute(), 2, 10, QLatin1Char('0'))
			.arg(second(), 2, 10, QLatin1Char('0'));
	}

	int d = (fps > 100) ? 3 : ((fps > 10) ? 2 : 1);
	bool f = fps == 10 || fps == 100 || fps == 1000;

	return QString("%1%2").arg(f ? "." : ":")
		.arg(frame(fps), d, 10, QLatin1Char('0'));
}

// Related non-member functions ------------------------------------------------

FArchive& operator<<(FArchive& ar, FTime t)
{
	ar << (double)t;
	return ar;
}

FArchive& operator>>(FArchive& ar, FTime& t)
{
	double v;
	ar >> v;
	t.set(v);
	return ar;
}

// -----------------------------------------------------------------------------