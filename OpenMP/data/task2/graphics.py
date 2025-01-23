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
        "VectorLength",
        "NumThreads",
        "ScalarProductTime"
    ]
    for col in required_columns:
        if col not in data.columns:
            print(f"Ошибка: В файле отсутствует столбец {col}")
            return

    # Уникальные значения VectorLength для отображения графиков по этим параметрам
    vector_lengths = data["VectorLength"].unique()

    # Построение графиков для каждого значения VectorLength
    for vector_length in vector_lengths:
        subset = data[data["VectorLength"] == vector_length]
        x = subset["NumThreads"]

        # Время на одном потоке для вычисления ускорения
        time_single_thread = subset[subset["NumThreads"] == 1]["ScalarProductTime"].iloc[0]

        # Построение графика времени выполнения
        plt.figure(figsize=(10, 6))
        plt.plot(x, subset["ScalarProductTime"], label="ScalarProductTime", marker="o")

        plt.title(f"Зависимость времени работы от количества потоков (VectorLength={vector_length})", fontsize=14)
        plt.xlabel("NumThreads", fontsize=12)
        plt.ylabel("Scalar Product Time (s)", fontsize=12)
        plt.xscale("log")
        plt.grid(True, which="both", linestyle="--", linewidth=0.5)
        plt.legend(fontsize=10)
        plt.tight_layout()
        plt.savefig(f"graph_time_VectorLength_{vector_length}.png")
        plt.show()

        # Построение графика ускорения
        speedup = time_single_thread / subset["ScalarProductTime"]

        plt.figure(figsize=(10, 6))
        plt.plot(x, speedup, label="Speedup", marker="o")

        plt.title(f"Ускорение от количества потоков (VectorLength={vector_length})", fontsize=14)
        plt.xlabel("NumThreads", fontsize=12)
        plt.ylabel("Speedup", fontsize=12)
        plt.xscale("log")
        plt.grid(True, which="both", linestyle="--", linewidth=0.5)
        plt.legend(fontsize=10)
        plt.tight_layout()
        plt.savefig(f"graph_speedup_VectorLength_{vector_length}.png")
        plt.show()


# Пример использования
csv_file = "t2_results.txt"  # Укажите путь к вашему CSV-файлу
plot_graphs(csv_file)
