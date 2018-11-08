cmake_minimum_required(VERSION 3.5)
project(cppJNI)

set(CMAKE_CXX_STANDARD 14)

option(BUILD_TESTS "Build tests" ON)

add_definitions(-DUSE_TYPESTRING=8)
if(GNU)
	add_compile_options(-ftemplate-depth-1024 -ftemplate-backtrace-limit=0 -Wno-gnu-string-literal-operator-template)
endif()

add_subdirectory(src)

if(BUILD_TESTS)
	enable_testing()
	add_subdirectory(tst)
endif()