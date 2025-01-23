#ifndef SPBU_HPC_TASK2_H
#define SPBU_HPC_TASK2_H

#pragma once
#include <vector>
#include "../utils/fileio.h"
#include "../utils/timer.h"

#include "utils/ScalarProduct.h"
#include "utils/randVecs.h"

void task2(const std::string& vec1_file, const std::string& vec2_file);
void testTask2(const std::string& filename);
#endif //SPBU_HPC_TASK2_H
