#!/bin/env sh

rm -rf build &&
mkdir build &&
cd build &&
cmake -DCMAKE_CXX_COMPILER=clang++ -DSTD_CPPM=$STD_CPPM -DCMAKE_BUILD_TYPE=Release -GNinja .. &&
ninja
