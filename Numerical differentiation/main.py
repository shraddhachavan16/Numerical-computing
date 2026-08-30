from differentiation import (
    ForwardDifference,
    BackwardDifference,
    CentralDifference,
    RichardsonExtrapolation
)

import math
import matplotlib.pyplot as plt
import os
x = 1.0
h_values = [
    10**-1,
    10**-2,
    10**-3,
    10**-4,
    10**-5,
    10**-6
]

def exponential(x):
    return math.exp(x)

def exponential_derivative(x):
    return math.exp(x)

def sine(x):
    return math.sin(x)

def sine_derivative(x):
    return math.cos(x)


def polynomial(x):
    return x**3 - 2*x + 1


def polynomial_derivative(x):
    return 3 * x**2 - 2

functions = [
    ("e^x", exponential, exponential_derivative),
    ("sin(x)", sine, sine_derivative),
    ("x^3 - 2x + 1", polynomial, polynomial_derivative)
]

os.makedirs("graphs", exist_ok=True)
all_errors = {}

for name, function, exact_derivative in functions:
    print("\n")
    print("=" * 125)
    print("Function:", name)
    print("Evaluation Point: x =", x)
    print("=" * 125)
    exact = exact_derivative(x)
    print(
        "Exact Derivative =",
        f"{exact:.10f}"
    )
    print()
    print(
        f"{'h':<10}"
        f"{'Forward':<15}"
        f"{'F Error':<15}"
        f"{'Backward':<15}"
        f"{'B Error':<15}"
        f"{'Central':<15}"
        f"{'C Error':<15}"
        f"{'Richardson':<15}"
        f"{'R Error':<15}"
    )

    print("-" * 125)
    forward_errors = []
    backward_errors = []
    central_errors = []
    richardson_errors = []

    for h in h_values:
        forward = ForwardDifference(x, h)
        backward = BackwardDifference(x, h)
        central = CentralDifference(x, h)
        richardson = RichardsonExtrapolation(x, h)


        forward_value = forward.calculate(function)
        backward_value = backward.calculate(function)
        central_value = central.calculate(function)
        richardson_value = richardson.calculate(function)


        forward_error = abs(exact - forward_value)
        backward_error = abs(exact - backward_value)
        central_error = abs(exact - central_value)
        richardson_error = abs(exact - richardson_value)


        forward_errors.append(forward_error)
        backward_errors.append(backward_error)
        central_errors.append(central_error)
        richardson_errors.append(richardson_error)


        print(
            f"{h:<10.0e}"
            f"{forward_value:<15.10f}"
            f"{forward_error:<15.5e}"
            f"{backward_value:<15.10f}"
            f"{backward_error:<15.5e}"
            f"{central_value:<15.10f}"
            f"{central_error:<15.5e}"
            f"{richardson_value:<15.10f}"
            f"{richardson_error:<15.5e}"
        )


    all_errors[name] = {
        "Forward": forward_errors,
        "Backward": backward_errors,
        "Central": central_errors,
        "Richardson": richardson_errors
    }


for name in all_errors:
    forward_errors = all_errors[name]["Forward"]
    backward_errors = all_errors[name]["Backward"]
    central_errors = all_errors[name]["Central"]
    richardson_errors = all_errors[name]["Richardson"]

    plt.figure(figsize=(9, 6))

    plt.loglog(
        h_values,
        forward_errors,
        marker='o',
        label='Forward Difference'
    )


    # Backward Difference
    plt.loglog(
        h_values,
        backward_errors,
        marker='s',
        label='Backward Difference'
    )


    # Central Difference
    plt.loglog(
        h_values,
        central_errors,
        marker='^',
        label='Central Difference'
    )


    # Richardson Extrapolation
    plt.loglog(
        h_values,
        richardson_errors,
        marker='D',
        label='Richardson Extrapolation'
    )


    # -------------------------------------------------
    # Graph Labels
    # -------------------------------------------------

    plt.xlabel("h")

    plt.ylabel("Absolute Error")

    plt.title(
        "Log-Log Error Plot - " + name
    )

    plt.legend()
    plt.grid(True)

    if name == "e^x":
        filename = "ex_error_plot.png"

    elif name == "sin(x)":
        filename = "sinx_error_plot.png"

    else:
        filename = "polynomial_error_plot.png"


    plt.savefig(
        "graphs/" + filename,
        dpi=300,
        bbox_inches="tight"
    )


    print()
    print("Graph saved:", "graphs/" + filename)

    plt.show()
    plt.close()