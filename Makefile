All: Timers DrMemory dmalloc Archer Darshan

.PHONY: Timers DrMemory dmalloc Archer

Timers:
	cd timers && mkdir build && cd build && cmake .. && make && ../runit.sh

DrMemory:
	cd DrMemory && make && drmemory -- memoryexample

dmalloc:
	cd Dmalloc && make && ./mallocexample

Archer:
	git clone https://github.com/spack/spack.git && export SPACK_ROOT=`pwd`/spack && \
	export PATH=$SPACK_ROOT/bin:$PATH && spack install archer && \
	mkdir build && cd build && cmake .. && make && ./stencil

Darshan:
	cd MPI_IO_Examples/mpi_io_block2d && mkdir build && cd build && cmake .. && make && \
	mpirun -n 4 mpi_io_block2d && darshan-job-summary.pl && darshan-job-summary.pl darshan-logs

clean:
	rm -rf timers/build
	cd DrMemory && make clean
	cd Dmalloc && make clean
