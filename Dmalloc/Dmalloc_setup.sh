#!/bin/sh

DMALLOC_VERSION=5.5.2
wget https://dmalloc.com/releases/dmalloc-${DMALLOC_VERSION}.tgz
tar -xzvf dmalloc-${DMALLOC_VERSION}.tgz 
cd dmalloc-${DMALLOC_VERSION}/
./configure --prefix=${HOME}/dmalloc
make
make install
