import matplotlib.pyplot as plt
import pandas as pd


# Функция для построения графиков
def plot_graphs(csv_file):
    # Чтение данных из CSV
    data = pd.read_csv(csv_file)

    # Проверка наличия данных
    if data.empty:
        print("Файл CSV пуст или данные отсутствуют.")
        return

    # Проверка наличия необходимых столбцов
    required_columns = [
        "MatrixRows",
        "MatrixCols",
        "NumThreads",
        "ExecutionTime"
    ]
    for col in required_columns:
        if col not in data.columns:
            print(f"Ошибка: В файле отсутствует столбец {col}")
            return

    # Уникальные значения MatrixRows и MatrixCols для отображения графиков по этим параметрам
    matrix_sizes = data[["MatrixRows", "MatrixCols"]].drop_duplicates()

    # Построение графиков для каждой комбинации MatrixRows и MatrixCols
    for _, size in matrix_sizes.iterrows():
        matrix_rows = size["MatrixRows"]
        matrix_cols = size["MatrixCols"]
        subset = data[(data["MatrixRows"] == matrix_rows) & (data["MatrixCols"] == matrix_cols)]
        x = subset["NumThreads"]

        # Время на одном потоке для вычисления ускорения
        time_single_thread = subset[subset["NumThreads"] == 1]["ExecutionTime"].iloc[0]

        # Построение графика времени выполнения
        plt.figure(figsize=(10, 6))
        plt.plot(x, subset["ExecutionTime"], label="ExecutionTime", marker="o")

        plt.title(f"Зависимость времени работы от количества потоков (Matrix={matrix_rows}x{matrix_cols})", fontsize=14)
        plt.xlabel("NumThreads", fontsize=12)
        plt.ylabel("Execution Time (s)", fontsize=12)
        plt.xscale("log")
        plt.grid(True, which="both", linestyle="--", linewidth=0.5)
        plt.legend(fontsize=10)
        plt.tight_layout()
        plt.savefig(f"graph_time_Matrix_{matrix_rows}x{matrix_cols}.png")
        plt.show()

        # Построение графика ускорения
        speedup = time_single_thread / subset["ExecutionTime"]

        plt.figure(figsize=(10, 6))
        plt.plot(x, speedup, label="Speedup", marker="o")

        plt.title(f"Ускорение от количества потоков (Matrix={matrix_rows}x{matrix_cols})", fontsize=14)
        plt.xlabel("NumThreads", fontsize=12)
        plt.ylabel("Speedup", fontsize=12)
        plt.xscale("log")
        plt.grid(True, which="both", linestyle="--", linewidth=0.5)
        plt.legend(fontsize=10)
        plt.tight_layout()
        plt.savefig(f"graph_speedup_Matrix_{matrix_rows}x{matrix_cols}.png")
        plt.show()


# Пример использования
csv_file = "t4_results.txt"  # Укажите путь к вашему CSV-файлу
plot_graphs(csv_file)
