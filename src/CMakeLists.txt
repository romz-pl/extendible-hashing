


add_library(hashex STATIC
bucket.cpp
data.cpp
directory.cpp
hashex.cpp
key.cpp
)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -pthread -g -O0 -fprofile-arcs -ftest-coverage")

target_compile_options( hashex PRIVATE -Wall -pedantic -pthread -g -O0 -fprofile-arcs -ftest-coverage -std=c++11 -DNOLOGGING )

