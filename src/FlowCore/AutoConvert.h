// -----------------------------------------------------------------------------
//  File        AutoConvert.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/12/23 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_AUTOCONVERT_H
#define FLOWCORE_AUTOCONVERT_H

#include "FlowCore/Library.h"
#include "FlowCore/Object.h"

#include <QString>

// -----------------------------------------------------------------------------
//  Class FAutoConvert
// -----------------------------------------------------------------------------

// Number to number ------------------------------------------------------------

template <typename TARGET, typename SOURCE>
struct FAutoConvert
{
	static inline TARGET convert(SOURCE src) {
		return TARGET(src);
	}
};

template <typename SOURCE>
struct FAutoConvert<bool, SOURCE>
{
	static inline bool convert(SOURCE src) {
		return src != SOURCE(0);
	}
};

// Number to string ------------------------------------------------------------

template <typename SOURCE>
struct FAutoConvert<QString, SOURCE>
{
	static inline QString convert(SOURCE val) {
		return QString::number(val);
	}
};

template <>
struct FAutoConvert<QString, bool>
{
	static inline QString convert(bool val) {
		return val ? QStringLiteral("true") : QStringLiteral("false");
	}
};

template <>
struct FAutoConvert<QString, float>
{
	static inline QString convert(float val) {
		return QString::number(val);
	}
};

template <>
struct FAutoConvert<QString, double>
{
	static inline QString convert(double val) {
		return QString::number(val);
	}
};

template <>
struct FAutoConvert<QString, FObject*>
{
	static inline QString convert(const FObject* pObj) {
		if (pObj)
			return pObj->toString();
		else
			return QStringLiteral("NULL");
	}
};

// String to number ------------------------------------------------------------

template <typename TARGET>
struct FAutoConvert<TARGET, QString>
{
	static inline TARGET convert(const QString& str) {
		return str.toInt();
	}
};

template <>
struct FAutoConvert<float, QString>
{
	static inline float convert(const QString& str) {
		return str.toFloat();
	}
};

template <>
struct FAutoConvert<double, QString>
{
	static inline double convert(const QString& str) {
		return str.toDouble();
	}
};

template <>
struct FAutoConvert<bool, QString>
{
	static inline bool convert(const QString& str) {
		double val = FAutoConvert<double, QString>::convert(str);
		return val != 0.0;
	}
};

template <>
struct FAutoConvert<qint8, QString>
{
	static inline qint8 convert(const QString& str) {
		return (qint8)str.toShort();
	}
};

template <>
struct FAutoConvert<quint8, QString>
{
	static inline quint8 convert(const QString& str) {
		return (quint8)str.toUShort();
	}
};

template <>
struct FAutoConvert<int16_t, QString>
{
	static inline int16_t convert(const QString& str) {
		return (int16_t)str.toShort();
	}
};

template <>
struct FAutoConvert<uint16_t, QString>
{
	static inline uint16_t convert(const QString& str) {
		return (uint16_t)str.toUShort();
	}
};

template <>
struct FAutoConvert<qint32, QString>
{
	static inline qint32 convert(const QString& str) {
		return str.toInt();
	}
};

template <>
struct FAutoConvert<quint32, QString>
{
	static inline quint32 convert(const QString& str) {
		return str.toUInt();
	}
};

template <>
struct FAutoConvert<qint64, QString>
{
	static inline qint64 convert(const QString& str) {
		return (qint64)str.toLongLong();
	}
};

template <>
struct FAutoConvert<quint64, QString>
{
	static inline quint64 convert(const QString& str) {
		return (quint64)str.toULongLong();
	}
};

template <>
struct FAutoConvert<FObject*, QString>
{
    static inline FObject* convert(const QString& /* str */) {
		return NULL;
	}
};

// String to string ------------------------------------------------------------

template <>
struct FAutoConvert<QString, QString>
{
	static inline QString convert(const QString& str) {
		return str;
	}
};

// Number to Object ------------------------------------------------------------

template <typename SOURCE>
struct FAutoConvert<FObject*, SOURCE>
{
    static inline FObject* convert(const SOURCE& /* val */) {
		return NULL;
	}
};

// Object to Number ------------------------------------------------------------

template <typename TARGET>
struct FAutoConvert<TARGET, FObject*>
{
    static inline TARGET convert(const FObject* /* pObj */) {
		return TARGET(0);
	}
};

template <>
struct FAutoConvert<bool, FObject*>
{
    static inline bool convert(const FObject* /* pObj */) {
		return false;
	}
};

// Object to Object ------------------------------------------------------------

template <>
struct FAutoConvert<FObject*, FObject*>
{
	static inline FObject* convert(const FObject* pObj) {
		return const_cast<FObject*>(pObj);
	}
};

// Cast-operator style template ------------------------------------------------

template <typename TARGET, typename SOURCE>
inline TARGET auto_convert(SOURCE src)
{
	return FAutoConvert<TARGET, SOURCE>::convert(src);
}
	
// -----------------------------------------------------------------------------

#endif // FLOWCORE_AUTOCONVERT_H
