// -----------------------------------------------------------------------------
//  File        JsonUtils.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2014/01/02 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_JSONUTILS_H
#define FLOWCORE_JSONUTILS_H

#include "FlowCore/Library.h"

#include "FlowCore/Vector2T.h"
#include "FlowCore/Vector3T.h"
#include "FlowCore/Vector4T.h"
#include "FlowCore/Matrix3T.h"
#include "FlowCore/Matrix4T.h"

#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>

#include <vector>

// -----------------------------------------------------------------------------
//  Class FJsonUtils
// -----------------------------------------------------------------------------

class FLOWCORE_EXPORT FJsonUtils
{
	//  Constructors and destructor ----------------------------------

private:
	/// Private constructor. Class provides only static methods
	FJsonUtils();

	//  Public static functions --------------------------------------

public:
	template <typename T>
	static QJsonArray toArray(const FVector2T<T>& vec);

	template <typename T>
	static QJsonArray toArray(const FVector3T<T>& vec);

	template <typename T>
	static QJsonArray toArray(const FVector4T<T>& vec);

	template <typename T>
	static QJsonArray toArray(const FMatrix3T<T>& vec);

	template <typename T>
	static QJsonArray toArray(const FMatrix4T<T>& vec);

	template <typename T>
	static QJsonArray toArray(const std::vector<T>& vec);

	template <typename T>
	static bool toVector(const QJsonValue& val, FVector2T<T>& vec);

	template <typename T>
	static bool toVector(const QJsonValue& val, FVector3T<T>& vec);

	template <typename T>
	static bool toVector(const QJsonValue& val, FVector4T<T>& vec);

	template <typename T>
	static bool toVector(const QJsonValue& val, FMatrix3T<T>& vec);

	template <typename T>
	static bool toVector(const QJsonValue& val, FMatrix4T<T>& vec);

	template <typename T>
	static bool toVector(const QJsonValue& val, std::vector<T>& vec);
};

// Template functions ----------------------------------------------------------

template <typename T>
QJsonArray FJsonUtils::toArray(const FVector2T<T>& vec)
{
	QJsonArray arr;
	arr.push_back(vec.x);
	arr.push_back(vec.y);
	return arr;
}

template <typename T>
QJsonArray FJsonUtils::toArray(const FVector3T<T>& vec)
{
	QJsonArray arr;
	arr.push_back(vec.x);
	arr.push_back(vec.y);
	arr.push_back(vec.z);
	return arr;
}

template <typename T>
QJsonArray FJsonUtils::toArray(const FVector4T<T>& vec)
{
	QJsonArray arr;
	arr.push_back(vec.x);
	arr.push_back(vec.y);
	arr.push_back(vec.z);
	arr.push_back(vec.w);
	return arr;
}

template <typename T>
QJsonArray FJsonUtils::toArray(const FMatrix3T<T>& mat)
{
	QJsonArray arr;
	for (size_t col = 0; col < 3; ++col) {
		for (size_t row = 0; row < 3; ++row) {
			arr.push_back(mat[row][col]);
		}
	}
	return arr;
}

template <typename T>
QJsonArray FJsonUtils::toArray(const FMatrix4T<T>& mat)
{
	QJsonArray arr;
	for (size_t col = 0; col < 4; ++col) {
		for (size_t row = 0; row < 4; ++row) {
			arr.push_back(mat[row][col]);
		}
	}
	return arr;
}

template <typename T>
QJsonArray FJsonUtils::toArray(const std::vector<T>& vec)
{
	QJsonArray arr;
	for (size_t i = 0; i < vec.size(); ++i) {
		arr.push_back(vec[i]);
	}
	return arr;
}

template <typename T>
bool FJsonUtils::toVector(const QJsonValue& val, FVector2T<T>& vec)
{
	QJsonArray arr = val.toArray();
	if (arr.count() < 2) {
		return false;
	}

	vec.x = (T)(arr[0].toDouble());
	vec.y = (T)(arr[1].toDouble());

	return true;
}

template <typename T>
bool FJsonUtils::toVector(const QJsonValue& val, FVector3T<T>& vec)
{
	QJsonArray arr = val.toArray();
	if (arr.count() < 3) {
		return false;
	}

	vec.x = (T)(arr[0].toDouble());
	vec.y = (T)(arr[1].toDouble());
	vec.z = (T)(arr[2].toDouble());

	return true;
}

template <typename T>
bool FJsonUtils::toVector(const QJsonValue& val, FVector4T<T>& vec)
{
	QJsonArray arr = val.toArray();
	if (arr.count() < 4) {
		return false;
	}

	vec.x = (T)(arr[0].toDouble());
	vec.y = (T)(arr[1].toDouble());
	vec.z = (T)(arr[2].toDouble());
	vec.w = (T)(arr[3].toDouble());

	return true;
}

// -----------------------------------------------------------------------------

#endif // FLOWCORE_JSONUTILS_H