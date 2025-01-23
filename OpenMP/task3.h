#ifndef SPBU_HPC_TASK3_H
#define SPBU_HPC_TASK3_H

#include <vector>
#include <cmath>
#include <iostream>
#include "../utils/timer.h"
#include "../utils/fileio.h"

#include "utils/DefiniteIntegral.h"
#include "utils/randVecs.h"

double f(double x);

void task3(double a, double b, int N);
void testTask3(const std::string& filename, double a, double b);
#endif //SPBU_HPC_TASK3_H
