#ifndef SPBU_HPC_FILEIO_H
#define SPBU_HPC_FILEIO_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

/**
 * @brief Reads data from a file and stores it in a vector.
 *
 * This function reads values from a file and stores them in the provided vector.
 * It tries to open the specified file and, if successful, reads the data from the
 * file one by one and appends it to the vector.
 *
 * @tparam T The type of elements in the vector. The function reads values of type
 *           T from the file. Common types can be `int`, `float`, `double`, etc.
 *
 * @param filename The name of the file to read data from. This string specifies
 *                 the path to the file.
 * @param vec A reference to a `std::vector<T>` where the read data will be stored.
 *            The vector will be populated with values read from the file.
 *
 * @return `true` if the file was successfully opened and data was read into the vector;
 *         `false` if there was an error opening the file or reading data.
 *
 * @note The function assumes that the file contains values of type T separated by
 *       whitespace (spaces, newlines). If the file contains invalid data that doesn't
 *       match the expected type, the reading process will stop at that point.
 *
 * @example
 * std::vector<double> vec;
 * bool success = file2vec("data.txt", vec);
 * if (success) {
 *     // Process the vector
 * } else {
 *     // Handle error
 * }
 */
template<typename T>
bool file2vec(const std::string& filename, std::vector<T>& vec) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }

    T value;
    while (file >> value) {
        vec.push_back(value);
    }

    file.close();
    return true;
}

/**
 * @brief Reads a matrix from a file and stores it in a 2D vector.
 *
 * This function reads the dimensions of a matrix (N and M) from the first two lines
 * of the file, then reads the matrix data and stores it in a 2D vector of type `std::vector<std::vector<T>>`.
 * The matrix dimensions are specified in the first two lines of the file.
 *
 * @tparam T The type of the elements in the matrix. The function reads values of type
 *           T (such as `int`, `float`, `double`, etc.) from the file.
 *
 * @param filename The name of the file containing the matrix. The first two lines of the file
 *                 must contain the values of N (number of rows) and M (number of columns),
 *                 followed by matrix data, one element per line or separated by spaces.
 * @param matrix A reference to a `std::vector<std::vector<T>>` where the matrix will be stored.
 *               The matrix will be populated with the data read from the file.
 *
 * @return `true` if the file was successfully opened and data was read into the matrix;
 *         `false` if there was an error opening the file or reading data.
 *
 * @note The first line of the file should contain N (number of rows), the second line should
 *       contain M (number of columns). The remaining lines should contain the matrix elements,
 *       row by row.
 *
 * @example
 * std::vector<std::vector<int>> matrix;
 * bool success = file2matrix("matrix_data.txt", matrix);
 * if (success) {
 *     // Process the matrix
 * } else {
 *     // Handle error
 * }
 */
template<typename T>
bool file2matrix(const std::string &filename, std::vector<std::vector<T>> &matrix) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }

    // Read dimensions
    int N, M;
    file >> N >> M;  // First two lines contain N and M (rows and columns)

    // Check if the dimensions are valid
    if (N <= 0 || M <= 0) {
        std::cerr << "Invalid matrix dimensions: N=" << N << ", M=" << M << std::endl;
        return false;
    }

    // Resize the matrix to the appropriate size
    matrix.resize(N, std::vector<T>(M));

    // Read matrix data
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (!(file >> matrix[i][j])) {
                std::cerr << "Error reading matrix data at position (" << i << "," << j << ")" << std::endl;
                return false;
            }
        }
    }

    file.close();
    return true;
}

/**
 * @brief Writes a vector of vectors (matrix) of arbitrary elements to a file.
 *
 * This function takes a vector of vectors of arbitrary elements (template type),
 * and writes each element to a file, with elements of an inner vector separated
 * by spaces and each inner vector written on a new line.
 *
 * @tparam T The type of the elements in the vector.
 * @param vecOfVecs The vector of vectors to be written to the file.
 * @param filename The name of the file where the data will be written.
 */
template <typename T>
void matrix2file(const std::vector<std::vector<T>>& vecOfVecs, const std::string& filename) {
    std::ofstream outFile(filename);

    if (!outFile) {
        std::cerr << "Error opening file for writing!" << std::endl;
        return;
    }

    for (const auto& innerVec : vecOfVecs) {
        for (const auto& elem : innerVec) {
            outFile << elem << " ";
        }
        outFile << "\n";
    }

    outFile.close();

}

#endif // SPBU_HPC_FILEIO_H
