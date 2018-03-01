


add_library(hashex STATIC
bucket.cpp
data.cpp
directory.cpp
hashex.cpp
key.cpp
)

target_compile_options( hashex PRIVATE -Wall -Wextra -std=c++11 -DNDEBUG -DNOLOGGING )

