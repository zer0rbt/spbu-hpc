import numpy as np

def read_matrix_from_file(filename):
    """Читает матрицу из файла, где элементы разделены пробелами, а строки разделены переносами."""
    try:
        with open(filename, 'r') as file:
            matrix = []
            for line in file:
                row = list(map(float, line.split()))
                matrix.append(row)
        return np.array(matrix)
    except Exception as e:
        print(f"Error reading file {filename}: {e}")
        return None

def write_matrix_to_file(matrix, filename):
    """Записывает матрицу в файл с указанной точностью."""
    try:
        with open(filename, 'w') as file:
            for row in matrix:
                file.write(' '.join(f"{val:.10f}" for val in row) + "\n")
        print(f"Result saved to file: {filename}")
    except Exception as e:
        print(f"Error writing to file {filename}: {e}")

def multiply_matrices(file1, file2, output_file):
    """Читает две матрицы из файлов, перемножает их и сохраняет результат в другой файл."""
    matrix1 = read_matrix_from_file(file1)
    matrix2 = read_matrix_from_file(file2)

    if matrix1 is None or matrix2 is None:
        print("One of the matrices could not be loaded.")
        return

    # Проверяем, можно ли перемножить матрицы
    if matrix1.shape[1] != matrix2.shape[0]:
        print(f"Matrix multiplication is not possible: {matrix1.shape} and {matrix2.shape} are incompatible.")
        return

    # Перемножаем матрицы
    result = np.dot(matrix1, matrix2)

    # Сохраняем результат
    write_matrix_to_file(result, output_file)

def subtract_matrices(file1, file2, output_file):
    """Читает две матрицы из файлов, вычисляет их разницу и сохраняет результат в другой файл."""
    matrix1 = read_matrix_from_file(file1)
    matrix2 = read_matrix_from_file(file2)

    if matrix1 is None or matrix2 is None:
        print("One of the matrices could not be loaded.")
        return

    # Проверяем, имеют ли матрицы одинаковый размер
    if matrix1.shape != matrix2.shape:
        print(f"Matrix subtraction is not possible: {matrix1.shape} and {matrix2.shape} have different sizes.")
        return

    # Вычисляем разницу матриц
    result = matrix1 - matrix2

    # Сохраняем результат

    print(np.linalg.det(result))
    write_matrix_to_file(result, output_file)

if __name__ == "__main__":
    # Укажите пути к файлам с матрицами и файлы для результата
    file1 = "A.txt"
    file2 = "B.txt"
    file3 = "C.txt"
    output_file_multiply = "C1.txt"
    output_file_subtract = "result_subtract.txt"

    multiply_matrices(file1, file2, output_file_multiply)
    subtract_matrices(file3, output_file_multiply, output_file_subtract)
