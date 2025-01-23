#include "task5.h"

void triangularTest(const std::string &filename) {
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "File open error!" << std::endl;
        return;
    }

    outfile
            << "MatrixRows,MatrixCols,NumThreads,ExecutionTime,ExecutionTimeTriangularStatic,ExecutionTimeTriangularDynamic,ExecutionTimeTriangularGuided\n";

    std::vector<std::pair<int, int>> dimensions = {
            {100,    100},
            {500,    500},
            {1000,   1000},
            {5000,   5000},
            {10000,   10000},
    };

    std::vector<int> numThreads = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 24, 30, 36, 48, 60,
                                   90, 120, 144};

    for (const auto &[rows, cols]: dimensions) {
        std::vector<std::vector<float>> matrix(rows);
        for (int i = 0; i < rows; ++i) {
            matrix[i] = createRandomVector(i + 1, (float) 0, (float) 1000);
            matrix[i].resize(cols, 0);
        }

        for (int threads: numThreads) {
            omp_set_num_threads(threads);

            double executionTimeS = measureExecutionTime(maxFromMin<float>, matrix);
            double executionTimeTG = measureExecutionTime(triangularGuidedMaxFromMin<float>, matrix);
            double executionTimeTS = measureExecutionTime(triangularStaticMaxFromMin<float>, matrix);
            double executionTimeTD = measureExecutionTime(triangularDynamicMaxFromMin<float>, matrix);

            //std::cout << maxFromMin(matrix) << " " << triangularGuidedMaxFromMin(matrix) << " " << triangularDynamicMaxFromMin(matrix) << " " << triangularStaticMaxFromMin(matrix) << "\n";

            outfile << rows << "," << cols << "," << threads << "," << executionTimeS << "," << executionTimeTS << ","
                    << executionTimeTD << "," << executionTimeTG << "\n";
        }
    }

    outfile.close();
    std::cout << "Triangular test done! Results saved to " << filename << std::endl;
}

/*void testBandMatrix(const std::string& filename) {
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "File open error!" << std::endl;
        return;
    }

    // Заголовок таблицы
    outfile << "MatrixSize,BandWidth,NumThreads,ExecutionTime,ExecutionTimeBW\n";

    // Размеры матриц и ширина ленты для тестирования
    std::vector<int> matrixSizes = {500, 1000, 2000};
    std::vector<int> bandWidths = {1, 3, 5, 10, 20, 49, 100, 137, 194, 211, 249}; // Полуширина ленты (от центра диагонали)
    std::vector<int> numThreads = {1, 2, 4, 8, 12};

    for (int size : matrixSizes) {
        for (int bandWidth : bandWidths) {
            std::vector<std::vector<int>> matrix(size, std::vector<int>(size, 0));

            // Генерация ленточной матрицы
            for (int i = 0; i < size; ++i) {
                for (int j = std::max(0, i - bandWidth); j <= std::min(size - 1, i + bandWidth); ++j) {
                    matrix[i][j] = rand() % 1000; // Случайные значения в пределах ленты
                }
            }

            for (int threads : numThreads) {
                omp_set_num_threads(threads);

                double executionTime = measureExecutionTime(maxFromMin<int>, matrix);
                double executionTimeBW = measureExecutionTime<int (*)(std::vector<std::vector<int>>, long), std::vector<int>>(bandMaxFromMin<int>, matrix);

                // Запись результатов в файл
                outfile << size << "," << bandWidth << "," << threads << "," << result << "," << executionTime << "\n";
            }
        }
    }

    outfile.close();
    std::cout << "Done! Results saved to " << resultsFilename << std::endl;
}*/

void testTask5(const std::string &filename){
    triangularTest(filename);
};