#include "mz/range.hpp"
#include "mz/time.h"
using namespace std;
using namespace std::mz;

int main() {
  long long a = 0;
  {
    auto t1=bench1([&] { // Execute once, and return elapsed time in seconds
      for(auto i:range(1000))a += i;
    });
    printf("bench1: %gns\n",t1*1e9);
    auto tN = benchN(10,[&] { // Execute N times and return average execution time
      for(auto i:range(1000))a += i;
    });
    printf("benchN: %gns\n",tN*1e9);
    auto tT = benchT(0.5,[&] { // Execute until time "t" is elapsed and return average execution time
      for(auto i:range(1000))a += i;
    });
    printf("benchT: %gns\n",tT*1e9);
  }
   
  {
    Tbench b; // Benchmarking: Average over multiple separate executions. This class also stores the fastest, the slowest, and last execution time.
    for(auto i:range(1000)) {
      b.Run([&] {
        for(auto i:range(1000))a += i;
      });
    }
    printf("TBench: tot=%gns; avg=%gns; min=%gns; max=%gns; last=%gns\n",b.dur_tot()*1e9,b.dur_avg()*1e9,b.dur_min*1e9,b.dur_max*1e9,b.dur_min*1e9);
    printf("Total execution result: %lld (should be 10232164093500)\n",a);
  }
}

