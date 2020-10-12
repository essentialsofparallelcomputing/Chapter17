# Chapter 17 Tools and resources for better code
This is from Chapter 17 of Parallel and High Performance Computing, Robey and Zamora,
Manning Publications, available at http://manning.com

The book may be obtained at
   http://www.manning.com/?a_aid=ParallelComputingRobey

Copyright 2019-2020 Robert Robey, Yuliana Zamora, and Manning Publications
Emails: brobey@earthlink.net, yzamora215@gmail.com

See License.txt for licensing information.

Timers: (Book: listing 17.1 - 17.2)
   Build with cmake
      cd timers
      mkdir build && cd build
      cmake .. && make
   Run with
      ../runit.sh

DrMemory: (Book: listing 17.3)
   Build with make
      cd DrMemory && make
   Run with
      drmemory -- memoryexample

dmalloc: (Book: listing 17.4)
   Build with make
      cd Dmalloc
      make
   Run with
      ./mallocexample

Archer: (Book: listing 17.5)
   Install with spack
      git clone https://github.com/spack/spack.git
      export PATH=`pwd`/spack/bin:${PATH}
      spack install archer
   Build example with cmake
      cd Archer
      mkdir build && cd build
      cmake .. && make
   Run with
      ./stencil

Darshan:
   Build with cmake
      cd MPI_IO_Examples/mpi_io_block2d
      mkdir build && cd build
      cmake .. && make
   Run with
      mpirun -n 4 mpi_io_block2d
   View results
      darshan-job-summary.pl ../../../mpi_io_block2d.darshan
      evince mpi_io_block2d.darshan.pdf

clean:
	rm -rf timers/build
	cd DrMemory && make clean
	cd Dmalloc && make clean
	rm -rf spack && rm -rf Archer/build
	rm -rf MPI_IO_Examples/mpi_io_block2d/build mpi_io_block2d.darshan
