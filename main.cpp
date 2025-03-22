#include <omp.h>

#include "OpenMP/task1.h"
#include "OpenMP/task2.h"
#include "OpenMP/task3.h"
#include "OpenMP/task4.h"
#include "OpenMP/task5.h"
#include "OpenMP/task6.h"
#include "OpenMP/task7.h"
#include "OpenMP/task8.h"
#include "OpenMP/task9.h"

int main() {
    omp_set_nested(1);

    //testTask1("../OpenMP/data/task1/t1_results.txt");
    //testTask2("../OpenMP/data/task2/t2_results.txt");
    //testTask3("../OpenMP/data/task3/t3_results.txt", -1, 1);
    //testTask4("../OpenMP/data/task4/t4_results.txt");
    //testTask5("../OpenMP/data/task5/t5_results.txt");
    //testTask6("../OpenMP/data/task6/t6_results.txt");
    //testTask7("../OpenMP/data/task7/t7_results.txt");
    testTask8("../OpenMP/data/task8/t8_results.txt");
    //testTask9("../OpenMP/data/task9/t9_results.txt");


    return 0;
}
