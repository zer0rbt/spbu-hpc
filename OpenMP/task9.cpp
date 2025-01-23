#include "task9.h"


void testTask9(const std::string& resultsFilename) {
    std::ofstream outfile(resultsFilename);
    if (!outfile.is_open()) {
        std::cerr << "File open error!" << std::endl;
        return;
    }

    // Заголовок таблицы
    outfile << "MatrixRows,MatrixCols,NumThreads,ExecutionTime,ExecutionTimeHighlyParallel\n";

    // Размеры матриц для тестирования
    std::vector<std::pair<int, int>> dimensions = {
            {100, 100}, {500, 500}, {10000, 10}, {1000, 100}, {10, 10000}, {100, 1000}
    };

    // Количество потоков
    std::vector<int> numThreads = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 24, 30, 36, 48, 60, 90, 120, 144};
    for (const auto& [rows, cols] : dimensions) {
        std::vector<std::vector<float>> matrix(rows);
        for (int i = 0; i < rows; ++i) {
            matrix[i] = createRandomVector(cols, (float)1.00, 1000000.0);
        }

        for (int threads : numThreads) {
            omp_set_num_threads(threads);

            // Измерение времени выполнения maxFromMin
            double executionTime = measureExecutionTime(maxFromMin<float>, matrix);
            double executionTimeHP = measureExecutionTime(highlyParallelMaxFromMin<float>, matrix);

            // Запись результатов в файл
            outfile << rows << "," << cols << "," << threads << "," << executionTime << "," << executionTimeHP << "\n";
        }
    }

    outfile.close();
    std::cout << "Done! Results saved to " << resultsFilename << std::endl;
}