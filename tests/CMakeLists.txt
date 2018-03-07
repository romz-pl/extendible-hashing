#cmake_minimum_required(VERSION 3.0)

#project(hashex-tests)

add_executable(tests
bucket.cpp
#construct.cpp
data.cpp
GetRandomString.cpp
#insert.cpp
key.cpp
#update.cpp
main.cpp
#print.cpp
)

# target_compile_options( tests PRIVATE -Wall -Wextra -std=c++11 -DNDEBUG -fprofile-arcs -ftest-coverage )
target_compile_options( tests PRIVATE -Wall -pedantic -pthread -g -O0 -fprofile-arcs -ftest-coverage -std=c++11 -DNDEBUG )

target_include_directories( tests PUBLIC ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} )

target_include_directories(tests PUBLIC ${PROJECT_SOURCE_DIR}/src)


# target_link_libraries(tests gtest gtest_main pthread hashex -fprofile-arcs )
target_link_libraries(tests -fprofile-arcs gtest gtest_main pthread hashex )

#enable_testing(true)
#add_test( tests tests )

add_test(NAME hashex_test COMMAND tests)

