#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void exchange_messages(int n) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    char* send_buffer = (char*)malloc(n * sizeof(char));
    char* recv_buffer = (char*)malloc(n * sizeof(char));

    // Инициализация отправляемого сообщения
    for (int i = 0; i < n; i++) {
        send_buffer[i] = 'a';
    }

    double start_time, end_time;
    int dest, source;

    if (rank == 0) {
        dest = 1;
        source = 1;
        start_time = MPI_Wtime();

        for (int i = 0; i < 100; i++) {
            MPI_Sendrecv(send_buffer, n, MPI_BYTE, dest, 0,
                         recv_buffer, n, MPI_BYTE, source, 0,
                         MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        end_time = MPI_Wtime();
        printf("Message size: %d bytes\n", n);
        printf("Time taken: %f seconds\n", end_time - start_time);
    }
    else if (rank == 1) {
        dest = 0;
        source = 0;

        for (int i = 0; i < 100; i++) {
            MPI_Sendrecv(send_buffer, n, MPI_BYTE, dest, 0,
                         recv_buffer, n, MPI_BYTE, source, 0,
                         MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
    }

    free(send_buffer);
    free(recv_buffer);
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int sizes[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};

    for (int i = 0; i < 9; i++) {
        exchange_messages(sizes[i]);
    }

    MPI_Finalize();
    return 0;
}