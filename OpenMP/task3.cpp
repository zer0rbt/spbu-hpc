
#include "task3.h"

double f(double x){
    return x / (sin(20 * x) + 1.01);
}

void task3(double a, double b, int N){

    std::cout<< "Integral is:" << definiteIntegral(f, a, b, N)<<std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    definiteIntegral(f, a, b, N);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout<<"Time to eval:" << duration.count() << " seconds" << std::endl;

}

void testTask3(const std::string& filename, double a, double b) {
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "File open error!" << std::endl;
        return;
    }

    // Заголовок таблицы
    outfile << "NumIntervals,NumThreads,IntegralValue,ExecutionTime\n";

    // Количество разбиений для интеграла
    std::vector<int> intervals = {1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
    // Количество потоков
    std::vector<int> numThreads = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 24, 30, 36, 48, 60, 90, 120, 144};

    for (int N : intervals) {
        for (int threads : numThreads) {
            omp_set_num_threads(threads);

            // Измерение времени выполнения интеграла
            auto start = std::chrono::high_resolution_clock::now();
            double result = definiteIntegral(f, a, b, N);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration = end - start;

            // Запись результатов в файл
            outfile << N << "," << threads << "," << result << "," << duration.count() << "\n";
        }
    }

    outfile.close();
    std::cout << "Done! Results saved to " << filename << std::endl;
}