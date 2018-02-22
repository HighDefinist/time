// Contains some very basic macros and templates, which are more or less always used. It only adds a neglible amount of extra compile time. It is mostly tested with Visual Studio, but should also work with GCC and Clang.

#pragma once
#include <cstddef>

/////////////////
// Base macros //
/////////////////

#define WIN32_LEAN_AND_MEAN
#define _USE_MATH_DEFINES
#pragma warning( disable : 4996 )
# if defined(__GNUC__)
#   define inli __attribute__((always_inline))
#   define ifGCC(A) A
#   define ifnGCC(A)
#   define ifeGCC(A,B) A
#   define sprintf_s snprintf
# else
#   define inli __forceinline
#   define ifGCC(A)
#   define ifnGCC(A) A
#   define ifeGCC(A,B) B
# endif



////////////////////////
// Symbols for macros //
////////////////////////

# define _COMMA ,
# define _BRACKET_OPEN (
# define _BRACKET_CLOSE )
# define _TEMPLATE_OPEN <
# define _TEMPLATE_CLOSE >
# define _SEMICOLON ;




/////////////////
// CUDA things //
/////////////////

#ifdef __CUDACC__
#  define __PUalso __host__ __device__
#  define __PUonly __device__
#  define __PUkernel __global__
#else
#  define __PUalso inli
#  define __PUonly inli // inli means "forceinline", and is defined further below
#  define __PUkernel 
#endif

#if !defined(useCPU) && !defined(useCUDA)
#  ifdef __CUDACC__
#    define useCUDA
#  else 
#    define useCPU
#  endif
#endif

#ifdef __CUDACC__
#  define ifCUDACC(A) A
#  define ifnCUDACC(A)
#  define ifeCUDACC(A,B) A
#else
#  define ifCUDACC(A)
#  define ifnCUDACC(A) A
#  define ifeCUDACC(A,B) B
#  ifndef __GNUC__
#  endif
#endif




////////////////
// Exceptions //
////////////////

#if defined(__clang__)
#  undef _HAS_EXCEPTIONS
#  define _HAS_EXCEPTIONS 0
#endif

#if defined(_HAS_EXCEPTIONS) && (_HAS_EXCEPTIONS==0)
#  define ifEX(A)
#  define ifeEX(A,B) B
#  define isEX 0
#  define M_try {{
#  define M_catch(x) } if (false) {
#  define M_catchA   } if (false) {
#  define M_return   }}
#  define BOOST_EXCEPTION_DISABLE
#  define BOOST_NO_EXCEPTIONS
#else
#  define ifEX(A) A
#  define ifeEX(A,B) A
#  define isEX 1
#  define M_try	try  {
#  define M_catch(x) } catch (x) {
#  define M_catchA	 } catch (...) {
#  define M_return	 }
#endif



///////////////
// Debugging //
///////////////

#ifdef NDEBUG
#  define Assert(c, exec)
#else
#  define Assert(c, exec) if (!(c)) exec
#endif

# ifdef _DEBUG
#   define isDebug 1
#   define ifDebug(A) A
# if isCPU
#   define __stopcpudebug __debugbreak()
# else
#   define __stopcpudebug {}
# endif
#   define __stopdebug __debugbreak()
#   undef _SECURE_SCL
#   define _SECURE_SCL 1
# else
#   define isDebug 0
#   define ifDebug(A)
#   define __stopcpudebug {}
#   define __stopdebug {}
# undef _SECURE_SCL
#   define _SECURE_SCL 0
# endif



///////////////////
// Min/Max fixes //
///////////////////

#undef NOMINMAX
#define NOMINMAX
#ifdef min
#  undef min
#endif
#ifdef max
#  undef max
#endif

#ifndef __CUDACC__
#  ifndef __GNUC__
inli float min(const float& a, const float& b) { return (a<b) ? a : b; }
inli float max(const float& a, const float& b) { return (a>b) ? a : b; }
inli double min(const double& a, const double& b) { return (a<b) ? a : b; }
inli double max(const double& a, const double& b) { return (a>b) ? a : b; }
#  endif
#endif



/////////////
// Unicode //
/////////////

#ifdef _UNICODE
#  define tstring wstring
#  define ystrt ystrw
#  define tchar wchar_t
#  define tmain wmain
#  ifndef _T
#    define _T(x) L ## x
#  endif
#  define ifeU(A,B) A
#else
#  define tstring string
#  define ystrt ystr
#  define tchar char
#  define tmain main
#  ifndef _T
#    define _T(x) x
#  endif
#  define ifeU(A,B) B
#endif



///////////////////////
// Numeric constants //
///////////////////////

#define f_E        2.71828182845904523536f
#define f_LOG2E    1.44269504088896340736f
#define f_LOG10E   0.434294481903251827651f
#define f_LN2      0.693147180559945309417f
#define f_LN10     2.30258509299404568402f
#define f_2PI      6.28318530717958647692f
#define f_4PI      12.56637061435917295384f
#define f_PI       3.14159265358979323846f
#define f_PI_2     1.57079632679489661923f
#define f_PI_4     0.785398163397448309616f
#define f_1_2PI    0.15915494309189533576888376337251f
#define f_1_PI     0.318309886183790671538f
#define f_2_PI     0.636619772367581343076f
#define f_2_SQRTPI 1.12837916709551257390f
#define f_SQRT2    1.41421356237309504880f
#define f_SQRT1_2  0.707106781186547524401f
#define M_E        2.71828182845904523536
#define M_LOG2E    1.44269504088896340736
#define M_LOG10E   0.434294481903251827651
#define M_LN2      0.693147180559945309417
#define M_LN10     2.30258509299404568402
#define M_2PI      6.28318530717958647692
#define M_4PI      12.56637061435917295384
#define M_PI       3.14159265358979323846
#define M_PI_2     1.57079632679489661923
#define M_PI_4     0.785398163397448309616
#define M_1_2PI    0.15915494309189533576888376337251
#define M_1_PI     0.318309886183790671538
#define M_2_PI     0.636619772367581343076
#define M_2_SQRTPI 1.12837916709551257390
#define M_SQRT2    1.41421356237309504880
#define M_SQRT1_2  0.707106781186547524401


/////////////////////////////////////
// Abbreviations for numeric types //
/////////////////////////////////////

// Defines a const type from a type
#define Ctypecopy(name) typedef const name C##name
// Defines a type, and its const type
#define Ctypedef(type,name) typedef type name; Ctypecopy(name)

#define Cauto const auto
#define Cfunction const function

Ctypedef(char, i8);
Ctypedef(short, i16);
Ctypedef(int, i32);
Ctypedef(long long, i64);
Ctypedef(unsigned char, ui8);
Ctypedef(unsigned short, ui16);
Ctypedef(unsigned int, ui32);
Ctypedef(unsigned long long, ui64);

Ctypedef(float, fl);
Ctypedef(double, db);
Ctypecopy(bool);



/////////////////////////
// Mathematical macros //
/////////////////////////

#define M_max(a,b)            (((a) > (b)) ? (a) : (b))
#define M_min(a,b)            (((a) < (b)) ? (a) : (b))
#define A_min(a,b)            if((b)<a)a=(b)
#define A_max(a,b)            if((b)>a)a=(b)
#define M_clamp(v,a,b) M_min(M_max(v,a),b)
#define M_within(v,a,b) (((v)>=(a))&&((v)<=(b)))
#define ddiv(a,b) ((a-1)/b+1)

template <typename T> T M_wrap_direct(T v, T a, T b) {
  auto divi = (v-a)/(b-a);
  divi -= floor(divi);
  return divi*(b-a)+a;
}
template <typename T> inli T M_wrap(T v, T a, T b) {
  if ((v<a)||(v>=b)) return M_wrap_direct(v, a, b); else return v;
}

#define _db(A) ((db)(A))



////////////////////////////////////
// Memory reinterpretation macros //
////////////////////////////////////

#define M_int(A)  (*(ui32*)(&A))    
#define M_int64(A)  (*(ui64*)(&A))  
#define M_char(A) (*(ui8*)(&A))    
#define M_float(A) (*(fl*)(&A)) 
#define M_double(A) (*(db*)(&A)) 



////////////
// Legacy //
////////////

inline ui32 _ui(db val) { return (ui32)(val+0.5); }
inline ui32 _ui(size_t val) { return (ui32)val; }
#define test_delete(A) if(A!=nullptr){delete A; A=nullptr;}
#define strprint(str,text, ...) {char buf[1000]; sprintf_s(buf,1000,text, __VA_ARGS__); str+=buf;}
# if defined(_MSC_VER)
#   define M_streamargs(A,B,C) (A,B,C)
# else
#   define M_streamargs(A,B,C) (A,B)
# endif

# define CFVector const FVector
# define CFVector2D const FVector2D

// Placeholder for conditional assertions (Syntax may change in the future)
#define AssertCond(Condition, Assertion, Message)



