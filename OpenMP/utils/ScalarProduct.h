#ifndef SPBU_HPC_SCALARPRODUCT_H
#define SPBU_HPC_SCALARPRODUCT_H

#include <vector>
#include <omp.h>
#include <limits>
#include <iostream>
#include "../../utils/fileio.h"

template<typename T>
T scalarProd(std::vector<T> vec1, std::vector<T> vec2) {
    if (vec1.size() != vec2.size()) {
        std::cerr << "Error: vectors sizes do not match." << std::endl;
        return 0;
    }
    int n = vec1.size();
    T product = 0;
#pragma omp parallel for schedule(static) reduction(+ : product)
    for (int i = 0; i < n; i++) {
        product += vec1[i] * vec2[i];
    }
    return product;
}

template<typename T>
std::vector<T> files2scalarProd(const std::vector<std::string> &filenames) {
    std::vector<T> out(filenames.size(), 0);
    std::vector<std::vector<T>> fileData(filenames.size());

#pragma omp parallel for
    for (int i = 0; i < filenames.size(); i++) {
        std::vector<T> vec1, vec2;
        bool vec1Ready = false, vec2Ready = false, computationDone = false;

#pragma omp parallel sections nowait
        {

#pragma omp section
            {
                if (file2vec(vec1, filenames[i])) {
#pragma omp flush(vec1Ready)
                    vec1Ready = true;
#pragma omp flush(vec1Ready)
                } else {
                    std::cerr << "Error reading file: " << filenames[i] << std::endl;
                }
            }

#pragma omp section
            {
                if (i > 0) {
                    vec2 = fileData[i - 1];
#pragma omp flush(vec2Ready)
                    vec2Ready = true;
#pragma omp flush(vec2Ready)
                }
            }

#pragma omp section
            {
                while (!vec1Ready || (i > 0 && !vec2Ready)) {
#pragma omp flush(vec1Ready, vec2Ready)
                }
                if (i > 0 && !vec2.empty()) {
                    out[i] = scalarProd(vec1, vec2);
                }

            }
        }
    }


    return out;
}


#endif //SPBU_HPC_SCALARPRODUCT_H
