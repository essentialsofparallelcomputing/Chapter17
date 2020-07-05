cmake_minimum_required (VERSION 3.0)
project (stream_triad)

set (CMAKE_C_STANDARD 99)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# Set vectorization flags for a few compilers
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O3")

find_package(Vector)

# Adds build target of stream_triad with source code files
add_executable(stream_triad stream_triad.c timer.c timer.h)

add_executable(stream_triad1 stream_triad.c timer.c timer.h)
set_target_properties(stream_triad1 PROPERTIES DEFINE_SYMBOL -DTIMER1)

if (APPLE)
  add_executable(stream_triad2 stream_triad.c timer.c timer.h)
  set_target_properties(stream_triad2 PROPERTIES DEFINE_SYMBOL -DTIMER2)
endif (APPLE)

add_executable(stream_triad3 stream_triad.c timer.c timer.h)
set_target_properties(stream_triad3 PROPERTIES DEFINE_SYMBOL -DTIMER3)

add_executable(stream_triad4 stream_triad.c timer.c timer.h)
set_target_properties(stream_triad4 PROPERTIES DEFINE_SYMBOL -DTIMER4)

add_executable(stream_triad5 stream_triad.c timer.c timer.h)
set_target_properties(stream_triad5 PROPERTIES DEFINE_SYMBOL -DTIMER5)

# Cleanup
add_custom_target(distclean COMMAND rm -rf CMakeCache.txt CMakeFiles
                  Makefile cmake_install.cmake stream_triad.dSYM ipo_out.optrpt
                  streamtriad streamtriad1 streamtriad2 streamtriad3 streamtriad4 streamtriad5)
