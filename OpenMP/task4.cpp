#include "task4.h"

void task4(const std::string& filename){
    std::vector<std::vector<int>> matrix;
    if (!file2matrix(filename, matrix)){

        std::cout << "Task 4 readfile error!" << std::endl;
        return;
    }

    std::cout << "Matrix dismensions = " << matrix.size() << "x" << matrix[0].size() << std::endl;
    std::cout << "Max from mins is " << maxFromMin(matrix) << std::endl;
    measureExecutionTime(maxFromMin<int>, matrix, "maximin (standart)");
}