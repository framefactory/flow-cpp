// -----------------------------------------------------------------------------
//  File        SingletonT.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/10/18 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_SINGLETONT_H
#define FLOWCORE_SINGLETONT_H

#include "FlowCore/Library.h"

// -----------------------------------------------------------------------------
//  Class FSingletonAutoT
// -----------------------------------------------------------------------------

/// Template class which can be used as base for automatic singleton classes.
/// Singletons that derive from FSingletonAutoT are automatically created the
/// first time their instance() function is called and are destroyed automatically
/// when the program is terminated. The template type is the type of the derived
/// class. The derived class also must declare the template base class as a friend.
template <typename T>
class FSingletonAutoT
{
	//  Static methods -----------------------------------------------

public:
	/// Returns a pointer to the only instance of this class.
	/// The instance is created the first time this function is called.
	inline static T* instance()
	{
		if (!s_pInstance)
			s_pInstance = new T();

		return s_pInstance;
	}

	/// Returns true if no instance is present.
	static bool isNull() { return (s_pInstance == NULL); }

	//  Constructors and destructor ----------------------------------

protected:
	/// Protected default constructor. Use the static member Instance()
	/// to get access to the single instance of this class.
	FSingletonAutoT() { }
	/// Virtual destructor.
	virtual ~FSingletonAutoT() { }

	//  Internal data members ----------------------------------------

private:
	template <typename S>
	struct FSingletonGuardT
	{
		FSingletonGuardT(S** ppInstance)
			: m_ppInstance(ppInstance) { }

		~FSingletonGuardT()
		{
			if (*m_ppInstance)
			{
				delete *m_ppInstance;
				*m_ppInstance = NULL;
			}
		}

		S** m_ppInstance;
	};

	static T* s_pInstance;
	static FSingletonGuardT<T> s_guard;
};

template <typename T>
T* FSingletonAutoT<T>::s_pInstance = NULL;

template <typename T>
typename FSingletonAutoT<T>:: template FSingletonGuardT<T> FSingletonAutoT<T>::s_guard(&s_pInstance);

// -----------------------------------------------------------------------------
//  Class FSingletonT
// -----------------------------------------------------------------------------

/// Derive a class from this template to ensure that only one object can be
/// created from the class. The derived class must provide a private or protected
/// default constructor. createInstance() needs to be called explicitly to create
/// the singleton instance; destroyInstance() deletes the singleton instance.
/// The template parameter is the type of the derived class. The derived class
/// also must declare the template base class as a friend.
template <typename T>
class FSingletonT
{
	//  Static methods -----------------------------------------------

public:
	/// Creates the only instance of the class. If the instance
	/// was already created, the function throws an assertion.
	static void createInstance()
	{
		if (!s_pInstance)
			s_pInstance = new T();
		else
			F_ASSERT(false);
	}

	/// Returns a pointer to the only instance of this class.
	inline static T* instance()
	{
		F_ASSERT(s_pInstance);
		return s_pInstance;
	}

	/// Destroys the only instance of this class.
	static void destroyInstance()
	{
		if (s_pInstance)
		{
			delete s_pInstance;
			s_pInstance = NULL;
		}
	}

	/// Returns true if no instance is present.
	static bool isNull() { return (s_pInstance == NULL); }

	//  Constructors and destructor ----------------------------------

protected:
	/// Protected default constructor. Use the static member Instance()
	/// to get access to the single instance of this class.
	FSingletonT() { }
	/// Virtual destructor.
	virtual ~FSingletonT() { }

	//  Internal data members ----------------------------------------

private:
	template <typename S>
	class FSingletonGuardT
	{
	public:
		~FSingletonGuardT() { S::destroyInstance(); }
	};

	static T* s_pInstance;
	static FSingletonGuardT<T> s_guard;
};

template <typename T>
T* FSingletonT<T>::s_pInstance = NULL;

template <typename T>
typename FSingletonT<T>::template FSingletonGuardT<T> FSingletonT<T>::s_guard;

// -----------------------------------------------------------------------------
//  Class FSingletonAutoBaseT
// -----------------------------------------------------------------------------

/// Derive a class from this template to ensure that only one object can be created
/// from the class. The derived class must provide a private or protected default
/// constructor. In addition to FSingletonAutoT this class provides an additional
/// template parameter to specify a base class.
template <typename T, typename BASE>
class FSingletonAutoBaseT : public BASE
{
	//  Static methods -----------------------------------------------

public:
	/// Returns a pointer to the only instance of this class.
	/// The instance is created the first time this function is called.
	inline static T* instance()
	{
		if (!s_pInstance)
			s_pInstance = new T();

		return s_pInstance;
	}

	/// Returns true if no instance is present.
	static bool isNull() { return (s_pInstance == NULL); }

	//  Constructors and destructor ----------------------------------

protected:
	/// Protected default constructor. Use the static member Instance()
	/// to get access to the single instance of this class.
	FSingletonAutoBaseT() { }
	/// Virtual destructor.
	virtual ~FSingletonAutoBaseT() { }

	//  Internal data members ----------------------------------------

private:
	template <typename S>
	struct FSingletonGuardT
	{
		FSingletonGuardT(S** ppInstance)
			: m_ppInstance(ppInstance) { }

		~FSingletonGuardT()
		{
			if (*m_ppInstance)
			{
				delete *m_ppInstance;
				*m_ppInstance = NULL;
			}
		}

		S** m_ppInstance;
	};

	static T* s_pInstance;
	static FSingletonGuardT<T> s_guard;

};

template <typename T, typename BASE>
T* FSingletonAutoBaseT<T, BASE>::s_pInstance = NULL;

template <typename T, typename BASE>
typename FSingletonAutoBaseT<T, BASE>::template FSingletonGuardT<T>
	FSingletonAutoBaseT<T, BASE>::s_guard(&s_pInstance);

// -----------------------------------------------------------------------------
//  Class FSingletonBaseT
// -----------------------------------------------------------------------------

/// Derive a class from this template to ensure that only one object can be created
/// from the class. The derived class must provide a private or protected default
/// constructor. In addition to FSingletonT this class provides an additional
/// template parameter to specify a base class.
template <typename T, typename BASE>
class FSingletonBaseT : public BASE
{
	//  Static methods -----------------------------------------------

public:
	/// Creates the only instance of the class. If the instance
	/// was already created, the function throws an assertion.
	static void createInstance()
	{
		if (!s_pInstance)
			s_pInstance = new T();
		else
			F_ASSERT(false);
	}

	/// Returns a pointer to the only instance of this class.
	inline static T* instance()
	{
		F_ASSERT(s_pInstance);
		return s_pInstance;
	}

	/// Destroys the only instance of this class.
	static void destroyInstance()
	{
		if (s_pInstance)
		{
			delete s_pInstance;
			s_pInstance = NULL;
		}
	}

	/// Returns true if no instance is present.
	static bool isNull() { return (s_pInstance == NULL); }

	//  Constructors and destructor ----------------------------------

protected:
	/// Protected default constructor. Use the static member Instance()
	/// to get access to the single instance of this class.
	FSingletonBaseT() { }
	/// Virtual destructor.
	virtual ~FSingletonBaseT() { }

private:

	//  Internal data members ----------------------------------------

private:
	template <typename S>
	class FSingletonGuardT
	{
	public:
		~FSingletonGuardT() { S::destroyInstance(); }
	};

	static T* s_pInstance;
	static FSingletonGuardT<T> s_guard;
};

template <typename T, typename BASE>
T* FSingletonBaseT<T, BASE>::s_pInstance = NULL;

template <typename T, typename BASE>
typename FSingletonBaseT<T, BASE>:: template FSingletonGuardT<T> FSingletonBaseT<T, BASE>::s_guard;

// -----------------------------------------------------------------------------

#endif // FLOWCORE_SINGLETONT_H
