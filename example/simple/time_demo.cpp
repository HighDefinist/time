#include "mz/range.hpp"
#include "mz/time.h"
//#include "mz/base1.h"
using namespace std;
using namespace std::mz;

int main() {
  // Measure the duration of something
  long long a = 0;
  {
    auto t1=bench1([&] { // Execute once
      for(auto i:range(1000))a += i;
    });
    printf("bench1: %gns\n",t1*1e9);
    auto tN = benchN(10,[&] { // Execute N times and average
      for(auto i:range(1000))a += i;
    });
    printf("benchN: %gns\n",tN*1e9);
    auto tT = benchT(0.5,[&] { // Execute until time "t" is elapsed
      for(auto i:range(1000))a += i;
    });
    printf("benchT: %gns\n",tT*1e9);
  }

   // Benchmarking: Average over multiple separate executions
  {
    Tbench b;
    for(auto i:range(1000)) {
      b.Run([&] {
        for(auto i:range(1000))a += i;
      });
    }
    printf("TBench: tot=%gns; avg=%gns; min=%gns; max=%gns; last=%gns\n",b.dur_tot()*1e9,b.dur_avg()*1e9,b.dur_min*1e9,b.dur_max*1e9,b.dur_min*1e9);
    printf("Total execution result: %lld (should be 10232164093500)\n",a);
  }
}

