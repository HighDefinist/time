// Contains various macros and templates which are frequently used, related to strings, tuples and functional programming. Unlike the macros in base.h, they require additional, but common, includes

#pragma once

#include "base.h"
#include <functional>
#include <string>
#include <sstream>
#include <tuple>
#include <type_traits>
#include <numeric>
#include "range.hpp"

#if !defined(__GNUC__)
#  include "z_wstring.h"
#endif
#define _Z_BASICS2



////////////
// Tuples //
////////////

#define mt make_tuple
#define gt(A,B) get<B>(A)
#define auto1(A,Z) auto temp##A=Z; auto A=gt(temp##A,0);// Expands tuples into automatically generated variables
#define auto2(A,B,Z) auto temp##A##B=Z; auto A=gt(temp##A##B,0); auto B=gt(temp##A##B,1); // Expands tuples into automatically generated variables
#define auto3(A,B,C,Z) auto temp##A##B##C=Z; auto A=gt(temp##A##B##C,0); auto B=gt(temp##A##B##C,1); auto C=gt(temp##A##B##C,2); 
#define auto4(A,B,C,D,Z) auto temp##A##B##C##D=Z; auto A=gt(temp##A##B##C##D,0); auto B=gt(temp##A##B##C##D,1); auto C=gt(temp##A##B##C##D,2); auto D=gt(temp##A##B##C##D,3); 
#define auto5(A,B,C,D,E,Z) auto temp##A##B##C##D##E=Z; auto A=gt(temp##A##B##C##D##E,0); auto B=gt(temp##A##B##C##D##E,1); auto C=gt(temp##A##B##C##D##E,2); auto D=gt(temp##A##B##C##D##E,3); auto E=gt(temp##A##B##C##D##E,4); 
#define auto6(A,B,C,D,E,F,Z) auto temp##A##B##C##D##E##F=Z; auto A=gt(temp##A##B##C##D##E##F,0); auto B=gt(temp##A##B##C##D##E##F,1); auto C=gt(temp##A##B##C##D##E##F,2); auto D=gt(temp##A##B##C##D##E##F,3); auto E=gt(temp##A##B##C##D##E##F,4);  auto F=gt(temp##A##B##C##D##E##F,5); 

#define Cauto1(A,Z) const auto temp##A=Z; const auto A=gt(temp##A,0);// Expands tuples into automatically generated variables
#define Cauto2(A,B,Z) const auto temp##A##B=Z; const auto A=gt(temp##A##B,0); const auto B=gt(temp##A##B,1); // Expands tuples into automatically generated variables
#define Cauto3(A,B,C,Z) const auto temp##A##B##C=Z; const auto A=gt(temp##A##B##C,0); const auto B=gt(temp##A##B##C,1); const auto C=gt(temp##A##B##C,2); 
#define Cauto4(A,B,C,D,Z) const auto temp##A##B##C##D=Z; const auto A=gt(temp##A##B##C##D,0); const auto B=gt(temp##A##B##C##D,1); const auto C=gt(temp##A##B##C##D,2); const auto D=gt(temp##A##B##C##D,3); 
#define Cauto5(A,B,C,D,E,Z) const auto temp##A##B##C##D##E=Z; const auto A=gt(temp##A##B##C##D##E,0); const auto B=gt(temp##A##B##C##D##E,1); const auto C=gt(temp##A##B##C##D##E,2); const auto D=gt(temp##A##B##C##D##E,3); const auto E=gt(temp##A##B##C##D##E,4); 
#define Cauto6(A,B,C,D,E,F,Z) const auto temp##A##B##C##D##E##F=Z; const auto A=gt(temp##A##B##C##D##E##F,0); const auto B=gt(temp##A##B##C##D##E##F,1); const auto C=gt(temp##A##B##C##D##E##F,2); const auto D=gt(temp##A##B##C##D##E##F,3); const auto E=gt(temp##A##B##C##D##E##F,4);  const auto F=gt(temp##A##B##C##D##E##F,5); 

#define autoR1(A,Z) auto& temp##A=Z; auto& A=gt(temp##A,0);// Expands tuples into automatically generated variables
#define autoR2(A,B,Z) auto& temp##A##B=Z; auto& A=gt(temp##A##B,0); auto& B=gt(temp##A##B,1); // Expands tuples into automatically generated variables
#define autoR3(A,B,C,Z) auto& temp##A##B##C=Z; auto& A=gt(temp##A##B##C,0); auto& B=gt(temp##A##B##C,1); auto& C=gt(temp##A##B##C,2); 
#define autoR4(A,B,C,D,Z) auto& temp##A##B##C##D=Z; auto& A=gt(temp##A##B##C##D,0); auto& B=gt(temp##A##B##C##D,1); auto& C=gt(temp##A##B##C##D,2); auto& D=gt(temp##A##B##C##D,3); 
#define autoR5(A,B,C,D,E,Z) auto& temp##A##B##C##D##E=Z; auto& A=gt(temp##A##B##C##D##E,0); auto& B=gt(temp##A##B##C##D##E,1); auto& C=gt(temp##A##B##C##D##E,2); auto& D=gt(temp##A##B##C##D##E,3); auto& E=gt(temp##A##B##C##D##E,4); 
#define autoR6(A,B,C,D,E,F,Z) auto& temp##A##B##C##D##E##F=Z; auto& A=gt(temp##A##B##C##D##E##F,0); auto& B=gt(temp##A##B##C##D##E##F,1); auto& C=gt(temp##A##B##C##D##E##F,2); auto& D=gt(temp##A##B##C##D##E##F,3); auto& E=gt(temp##A##B##C##D##E##F,4);  auto& F=gt(temp##A##B##C##D##E##F,5); 



/////////////////////
// Tuple iteration //
/////////////////////

namespace std {
  namespace mz {
  #  if _MSC_VER>=1900
    template<class F, class T, size_t... Is> void IterateTupleHelper(T& tuple, F func, index_sequence<Is...>) {
      using expander = int[];
      expander{(func(gt(tuple,Is)),0)...};
    }
    template<class F, class...Ts> void IterateTuple(tuple<Ts...>& tuple, F func) {
      IterateTupleHelper(tuple, func, make_index_sequence<sizeof...(Ts)>());
    }

    template<class F, class T, size_t... Is> T ProcessTupleHelper(const T& tuple, F func, index_sequence<Is...>) {
      using expander = int[];
      T res;
      expander{(gt(res,Is) = func(gt(tuple,Is)),0)...};
      return res;
    }
    template<class F, class...Ts> tuple<Ts...> ProcessTuple(const tuple<Ts...>& tuple, F func) {
      return ProcessTupleHelper(tuple, func, make_index_sequence<sizeof...(Ts)>());
    }

    template<class F, class T, size_t... Is> T ProcessTupleHelper(const T& tuple, const T& tuple2, F func, index_sequence<Is...>) {
      using expander = int[];
      T res;
      expander{(gt(res,Is) = func(gt(tuple,Is),gt(tuple2,Is)),0)...};
      return res;
    }
    template<class F, class...Ts, class T> tuple<Ts...> ProcessTuple(const tuple<Ts...>& tuple, const T& tuple2, F func) {
      return ProcessTupleHelper(tuple, tuple2, func, make_index_sequence<sizeof...(Ts)>());
    }
  #  endif
  }
}



/////////////
// ystring //
/////////////

namespace std {
  namespace mz {
  #  if !defined(__GNUC__)
    inline void yadd_str(string& s, const wstring& value) {
      s += _string(value);
    }
  #  endif

    inline void yadd_str(string& s, const string& value) {
      s += value;
    }

    template<typename T> typename enable_if<is_integral<T>::value, void>::type yadd_str(string& s, const T& value) {
      s += to_string(value);
    }

    inline void yadd_str(string& s, const float& value) {
      char cc[20];
      auto i = sprintf_s(&cc[0], 20, "%.7g", value);
      (void)i;
      s += cc;
    }

    inline void yadd_str(string& s, const double& value) {
      char cc[30];
      auto i = sprintf_s(&cc[0], 30, "%.15g", value);
      (void)i;
      s += cc;
    }

    //template<typename T> typename enable_if<is_floating_point<T>::value,void>::type yadd_str(string& s,const T& value){
    //  char cc[30];
    ////  ss<<std::setprecision(std::numeric_limits<float>::digits10+1);
    //  auto i=sprintf_s(&cc[0],30,"%g",value);
    //  (void)i;
    //  s+=cc;
    //}

    inline void xstr(string& result, const char *s) {
      while (*s) {
        if (*s=='%') {
          if (*(s+1)=='%') ++s;
          ifeEX(else throw runtime_error("invalid format string: missing arguments"), return);
        }
        result += *s++;
      }
    }

    template<typename... Args> void yadd_str(string& s, tuple<Args...> value);
    template<size_t i, typename... Args> typename enable_if<i==0, void>::type ytuple_str(string& str, tuple<Args...> &args) {
      str += "[";
      yadd_str(str, gt(args, i));
    }
    template<size_t i, typename... Args> typename enable_if<i!=0, void>::type ytuple_str(string& str, tuple<Args...> &args) {
      ytuple_str<i-1, Args...>(str, args);
      str += ";";
      yadd_str(str, gt(args, i));
    }
    template<typename... Args> void yadd_str(string& s, tuple<Args...> value) {
      ytuple_str<sizeof...(Args)-1, Args...>(s, value);
      s += "]";
    }

    template<typename T, typename... Args> void xstr(string& result, const char *s, const T& value, Args... args) {
      while (*s) {
        if (*s=='%') {
          if (*(s+1)=='%') {
            ++s;
          } else {
            yadd_str(result, value);
            xstr(result, s+1, args...); // call even when *s == 0 to throw exception on extra arguments
            return;
          }
        }
        result += *s++;
      }
      ifEX(throw logic_error("extra arguments provided to xstr"));
    }

    template<typename... Args> string ystr(string s, Args... args) {
      string str;
      str.reserve(s.length());
      xstr(str, s.c_str(), args...);
      return str;
    }

    template<typename... Args> wstring ystrw(Args... args) {
      return _wstring(ystr(args...));
    }

    template<typename... Args> void yprintf(string s, Args... args) {
      auto ll = ystr(s, args...);
      printf("%s", ll.c_str());
    }

    template<typename T>string _str(const T& value) {
      return ystr("%", value);
    }
    template<typename T>wstring _wstr(const T& value) {
      return ystrw("%", value);
    }
  }
}

////////////////////////////////////////////////////
// STL Algorithms (requires #include <algorithm>) //
////////////////////////////////////////////////////

namespace std {
  namespace mz {
    template<typename T1, typename F> T1 STL_Merge(const T1& v1, const T1& v2, F f) {
      T1 vMerged(v1.size());
      transform(v1.begin(), v1.end(), v2.begin(), vMerged.begin(), f);
      return vMerged;
    }
    template<typename T1> void STL_Append(T1& v1, const T1& v2) {
      v1.insert(v1.end(), v2.begin(), v2.end());
    }
    template<typename T1> T1& STL_Slice(T1& v1, int start, int end) {
      T1 result;
      for (auto i:range(start, end))result.push_back(v1[i]);
      return result;
    }
    template<typename T1> auto STL_Accumulate(T1& v1) ->std::decay_t<decltype(v1[0])> {
      std::decay_t<decltype(v1[0])> sum = 0;
      return accumulate(v1.begin(), v1.end(), sum);
    }
    template<typename T1> auto STL_FindMax(T1& v1) ->std::decay_t<decltype(v1[0])> {
      std::decay_t<decltype(v1[0])> Summary = v1[0];
      for (auto &x:v1) {
        if (x>Summary) Summary = x;
      }
      return Summary;
    }
    template<typename T1, typename Tf> T1& STL_SelectIf(T1& v1, Tf Selector) {
      T1 result;
      for (auto x:v1) {
        if (Selector(x)) result.push_back(x);
      }
      return result;
    }
  }
}



////////////////////
// Misc functions //
////////////////////

namespace std {
  namespace mz {
    template <typename T> bool isin(const T& val, const initializer_list<T>& list) {
      for (const auto& i:list) if (val==i) return true;
      return false;
    }

    template <typename Tstring> inline void StrReplaceAll(Tstring& str, const Tstring& from, const Tstring& to) {
      if (from.empty()) return;
      size_t start_pos = 0;
      while ((start_pos = str.find(from, start_pos))!=Tstring::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
      }
    }

    inline float Halton(int i, int b) {
      float f = 1;
      float r = 0;
      while (i>0) {
        f = f/(float)b;
        r = r+f*((float)(i % b));
        i = i/b;
      }
      return r;
    }
  }
}



///////////////////
// Finally class //
///////////////////

namespace std {
  namespace mz {
    class finally{ // Pass a function as parameter, which is called if this variable goes out of scope. Example: finally F([]{dosomething();});
      function<void()> functor;
    public:
      finally(const function<void()> &functor) : functor(functor) {}
      ~finally() { functor(); }
    };
  }
}



//////////////////////////////////////////
// Lambda parameter query (alternative) //
//////////////////////////////////////////

namespace std{
  namespace mz{
    // Template to extract the n-th parameter of a function type
    template <typename T> struct function_traits : public function_traits<decltype(&T::operator())> {};

    template <typename ClassType, typename ReturnType, typename... Args> struct function_traits<ReturnType(ClassType::*)(Args...) const> {
      enum { arity = sizeof...(Args) };  // Number of parameters
      typedef ReturnType result_type;
      template <size_t i> struct arg {
        typedef typename tuple_element<i, tuple<Args...>>::type type;
      };
    };

  #   define lambda_arg(lambda,ParameterIndex) std::mz::function_traits<decltype(lambda)>::arg<ParameterIndex>::type
  #   define lambda_result(lambda) std::mz::function_traits<decltype(lambda)>::result_type
  }
}



//////////
// Misc //
//////////
namespace std {
  namespace mz {
    Ctypecopy(string);
#if !defined(__GNUC__)
    Ctypecopy(wstring);
#endif

  }
}


#ifdef _Z_WSTRING
#include "z_wstring2.h"
#endif
