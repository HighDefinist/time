# time
**A simple library for performing benchmarks.**

### Requirements

- C++11, including the ```<chrono>``` library
- [CMake](https://cmake.org/) (only necessary for building the example)

### Installation

- *time* is header only. Therefore, simply copy ```includes/mz/time.h``` into a directory of your choice, and ```#include``` it.
- The namespace is ```std::mz```.

### Tested on

| [Linux][lin-link] | [Windows][win-link] | [Code-coverage][cov-link] |
| :---------------: | :---------------: | :---------------: |
| ![lin-badge]      | ![win-badge]      | ![cov-badge]      | 

[lin-badge]: https://travis-ci.org/HighDefinist/time.svg?branch=master "Travis build status"
[lin-link]:  https://travis-ci.org/HighDefinist/time "Travis build status"
[win-badge]: https://ci.appveyor.com/api/projects/status/afkqghkq5sx6iqkn/branch/master?svg=true "AppVeyor build status"
[win-link]:  https://ci.appveyor.com/project/HighDefinist/time/branch/master "AppVeyor build status"
[cov-badge]: https://codecov.io/gh/HighDefinist/time/branch/master/graph/badge.svg "Code coverage status"
[cov-link]:  https://codecov.io/gh/HighDefinist/time/branch/master "Code coverage status"

- Visual Studio 2015 or newer
- GCC 5 or newer
- Clang 4 or newer
- XCode 6.4 or newer

### Download 

You can download the latest version of *time* by cloning the GitHub repository:

	git clone https://github.com/HighDefinist/time.git
	
### Usage

Execute a function once, and return the elapsed time in seconds:

	double ElapsedTime = bench1([&] { 
	  // Insert code to benchmark here
	});


Take a look at the example file for the other available functions and classes:

	example\simple\time_demo.cpp
