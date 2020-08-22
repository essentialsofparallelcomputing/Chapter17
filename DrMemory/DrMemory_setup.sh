#!/bin/sh
wget https://github.com/DynamoRIO/drmemory/releases/download/release_2.3.0/DrMemory-Linux-2.3.0-1.tar.gz && \
   tar -xzvf DrMemory-Linux-2.3.0-1.tar.gz
export PATH=`pwd`/DrMemory-Linux-2.3.0-1/bin64:$PATH
