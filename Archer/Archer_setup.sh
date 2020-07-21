#!/bin/sh
set -v
rm -rf ninja
git clone https://github.com/ninja-build/ninja.git
cd ninja
git checkout release
./configure.py --bootstrap

export PATH=${PATH}:`pwd`
cd ..

#  Create a folder in which to download and build Archer:
   
rm -rf ArcherBuild

export ARCHER_BUILD=$PWD/ArcherBuild
mkdir $ARCHER_BUILD && cd $ARCHER_BUILD

#  Obtain the LLVM OpenMP Runtime with OMPT support:
   
git clone --branch tr6_forwards https://github.com/OpenMPToolsInterface/LLVM-openmp.git openmp

#  and build it with the following command:
   
export OPENMP_INSTALL=$HOME/llvm-openmp   # or any other install path
cd openmp
mkdir build && cd build
cmake -G Ninja \
  -D CMAKE_C_COMPILER=clang \
  -D CMAKE_CXX_COMPILER=clang++ \
  -D CMAKE_BUILD_TYPE=Release \
  -D CMAKE_INSTALL_PREFIX:PATH=$OPENMP_INSTALL \
  -D LIBOMP_OMPT_SUPPORT=on \
  -D LIBOMP_OMPT_BLAME=on \
  -D LIBOMP_OMPT_TRACE=on \
  ..
ninja -j8 -l8                             # or any number of available cores
ninja install

#  Obtain Archer:
   
cd $ARCHER_BUILD
git clone https://github.com/PRUNERS/archer.git archer

#  and build it with the following commands:
   
export ARCHER_INSTALL=$HOME/archer        # or any other install path
cd archer
mkdir build && cd build
cmake -G Ninja \
  -D CMAKE_C_COMPILER=clang \
  -D CMAKE_CXX_COMPILER=clang++ \
  -D OMP_PREFIX:PATH=$OPENMP_INSTALL \
  -D CMAKE_INSTALL_PREFIX:PATH=${ARCHER_INSTALL} \
  ..
ninja -j8 -l8                             # or any number of available cores
ninja install
cd ../..

export PATH=${ARCHER_INSTALL}/bin:${PATH}"
export LD_LIBRARY_PATH=${ARCHER_INSTALL}/lib:${LD_LIBRARY_PATH}"
