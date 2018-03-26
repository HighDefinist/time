#include "mz/time.h"

using namespace std;
using namespace std::mz;

#define CATCH_CONFIG_MAIN   
#include "catch.hpp"

TEST_CASE("time main", "Main functionality") {
  SECTION("Benchmarks"){
    long long a=0;
    auto t1=bench1([&] { // Execute once, and return elapsed time in seconds
      a+=1;
    });
    REQUIRE(a==1);
    auto tN=benchN(10,[&] { // Execute once, and return elapsed time in seconds
      a+=1;
    });
    REQUIRE(a==11);
    auto tT=benchT(0.1,[&] { // Execute once, and return elapsed time in seconds
      a+=1;
    });
    REQUIRE(a>11);
  }   
}

