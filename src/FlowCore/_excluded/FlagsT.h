// -----------------------------------------------------------------------------
//  File        FlagsT.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/11/22 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_FLAGST_H
#define FLOWCORE_FLAGST_H

#include "FlowCore/Library.h"
#include <ostream>

class FArchive;

// -----------------------------------------------------------------------------
//  Class FFlagsT
// -----------------------------------------------------------------------------

template <typename T>
class FFlagsT
{
public:
	typedef T enum_t;

	//  Constructors -------------------------------------------------

	FFlagsT() : m_flags(0) { }
	FFlagsT(T flag) : m_flags(flag) { }
	FFlagsT(const FFlagsT<T>& flags) : m_flags(flags.m_flags) { }

private:
	explicit FFlagsT(int32_t flags) : m_flags(flags) { }

	//  Operators ----------------------------------------------------

public:
	operator int32_t() const {
		return m_flags;
	}

	FFlagsT<T>& operator=(const FFlagsT<T>& flags) {
		m_flags = flags.m_flags;
		return *this;
	}

	FFlagsT<T>& operator=(T flag) {
		m_flags = flag;
		return *this;
	}

	FFlagsT<T>& operator&=(int32_t mask) {
		m_flags &= mask;
		return *this;
	}
	FFlagsT<T>& operator&=(uint32_t mask) {
		m_flags &= mask;
		return *this;
	}

	FFlagsT<T>& operator|=(FFlagsT<T> flags) {
		m_flags |= flags.m_flags;
		return *this;
	}
	FFlagsT<T>& operator|=(T flag) {
		m_flags |= flag;
		return *this;
	}

	FFlagsT<T> operator|(FFlagsT<T> flags) const {
		return FFlagsT<T>(m_flags | flags.m_flags);
	}
	FFlagsT<T> operator|(T flag) const {
		return FFlagsT<T>(m_flags | flag);
	}
	
	FFlagsT<T> operator&(int32_t mask) const {
		return FFlagsT<T>(m_flags & mask);
	}
	FFlagsT<T> operator&(uint32_t mask) const {
		return FFlagsT<T>(m_flags & mask);
	}
	FFlagsT<T> operator&(T flag) const {
		return FFlagsT<T>(m_flags & flag);
	}

	/// Tests if the given flag is set.
	bool test(enum_t flag) const {
		return (m_flags & flag) == flag && (flag != 0 || m_flags == int32_t(flag));
	}

	/// Prints a comma-separated list of all active flags to the given stream.
	template <typename C>
	friend std::basic_ostream<C>& operator<<(
		std::basic_ostream<C>& stream, FFlagsT<T>& flags);

	friend FArchive& operator<< (FArchive& ar, const FFlagsT<T>& flags);
	friend FArchive& operator>> (FArchive& ar, FFlagsT<T>& flags);

private:
	int32_t m_flags;
};

// Related non-member functions ------------------------------------------------

template <typename C, typename T>
std::basic_ostream<C>& operator<<(
	std::basic_ostream<C>& stream, FFlagsT<T>& flags)
{
	uint32_t bit = 1;
	bool first = true;
	
	do {
		const char* name = T((typename T::state_t)bit).name();
		if (name) {
			if (first) {
				first = false;
				stream << ", ";
			}
			stream << name;
		}
	} while (bit <<= 1);

	return stream;
}

#define F_DECLARE_FLAGS(flagClassName, enumClassName) \
	typedef FFlagsT<enumClassName> flagClassName; \
	inline flagClassName operator|(enumClassName f1, enumClassName f2) { \
		return flagClassName(f1) | f2; } \
	inline flagClassName operator|(enumClassName f1, flagClassName f2) { \
		return f2 | f1; }

// -----------------------------------------------------------------------------

#endif // FLOWCORE_FLAGST_H