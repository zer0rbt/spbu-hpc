def read_vector_from_file(filename):
    with open(filename, 'r') as file:
        return [float(line.strip()) for line in file if line.strip()]

def dot_product(vector1, vector2):
    return sum(x * y for x, y in zip(vector1, vector2))

file1 = 'vec1.txt'
file2 = 'vec2.txt'

vector1 = read_vector_from_file(file1)
vector2 = read_vector_from_file(file2)

result = dot_product(vector1, vector2)
print(f"Скалярное произведение: {result}")