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
        "ArrayLength",
        "NumThreads",
        "MaxReductionTime",
        "MaxNoReductionTime",
        "MinReductionTime",
        "MinNoReductionTime"
    ]
    for col in required_columns:
        if col not in data.columns:
            print(f"Ошибка: В файле отсутствует столбец {col}")
            return

    # Уникальные значения ArrayLength для отображения графиков по этим параметрам
    array_lengths = data["ArrayLength"].unique()

    # Построение графиков для каждого значения ArrayLength
    for array_length in array_lengths:
        subset = data[data["ArrayLength"] == array_length]
        x = subset["NumThreads"]

        # Время на одном потоке для вычисления ускорения (по каждому из типов времени)
        time_max_reduction_1 = subset[subset["NumThreads"] == 1]["MaxReductionTime"].iloc[0]
        time_max_no_reduction_1 = subset[subset["NumThreads"] == 1]["MaxNoReductionTime"].iloc[0]
        time_min_reduction_1 = subset[subset["NumThreads"] == 1]["MinReductionTime"].iloc[0]
        time_min_no_reduction_1 = subset[subset["NumThreads"] == 1]["MinNoReductionTime"].iloc[0]

        # Построение графика времени выполнения
        plt.figure(figsize=(10, 6))
        plt.plot(x, subset["MaxReductionTime"], label="MaxReductionTime", marker="o")
        plt.plot(x, subset["MaxNoReductionTime"], label="MaxNoReductionTime", marker="s")
        plt.plot(x, subset["MinReductionTime"], label="MinReductionTime", marker="^")
        plt.plot(x, subset["MinNoReductionTime"], label="MinNoReductionTime", marker="D")

        plt.title(f"Зависимость времени работы от количества потоков (ArrayLength={array_length})", fontsize=14)
        plt.xlabel("NumThreads", fontsize=12)
        plt.ylabel("Time (s)", fontsize=12)
        plt.xscale("log")
        plt.grid(True, which="both", linestyle="--", linewidth=0.5)
        plt.legend(fontsize=10)
        plt.tight_layout()
        plt.savefig(f"graph_time_ArrayLength_{array_length}.png")
        plt.show()

        # Построение графика ускорения
        speedup_max_reduction = time_max_reduction_1 / subset["MaxReductionTime"]
        speedup_max_no_reduction = time_max_no_reduction_1 / subset["MaxNoReductionTime"]
        speedup_min_reduction = time_min_reduction_1 / subset["MinReductionTime"]
        speedup_min_no_reduction = time_min_no_reduction_1 / subset["MinNoReductionTime"]

        plt.figure(figsize=(10, 6))
        plt.plot(x, speedup_max_reduction, label="SpeedupMaxReduction", marker="o")
        plt.plot(x, speedup_max_no_reduction, label="SpeedupMaxNoReduction", marker="s")
        plt.plot(x, speedup_min_reduction, label="SpeedupMinReduction", marker="^")
        plt.plot(x, speedup_min_no_reduction, label="SpeedupMinNoReduction", marker="D")

        plt.title(f"Ускорение от количества потоков (ArrayLength={array_length})", fontsize=14)
        plt.xlabel("NumThreads", fontsize=12)
        plt.ylabel("Speedup", fontsize=12)
        plt.xscale("log")
        plt.grid(True, which="both", linestyle="--", linewidth=0.5)
        plt.legend(fontsize=10)
        plt.tight_layout()
        plt.savefig(f"graph_speedup_ArrayLength_{array_length}.png")
        plt.show()


# Пример использования
csv_file = "t1_results.txt"  # Укажите путь к вашему CSV-файлу
plot_graphs(csv_file)
