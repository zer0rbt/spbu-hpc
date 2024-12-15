cmake_minimum_required(VERSION 3.25)
project(spbu_hpc)

set(CMAKE_CXX_STANDARD 14)

add_executable(spbu_hpc
        OpenMP/utils/vectorMin.cpp utils/timer.h utils/fileio.h main.cpp main.cpp main.cpp OpenMP/utils/vectorMin.h OpenMP/utils/vectorMax.cpp OpenMP/utils/vectorMax.h OpenMP/task1.cpp OpenMP/task1.h)
