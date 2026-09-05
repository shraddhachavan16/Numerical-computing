import math
import csv
import os
import matplotlib.pyplot as plt

from differentiation import (
    ForwardDifference,
    BackwardDifference,
    CentralDifference,
    RichardsonExtrapolation
)

from lagrange import LagrangeInterpolation
from newton import NewtonInterpolation


# ============================================================
# FUNCTIONS
# ============================================================

functions = [
    ("e^x", math.exp, math.exp),

    ("sin(x)", math.sin, math.cos),

    ("x^3 - 2x + 1",
     lambda x: x**3 - 2*x + 1,
     lambda x: 3*x**2 - 2)
]


# ============================================================
# INPUT
# ============================================================

x = float(input("Enter x value: "))

data = input("Enter known x values separated by comma: ")

x_data = [float(v.strip()) for v in data.split(",")]


if len(x_data) < 2:
    print("Enter at least 2 x values.")
    exit()

if len(x_data) != len(set(x_data)):
    print("x values must be different.")
    exit()


# ============================================================
# H VALUES
# ============================================================

h_values = [
    0.1,
    0.01,
    0.001,
    0.0001,
    0.00001,
    0.000001
]


# ============================================================
# CREATE GRAPH FOLDER
# ============================================================

os.makedirs("graphs", exist_ok=True)


# ============================================================
# STORE RESULTS
# ============================================================

diff_results = []
lagrange_results = []
newton_results = []


# ============================================================
# DIFFERENTIATION
# ============================================================

for name, f, df in functions:

    exact = df(x)

    forward_errors = []
    backward_errors = []
    central_errors = []
    richardson_errors = []

    print("\n" + "=" * 120)
    print("DIFFERENTIATION -", name)
    print("=" * 120)

    print("x =", x)
    print("Exact Derivative =", f"{exact:.10f}")

    print("-" * 120)

    print(
        f"{'h':<12}"
        f"{'Forward':<18}{'F Error':<16}"
        f"{'Backward':<18}{'B Error':<16}"
        f"{'Central':<18}{'C Error':<16}"
        f"{'Richardson':<18}{'R Error':<16}"
    )

    print("-" * 120)


    # Calculate all h values
    for h in h_values:

        forward = ForwardDifference(x, h).calculate(f)

        backward = BackwardDifference(x, h).calculate(f)

        central = CentralDifference(x, h).calculate(f)

        richardson = RichardsonExtrapolation(x, h).calculate(f)


        # Absolute errors
        f_error = abs(exact - forward)
        b_error = abs(exact - backward)
        c_error = abs(exact - central)
        r_error = abs(exact - richardson)


        # Store errors for graph
        forward_errors.append(f_error)
        backward_errors.append(b_error)
        central_errors.append(c_error)
        richardson_errors.append(r_error)


        # Print result
        print(
            f"{h:<12.0e}"
            f"{forward:<18.10f}{f_error:<16.5e}"
            f"{backward:<18.10f}{b_error:<16.5e}"
            f"{central:<18.10f}{c_error:<16.5e}"
            f"{richardson:<18.10f}{r_error:<16.5e}"
        )


        # Store CSV data
        diff_results.append([
            name,
            x,
            h,
            exact,
            forward,
            f_error,
            backward,
            b_error,
            central,
            c_error,
            richardson,
            r_error
        ])


    # ========================================================
    # DIFFERENTIATION GRAPH
    # SAVE ONLY ONCE
    # ========================================================

    plt.figure(figsize=(8, 5))

    plt.loglog(
        h_values,
        [max(e, 1e-16) for e in forward_errors],
        "o-",
        label="Forward"
    )

    plt.loglog(
        h_values,
        [max(e, 1e-16) for e in backward_errors],
        "s-",
        label="Backward"
    )

    plt.loglog(
        h_values,
        [max(e, 1e-16) for e in central_errors],
        "^-",
        label="Central"
    )

    plt.loglog(
        h_values,
        [max(e, 1e-16) for e in richardson_errors],
        "D-",
        label="Richardson"
    )

    plt.xlabel("h")
    plt.ylabel("Absolute Error")
    plt.title("Differentiation Error - " + name)

    plt.legend()
    plt.grid(True)

    if name == "e^x":
        file_name = "graphs/ex_differentiation.png"

    elif name == "sin(x)":
        file_name = "graphs/sin_differentiation.png"

    else:
        file_name = "graphs/polynomial_differentiation.png"


    plt.savefig(file_name, dpi=300, bbox_inches="tight")

    plt.close()


# ============================================================
# INTERPOLATION
# ============================================================

for name, f, df in functions:

    # --------------------------------------------------------
    # Calculate y values only once
    # --------------------------------------------------------

    y_data = [f(value) for value in x_data]

    print("\n" + "=" * 70)
    print("INTERPOLATION DATA -", name)
    print("=" * 70)

    print("x_data:", x_data)

    print(
        "y_data:",
        [round(value, 6) for value in y_data]
    )


    # ========================================================
    # LAGRANGE
    # ========================================================

    lagrange = LagrangeInterpolation(
        x_data,
        y_data
    )

    lagrange_value = lagrange.calculate(x)

    exact_value = f(x)

    lagrange_error = abs(
        exact_value - lagrange_value
    )


    lagrange_results.append([
        name,
        exact_value,
        lagrange_value,
        lagrange_error
    ])


    # ========================================================
    # NEWTON
    # ========================================================

    newton = NewtonInterpolation(
        x_data,
        y_data
    )

    newton_value = newton.calculate(x)

    newton_error = abs(
        exact_value - newton_value
    )


    newton_results.append([
        name,
        exact_value,
        newton_value,
        newton_error
    ])


    # ========================================================
    # GRAPH DATA
    # ========================================================

    minimum = min(x_data)
    maximum = max(x_data)

    graph_x = []

    for i in range(101):

        value = (
            minimum +
            i * (maximum - minimum) / 100
        )

        graph_x.append(value)


    actual_y = [
        f(value)
        for value in graph_x
    ]

    lagrange_y = [
        lagrange.calculate(value)
        for value in graph_x
    ]

    newton_y = [
        newton.calculate(value)
        for value in graph_x
    ]


    # ========================================================
    # LAGRANGE GRAPH
    # SAVE ONLY ONCE
    # ========================================================

    plt.figure(figsize=(8, 5))

    plt.plot(
        graph_x,
        actual_y,
        label="Actual Function"
    )

    plt.plot(
        graph_x,
        lagrange_y,
        "--",
        label="Lagrange Polynomial"
    )

    plt.scatter(
        x_data,
        y_data,
        label="Known Data"
    )

    plt.xlabel("x")
    plt.ylabel("f(x)")
    plt.title("Lagrange Interpolation - " + name)

    plt.legend()
    plt.grid(True)


    if name == "e^x":
        file_name = "graphs/ex_lagrange.png"

    elif name == "sin(x)":
        file_name = "graphs/sin_lagrange.png"

    else:
        file_name = "graphs/polynomial_lagrange.png"


    plt.savefig(
        file_name,
        dpi=300,
        bbox_inches="tight"
    )

    plt.close()


    # ========================================================
    # NEWTON GRAPH
    # SAVE ONLY ONCE
    # ========================================================

    plt.figure(figsize=(8, 5))

    plt.plot(
        graph_x,
        actual_y,
        label="Actual Function"
    )

    plt.plot(
        graph_x,
        newton_y,
        "--",
        label="Newton Polynomial"
    )

    plt.scatter(
        x_data,
        y_data,
        label="Known Data"
    )

    plt.xlabel("x")
    plt.ylabel("f(x)")
    plt.title("Newton Interpolation - " + name)

    plt.legend()
    plt.grid(True)


    if name == "e^x":
        file_name = "graphs/ex_newton.png"

    elif name == "sin(x)":
        file_name = "graphs/sin_newton.png"

    else:
        file_name = "graphs/polynomial_newton.png"


    plt.savefig(
        file_name,
        dpi=300,
        bbox_inches="tight"
    )

    plt.close()


# ============================================================
# LAGRANGE RESULT TABLE
# ============================================================

print("\n" + "=" * 85)
print("LAGRANGE INTERPOLATION RESULTS")
print("=" * 85)

print(
    f"{'Function':<25}"
    f"{'Exact f(x)':<20}"
    f"{'Lagrange P(x)':<20}"
    f"{'Absolute Error':<20}"
)

print("-" * 85)

for name, exact, value, error in lagrange_results:

    print(
        f"{name:<25}"
        f"{exact:<20.10f}"
        f"{value:<20.10f}"
        f"{error:<20.5e}"
    )


# ============================================================
# NEWTON RESULT TABLE
# ============================================================

print("\n" + "=" * 85)
print("NEWTON INTERPOLATION RESULTS")
print("=" * 85)

print(
    f"{'Function':<25}"
    f"{'Exact f(x)':<20}"
    f"{'Newton P(x)':<20}"
    f"{'Absolute Error':<20}"
)

print("-" * 85)

for name, exact, value, error in newton_results:

    print(
        f"{name:<25}"
        f"{exact:<20.10f}"
        f"{value:<20.10f}"
        f"{error:<20.5e}"
    )


# ============================================================
# SAVE CSV
# ============================================================

with open("result.csv", "w", newline="") as file:

    writer = csv.writer(file)


    # Differentiation
    writer.writerow(["DIFFERENTIATION RESULTS"])

    writer.writerow([
        "Function",
        "x",
        "h",
        "Exact",
        "Forward",
        "F Error",
        "Backward",
        "B Error",
        "Central",
        "C Error",
        "Richardson",
        "R Error"
    ])

    writer.writerows(diff_results)


    writer.writerow([])
    writer.writerow([])


    # Lagrange
    writer.writerow([
        "LAGRANGE INTERPOLATION RESULTS"
    ])

    writer.writerow([
        "Function",
        "Exact f(x)",
        "Lagrange P(x)",
        "Absolute Error"
    ])

    writer.writerows(lagrange_results)


    writer.writerow([])
    writer.writerow([])


    # Newton
    writer.writerow([
        "NEWTON INTERPOLATION RESULTS"
    ])

    writer.writerow([
        "Function",
        "Exact f(x)",
        "Newton P(x)",
        "Absolute Error"
    ])

    writer.writerows(newton_results)


# ============================================================
# FINAL MESSAGE
# ============================================================

print("\n" + "=" * 60)
print("ALL RESULTS SAVED SUCCESSFULLY")
print("=" * 60)

print("CSV file : result.csv")
print("Graphs   : graphs/")
print("Total graphs : 9")