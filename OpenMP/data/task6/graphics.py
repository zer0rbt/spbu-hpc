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
        "Iterations",
        "Threads",
        "ProbabilityNothing",
        "ProbabilitySquareCalc",
        "ProbabilityRandCalc",
        "ExecutionTimeStatic",
        "ExecutionTimeGuided",
        "ExecutionTimeDynamic"
    ]
    for col in required_columns:
        if col not in data.columns:
            print(f"Ошибка: В файле отсутствует столбец {col}")
            return

    # Уникальные значения Iterations
    iterations_values = data["Iterations"].unique()

    # Построение графиков
    for iterations in iterations_values:
        subset = data[data["Iterations"] == iterations]
        x = subset["Threads"]

        # Время на одном потоке для вычисления ускорения
        time_static_1 = subset[subset["Threads"] == 1]["ExecutionTimeStatic"].iloc[0]
        time_guided_1 = subset[subset["Threads"] == 1]["ExecutionTimeGuided"].iloc[0]
        time_dynamic_1 = subset[subset["Threads"] == 1]["ExecutionTimeDynamic"].iloc[0]

        # Построение графика времени выполнения
        plt.figure(figsize=(10, 6))
        plt.plot(x, subset["ExecutionTimeStatic"], label="ExecutionTimeStatic", marker="o")
        plt.plot(x, subset["ExecutionTimeGuided"], label="ExecutionTimeGuided", marker="s")
        plt.plot(x, subset["ExecutionTimeDynamic"], label="ExecutionTimeDynamic", marker="^")

        plt.title(f"Зависимость времени работы от количества потоков (Iterations={iterations})", fontsize=14)
        plt.xlabel("Threads", fontsize=12)
        plt.ylabel("Execution Time (s)", fontsize=12)
        plt.xscale("log")
        plt.grid(True, which="both", linestyle="--", linewidth=0.5)
        plt.legend(fontsize=10)
        plt.tight_layout()
        plt.savefig(f"graph_time_Iterations_{iterations}.png")
        plt.show()

        # Построение графика ускорения
        speedup_static = time_static_1 / subset["ExecutionTimeStatic"]
        speedup_guided = time_guided_1 / subset["ExecutionTimeGuided"]
        speedup_dynamic = time_dynamic_1 / subset["ExecutionTimeDynamic"]

        plt.figure(figsize=(10, 6))
        plt.plot(x, speedup_static, label="SpeedupStatic", marker="o")
        plt.plot(x, speedup_guided, label="SpeedupGuided", marker="s")
        plt.plot(x, speedup_dynamic, label="SpeedupDynamic", marker="^")

        plt.title(f"Ускорение от количества потоков (Iterations={iterations})", fontsize=14)
        plt.xlabel("Threads", fontsize=12)
        plt.ylabel("Speedup", fontsize=12)
        plt.xscale("log")
        plt.grid(True, which="both", linestyle="--", linewidth=0.5)
        plt.legend(fontsize=10)
        plt.tight_layout()
        plt.savefig(f"graph_speedup_Iterations_{iterations}.png")
        plt.show()


# Пример использования
csv_file = "t6_results.txt"  # Укажите путь к вашему CSV-файлу
plot_graphs(csv_file)
