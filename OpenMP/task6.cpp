#include "task6.h"


void testTask6(const std::string &filename) {
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "File open error!" << std::endl;
        return;
    }

    // Заголовок таблицы
    outfile
            << "Iterations,Threads,ProbabilityNothing,ProbabilitySquareCalc,ProbabilityRandCalc,ExecutionTimeStatic,ExecutionTimeGuided,ExecutionTimeDynamic\n";


    std::vector<int> lengths = {10000, 100000, 1000000, 10000000, 100000000, 1000000000};
    std::vector<int> numThreads = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 24, 30, 36, 48, 60,
                                   90, 120, 144};
    float p1 = 0.1;
    float p2 = 0.5;
    float p3 = 0.4;

    for (int length: lengths) {

        for (int threads: numThreads) {
            omp_set_num_threads(threads);
            auto start = std::chrono::high_resolution_clock::now();
            randItersParallelDynamic(length, p1, p2, p3);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> durationPD = end - start;

            start = std::chrono::high_resolution_clock::now();
            randItersParallelStatic(length, p1, p2, p3);
            end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> durationPS = end - start;

            start = std::chrono::high_resolution_clock::now();
            randItersParallelGuided(length, p1, p2, p3);
            end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> durationPG = end - start;

            // Запись результата в файл
            outfile << length << "," << threads << "," << p1 << "," << p2 << "," << p3 << "," << durationPD.count() << ","
                    << durationPS.count() << "," << durationPG.count() << "," << "\n";
        }
    }
}