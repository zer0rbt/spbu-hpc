#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void exchange_messages(int n) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    char* message = (char*)malloc(n * sizeof(char));  // Выделяем память для сообщения
    for (int i = 0; i < n; i++) {
        message[i] = 'a'; // Инициализируем сообщение символами
    }

    double start_time, end_time;

    if (rank == 0) {
        // Начало измерения времени
        start_time = MPI_Wtime();

        for (int i = 0; i < 100; i++) {
            // Процесс 0 отправляет сообщение процессу 1
            MPI_Send(message, n, MPI_BYTE, 1, 0, MPI_COMM_WORLD);
            // Процесс 0 получает сообщение обратно от процесса 1
            MPI_Recv(message, n, MPI_BYTE, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        // Конец измерения времени
        end_time = MPI_Wtime();

        // Вывод времени выполнения
        printf("Message size: %d bytes\n", n);
        printf("Time taken: %f seconds\n", end_time - start_time);
    }
    else if (rank == 1) {
        for (int i = 0; i < 100; i++) {
            // Процесс 1 получает сообщение от процесса 0
            MPI_Recv(message, n, MPI_BYTE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            // Процесс 1 отправляет сообщение обратно процессу 0
            MPI_Send(message, n, MPI_BYTE, 0, 0, MPI_COMM_WORLD);
        }
    }

    free(message);  // Освобождение памяти
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    // Перебираем несколько значений размера сообщения
    int sizes[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};  // Размеры сообщений для эксперимента
    for (int i = 0; i < 9; i++) {
        exchange_messages(sizes[i]);
    }

    MPI_Finalize();
    return 0;
}
