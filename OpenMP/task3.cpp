
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
