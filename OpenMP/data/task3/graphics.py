import matplotlib.pyplot as plt
import pandas as pd


# Функция для построения графиков
import matplotlib.pyplot as plt
import pandas as pd


# Функция для построения графиков
def plot_int_value(csv_file):
    # Чтение данных из CSV
    data = pd.read_csv(csv_file)

    # Проверка наличия данных
    if data.empty:
        print("Файл CSV пуст или данные отсутствуют.")
        return

    # Проверка наличия необходимых столбцов
    required_columns = [
        "NumIntervals",
        "NumThreads",
        "IntegralValue",
        "ExecutionTime"
    ]
    for col in required_columns:
        if col not in data.columns:
            print(f"Ошибка: В файле отсутствует столбец {col}")
            return

    # Построение графика зависимости значения интеграла от количества интервалов
    plt.figure(figsize=(10, 6))
    plt.plot(data["NumIntervals"], abs(data["IntegralValue"] - 0.815986), label="IntegralValue", marker="o")

    plt.title(f"Зависимость ошибки вычисления интеграла от количества интервалов", fontsize=14)
    plt.xlabel("NumIntervals", fontsize=12)
    plt.ylabel("Error Value", fontsize=12)
    plt.grid(True, which="both", linestyle="--", linewidth=0.5)
    plt.legend(fontsize=10)
    plt.yscale("log")
    plt.xscale("log")
    plt.tight_layout()
    plt.savefig("graph_integral_NumIntervals.png")
    plt.show()

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
        "NumIntervals",
        "NumThreads",
        "IntegralValue",
        "ExecutionTime"
    ]
    for col in required_columns:
        if col not in data.columns:
            print(f"Ошибка: В файле отсутствует столбец {col}")
            return

    # Уникальные значения NumIntervals для отображения графиков по этим параметрам
    num_intervals = data["NumIntervals"].unique()

    # Построение графиков для каждого значения NumIntervals
    for num_intervals_value in num_intervals:
        subset = data[data["NumIntervals"] == num_intervals_value]
        x = subset["NumThreads"]

        # Время на одном потоке для вычисления ускорения
        time_single_thread = subset[subset["NumThreads"] == 1]["ExecutionTime"].iloc[0]

        # Построение графика времени выполнения
        plt.figure(figsize=(10, 6))
        plt.plot(x, subset["ExecutionTime"], label="ExecutionTime", marker="o")

        plt.title(f"Зависимость времени работы от количества потоков (NumIntervals={num_intervals_value})", fontsize=14)
        plt.xlabel("NumThreads", fontsize=12)
        plt.ylabel("Execution Time (s)", fontsize=12)
        plt.xscale("log")
        plt.grid(True, which="both", linestyle="--", linewidth=0.5)
        plt.legend(fontsize=10)
        plt.tight_layout()
        plt.savefig(f"graph_time_NumIntervals_{num_intervals_value}.png")
        plt.show()

        # Построение графика интеграла
        plt.figure(figsize=(10, 6))
        plt.plot(x, subset["IntegralValue"], label="IntegralValue", marker="o")

        plt.title(f"Зависимость значения интеграла от количества потоков (NumIntervals={num_intervals_value})", fontsize=14)
        plt.xlabel("NumThreads", fontsize=12)
        plt.ylabel("Integral Value", fontsize=12)
        plt.xscale("log")
        plt.grid(True, which="both", linestyle="--", linewidth=0.5)
        plt.legend(fontsize=10)
        plt.tight_layout()
        plt.savefig(f"graph_integral_NumIntervals_{num_intervals_value}.png")
        plt.show()

        # Построение графика ускорения
        speedup = time_single_thread / subset["ExecutionTime"]

        plt.figure(figsize=(10, 6))
        plt.plot(x, speedup, label="Speedup", marker="o")

        plt.title(f"Ускорение от количества потоков (NumIntervals={num_intervals_value})", fontsize=14)
        plt.xlabel("NumThreads", fontsize=12)
        plt.ylabel("Speedup", fontsize=12)
        plt.xscale("log")
        plt.grid(True, which="both", linestyle="--", linewidth=0.5)
        plt.legend(fontsize=10)
        plt.tight_layout()
        plt.savefig(f"graph_speedup_NumIntervals_{num_intervals_value}.png")
        plt.show()



# Пример использования
csv_file = "t3_results.txt"  # Укажите путь к вашему CSV-файлу
plot_graphs(csv_file)
