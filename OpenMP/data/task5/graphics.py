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
        "ExecutionTime",
        "ExecutionTimeTriangularStatic",
        "ExecutionTimeTriangularDynamic",
        "ExecutionTimeTriangularGuided"
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
        time_triangular_static_1 = subset[subset["NumThreads"] == 1]["ExecutionTimeTriangularStatic"].iloc[0]
        time_triangular_dynamic_1 = subset[subset["NumThreads"] == 1]["ExecutionTimeTriangularDynamic"].iloc[0]
        time_triangular_guided_1 = subset[subset["NumThreads"] == 1]["ExecutionTimeTriangularGuided"].iloc[0]

        # Построение графика времени выполнения
        plt.figure(figsize=(10, 6))
        plt.plot(x, subset["ExecutionTime"], label="ExecutionTime", marker="o")
        plt.plot(x, subset["ExecutionTimeTriangularStatic"], label="ExecutionTimeTriangularStatic", marker="s")
        plt.plot(x, subset["ExecutionTimeTriangularDynamic"], label="ExecutionTimeTriangularDynamic", marker="^")
        plt.plot(x, subset["ExecutionTimeTriangularGuided"], label="ExecutionTimeTriangularGuided", marker="D")

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
        speedup_static = time_triangular_static_1 / subset["ExecutionTimeTriangularStatic"]
        speedup_dynamic = time_triangular_dynamic_1 / subset["ExecutionTimeTriangularDynamic"]
        speedup_guided = time_triangular_guided_1 / subset["ExecutionTimeTriangularGuided"]

        plt.figure(figsize=(10, 6))
        plt.plot(x, speedup_static, label="SpeedupTriangularStatic", marker="o")
        plt.plot(x, speedup_dynamic, label="SpeedupTriangularDynamic", marker="s")
        plt.plot(x, speedup_guided, label="SpeedupTriangularGuided", marker="^")

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
csv_file = "t5_results.txt"  # Укажите путь к вашему CSV-файлу
plot_graphs(csv_file)
