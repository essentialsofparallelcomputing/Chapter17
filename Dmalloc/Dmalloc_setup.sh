#!/bin/sh

VERSION=5.4.3
wget https://dmalloc.com/releases/dmalloc-${VERSION}.tgz
tar -xzvf dmalloc-${VERSION}.tgz 
cd dmalloc-${VERSION}/
./configure --prefix=${HOME}/dmalloc
make
make install
