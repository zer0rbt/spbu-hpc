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

#endif // FILEIO_H
