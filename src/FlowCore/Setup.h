// -----------------------------------------------------------------------------
//  File        Setup.h
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2012/10/17 $
// -----------------------------------------------------------------------------

#ifndef FLOWCORE_SETUP_H
#define FLOWCORE_SETUP_H

#include <stdint.h>

// -----------------------------------------------------------------------------
//  Platform 
// -----------------------------------------------------------------------------

#define FLOW_PLATFORM_UNKNOWN          0x00000000
#define FLOW_PLATFORM_WINDOWS          0x00010000
#define FLOW_PLATFORM_LINUX            0x00020000
#define FLOW_PLATFORM_UNIX             0x00040000
#define FLOW_PLATFORM_OSX              0x00080000
#define FLOW_PLATFORM_IOS              0x00100000
#define FLOW_PLATFORM_ANDROID          0x00200000

#if defined(_WIN32)
  #define FLOW_PLATFORM FLOW_PLATFORM_WINDOWS
#elif defined(__linux)
  #define FLOW_PLATFORM FLOW_PLATFORM_LINUX
#elif defined(__unix)
  #define FLOW_PLATFORM FLOW_PLATFORM_UNIX
#elif defined(__APPLE__)
  #define FLOW_PLATFORM FLOW_PLATFORM_OSX
//#elif defined(???)
//  #define FLOW_PLATFORM FLOW_PLATFORM_IOS
#elif defined(__ANDROID__)
  #define FLOW_PLATFORM FLOW_PLATFORM_ANDROID
#else
  #define FLOW_PLATFORM FLOW_PLATFORM_UNKNOWN
#endif

// -----------------------------------------------------------------------------
//  Compiler 
// -----------------------------------------------------------------------------

#define FLOW_COMPILER_UNKNOWN          0x00000000

// Visual C++
#define FLOW_COMPILER_VC               0x01000000
#define FLOW_COMPILER_VC2              0x01000010
#define FLOW_COMPILER_VC4              0x01000020
#define FLOW_COMPILER_VC5              0x01000030
#define FLOW_COMPILER_VC6              0x01000040
#define FLOW_COMPILER_VC2002           0x01000050
#define FLOW_COMPILER_VC2003           0x01000060
#define FLOW_COMPILER_VC2005           0x01000070
#define FLOW_COMPILER_VC2008           0x01000080
#define FLOW_COMPILER_VC2010           0x01000090
#define FLOW_COMPILER_VC2011           0x010000A0

// GCC
#define FLOW_COMPILER_GCC              0x02000000
#define FLOW_COMPILER_GCC_LLVM         0x02000001
#define FLOW_COMPILER_GCC_CLANG        0x02000002
#define FLOW_COMPILER_GCC30            0x02000010
#define FLOW_COMPILER_GCC31            0x02000020
#define FLOW_COMPILER_GCC32            0x02000030
#define FLOW_COMPILER_GCC33            0x02000040
#define FLOW_COMPILER_GCC34            0x02000050
#define FLOW_COMPILER_GCC35            0x02000060
#define FLOW_COMPILER_GCC40            0x02000070
#define FLOW_COMPILER_GCC41            0x02000080
#define FLOW_COMPILER_GCC42            0x02000090
#define FLOW_COMPILER_GCC43            0x020000A0
#define FLOW_COMPILER_GCC44            0x020000B0
#define FLOW_COMPILER_GCC45            0x020000C0
#define FLOW_COMPILER_GCC46            0x020000D0
#define FLOW_COMPILER_GCC47            0x020000E0
#define FLOW_COMPILER_GCC48            0x020000F0
#define FLOW_COMPILER_GCC49            0x02000100
#define FLOW_COMPILER_GCC50            0x02000200

// Clang
#define FLOW_COMPILER_CLANG            0x20000000
#define FLOW_COMPILER_CLANG26          0x20000010
#define FLOW_COMPILER_CLANG27          0x20000020
#define FLOW_COMPILER_CLANG28          0x20000030
#define FLOW_COMPILER_CLANG29          0x20000040
#define FLOW_COMPILER_CLANG30          0x20000050
#define FLOW_COMPILER_CLANG31          0x20000060
#define FLOW_COMPILER_CLANG32          0x20000070
#define FLOW_COMPILER_CLANG33          0x20000080

// LLVM GCC
#define FLOW_COMPILER_LLVM_GCC         0x40000000

// Intel
#define FLOW_COMPILER_INTEL            0x80000000
#define FLOW_COMPILER_INTEL9           0x80000010
#define FLOW_COMPILER_INTEL10_0        0x80000020
#define FLOW_COMPILER_INTEL10_1        0x80000030
#define FLOW_COMPILER_INTEL11_0        0x80000040
#define FLOW_COMPILER_INTEL11_1        0x80000050
#define FLOW_COMPILER_INTEL12_0        0x80000060
#define FLOW_COMPILER_INTEL12_1        0x80000070
#define FLOW_COMPILER_INTEL13_0        0x80000080

#if defined(__INTEL_COMPILER)
#  if __INTEL_COMPILER == 900
#    define FLOW_COMPILER FLOW_COMPILER_INTEL9
#  elif __INTEL_COMPILER == 1000
#    define FLOW_COMPILER FLOW_COMPILER_INTEL10_0
#  elif __INTEL_COMPILER == 1010
#    define FLOW_COMPILER FLOW_COMPILER_INTEL10_1
#  elif __INTEL_COMPILER == 1100
#    define FLOW_COMPILER FLOW_COMPILER_INTEL11_0
#  elif __INTEL_COMPILER == 1110
#    define FLOW_COMPILER FLOW_COMPILER_INTEL11_1
#  elif __INTEL_COMPILER == 1200
#    define FLOW_COMPILER FLOW_COMPILER_INTEL12_0
#  elif __INTEL_COMPILER == 1210
#    define FLOW_COMPILER FLOW_COMPILER_INTEL12_1
#  elif __INTEL_COMPILER == 1300
#    define FLOW_COMPILER FLOW_COMPILER_INTEL13_0
#  else
#    define FLOW_COMPILER FLOW_COMPILER_INTEL
#  endif

#elif defined(_MSC_VER)
#  if _MSC_VER == 900
#    define FLOW_COMPILER FLOW_COMPILER_VC2
#  elif _MSC_VER == 1000
#    define FLOW_COMPILER FLOW_COMPILER_VC4
#  elif _MSC_VER == 1100
#    define FLOW_COMPILER FLOW_COMPILER_VC5
#  elif _MSC_VER == 1200
#    define FLOW_COMPILER FLOW_COMPILER_VC6
#  elif _MSC_VER == 1300
#    define FLOW_COMPILER FLOW_COMPILER_VC2002
#  elif _MSC_VER == 1310
#    define FLOW_COMPILER FLOW_COMPILER_VC2003
#  elif _MSC_VER == 1400
#    define FLOW_COMPILER FLOW_COMPILER_VC2005
#  elif _MSC_VER == 1500
#    define FLOW_COMPILER FLOW_COMPILER_VC2008
#  elif _MSC_VER == 1600
#    define FLOW_COMPILER FLOW_COMPILER_VC2010
#  elif _MSC_VER == 1700
#    define FLOW_COMPILER FLOW_COMPILER_VC2011
#  else
#    define FLOW_COMPILER FLOW_COMPILER_VC
#  endif

#elif defined(__clang__)
#  if(__clang_major__ == 2) && (__clang_minor__ == 6)
#    define FLOW_COMPILER FLOW_COMPILER_CLANG26
#  elif(__clang_major__ == 2) && (__clang_minor__ == 7)
#    define FLOW_COMPILER FLOW_COMPILER_CLANG27
#  elif(__clang_major__ == 2) && (__clang_minor__ == 8)
#    define FLOW_COMPILER FLOW_COMPILER_CLANG28
#  elif(__clang_major__ == 2) && (__clang_minor__ == 9)
#    define FLOW_COMPILER FLOW_COMPILER_CLANG29
#  elif(__clang_major__ == 3) && (__clang_minor__ == 0)
#    define FLOW_COMPILER FLOW_COMPILER_CLANG30
#  elif(__clang_major__ == 3) && (__clang_minor__ == 1)
#    define FLOW_COMPILER FLOW_COMPILER_CLANG31
#  elif(__clang_major__ == 3) && (__clang_minor__ == 2)
#    define FLOW_COMPILER FLOW_COMPILER_CLANG32
#  elif(__clang_major__ == 3) && (__clang_minor__ == 3)
#    define FLOW_COMPILER FLOW_COMPILER_CLANG33
#  else
#    define FLOW_COMPILER FLOW_COMPILER_CLANG
#  endif

#elif(defined(__GNUC__) || defined(__MINGW32__))
#  if defined (__llvm__)
#    define FLOW_COMPILER_GCC_EXTRA FLOW_COMPILER_GCC_LLVM
#  elif defined (__clang__)
#    define FLOW_COMPILER_GCC_EXTRA FLOW_COMPILER_GCC_CLANG
#  else
#    define FLOW_COMPILER_GCC_EXTRA 0
#  endif
#
#  if   (__GNUC__ == 3) && (__GNUC_MINOR__ == 2)
#    define FLOW_COMPILER FLOW_COMPILER_GCC32
#  elif (__GNUC__ == 3) && (__GNUC_MINOR__ == 3)
#    define FLOW_COMPILER FLOW_COMPILER_GCC33
#  elif (__GNUC__ == 3) && (__GNUC_MINOR__ == 4)
#    define FLOW_COMPILER FLOW_COMPILER_GCC34
#  elif (__GNUC__ == 3) && (__GNUC_MINOR__ == 5)
#    define FLOW_COMPILER FLOW_COMPILER_GCC35
#  elif (__GNUC__ == 4) && (__GNUC_MINOR__ == 0)
#    define FLOW_COMPILER (FLOW_COMPILER_GCC40 | FLOW_COMPILER_GCC_EXTRA)
#  elif (__GNUC__ == 4) && (__GNUC_MINOR__ == 1)
#    define FLOW_COMPILER (FLOW_COMPILER_GCC41 | FLOW_COMPILER_GCC_EXTRA)
#  elif (__GNUC__ == 4) && (__GNUC_MINOR__ == 2)
#    define FLOW_COMPILER (FLOW_COMPILER_GCC42 | FLOW_COMPILER_GCC_EXTRA)
#  elif (__GNUC__ == 4) && (__GNUC_MINOR__ == 3)
#    define FLOW_COMPILER (FLOW_COMPILER_GCC43 | FLOW_COMPILER_GCC_EXTRA)
#  elif (__GNUC__ == 4) && (__GNUC_MINOR__ == 4)
#    define FLOW_COMPILER (FLOW_COMPILER_GCC44 | FLOW_COMPILER_GCC_EXTRA)
#  elif (__GNUC__ == 4) && (__GNUC_MINOR__ == 5)
#    define FLOW_COMPILER (FLOW_COMPILER_GCC45 | FLOW_COMPILER_GCC_EXTRA)
#  elif (__GNUC__ == 4) && (__GNUC_MINOR__ == 6)
#    define FLOW_COMPILER (FLOW_COMPILER_GCC46 | FLOW_COMPILER_GCC_EXTRA)
#  elif (__GNUC__ == 4) && (__GNUC_MINOR__ == 7)
#    define FLOW_COMPILER (FLOW_COMPILER_GCC47 | FLOW_COMPILER_GCC_EXTRA)
#  elif (__GNUC__ == 4) && (__GNUC_MINOR__ == 8)
#    define FLOW_COMPILER (FLOW_COMPILER_GCC48 | FLOW_COMPILER_GCC_EXTRA)
#  elif (__GNUC__ == 4) && (__GNUC_MINOR__ == 9)
#    define FLOW_COMPILER (FLOW_COMPILER_GCC49 | FLOW_COMPILER_GCC_EXTRA)
#  elif (__GNUC__ == 5) && (__GNUC_MINOR__ == 0)
#    define FLOW_COMPILER (FLOW_COMPILER_GCC50 | FLOW_COMPILER_GCC_EXTRA)
#  else
#    define FLOW_COMPILER (FLOW_COMPILER_GCC | FLOW_COMPILER_GCC_EXTRA)
#  endif

#else
#  define FLOW_COMPILER FLOW_COMPILER_UNKNOWN
#endif

// -----------------------------------------------------------------------------
//  Language 
// -----------------------------------------------------------------------------

#define FLOW_LANG_CXX                  0x00000000
#define FLOW_LANG_CXX98               (0x00000002 | FLOW_LANG_CXX)
#define FLOW_LANG_CXX03               (0x00000004 | FLOW_LANG_CXX98)
#define FLOW_LANG_CXX0X               (0x00000008 | FLOW_LANG_CXX03)
#define FLOW_LANG_CXX11               (0x00000010 | FLOW_LANG_CXX0X)
#define FLOW_LANG_CXXMS                0x00000020
#define FLOW_LANG_CXXGNU               0x00000040

#if(((FLOW_COMPILER & FLOW_COMPILER_GCC) == FLOW_COMPILER_GCC) && defined(__GXX_EXPERIMENTAL_CXX0X__)) 
#  define FLOW_LANG FLOW_LANG_CXX0X
#elif(((FLOW_COMPILER & FLOW_COMPILER_VC) == FLOW_COMPILER_VC) && defined(_MSC_EXTENSIONS))
#  define FLOW_LANG FLOW_LANG_CXXMS
#elif(((FLOW_COMPILER & FLOW_COMPILER_VC) == FLOW_COMPILER_VC) && !defined(_MSC_EXTENSIONS))
#  if(FLOW_COMPILER >= FLOW_COMPILER_VC2010)
#    define FLOW_LANG FLOW_LANG_CXX0X
#  else
#    define FLOW_LANG FLOW_LANG_CXX98
#  endif
#elif((FLOW_COMPILER & FLOW_COMPILER_GCC) == FLOW_COMPILER_GCC)
#  define FLOW_LANG FLOW_LANG_CXX98
#elif((FLOW_COMPILER & FLOW_COMPILER_CLANG) == FLOW_COMPILER_CLANG) 
#  define FLOW_LANG FLOW_LANG_CXX98
#else
#  define FLOW_LANG FLOW_LANG_CXX
#endif

// -----------------------------------------------------------------------------
//  Architecture 
// -----------------------------------------------------------------------------

#define FLOW_ARCH_32                   0x00000010
#define FLOW_ARCH_64                   0x00000020

#define FLOW_INTRINSICS_NONE           0x00000000
#define FLOW_INTRINSICS_SSE2           0x00000100
#define FLOW_INTRINSICS_SSE3           0x00000200
#define FLOW_INTRINSICS_SSE4           0x00000400
#define FLOW_INTRINSICS_AVX            0x00000800
#define FLOW_INTRINSICS_AVX2           0x00001000
#define FLOW_INTRINSICS_NEON           0x00002000

#if ((defined(__WORDSIZE) && (__WORDSIZE == 64)) || defined(__arch64__) || defined(__LP64__) || defined(_M_X64) || defined(__ppc64__) || defined(__x86_64__))
#  define FLOW_ARCH FLOW_ARCH_64
#elif (defined(__i386__) || defined(__ppc__))
#  define FLOW_ARCH FLOW_ARCH_32
#else
#  define FLOW_ARCH FLOW_ARCH_32
#endif

#if ((FLOW_COMPILER & FLOW_COMPILER_VC) && (defined(_M_IX86) || defined(_M_X64)))
#  if (defined(_M_CEE_PURE))
#    define FLOW_INTRINSICS FLOW_INTRINSICS_NONE
#  elif (FLOW_COMPILER >= FLOW_COMPILER_VC2010)
#    if (_MSC_FULL_VER >= 160031118) //160031118: VC2010 SP1 beta full version
#      define FLOW_INTRINSICS FLOW_INTRINSICS_AVX //FLOW_INTRINSICS_AVX (Require SP1)
#    else
#      define FLOW_INTRINSICS FLOW_INTRINSICS_SSE3
#    endif
#  elif (FLOW_COMPILER >= FLOW_COMPILER_VC2008) 
#    define FLOW_INTRINSICS FLOW_INTRINSICS_SSE3
#  elif (FLOW_COMPILER >= FLOW_COMPILER_VC2005)
#    define FLOW_INTRINSICS FLOW_INTRINSICS_SSE2
#  else
#    define FLOW_INTRINSICS FLOW_INTRINSICS_NONE
#  endif
#elif ((FLOW_PLATFORM & FLOW_PLATFORM_OSX) && (FLOW_COMPILER & FLOW_COMPILER_GCC))
#	define FLOW_INTRINSICS FLOW_INTRINSICS_NONE
#elif (((FLOW_COMPILER & FLOW_COMPILER_GCC) && (defined(__i386__) || defined(__x86_64__))) || (FLOW_COMPILER & FLOW_COMPILER_LLVM_GCC))
#  if(defined(__AVX2__))
#    define FLOW_INTRINSICS FLOW_INTRINSICS_AVX2
#  elif(defined(__AVX__))
#    define FLOW_INTRINSICS FLOW_INTRINSICS_AVX
#  elif(defined(__SSE4__))
#    define FLOW_INTRINSICS FLOW_INTRINSICS_SSE4
#  elif(defined(__SSE3__))
#    define FLOW_INTRINSICS FLOW_INTRINSICS_SSE3
#  elif(defined(__SSE2__))
#    define FLOW_INTRINSICS FLOW_INTRINSICS_SSE2
#  else
#    define FLOW_INTRINSICS FLOW_INTRINSICS_NONE
#  endif
#else
#	define FLOW_INTRINSICS FLOW_INTRINSICS_NONE
#endif

// -----------------------------------------------------------------------------
//  Build 
// -----------------------------------------------------------------------------

#if defined(_DEBUG) || defined(DEBUG)
#  define FLOW_DEBUG
#else
#  define FLOW_RELEASE
#endif

// -----------------------------------------------------------------------------
//  Qualifiers 
// -----------------------------------------------------------------------------

#if ((FLOW_COMPILER & FLOW_COMPILER_VC) && (FLOW_COMPILER >= FLOW_COMPILER_VC2005))
#  define FLOW_FORCEINLINE __forceinline
#elif ((FLOW_COMPILER & FLOW_COMPILER_GCC) && (FLOW_COMPILER >= FLOW_COMPILER_GCC34))
#  define FLOW_FORCEINLINE __attribute__((always_inline))
#else
#  define FLOW_FORCEINLINE inline
#endif

// -----------------------------------------------------------------------------
//  Constants 
// -----------------------------------------------------------------------------

#ifndef NULL
#  ifdef __cplusplus
#    define NULL 0
#  else
#    define NULL ((void *)0)
#  endif
#endif

#ifndef FALSE
#  define FALSE 0
#endif

#ifndef TRUE
#  define TRUE  1
#endif

#ifndef IN
#  define IN
#endif

#ifndef OUT
#  define OUT
#endif

// -----------------------------------------------------------------------------
//  Helper Macros 
// -----------------------------------------------------------------------------

#define F_SAFE_DELETE(p)			{ if(p) { delete (p);     (p) = NULL; } }
#define F_SAFE_DELETE_ARRAY(p)		{ if(p) { delete[] (p);   (p) = NULL; } }
#define F_SAFE_RELEASE(p)			{ if(p) { (p)->Release(); (p) = NULL; } }

// Library helper macros -------

#if defined(WIN32)
    #define F_DECLARE_EXPORT __declspec(dllexport)
    #define F_DECLARE_IMPORT __declspec(dllimport)
#else
    #define F_DECLARE_EXPORT
    #define F_DECLARE_IMPORT
#endif

// Shared pointer macros -------

#define F_DECLARE_VECTOR(className) \
	typedef std::vector<className> className##Vec;

#define F_DECLARE_SHARED_PTR(className) \
	class className; \
	typedef std::shared_ptr<className> className##Ptr;
#define F_DECLARE_WEAK_PTR(className) \
	class className; \
	typedef std::weak_ptr<className> className##WeakPtr;
#define F_DECLARE_PTRS(className) \
	class className; \
	typedef std::shared_ptr<className> className##Ptr; \
	typedef std::weak_ptr<className> className##WeakPtr;

#define F_DECLARE_SHARED_PTR_VECTOR(className) \
	class className; \
	typedef boost::shared_ptr<className> className##Ptr; \
	typedef std::vector<className> className##PtrVec;
#define F_DECLARE_WEAK_PTR_VECTOR(className) \
	class className; \
	typedef boost::weak_ptr<className> className##WeakPtr; \
	typedef std::vector<className> className##WeakPtrVec;
#define F_DECLARE_PTRS_VECTORS(className) \
	F_DECLARE_SHARED_PTR_VECTOR(className) \
	F_DECLARE_WEAK_PTR_VECTOR(className)
	
// Class definition helpers ----

#define F_DISABLE_COPY_AND_DEFAULT_CTOR(className)         \
protected:                                                 \
	className();                                           \
	className(const className& other);                     \
private:                                                   \
	className& operator=(const className& other);

#define F_DISABLE_COPY(className)                          \
protected:                                                 \
	className(const className& other);                     \
private:                                                   \
	className& operator=(const className& other);

// Version String --------------

#ifdef FLOW_DEBUG
#define F_BUILD_VERSION "Debug Version, " __DATE__ ", " __TIME__
#else
#define F_BUILD_VERSION "Release Version, " __DATE__ ", " __TIME__
#endif

// Functions -------------------

template <typename T>
inline const T fMin(const T& a, const T& b)
{ return b < a ? b : a; }

template <typename T>
inline const T fMax(const T& a, const T& b)
{ return b > a ? b : a; }

template <typename T>
inline const T& fMinMax(const T& val, const T& minVal, const T& maxVal) {
	return (val < minVal ? minVal : (val > maxVal ? maxVal : val)); }

template <typename T>
inline const T& fTripleMin(const T& val_a, const T& val_b, const T& val_c) {
	return (val_a < val_b) ? (val_a < val_c ? val_a : val_c) : (val_b < val_c ? val_b : val_c); }

template <typename T>
inline const T& fTripleMax(const T& val_a, const T& val_b, const T& val_c) {
	return (val_a > val_b) ? (val_a > val_c ? val_a : val_c) : (val_b > val_c ? val_b : val_c); }

template <typename T>
inline void fSwap(T& val_a, T& val_b) {
	T tmp = val_a; val_a = val_b; val_b = tmp; }

// Asserts ---------------------

#ifdef FLOW_DEBUG
#  if (FLOW_PLATFORM & FLOW_PLATFORM_WINDOWS)
#    include <crtdbg.h>
#    define F_ASSERT(f)     _ASSERTE(f)
#  else
#    include <assert.h>
#    define F_ASSERT(f)     assert(f)
#  endif
#  define F_VERIFY(f)     { if (!(f)) F_ASSERT(false); }
#else
#  define F_ASSERT(f)     ((void)0)
#  define F_VERIFY(f)     (f)
#endif

// Exceptions ------------------

#ifdef FLOW_DEBUG
#  define F_THROW(exception) { \
	  if (1 == _CrtDbgReportW(_CRT_ASSERT, _CRT_WIDE(__FILE__), __LINE__, _CRT_WIDE(__FUNCTION__), \
			  (exception).toString().toStdWString().data())) \
		  _CrtDbgBreak(); else throw (exception); }
#else
#  define F_THROW(exception) throw exception
#endif

// Storage Alignment -----------

#if ((FLOW_COMPILER & FLOW_COMPILER_VC) && (FLOW_COMPILER >= FLOW_COMPILER_VC2005))
#  define F_ALIGN(x) __declspec(align(x))
#  define F_ALIGN_STRUCT(x) __declspec(align(x)) struct
#  define F_ALIGN_CLASS(x) __declspec(align(x)) class
#elif ((FLOW_COMPILER & FLOW_COMPILER_GCC) && (FLOW_COMPILER >= FLOW_COMPILER_GCC31))
#  define F_ALIGN(x) __attribute__((aligned(x)))
#  define F_ALIGN_STRUCT(x) struct __attribute((aligned(x)))
#  define F_ALIGN_CLASS(x) class __attribute((aligned(x)))
#else
#  define F_ALIGN(x)
#  define F_ALIGN_STRUCT(x)
#  define F_ALIGN_CLASS(x)
#endif

// Debugging -------------------

#define F_QSTR(string) ((string).toStdString().c_str())

// COM stuff -------------------

#if (FLOW_PLATFORM & FLOW_PLATFORM_WINDOWS)
#  if defined (FLOW_DEBUG)
#    define F_CHECK_HR(f)				{ HRESULT hr = (f); if (FAILED(hr)) assert(false); }
#    define F_TRACE_FAILURE(hr, string)	{ if (FAILED(hr)) F_TRACE(string); }
#    define F_TRACE_ASSERT_FAILURE(hr, string) { if (FAILED(hr)) { F_TRACE(string); assert(false); } }
/// Check HRESULT. Throw an assertion if failed and return with the HRESULT.
#    define F_FAIL_ASSERT(f)            { HRESULT hr = (f); if (FAILED(hr)) { assert(false); return hr; } }
/// Check HRESULT. Return with the HRESULT if failed.
#    define F_FAIL_RETURN(f)            { HRESULT hr = (f); if (FAILED(hr)) return hr; }
#  else
#    define F_CHECK_HR(f)				{ f }
#    define F_TRACE_FAILURE(hr, string)
#    define F_TRACE_ASSERT_FAILURE(hr, string)
/// Check HRESULT. Throw an assertion if failed and return with the HRESULT.
#    define F_FAIL_ASSERT(f)            { HRESULT hr = (f); if (FAILED(hr)) return hr; }
/// Check HRESULT. Return with the HRESULT if failed.
#    define F_FAIL_RETURN(f)            { HRESULT hr = (f); if (FAILED(hr)) return hr; }
#  endif
#endif

// Enumeration -----------------

#define F_DECLARE_ENUM(exportMacro, className, defaultState) \
	public: className(enum_type state = defaultState) : _state(state) { } \
	operator enum_type() const { return _state; } \
	bool operator==(enum_type state) const { return _state == state; } \
	bool operator!=(enum_type state) const { return _state != state; } \
	friend exportMacro FArchive& operator<<(FArchive& ar, const className& obj); \
	friend exportMacro FArchive& operator>>(FArchive& ar, className& obj); \
	const char* name() const; \
	private: enum_type _state;

#define F_IMPLEMENT_ENUM(className) \
	FArchive& operator<<(FArchive& ar, const className& obj) { \
	ar << (className::value_type)obj._state; return ar; } \
	FArchive& operator>>(FArchive& ar, className& obj) { \
	className::value_type val; ar >> val; obj._state = (className::enum_type)val; return ar; } \

#define F_ENUM_NAME(text) case text: return #text;
#define F_ENUM_CASE(entry, text) case entry: return text;

// -----------------------------------------------------------------------------

#endif // FLOWCORE_SETUP_H
