#include "task7.h"

void testTask7(const std::string& filename){
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "File open error!" << std::endl;
        return;
    }

    // Заголовок для таблицы
    outfile << "ArrayLength,NumThreads,MaxReductionTime,MaxNoReductionTime,"
               "MaxLock,MaxCritical\n";

    std::vector<int> lengths = {1000000, 10000000, 10000000, 1000000000};
    std::vector<int> numThreads = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 24, 30, 36, 48, 60, 90, 120, 144};

    for (int length : lengths) {
        std::vector<int> arr(length);

        arr = createRandomVector(length, INT8_MIN, INT8_MAX);

        for (int threads : numThreads) {
            omp_set_num_threads(threads);

            double maxRedTime = measureExecutionTime(maxReduction, arr);
            double maxNoRedTime = measureExecutionTime(maxNoReduction, arr);


            double minRedTime = measureExecutionTime(maxCritical, arr);
            double minNoRedTime = measureExecutionTime(maxLock, arr);

            outfile << length << "," << threads << "," << maxRedTime << ","
                    << maxNoRedTime << "," << minRedTime << ","
                    << minNoRedTime << "," << "\n";
        }
    }

    outfile.close();
    std::cout << "Done!" << filename << std::endl;
}