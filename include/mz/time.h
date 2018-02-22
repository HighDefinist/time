// Some functions for timing things
#pragma once
#include <chrono>
#include <functional>
#ifdef _WIN32
#  include <windows.h>
#endif
//#include "base.h"

#define MZ_max(a,b)            (((a) > (b)) ? (a) : (b))
#define MZ_min(a,b)            (((a) < (b)) ? (a) : (b))
#define MZ_Ctypecopy(name) typedef const name C##name
#define MZ_Ctypedef(type,name) typedef type name; MZ_Ctypecopy(name)

namespace std {
  namespace mz {
    MZ_Ctypedef(unsigned long long, ui64);

    // Manages timing and profiling
#  ifdef _WIN32
    const long long g_Frequency=[]() -> long long {
      LARGE_INTEGER frequency;
      QueryPerformanceFrequency(&frequency);
      return frequency.QuadPart;
    }();

    struct WinQPClock {
      typedef long long                               rep;
      typedef nano                               period;
      typedef chrono::duration<rep,period>      duration;
      typedef chrono::time_point<WinQPClock>     time_point;
      static const bool is_steady=true;

      static time_point now() {
        LARGE_INTEGER count;
        QueryPerformanceCounter(&count);
        return time_point(duration(count.QuadPart*static_cast<rep>(period::den)/g_Frequency));
      }
    };

    typedef WinQPClock HighResClock;
#  else
    typedef chrono::high_resolution_clock HighResClock;
#  endif
    template <typename T> inline double to_s(T dur) {
      return chrono::duration_cast<chrono::duration<double,std::ratio<1> >> (dur).count();
    }
    typedef chrono::time_point<HighResClock,HighResClock::duration> HighResTimepoint;

    // Basic timer
    class Ttimer {
    protected:
      HighResClock Clock;
      double time_;
      bool ison;
      chrono::time_point<HighResClock,HighResClock::duration> a;
    public:
      bool enabled;
      const double& time;
      Ttimer(): time_(0),ison(false),time(time_),enabled(true) {}
      bool Start() {
        if(!enabled) return false;
        if (ison) throw invalid_argument("Ttimer::Start(): Timer was already running!");
        ison=true;
        a=HighResClock::now();
        return true;
      }
      void Stop() {
        if(!enabled) return;
        double dur=to_s(HighResClock::now()-a);
        if(ison) {
          ison=false;
          time_+=dur;
        }
      }
      template <typename Tl> void Run(Tl f) {
        Start();
        f();
        Stop();
      }
      void Reset(double newtime=0) {
        if(ison) Stop();
        time_=newtime;
      }
    };

    class Tbench:public Ttimer {
      ui64 N_;
      double t_min_,t_max_,t_last_;
    public:
      double dur_avg() { return time_/(double)N_; }
      double dur_tot() { return time_; }
      const ui64& N;
      const double &dur_min,&dur_max,&dur_last;
      Tbench(): N(N_),dur_min(t_min_),dur_max(t_max_),dur_last(t_last_) { Reset(); }
      void Reset() {
        if(ison)Stop();
        N_=0;
        t_min_=1e100;
        t_max_=0;
        t_last_=0;
        time_=0;

      }
      void Stop() {
        if(!enabled) return;
        double dur=to_s(HighResClock::now()-a);
        if(ison) {
          ison=false;
          t_last_=dur;
          time_+=dur;
          t_min_=MZ_min(t_min_,dur);
          t_max_=MZ_max(t_max_,dur);
          N_++;
        }
      }
      template <typename Tl> void Run(Tl f) {
        Start();
        f();
        Stop();
      }
      void AddTime(double DurationInSeconds) {
        t_last_ = DurationInSeconds;
        time_ += DurationInSeconds;
        t_min_ = MZ_min(t_min_,DurationInSeconds);
        t_max_ = MZ_max(t_max_,DurationInSeconds);
        N_++;
      }
    };

    // Execute once
    inline double bench1(function<void()> f) {
      auto start=HighResClock::now();
      f();
      return to_s(HighResClock::now()-start);
    }

    // Execute N times and average
    inline double benchN(int N,function<void()> f) {
      auto start=HighResClock::now();
      for(int i=0; i<N; i++)f();
      return to_s(HighResClock::now()-start)/N;
    }

    // Execute until time "t" is elapsed, then average
    inline double benchT(double t,function<void()> f) {
      auto start=HighResClock::now();
      auto now=start;
      int N=0;
      do {
        f();
        now=HighResClock::now();
        N++;
      } while(to_s(now-start)<t);
      return to_s(now-start)/N;
    }
  }
}