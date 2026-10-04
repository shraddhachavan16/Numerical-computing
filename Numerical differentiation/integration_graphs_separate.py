import os

import matplotlib.pyplot as plt

from integration_separate import FUNCTIONS, run_integration


def create_separate_graphs(
    function_name="e^x",
    lower=0.0,
    upper=1.0,
    interval_values=(2, 4, 6, 8, 12, 16, 24, 48),
    output_folder="graphs",
):
    results = run_integration(function_name, lower, upper, interval_values)
    exact = results[0]["exact"]
    os.makedirs(output_folder, exist_ok=True)

    graph_definitions = (
        ("trapezoidal", "Trapezoidal Rule", "trapezoidal"),
        ("simpson_1_3", "Simpson 1/3 Rule", "simpson_1_3"),
        ("simpson_3_8", "Simpson 3/8 Rule", "simpson_3_8"),
    )

    saved_paths = []
    for result_key, title, filename in graph_definitions:
        points = [
            (
                (upper - lower) / row["n"],
                max(abs(exact - row[result_key]), 1e-16),
            )
            for row in results
            if row[result_key] is not None
        ]

        if not points:
            continue

        points.sort()
        step_sizes, errors = zip(*points)

        plt.figure(figsize=(8, 5))
        plt.loglog(step_sizes, errors, "o-")
        plt.xlabel("Step size (h)")
        plt.ylabel("Absolute error")
        plt.title(f"{title} Error - {function_name}")
        plt.grid(True, which="both")
        plt.tight_layout()

        path = os.path.join(output_folder, f"{filename}_{function_name.replace('^', '')}.png")
        plt.savefig(path, dpi=300)
        plt.close()
        saved_paths.append(path)

    return saved_paths


if __name__ == "__main__":
    for function_name in FUNCTIONS:
        paths = create_separate_graphs(function_name=function_name)
        print(f"{function_name}: {', '.join(paths)}")