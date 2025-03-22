#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

void generate_vector(float* vector, int vector_length) {
    srand(time(NULL));
    for (int i = 0; i < vector_length; i++) {
        vector[i] = (float)rand() / RAND_MAX * 1000.0; // Числа от 0 до 999.999
    }
}

void find_min_max(float* vector, int vector_length, float* global_min, float* global_max) {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Определяем длину локального массива
    int local_length = vector_length / size;
    int remainder = vector_length % size;

    // Учитываем остаток (если длина не делится нацело)
    if (rank < remainder) local_length++;

    float* local_vector = (float*)malloc(local_length * sizeof(float));
    int* sendcounts = (int*)malloc(size * sizeof(int));
    int* displs = (int*)malloc(size * sizeof(int));

    for (int i = 0; i < size; i++) {
        sendcounts[i] = vector_length / size + (i < remainder ? 1 : 0);
        displs[i] = (i > 0 ? displs[i - 1] + sendcounts[i - 1] : 0);
    }

    MPI_Scatterv(vector, sendcounts, displs, MPI_FLOAT, local_vector, local_length, MPI_FLOAT, 0, MPI_COMM_WORLD);

    // Нахождение локальных минимального и максимального значений
    float local_min = local_vector[0];
    float local_max = local_vector[0];
    for (int i = 1; i < local_length; i++) {
        if (local_vector[i] < local_min) local_min = local_vector[i];
        if (local_vector[i] > local_max) local_max = local_vector[i];
    }

    // Сбор глобальных минимального и максимального значений
    MPI_Reduce(&local_min, global_min, 1, MPI_FLOAT, MPI_MIN, 0, MPI_COMM_WORLD);
    MPI_Reduce(&local_max, global_max, 1, MPI_FLOAT, MPI_MAX, 0, MPI_COMM_WORLD);

    free(local_vector);
    free(sendcounts);
    free(displs);
}

int main(int argc, char** argv) {
    int size, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Длина вектора (задаётся, например, 100)
    int vector_length = 1000000;
    float* vector = NULL;
    float global_min, global_max;

    if (rank == 0) {
        // Генерация вектора на процессе 0
        vector = (float*)malloc(vector_length * sizeof(float));
        generate_vector(vector, vector_length);
    }

    double start_time = MPI_Wtime();
    find_min_max(vector, vector_length, &global_min, &global_max);
    double end_time = MPI_Wtime();

    if (rank == 0) {
        printf("%f\n", end_time - start_time);
        free(vector);
    }

    MPI_Finalize();
    return 0;
}
