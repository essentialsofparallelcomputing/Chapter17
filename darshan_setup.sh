#!/bin/sh
export CFLAGS=-I${MPI_INCLUDE}
export LDFLAGS=-L${MPI_LIB}
rm -rf darshan-3.2.1
tar -xvf darshan-3.2.1.tar
cd darshan-3.2.1/darshan-runtime
./configure --prefix=${HOME}/darshan --with-log-path=${HOME}/darshan-logs --with-jobid-env=SLURM_JOB_ID --enable-mpiio-mod
make
make install
cd ../darshan-util
./configure --prefix=${HOME}/darshan
make
make install
export PATH=${PATH}:${HOME}/darshan/bin
#export DARSHAN_LOGPATH=/home/brobey/darshan-logs

darshan-mk-log-dirs.pl
