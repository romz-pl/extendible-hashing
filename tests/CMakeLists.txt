cmake_minimum_required(VERSION 3.0)

project(hashex-tests)

add_executable(tests.x
#delete.cpp
insert.cpp
main.cpp
#open.cpp
#scan.cpp
)

target_include_directories(tests.x PUBLIC ${PROJECT_SOURCE_DIR}/../3rdparty/googletest/include)
find_library(GOOGLETEST_LIB gtest.a HINT ${PROJECT_SOURCE_DIR}/../3rdparty/googletest)

target_include_directories(tests.x PUBLIC ${PROJECT_SOURCE_DIR}/../src)


target_link_libraries(tests.x ${GOOGLETEST_LIB} pthread hashex)
