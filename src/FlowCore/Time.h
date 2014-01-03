// -----------------------------------------------------------------------------
//  File        Time.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/05 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_TIME_H
#define FLOWCORE_TIME_H

#include "FlowCore/Library.h"
#include <QString>

class FArchive;

// -----------------------------------------------------------------------------
//  Class FTime
// -----------------------------------------------------------------------------

class FLOWCORE_EXPORT FTime
{
	//  Static members -----------------------------------------------

public:
	static FTime zero() { return FTime(0.0); }
	static FTime now();

	//  Constructors -------------------------------------------------

public:
	/// Default constructor (no initialization).
	FTime() { }

	/// Initializes a FTime value to a given number of seconds.
	FTime(double seconds) : m_time(seconds) { }

	/// Initializes a FTime to the given number of hours, minutes and seconds.
	FTime(int hours, int minutes, int seconds) {
		m_time = hours * 3600.0 + minutes * 60.0 + (double)seconds;
	}

	/// Initializes the time to the given number of hours, minutes, seconds and frames
	/// using the frame rate specified.
	FTime(int hours, int minutes, int seconds, int frames, int fps) {
		F_ASSERT(fps > 0);
		m_time = hours * 3600.0 + minutes * 60.0 + seconds + (double)frames / fps;
	}

	/// Initializes a FTime value using a given time code and frame rate.
	FTime(const QString& timecode, int fps) {
		F_ASSERT(fps > 0);
		_setTimecode(timecode, fps);
	}

	//  Public commands ----------------------------------------------

public:
	/// Sets the time to the given number of seconds.
	void set(double seconds) {
		m_time = seconds;
	}

	/// Sets the time to the given number of hours, minutes and seconds.
	void set(int hours, int minutes, int seconds) {
		m_time = hours * 3600.0 + minutes * 60.0 + (double)seconds;
	}

	/// Sets the time to the given number of hours, minutes, seconds and frames
	/// using the frame rate specified.
	void set(int hours, int minutes, int seconds, int frames, int fps) {
		F_ASSERT(fps > 0);
		m_time = hours * 3600.0 + minutes * 60.0 + seconds + (double)frames / fps;
	}

	/// Sets the time to the given time code using the frame rate specified.
	void set(const QString& timecode, int fps) {
		F_ASSERT(fps > 0);
		_setTimecode(timecode, fps);
	}

	/// Sets only the hours component of the time.
	void setHour(int hours) {
		m_time = m_time - floor(m_time / 3600.0) * 3600.0 + hours * 3600.0;
	}

	/// Sets only the minutes component of the time.
	void setMinute(int minutes) {
		double hours = floor(m_time / 3600.0);
		m_time = m_time - floor(m_time / 60.0) * 60.0 + hours * 3600.0 + minutes * 60.0;
	}

	/// Sets only the seconds component of the time.
	void setSecond(int seconds) {
		double minutes = floor(m_time / 60.0);
		m_time = m_time - floor(m_time) + minutes * 60.0 + seconds;
	}

	/// Sets only the frames component of the time.
	void setFrame(int frames, int fps)
	{
		F_ASSERT(fps > 0);
		double seconds = floor(m_time);
		m_time = (double)frames / fps + seconds;
	}

	/// Adds the given number of hours to the time.
	void addHours(int hours) {
		m_time += hours * 3600.0;
	}

	/// Adds the given number of minutes to the time.
	void addMinutes(int minutes) {
		m_time += minutes * 60.0;
	}

	/// Adds the given number of seconds to the time.
	void addSeconds(int seconds) {
		m_time += (double)seconds;
	}

	/// Adds the given number of frames to the time according to the specified frame rate.
	void addFrames(int frames, int fps) {
		F_ASSERT(fps > 0);
		m_time += ((double)frames / fps);
	}

	void roundToFrames(int fps) {
		F_ASSERT(fps > 0);
		m_time = floor(m_time * fps + 0.5) / fps;
	}

	//  Public queries -----------------------------------------------

	/// Returns the sign component of the time. If the time is positive or zero,
	/// the function returns 1, otherwise -1.
	int sign() const {
		return m_time < 0 ? -1 : 1;
	}

	/// Returns the hour component of the time. For -04:12:39:05, the returned
	/// number of hours is 4.
	int hour() const {
		return (int)floor(abs(m_time) / 3600.0);
	}

	/// Returns the minute component of the time. For -04:12:39:05, the returned
	/// number of minutes is 12.
	int minute() const {
		double absTime = abs(m_time);
		return (int)floor((absTime - floor(absTime / 3600.0) * 3600.0) / 60.0);
	}

	/// Returns the second component of the time. For -04:12:39:05, the returned
	/// number of seconds is 39.
	int second() const {
		double absTime = abs(m_time);
		return (int)floor(absTime - floor(absTime / 60.0) * 60.0);
	}

	/// Returns the frame component of the time according to the given frame rate.
	/// For -04:12:39:05, the returned number of frames is 5.
	int frame(int fps) const {
		F_ASSERT(fps > 0);
		double absTime = abs(m_time);
		return (int)((absTime - floor(absTime) + s_eps) * fps);
	}

	/// Returns the fraction of a second in the range [0.0, 1.0)
	double fraction() const {
		double absTime = abs(m_time);
		return absTime - floor(absTime);
	}

	/// Returns the total number of hours. For -01:30:00:00, the returned
	/// number of hours is -1.5.
	double toHours() const {
		return m_time / 3600.0;
	}

	/// Returns the total number of minutes. For -01:30:00:00, the returned
	/// number of minutes is -90.
	double toMins() const {
		return m_time / 600.0;
	}

	/// Returns the total number of seconds. For -01:30:00:00, the returned
	/// number of seconds is -5400.
	double toSeconds() const {
		return m_time;
	}

	/// Returns the total number of frames according to the given frame rate.
	double toFrames(int fps) const {
		F_ASSERT(fps > 0);
		return m_time * fps;
	}

	/// Returns a string representation of the time according to the given frame rate.
	/// The format of the string is 'ghh:mm:ss:ff' where g is either a space character
	/// or a minus sign if the time is negative.
	QString timecode(int fps) const {
		return _getTimecode(fps);
	}

	/// Returns a string representation of the time according to the given frame rate.
	/// The format of the string is 'ghh:mm:ss:ff' where g is either a space character
	/// or a minus sign if the time is negative.
	QString toString(int fps = 1000) const {
		return _getTimecode(fps);
	}

	//  Operator overloads -------------------------------------------

	/// Adds two time values.
	FTime operator+(const FTime rhs) const {
		return FTime(m_time + rhs.m_time);
	}

	/// Adds two time values.
	FTime operator+=(const FTime rhs) {
		m_time += rhs.m_time;
		return FTime(m_time);
	}

	/// Subtracts two time values.
	FTime operator-(const FTime rhs) const {
		return FTime(m_time - rhs.m_time);
	}

	/// Subtracts two time values.
	FTime operator-=(const FTime rhs) {
		m_time -= rhs.m_time;
		return FTime(m_time);
	}

	/// Multiplies a time by a given factor.
	FTime operator*(double factor) const {
		return FTime(m_time * factor);
	}

	/// Multiplies a time by a given factor.
	FTime operator*=(double factor) {
		m_time *= factor;
		return FTime(m_time);
	}

	/// Divides a time by a given factor.
	FTime operator/(double factor) const {
		return FTime(m_time * factor);
	}

	/// Divides a time by a given factor.
	FTime operator/=(double factor) {
		m_time /= factor;
		return FTime(m_time);
	}

	bool operator>(const FTime rhs) const {
		return m_time > rhs.m_time;
	}

	bool operator<(const FTime rhs) const {
		return m_time < rhs.m_time;
	}

	bool operator==(const FTime rhs) const {
		return m_time == rhs.m_time;
	}

	bool operator!=(const FTime rhs) const {
		return m_time != rhs.m_time;
	}

	operator double() const { return m_time; }

	//  Internal functions -------------------------------------------

private:
	void _setTimecode(const QString& timecode, int fps);
	QString _getTimecode(int fps) const;

	//  Internal data members ----------------------------------------

	static const double s_eps;
	double m_time;
};

// Related non-member functions ------------------------------------------------

	/// Serialization: write operator.
	FLOWCORE_EXPORT FArchive& operator<<(FArchive& ar, FTime t);
	/// Serialization: read operator.
	FLOWCORE_EXPORT FArchive& operator>>(FArchive& ar, FTime& t);

// -----------------------------------------------------------------------------

#endif // FLOWCORE_TIME_H