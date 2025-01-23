#include "task1.h"

void task1(const std::string &filename) {
    std::vector<int> arr;
    if (!file2vec(filename, arr)) {
        std::cout << "Error in task 1" << std::endl;
        return;
    }

    std::cout << "File length = " << arr.size() << std::endl;
    std::cout << "Max vale (with reduction): " << maxReduction(arr) << std::endl;
    std::cout << "Max value (without reduction): " << maxNoReduction(arr) << std::endl;
    printExecutionTime(maxReduction, arr, "maxReduction (with reduction)");
    printExecutionTime(maxNoReduction, arr, "maxNoReduction (without reduction)");
    printExecutionTime(sequentialMaxReduction, arr, "sequential");

    std::cout << "Min value (with reduction): " << minReduction(arr) << std::endl;
    std::cout << "Min value (without reduction): " << minNoReduction(arr) << std::endl;
    printExecutionTime(minReduction, arr, "minReduction (with reduction)");
    printExecutionTime(minNoReduction, arr, "minNoReduction (without reduction)");

}

void testTask1(const std::string &filename) {
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "File open error!" << std::endl;
        return;
    }

    // Заголовок для таблицы
    outfile << "ArrayLength,NumThreads,MaxReductionTime,MaxNoReductionTime,"
               "MinReductionTime,MinNoReductionTime\n";

    std::vector<int> lengths = {1000000, 10000000, 100000000, 1000000000};
    std::vector<int> numThreads = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 24, 30, 36, 48, 60,
                                   90, 120, 144};

    for (int length: lengths) {
        std::vector<int> arr(length);

        arr = createRandomVector(length, INT8_MIN, INT8_MAX);

        for (int threads: numThreads) {
            omp_set_num_threads(threads);

            double maxRedTime = 0;
            double maxNoRedTime = 0;
            double minRedTime = 0;
            double minNoRedTime = 0;
            int rounds = 10;
            for (int k =0; k < rounds;k++){
            maxRedTime += measureExecutionTime(maxReduction, arr);
            maxNoRedTime += measureExecutionTime(maxNoReduction, arr);


            minRedTime += measureExecutionTime(minReduction, arr);
            minNoRedTime += measureExecutionTime(minNoReduction, arr);}

            outfile << length << "," << threads << "," << maxRedTime / rounds << ","
                    << maxNoRedTime / rounds << "," << minRedTime / rounds << ","
                    << minNoRedTime / rounds << "," << "\n";
        }
    }

    outfile.close();
    std::cout << "Done!" << filename << std::endl;
}
