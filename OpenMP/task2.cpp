#pragma once
#include "task2.h"

void task2(const std::string& vec1_file, const std::string& vec2_file){
    std::vector<float> vec1, vec2;
    if (!(file2vec(vec1_file, vec1) && file2vec(vec2_file, vec2))) {
        std::cout << "Error in task 2" << std::endl;
        return;
    }
    std::cout<< "Scalar product is:" << scalarProd(vec1, vec2)<<std::endl;
    std::string name = "scalarProd";
    printExecutionTime(scalarProd<float>, vec1, vec2, name);

}

void testTask2(const std::string& filename) {
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "File open error!" << std::endl;
        return;
    }

    // Заголовок таблицы
    outfile << "VectorLength,NumThreads,ScalarProductTime\n";

    std::vector<int> lengths = {10000, 100000, 1000000, 10000000, 100000000, 1000000000};
    std::vector<int> numThreads = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 24, 30, 36, 48, 60, 90, 120, 144};

    for (int length : lengths) {
        // Создание двух случайных векторов
        std::vector<float> vec1 = createRandomVector(length, -100.0f, 100.0f);
        std::vector<float> vec2 = createRandomVector(length, -100.0f, 100.0f);

        for (int threads : numThreads) {
            omp_set_num_threads(threads);

            // Измерение времени выполнения скалярного произведения
            double time = measureExecutionTime(scalarProd<float>, vec1, vec2);

            // Запись результата в файл
            outfile << length << "," << threads << "," << time << "\n";
        }
    }

    outfile.close();
    std::cout << "Done! Results saved to " << filename << std::endl;
}
