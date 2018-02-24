# time
**A simple library for performing benchmarks.**

### Requirements

- C++11, including the ```<chrono>``` library
- [CMake](https://cmake.org/) (only necessary for building the example)

### Installation

- *time* is header only. Therefore, simply copy ```includes/mz/time.h``` into a directory of your choice, and ```#include``` it.
- The namespace is ```std::mz```.

### Tested on

- Visual Studio 2017
- GCC 7.3.1
- Clang 5.0.1

### Download 

You can download the latest version of *time* by cloning the GitHub repository:

	git clone https://github.com/Solenism/time.git
	
### Usage

Execute a function once, and return the elapsed time in seconds:

	double ElapsedTime = bench1([&] { 
	  // Insert code to benchmark here
	});


Take a look at the example file for the other available functions and classes:

	example\simple\time_demo.cpp
