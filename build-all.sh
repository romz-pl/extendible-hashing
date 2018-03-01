#!/bin/bash

#
# Create 'build' directory
#
rm -rf build || exit 1
mkdir build || exit 1
cd build || exit 1

#
# Run cmake
#
cmake -DBUILD_GTEST=ON -DBUILD_GMOCK=OFF   .. || exit 1
make || exit 1

#
# Run test
#
ctest --verbose



