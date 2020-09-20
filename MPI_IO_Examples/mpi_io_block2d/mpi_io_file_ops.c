#include <stddef.h>
#include "mpi_io_file_ops.h"

MPI_File create_mpi_io_file(const char *filename, MPI_Comm mpi_io_comm,
       long long file_size);
MPI_File open_mpi_io_file(const char *filename, MPI_Comm mpi_io_comm);

static long long file_offset = 0;

void mpi_io_file_init(int ng, int ndims, int *global_sizes, int *global_subsizes,
  int *global_starts, MPI_Datatype *memspace, MPI_Datatype *filespace){
  // create data descriptors on disk and in memory

  // Global view of entire 2D domain -- collates decomposed subarrays
  MPI_Type_create_subarray(ndims, global_sizes, global_subsizes, global_starts,
                           MPI_ORDER_C, MPI_DOUBLE, filespace);
  MPI_Type_commit(filespace);

  // Local 2D subarray structure -- strips ghost cells on node
  int ny = global_subsizes[0], nx = global_subsizes[1];
  int local_sizes[]    = {ny+2*ng,   nx+2*ng};
  int local_subsizes[] = {ny,        nx};
  int local_starts[]   = {ng,        ng};

  MPI_Type_create_subarray(ndims, local_sizes, local_subsizes, local_starts,
                           MPI_ORDER_C, MPI_DOUBLE, memspace);
  MPI_Type_commit(memspace);
}

void mpi_io_file_finalize(MPI_Datatype *memspace, MPI_Datatype *filespace){
  MPI_Type_free(memspace);
  MPI_Type_free(filespace);
}

void write_mpi_io_file(const char *filename, double **data, int data_size,
    MPI_Datatype memspace, MPI_Datatype filespace, MPI_Comm mpi_io_comm){
  MPI_File file_handle = create_mpi_io_file(filename, mpi_io_comm,
         (long long)data_size);

  MPI_File_set_view(file_handle, file_offset, MPI_DOUBLE, filespace,
         "native", MPI_INFO_NULL);
  MPI_File_write_all(file_handle, &(data[0][0]), 1, memspace, MPI_STATUS_IGNORE);
  file_offset += data_size;
  
  MPI_File_close(&file_handle);
  file_offset = 0;
}

MPI_File create_mpi_io_file(const char *filename, MPI_Comm mpi_io_comm,
        long long file_size){
  int file_mode = MPI_MODE_WRONLY | MPI_MODE_CREATE | MPI_MODE_UNIQUE_OPEN;

  MPI_Info mpi_info = MPI_INFO_NULL; // For MPI IO hints
  MPI_Info_create(&mpi_info);
  MPI_Info_set(mpi_info, "collective_buffering", "true");
  MPI_Info_set(mpi_info, "striping_factor", "8");
  MPI_Info_set(mpi_info, "striping_unit", "4194304");

  MPI_File file_handle = NULL;
  MPI_File_open(mpi_io_comm, filename, file_mode, mpi_info, &file_handle);
  if (file_size > 0) MPI_File_set_size(file_handle, file_size);
  file_offset = 0;
  return file_handle;
}

void read_mpi_io_file(const char *filename, double **data, int data_size,
    MPI_Datatype memspace, MPI_Datatype filespace, MPI_Comm mpi_io_comm){
  MPI_File file_handle = open_mpi_io_file(filename, mpi_io_comm);

  MPI_File_set_view(file_handle, file_offset, MPI_DOUBLE, filespace,
         "native", MPI_INFO_NULL);
  MPI_File_read_all(file_handle, &(data[0][0]), 1, memspace, MPI_STATUS_IGNORE);
  file_offset += data_size;
  
  MPI_File_close(&file_handle);
  file_offset = 0;
}

MPI_File open_mpi_io_file(const char *filename, MPI_Comm mpi_io_comm){
  int file_mode = MPI_MODE_RDONLY | MPI_MODE_UNIQUE_OPEN;

  MPI_Info mpi_info = MPI_INFO_NULL; // For MPI IO hints
  MPI_Info_create(&mpi_info);
  MPI_Info_set(mpi_info, "collective_buffering", "true");

  MPI_File file_handle = NULL;
  MPI_File_open(mpi_io_comm, filename, file_mode, mpi_info, &file_handle);
  return file_handle;
}
