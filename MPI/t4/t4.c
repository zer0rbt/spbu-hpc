#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void init_matrix(double* matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i * cols + j] = (double)rand() / RAND_MAX;
        }
    }
}

void write_matrix_to_file(double* matrix, int rows, int cols, const char* filename) {
    FILE* file = fopen(filename, "w"); // Открываем файл для записи
    if (file == NULL) {
        perror("FILE IO ERROR");
        return;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(file, "%.10f ", matrix[i * cols + j]); // Записываем элементы с высокой точностью
        }
        fprintf(file, "\n"); // Переход на новую строку после каждой строки матрицы
    }

    fclose(file); // Закрываем файл
    printf("Matrix saved to file: %s\n", filename);
}

int main(int argc, char** argv) {
    int rank, size;
    int N = 1000;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (N % size != 0) {
        if (rank == 0) {
            printf("Matrix size must be divisible by number of processes\n");
        }
        MPI_Finalize();
        return 1;
    }

    int strip_size = N / size;

    // Выделяем память под локальные части матриц
    double *A = NULL, *B = NULL, *C = NULL;
    double *local_A = (double*)malloc(strip_size * N * sizeof(double));
    double *local_C = (double*)malloc(strip_size * N * sizeof(double));
    double *B_local = (double*)malloc(N * N * sizeof(double)); // Буфер для матрицы B

    // Инициализируем матрицы только в корневом процессе
    if (rank == 0) {
        A = (double*)malloc(N * N * sizeof(double));
        B = (double*)malloc(N * N * sizeof(double));
        C = (double*)malloc(N * N * sizeof(double));

        srand(time(NULL));
        init_matrix(A, N, N);
        init_matrix(B, N, N);
    }

    double start_time = MPI_Wtime();

    // Распределяем полосы матрицы A
    MPI_Scatter(A, strip_size * N, MPI_DOUBLE,
                local_A, strip_size * N, MPI_DOUBLE,
                0, MPI_COMM_WORLD);

    // Рассылаем матрицу B всем процессам
    MPI_Bcast(rank == 0 ? B : B_local, N * N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Вычисляем локальную часть результата
    for (int i = 0; i < strip_size; i++) {
        for (int j = 0; j < N; j++) {
            local_C[i * N + j] = 0;
            for (int k = 0; k < N; k++) {
                // Используем B_local для неосновных процессов
                local_C[i * N + j] += local_A[i * N + k] *
                                      (rank == 0 ? B[k * N + j] : B_local[k * N + j]);
            }
        }
    }

    // Собираем результаты
    MPI_Gather(local_C, strip_size * N, MPI_DOUBLE,
               C, strip_size * N, MPI_DOUBLE,
               0, MPI_COMM_WORLD);

    double end_time = MPI_Wtime();

    if (rank == 0) {
        printf("Time taken: %f seconds\n", end_time - start_time);

        write_matrix_to_file(A, N, N, "A.txt");
        write_matrix_to_file(B, N, N, "B.txt");
        write_matrix_to_file(C, N, N, "C.txt");

        free(A);
        free(B);
        free(C);
    }

    free(local_A);
    free(local_C);
    free(B_local);

    MPI_Finalize();
    return 0;
}