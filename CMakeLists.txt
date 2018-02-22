cmake_minimum_required (VERSION 3.1)
project("mz_time")
find_package(PythonLibs 3.5 REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE ${PROJECT_SOURCE_DIR}/include)
get_directory_property(hasParent PARENT_DIRECTORY)
if(NOT hasParent)
  include_directories(${PROJECT_SOURCE_DIR}/include)
  add_executable(time example/simple/time_demo.cpp)
endif()

 
