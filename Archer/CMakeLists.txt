cmake_minimum_required (VERSION 3.0)
project (stencil)

set (CC clang-archer)

set (CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O3")

find_package(OpenMP)

# Adds build target of stencil with source code files
add_executable(stencil stencil.c timer.c timer.h malloc2D.c malloc2D.h)
set_target_properties(stencil PROPERTIES COMPILE_FLAGS ${OpenMP_C_FLAGS})
set_target_properties(stencil PROPERTIES LINK_FLAGS "${OpenMP_C_FLAGS} -L${HOME}/archer/lib -larcher")

# Cleanup
add_custom_target(distclean COMMAND rm -rf CMakeCache.txt CMakeFiles
                  Makefile cmake_install.cmake stencil.dSYM ipo_out.optrpt)
