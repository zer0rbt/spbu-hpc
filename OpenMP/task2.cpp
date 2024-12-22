#include "task2.h"

void task2(const std::string& vec1_file, const std::string& vec2_file){
    std::vector<float> vec1, vec2;
    if (!(file2vec(vec1_file, vec1) && file2vec(vec2_file, vec2))) {
        std::cout << "Error in task 2" << std::endl;
        return;
    }
    std::cout<< "Scalar product is:" << scalarProd(vec1, vec2)<<std::endl;
    std::string name = "scalarProd";
    printExecutionTime(scalarProd<float>, vec1, vec2, name);

}
