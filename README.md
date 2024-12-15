# Introduction to Supercomputing Course

This repository contains solutions to tasks from the course *Introduction to Supercomputing* (Введение в суперкомпьютерные вычисления). The course covers parallel computing using **OpenMP** and **MPI**. The repository is structured into two main directories: `OpenMP` and `MPI`, each containing solutions to corresponding tasks, along with relevant documentation.

## Directory Structure

- `OpenMP/`: Contains code and documentation for tasks related to OpenMP (shared-memory parallelism).
- `MPI/`: Contains code and documentation for tasks related to MPI (distributed-memory parallelism).

## Tasks Overview

### OpenMP (Max 16 points)

1. **Finding Minimum/Maximum Value in a Vector**  
   Develop a program to find the minimum or maximum value in a vector, both with and without reduction.

2. **Scalar Product of Two Vectors**  
   Compute the scalar product of two vectors.

3. **Integral Calculation Using the Rectangular Method**  
   Calculate a definite integral using the rectangular method.

4. **Finding Maximum of Row Minimums in a Matrix**  
   Implement a program to find the maximum of the minimum elements of rows in a matrix.

5. **Matrix Computation with Special Matrix Types**  
   Implement matrix operations using special matrix types (e.g., band, triangular), and analyze performance with different parallelization strategies.

6. **Iteration Distribution in Loops (static, dynamic, guided)**  
   Investigate the impact of different iteration distribution strategies in a parallel loop with varying load.

7. **Reduction Operation Using Different Synchronization Methods**  
   Implement reduction operations with atomic operations, critical sections, and locks. Compare performance with OpenMP's built-in reduction.

8. **Parallel Scalar Product with Sectioning**  
   Implement the scalar product for a sequence of vectors, using OpenMP sections for parallelization.

9. **Nested Parallelism Support**  
   If supported by the compiler, implement nested parallelism and evaluate its impact on performance.

### MPI (Max 22 points)

1. **Finding Minimum/Maximum Value in a Vector**  
   Develop a program to find the minimum or maximum value in a vector using MPI.

2. **Scalar Product of Two Vectors**  
   Compute the scalar product of two vectors using MPI.

3. **Message Exchange Between Two Processes**  
   Implement a program where two processes exchange messages of varying sizes and analyze the performance impact.

4. **Matrix Multiplication Algorithms**  
   Implement both simple and advanced matrix multiplication algorithms (e.g., Fox, Cannon) and compare their performance.

5. **Configurable Computation and Communication Load**  
   Create a program with adjustable computation and communication loads, and analyze its performance.

6. **MPI Data Transfer Modes**  
   Implement and evaluate different MPI data transfer modes (synchronous, ready, buffered).

7. **Non-blocking MPI Communication**  
   Modify the program to use non-blocking MPI communication, and analyze the impact on performance.

8. **Simultaneous Data Transfer and Reception**  
   Modify the program to perform simultaneous data transfer and reception, comparing the results with earlier versions.

9. **Collective Operations with Pairwise Exchanges**  
   Implement collective operations (e.g., Broadcast, Reduce, Gather) using pairwise exchanges, and compare performance with built-in MPI functions.

10. **Derived Data Types in MPI**  
    Create a program to demonstrate derived data types in MPI, comparing performance with packed/unpacked data.

11. **Process Grid Representation and Collective Operations**  
    Represent processes as a rectangular grid and perform collective operations within specific communicators, comparing performance.

12. **Topology Creation in MPI**  
    Implement various MPI topologies (Cartesian, Torus, Graph, Star).

## Reports and Performance Analysis

For each task, the solution includes performance analysis with respect to:

- **Execution Time**: Time taken for computation with different numbers of parallel threads or processes.
- **Speedup**: The comparison of execution time with and without parallelism.
- **Scalability**: How the program performance changes with different problem sizes (e.g., array/matrix sizes).

Graphical plots and tables are included to visualize these performance metrics.

## Requirements

- For OpenMP: A compiler that supports OpenMP (e.g., GCC, Clang).
- For MPI: An MPI implementation (e.g., MPICH, OpenMPI).
- Suitable cluster or multi-core machine for parallel execution.
