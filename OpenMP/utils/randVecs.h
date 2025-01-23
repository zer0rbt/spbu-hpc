#ifndef SPBU_HPC_RANDVECS_H
#define SPBU_HPC_RANDVECS_H

#include <vector>
#include <cstdlib>
#include <ctime>

std::vector<int> createRandomVector(int size, int min, int max);

std::vector<float> createRandomVector(int size, float min, float max);
#endif //SPBU_HPC_RANDVECS_H
