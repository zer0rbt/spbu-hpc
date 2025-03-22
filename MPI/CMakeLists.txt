cmake_minimum_required(VERSION 3.25)
project(MPI_example)

set(CMAKE_CXX_STANDARD 17)


set(MPI_C_INCLUDE_DIRS "C:/Program Files (x86)/Microsoft SDKs/MPI/Include")
set(MPI_C_LIBRARIES "C:/Program Files (x86)/Microsoft SDKs/MPI/Lib/x64/msmpi.lib")
set(MPI_CXX_LIBRARIES "C:/Program Files (x86)/Microsoft SDKs/MPI/Lib/x64/msmpi.lib")
set(MPIEXEC_EXECUTABLE "C:/Program Files/Microsoft MPI/Bin/mpiexec.exe")

# Сообщение для отладки (опционально)
message(STATUS "MPI Include Path: ${MPI_C_INCLUDE_DIRS}")
message(STATUS "MPI C Library: ${MPI_C_LIBRARIES}")
message(STATUS "MPI CXX Library: ${MPI_CXX_LIBRARIES}")
message(STATUS "MPI Executable: ${MPIEXEC_EXECUTABLE}")

# Добавление исполняемого файла
add_executable(MPI_example t6/t6.c)

# Подключение заголовков и библиотек
target_include_directories(MPI_example PRIVATE ${MPI_C_INCLUDE_DIRS})
target_link_libraries(MPI_example PRIVATE ${MPI_C_LIBRARIES} ${MPI_CXX_LIBRARIES})