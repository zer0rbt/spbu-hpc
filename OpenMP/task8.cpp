#include "task8.h"

template<typename T>
T files2scalarProd(std::vector<T> vec1, std::vector<T> vec2){
    if (vec1.size() != vec2.size()) {
        std::cerr << "Error: vectors sizes do not match." << std::endl;
        return 0;
    }
    int n = vec1.size();
    T product = 0;
#pragma omp parallel for schedule(static) reduction(+ : product)
    for (int i = 0; i < n; i++){
        product += vec1[i] * vec2[i];
    }
    return product;
}

void task8(const std::vector<std::string>& filenames){
    for
};