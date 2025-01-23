#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Константы для режимов коммуникации
#define MODE_STANDARD 0
#define MODE_SYNCHRONOUS 1
#define MODE_READY 2
#define MODE_BUFFERED 3

void init_matrix(double* matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i * cols + j] = (double)rand() / RAND_MAX;
        }
    }
}

// Функция для выполнения умножения матриц с заданным режимом коммуникации
double matrix_multiply(int mode, int N, int rank, int size) {
    // Определяем количество строк для каждого процесса
    int* send_counts = (int*)malloc(size * sizeof(int));
    int* displs = (int*)malloc(size * sizeof(int));
    int base_strip_size = N / size;
    int remainder = N % size;

    for (int i = 0; i < size; i++) {
        send_counts[i] = base_strip_size + (i < remainder ? 1 : 0);
        send_counts[i] *= N; // Умножаем на количество столбцов
        displs[i] = (i == 0 ? 0 : displs[i - 1] + send_counts[i - 1]);
    }

    double *A = NULL, *B = NULL, *C = NULL;
    double *local_A = (double*)malloc(send_counts[rank] * sizeof(double));
    double *local_C = (double*)malloc(send_counts[rank] * sizeof(double));
    double *B_local = (double*)malloc(N * N * sizeof(double));
    double start_comm, end_comm, total_comm_time = 0;
    MPI_Status status;

    // Буфер для буферизованной отправки
    char* buffer = NULL;
    int buffer_size;
    if (mode == MODE_BUFFERED) {
        int max_message_size = N * N;
        buffer_size = max_message_size * sizeof(double) + MPI_BSEND_OVERHEAD;

        buffer = (char*)malloc(buffer_size);
        if (buffer == NULL) {
            printf("Failed to allocate buffer for buffered send\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        int result = MPI_Buffer_attach(buffer, buffer_size);
        if (result != MPI_SUCCESS) {
            printf("Failed to attach buffer\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
    }

    if (rank == 0) {
        A = (double*)malloc(N * N * sizeof(double));
        B = (double*)malloc(N * N * sizeof(double));
        C = (double*)malloc(N * N * sizeof(double));
        init_matrix(A, N, N);
        init_matrix(B, N, N);
    }

    // Измеряем время коммуникаций
    start_comm = MPI_Wtime();

    // Распределение данных в зависимости от режима
    MPI_Scatterv(A, send_counts, displs, MPI_DOUBLE,
                 local_A, send_counts[rank], MPI_DOUBLE,
                 0, MPI_COMM_WORLD);

    // Рассылка матрицы B
    MPI_Bcast(B_local, N * N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    end_comm = MPI_Wtime();
    total_comm_time = end_comm - start_comm;

    // Вычисление локальной части
    int local_rows = send_counts[rank] / N;
    for (int i = 0; i < local_rows; i++) {
        for (int j = 0; j < N; j++) {
            local_C[i * N + j] = 0;
            for (int k = 0; k < N; k++) {
                local_C[i * N + j] += local_A[i * N + k] * B_local[k * N + j];
            }
        }
    }

    // Сбор результатов
    start_comm = MPI_Wtime();
    MPI_Gatherv(local_C, send_counts[rank], MPI_DOUBLE,
                C, send_counts, displs, MPI_DOUBLE,
                0, MPI_COMM_WORLD);
    end_comm = MPI_Wtime();
    total_comm_time += end_comm - start_comm;

    if (mode == MODE_BUFFERED && buffer != NULL) {
        MPI_Buffer_detach(&buffer, &buffer_size);
        free(buffer);
    }

    if (rank == 0) {
        free(A);
        free(B);
        free(C);
    }
    free(local_A);
    free(local_C);
    free(B_local);
    free(send_counts);
    free(displs);

    return total_comm_time;
}

int main(int argc, char** argv) {
    int rank, size;
    int N = 2001;  // Размер матриц

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const char* mode_names[] = {
            "Standard mode",
            "Synchronous mode",
            "Ready mode",
            "Buffered mode"
    };

    // Тестируем каждый режим
    for (int mode = 0; mode < 4; mode++) {
        double comm_time = matrix_multiply(mode, N, rank, size);
        double max_comm_time;

        // Находим максимальное время коммуникаций среди всех процессов
        MPI_Reduce(&comm_time, &max_comm_time, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

        if (rank == 0) {
            printf("%s - Communication time: %f seconds\n",
                   mode_names[mode], max_comm_time);
        }

        MPI_Barrier(MPI_COMM_WORLD);
    }

    if (rank == 0) printf("----------------------------------------------------------------------\n");
    MPI_Finalize();

    return 0;
}
