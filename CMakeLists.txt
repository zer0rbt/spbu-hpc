cmake_minimum_required(VERSION 3.23)
project(spbu_hpc)

set(CMAKE_CXX_STANDARD 17)

# Убедитесь, что OpenMP доступен
find_package(OpenMP REQUIRED)

# Создайте исполнимый файл
add_executable(spbu_hpc
        OpenMP/utils/vectorMin.cpp
        utils/timer.h
        utils/fileio.h
        main.cpp
        OpenMP/utils/vectorMin.h
        OpenMP/utils/vectorMax.cpp
        OpenMP/utils/vectorMax.h
        OpenMP/task1.cpp
        OpenMP/task1.h
        OpenMP/task2.cpp
        OpenMP/task2.h
        OpenMP/utils/ScalarProduct.h
        OpenMP/task3.cpp
        OpenMP/task3.h
        OpenMP/utils/DefiniteIntegral.h
        OpenMP/utils/maximin.h
        OpenMP/task4.cpp
        OpenMP/task4.h
        utils/tester.h
        OpenMP/utils/randomisedFuncs.h
        OpenMP/utils/ranndomisedFuncs.cpp
        OpenMP/utils/randVecs.h
        OpenMP/utils/randVecs.cpp
        OpenMP/task5.cpp
        OpenMP/task5.h
        OpenMP/task5.cpp
        OpenMP/task6.cpp
        OpenMP/task6.h
        OpenMP/task7.cpp
        OpenMP/task7.h
        OpenMP/task9.cpp
        OpenMP/task9.h
        OpenMP/task9.h
        OpenMP/task9.h OpenMP/task8.h OpenMP/task8.cpp OpenMP/utils/ScalarProduct.cpp OpenMP/task8.cpp)

# Примените OpenMP только если он найден
if (OpenMP_CXX_FOUND)
    target_link_libraries(spbu_hpc PRIVATE OpenMP::OpenMP_CXX)
endif ()
