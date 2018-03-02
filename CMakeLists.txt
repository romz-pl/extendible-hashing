cmake_minimum_required (VERSION 3.0)
enable_language(CXX)
project(extendible-hashing)

include(CTest)
enable_testing(true)

add_subdirectory(3rdparty/googletest)
add_subdirectory(src)
add_subdirectory(tests)

#add_subdirectory(examples/ex01)
