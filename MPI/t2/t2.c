#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Функция для генерации вектора
void generate_vector(double* vector, int vector_length) {
    for (int i = 0; i < vector_length; i++) {
        vector[i] = (double )rand() / RAND_MAX * 1000.0; // Числа от 0 до 999.999
    }
}

void write_vector_to_file(const double* vector, int vector_length, const char* filename) {
    FILE* file = fopen(filename, "w"); // Открываем файл на запись
    if (file == NULL) {
        perror("FILE IO ERROR");
        return;
    }

    for (int i = 0; i < vector_length; i++) {
        fprintf(file, "%f\n", vector[i]); // Записываем каждый элемент в новую строку
    }

    fclose(file); // Закрываем файл
    printf("OK: %s\n", filename);
}

int main(int argc, char** argv) {
    int rank, size;
    int vector_length = 100000; // Длина векторов (можно задать другую длину)
    double *vector_a = NULL, *vector_b = NULL;
    double start_time, end_time;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int chunk_size = vector_length / size;
    int remainder = vector_length % size;

// Пересчитываем размер чанка для последнего процесса
    int last_chunk_size = chunk_size;
    if (rank == size - 1) {
        last_chunk_size += remainder;
    }

// Выделяем память с учётом возможного остатка
    double* local_a = (double*)malloc(last_chunk_size * sizeof(double));
    double* local_b = (double*)malloc(last_chunk_size * sizeof(double));
    double local_dot_product = 0.0;
    double global_dot_product = 0.0;

    // Генерация данных на процессе 0
    if (rank == 0) {
        vector_a = (double*)malloc(vector_length * sizeof(double));
        vector_b = (double*)malloc(vector_length * sizeof(double));

        generate_vector(vector_a, vector_length);
        generate_vector(vector_b, vector_length);

        write_vector_to_file(vector_a, vector_length, "vec1.txt");
        write_vector_to_file(vector_b, vector_length, "vec2.txt");



        start_time = MPI_Wtime(); // Начало измерения времени
    }

    int *sendcounts = NULL, *displs = NULL;
    if (rank == 0) {
        sendcounts = (int*)malloc(size * sizeof(int));
        displs = (int*)malloc(size * sizeof(int));

        for (int i = 0; i < size; i++) {
            sendcounts[i] = chunk_size;
            if (i == size - 1) {
                sendcounts[i] += remainder;
            }
            displs[i] = i * chunk_size;
        }
    }

    MPI_Scatterv(vector_a, sendcounts, displs, MPI_DOUBLE,
                 local_a, last_chunk_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatterv(vector_b, sendcounts, displs, MPI_DOUBLE,
                 local_b, last_chunk_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

// Вычисление локального скалярного произведения
    local_dot_product = 0.0;
    for (int i = 0; i < last_chunk_size; i++) {
        local_dot_product += local_a[i] * local_b[i];
    }

    // Сбор всех локальных результатов на процессе 0
    MPI_Reduce(&local_dot_product, &global_dot_product, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        end_time = MPI_Wtime(); // Конец измерения времени

        printf("%f\n", end_time - start_time);

        // Освобождение памяти
        free(vector_a);
        free(vector_b);
    }

    free(local_a);
    free(local_b);

    MPI_Finalize();
    return 0;
}
