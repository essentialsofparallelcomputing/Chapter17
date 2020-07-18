cmake_minimum_required(VERSION 3.0)
project(mpi_io_block2d LANGUAGES C)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set (CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")

# Require MPI for this project:
find_package(MPI REQUIRED)

find_package(Vector)
if (CMAKE_VECTOR_VERBOSE)
    set(VECTOR_C_FLAGS "${VECTOR_C_FLAGS} ${VECTOR_C_VERBOSE}")
endif (CMAKE_VECTOR_VERBOSE)
if (CMAKE_VECTOR_NOVEC)
    set(VECTOR_C_FLAGS "${VECTOR_NOVEC_C_FLAGS}")
endif (CMAKE_VECTOR_NOVEC)

add_executable(mpi_io_block2d mpi_io_file_ops.c mpi_io_block2d.c malloc2D.c)

execute_process(COMMAND darshan-config --dyn-ld-flags OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE DARSHAN_LINK_FLAGS)
set_target_properties(mpi_io_block2d PROPERTIES INCLUDE_DIRECTORIES "${MPI_C_INCLUDE_PATH}")
set_target_properties(mpi_io_block2d PROPERTIES COMPILE_FLAGS "${MPI_C_COMPILE_FLAGS}")
set_target_properties(mpi_io_block2d PROPERTIES LINK_FLAGS "${MPI_C_LINK_FLAGS} ${DARSHAN_LINK_FLAGS}")
target_link_libraries(mpi_io_block2d ${MPI_C_LIBRARIES})

add_executable(fs_detect fs_detect.c)

# Cleanup
add_custom_target(distclean COMMAND rm -rf CMakeCache.txt CMakeFiles
                  Makefile cmake_install.cmake *.data)
