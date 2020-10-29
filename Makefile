All: Timers DrMemory dmalloc Archer Darshan

.PHONY: Timers DrMemory dmalloc Archer Darshan

Timers:
	cd timers && mkdir build && cd build && cmake .. && make && ../runit.sh

DrMemory:
	cd DrMemory && make && drmemory -- memoryexample

dmalloc:
	cd Dmalloc && make && ./mallocexample

Archer:
	git clone https://github.com/spack/spack.git && \
	export PATH=`pwd`/spack/bin:${PATH} #&& spack install archer && \
	#cd Archer && mkdir build && cd build && cmake .. && make && ./stencil

Darshan:
	cd MPI_IO_Examples/mpi_io_block2d && mkdir build && cd build && cmake .. && make && \
	mpirun -n 4 mpi_io_block2d && \
	darshan-job-summary.pl ../../../mpi_io_block2d.darshan && \
	evince mpi_io_block2d.darshan.pdf

clean:
	rm -rf timers/build
	cd DrMemory && make clean
	cd Dmalloc && make clean
	rm -rf spack && rm -rf Archer/build
