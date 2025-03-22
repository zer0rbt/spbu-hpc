#include "task8.h"
#pragma once

void testTask8(const std::string& filename) {
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "File open error!" << std::endl;
        return;
    }

    // Заголовок для таблицы
    outfile << "VecLength,VecsNum,NumThreads,ExecutionTime\n";

    // Параметры для тестирования
    std::vector<int> N_values = {100, 500, 1000, 10000}; // Размеры N
    std::vector<int> vecs_num_values = {100, 500, 1000, 10000}; // Число векторов
    std::vector<int> numThreads = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 24, 30, 36, 48, 60,
                                   90, 120, 144};; // Количество потоков

    for (int N : N_values) {
        for (int vecs_num : vecs_num_values) {
            for (int threads : numThreads) {
                omp_set_num_threads(threads);

                // Измерение времени выполнения
                double time = 0;
                int rounds = 10;
                for (int y =0; y < rounds; y++){
                auto start = std::chrono::high_resolution_clock::now();
                std::vector<float> results = computeRandomVectorOperations(N, vecs_num);
                auto end = std::chrono::high_resolution_clock::now();

                // Вычисление времени
                std::chrono::duration<double> duration = end - start;
                time += duration.count();
                }

                // Запись результата в файл
                outfile << N << "," << vecs_num << "," << threads << "," << time / rounds << "\n";
            }
        }
    }

    outfile.close();
    std::cout << "Done! Results saved to " << filename << std::endl;
}
