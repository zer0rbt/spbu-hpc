#include "randVecs.h"

std::vector<int> createRandomVector(int size, int min, int max) {
    std::vector<int> vec(size);

    for (int i = 0; i < size; i++) {
        vec[i] = rand() % (max - min + 1) + min;
    }

    return vec;
}

std::vector<float> createRandomVector(int size, float min, float max) {
    std::vector<float> vec(size);

    for (int i = 0; i < size; i++) {
        vec[i] = rand() / (max - min + 1) + min;
    }

    return vec;
}