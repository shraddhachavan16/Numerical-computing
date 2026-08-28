from differentiation import (
    ForwardDifference,
    BackwardDifference,
    CentralDifference
)

import math
import matplotlib.pyplot as plt


# =====================================================
# Evaluation point
# =====================================================

x = 1.0


# =====================================================
# Values of h
# h = 10^-1, 10^-2, ..., 10^-6
# =====================================================

h_values = [
    10**-1,
    10**-2,
    10**-3,
    10**-4,
    10**-5,
    10**-6
]


# =====================================================
# Test Functions
# =====================================================

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
    return 3*x**2 - 2


# =====================================================
# Store all functions
# =====================================================

functions = [
    ("e^x", exponential, exponential_derivative),
    ("sin(x)", sine, sine_derivative),
    ("x^3 - 2x + 1", polynomial, polynomial_derivative)
]


# =====================================================
# Store errors for plotting
# =====================================================

all_errors = {}


# =====================================================
# Calculate results
# =====================================================

for name, function, exact_derivative in functions:

    print("\n")
    print("=" * 85)
    print("Function:", name)
    print("Evaluation point: x =", x)
    print("=" * 85)

    print(
        f"{'h':<12}"
        f"{'Forward Error':<20}"
        f"{'Backward Error':<20}"
        f"{'Central Error':<20}"
    )

    print("-" * 72)

    # Exact derivative at x = 1
    exact = exact_derivative(x)

    forward_errors = []
    backward_errors = []
    central_errors = []

    # Calculate for each h
    for h in h_values:

        # Create objects
        forward = ForwardDifference(x, h)
        backward = BackwardDifference(x, h)
        central = CentralDifference(x, h)

        # Numerical derivatives
        forward_result = forward.calculate(function)
        backward_result = backward.calculate(function)
        central_result = central.calculate(function)

        # Absolute errors
        forward_error = abs(exact - forward_result)
        backward_error = abs(exact - backward_result)
        central_error = abs(exact - central_result)

        # Store errors
        forward_errors.append(forward_error)
        backward_errors.append(backward_error)
        central_errors.append(central_error)

        # Display table
        print(
            f"{h:<12.0e}"
            f"{forward_error:<20.10e}"
            f"{backward_error:<20.10e}"
            f"{central_error:<20.10e}"
        )

    # Store errors
    all_errors[name] = (
        forward_errors,
        backward_errors,
        central_errors
    )


# =====================================================
# Log-Log Error Plots
# =====================================================

for name in all_errors:

    forward_errors = all_errors[name][0]
    backward_errors = all_errors[name][1]
    central_errors = all_errors[name][2]

    plt.figure(figsize=(8, 6))

    plt.loglog(
        h_values,
        forward_errors,
        marker='o',
        label='Forward Difference'
    )

    plt.loglog(
        h_values,
        backward_errors,
        marker='s',
        label='Backward Difference'
    )

    plt.loglog(
        h_values,
        central_errors,
        marker='^',
        label='Central Difference'
    )

    plt.xlabel("h")
    plt.ylabel("Absolute Error")

    plt.title("Log-Log Error Plot - " + name)

    plt.legend()

    plt.grid(True)

    plt.show()