#include "mpi.h"

void mpi_io_file_init(int ng, int *global_sizes, int *global_subsizes,
   int *global_starts, MPI_Datatype *memspace, MPI_Datatype *filespace);
void mpi_io_file_finalize(MPI_Datatype *memspace, MPI_Datatype *filespace);
void write_mpi_io_file(const char *filename, double **data, int data_size,
     MPI_Datatype memspace, MPI_Datatype filespace, MPI_Comm mpi_io_comm);
void read_mpi_io_file(const char *filename, double **data, int data_size,
     MPI_Datatype memspace, MPI_Datatype filespace, MPI_Comm mpi_io_comm);
