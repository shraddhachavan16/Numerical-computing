import math
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
from integration import (
    TrapezoidalRule,
    Simpson13Rule,
    Simpson38Rule
)


# ============================================================
# FUNCTIONS
# ============================================================

functions = [
    ("e^x", math.exp, math.exp),
    ("sin(x)", math.sin, math.cos),
    (
        "x^3 - 2x + 1",
        lambda x: x**3 - 2*x + 1,
        lambda x: 3*x**2 - 2
    )
]

# Create graphs folder
os.makedirs("graphs", exist_ok=True)


# ============================================================
# CHOOSE FUNCTION
# ============================================================

def choose_function():

    print("\nChoose function:")
    print("1. e^x")
    print("2. sin(x)")
    print("3. x^3 - 2x + 1")

    choice = int(input("Enter function choice: "))

    if choice < 1 or choice > 3:
        print("Invalid function choice.")
        return None

    return functions[choice - 1]


# ============================================================
# NUMERICAL DIFFERENTIATION
# ============================================================

def differentiation():

    print("\n" + "=" * 70)
    print("NUMERICAL DIFFERENTIATION")
    print("=" * 70)

    x = float(input("Enter x value: "))

    selected = choose_function()

    if selected is None:
        return

    name, f, df = selected

    h_values = [
        0.1,
        0.01,
        0.001,
        0.0001,
        0.00001,
        0.000001
    ]

    exact = df(x)

    print("\nFunction:", name)
    print("Exact Derivative:", f"{exact:.10f}")

    print("\n" + "-" * 120)

    print(
        f"{'h':<12}"
        f"{'Forward':<18}{'F Error':<16}"
        f"{'Backward':<18}{'B Error':<16}"
        f"{'Central':<18}{'C Error':<16}"
        f"{'Richardson':<18}{'R Error':<16}"
    )

    print("-" * 120)

    forward_errors = []
    backward_errors = []
    central_errors = []
    richardson_errors = []

    for h in h_values:

        forward = ForwardDifference(x, h).calculate(f)
        backward = BackwardDifference(x, h).calculate(f)
        central = CentralDifference(x, h).calculate(f)
        richardson = RichardsonExtrapolation(x, h).calculate(f)

        f_error = abs(exact - forward)
        b_error = abs(exact - backward)
        c_error = abs(exact - central)
        r_error = abs(exact - richardson)

        forward_errors.append(f_error)
        backward_errors.append(b_error)
        central_errors.append(c_error)
        richardson_errors.append(r_error)

        print(
            f"{h:<12.0e}"
            f"{forward:<18.10f}{f_error:<16.5e}"
            f"{backward:<18.10f}{b_error:<16.5e}"
            f"{central:<18.10f}{c_error:<16.5e}"
            f"{richardson:<18.10f}{r_error:<16.5e}"
        )

    # ========================================================
    # DIFFERENTIATION GRAPH
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

    filename = {
        "e^x": "graphs/ex_differentiation.png",
        "sin(x)": "graphs/sin_differentiation.png"
    }.get(
        name,
        "graphs/polynomial_differentiation.png"
    )

    # Save graph
    plt.savefig(
        filename,
        dpi=300,
        bbox_inches="tight"
    )

    print("\nGraph saved:", filename)

    # Show graph
    plt.show()

    plt.close()


# ============================================================
# LAGRANGE INTERPOLATION
# ============================================================

def lagrange_interpolation():

    print("\n" + "=" * 70)
    print("LAGRANGE INTERPOLATION")
    print("=" * 70)

    x = float(input("Enter x value: "))

    data = input(
        "Enter known x values separated by comma: "
    )

    x_data = [
        float(v.strip())
        for v in data.split(",")
    ]

    if len(x_data) < 2:
        print("Enter at least 2 x values.")
        return

    if len(x_data) != len(set(x_data)):
        print("x values must be different.")
        return

    selected = choose_function()

    if selected is None:
        return

    name, f, df = selected

    y_data = [
        f(value)
        for value in x_data
    ]

    method = LagrangeInterpolation(
        x_data,
        y_data
    )

    result = method.calculate(x)

    exact = f(x)

    error = abs(exact - result)

    print("\n" + "-" * 75)

    print(
        f"{'Function':<25}"
        f"{'Exact':<18}"
        f"{'Lagrange':<18}"
        f"{'Error':<15}"
    )

    print("-" * 75)

    print(
        f"{name:<25}"
        f"{exact:<18.10f}"
        f"{result:<18.10f}"
        f"{error:<15.5e}"
    )


# ============================================================
# NEWTON INTERPOLATION
# ============================================================

def newton_interpolation():

    print("\n" + "=" * 70)
    print("NEWTON INTERPOLATION")
    print("=" * 70)

    x = float(input("Enter x value: "))

    data = input(
        "Enter known x values separated by comma: "
    )

    x_data = [
        float(v.strip())
        for v in data.split(",")
    ]

    if len(x_data) < 2:
        print("Enter at least 2 x values.")
        return

    if len(x_data) != len(set(x_data)):
        print("x values must be different.")
        return

    selected = choose_function()

    if selected is None:
        return

    name, f, df = selected

    y_data = [
        f(value)
        for value in x_data
    ]

    method = NewtonInterpolation(
        x_data,
        y_data
    )

    result = method.calculate(x)

    exact = f(x)

    error = abs(exact - result)

    print("\n" + "-" * 75)

    print(
        f"{'Function':<25}"
        f"{'Exact':<18}"
        f"{'Newton':<18}"
        f"{'Error':<15}"
    )

    print("-" * 75)

    print(
        f"{name:<25}"
        f"{exact:<18.10f}"
        f"{result:<18.10f}"
        f"{error:<15.5e}"
    )

# ============================================================
# NUMERICAL INTEGRATION
# ============================================================

def get_exact_integral(name, a, b):

    if name == "e^x":
        return math.exp(b) - math.exp(a)

    elif name == "sin(x)":
        return -math.cos(b) + math.cos(a)

    else:
        # Integral of x^3 - 2x + 1
        # = x^4/4 - x^2 + x
        return (
            (b**4 / 4 - b**2 + b)
            - (a**4 / 4 - a**2 + a)
        )


def numerical_integration():

    print("\n" + "=" * 70)
    print("                 NUMERICAL INTEGRATION")
    print("=" * 70)

    selected = choose_function()

    if selected is None:
        return

    name, f, df = selected

    a = float(input("Enter lower limit: "))
    b = float(input("Enter upper limit: "))

    if a == b:
        print("Lower and upper limits must be different.")
        return


    print()
    data = input("Enter n values: ")

    try:
        n_values = [int(v.strip()) for v in data.split(",")]
    except ValueError:
        print("\nInvalid input. Example: 2,4,6,8,12")
        return

    if len(n_values) == 0 or any(n <= 0 for n in n_values):
        print("\nAll n values must be positive.")
        return

    # Remove duplicate n values
    n_values = list(dict.fromkeys(n_values))

    exact = get_exact_integral(name, a, b)

    # Store results for graph
    graph_h_trap = []
    graph_h_13 = []
    graph_h_38 = []

    trap_errors = []
    simpson13_errors = []
    simpson38_errors = []

    rows = []

    for n in n_values:

        h = (b - a) / n

        # --------------------------------------------------------
        # Trapezoidal Rule
        # Always valid for positive n
        # --------------------------------------------------------
        trap_result = TrapezoidalRule(a, b, n).calculate(f)
        trap_error = abs(exact - trap_result)

        # --------------------------------------------------------
        # Simpson 1/3 Rule
        # Valid only when n is even
        # --------------------------------------------------------
        if n % 2 == 0:
            s13_result = Simpson13Rule(a, b, n).calculate(f)
            s13_error = abs(exact - s13_result)
        else:
            s13_result = None
            s13_error = None

        # --------------------------------------------------------
        # Simpson 3/8 Rule
        # Valid only when n is divisible by 3
        # --------------------------------------------------------
        if n % 3 == 0:
            s38_result = Simpson38Rule(a, b, n).calculate(f)
            s38_error = abs(exact - s38_result)
        else:
            s38_result = None
            s38_error = None

        rows.append((
            n, h,
            trap_result, s13_result, s38_result,
            trap_error, s13_error, s38_error
        ))

        # Graph data
        if trap_error > 0:
            graph_h_trap.append(h)
            trap_errors.append(trap_error)

        if s13_error is not None and s13_error > 0:
            graph_h_13.append(h)
            simpson13_errors.append(s13_error)

        if s38_error is not None and s38_error > 0:
            graph_h_38.append(h)
            simpson38_errors.append(s38_error)

    # ============================================================
    # EXACT VALUE
    # ============================================================

    print("\n" + "=" * 70)
    print(f"Function: {name}")
    print(f"Limits: {a:g} to {b:g}")
    print(f"Exact Integral = {exact:.10f}")
    print("=" * 70)

    # ============================================================
    # RESULT COMPARISON TABLE
    # ============================================================

    print("\n" + "=" * 70)
    print("                    RESULT COMPARISON")
    print("=" * 70)

    print(
        f"{'n':>4} "
        f"{'h':>12} "
        f"{'Trapezoidal':>16} "
        f"{'Simpson 1/3':>16} "
        f"{'Simpson 3/8':>16}"
    )

    print("-" * 70)

    for row in rows:

        n, h, trap, s13, s38, _, _, _ = row

        trap_text = f"{trap:.10f}"
        s13_text = f"{s13:.10f}" if s13 is not None else "--"
        s38_text = f"{s38:.10f}" if s38 is not None else "--"

        print(
            f"{n:>4} "
            f"{h:>12.6f} "
            f"{trap_text:>16} "
            f"{s13_text:>16} "
            f"{s38_text:>16}"
        )

    # ============================================================
    # ERROR TABLE
    # ============================================================

    print("\n" + "=" * 70)
    print("                     ABSOLUTE ERROR")
    print("=" * 70)

    print(
        f"{'n':>4} "
        f"{'Trapezoidal':>18} "
        f"{'Simpson 1/3':>18} "
        f"{'Simpson 3/8':>18}"
    )

    print("-" * 70)

    for row in rows:

        n, _, _, _, _, trap_error, s13_error, s38_error = row

        trap_text = f"{trap_error:.6f}"
        s13_text = f"{s13_error:.6f}" if s13_error is not None else "--"
        s38_text = f"{s38_error:.6f}" if s38_error is not None else "--"

        print(
            f"{n:>4} "
            f"{trap_text:>18} "
            f"{s13_text:>18} "
            f"{s38_text:>18}"
        )

    print("=" * 70)

    # ============================================================
    # LOG-LOG ERROR GRAPH
    # ============================================================

    plt.figure(figsize=(9, 6))

    if graph_h_trap:
        plt.loglog(
            graph_h_trap,
            trap_errors,
            "o-",
            label="Trapezoidal"
        )

    if graph_h_13:
        plt.loglog(
            graph_h_13,
            simpson13_errors,
            "s-",
            label="Simpson 1/3"
        )

    if graph_h_38:
        plt.loglog(
            graph_h_38,
            simpson38_errors,
            "^-",
            label="Simpson 3/8"
        )

    plt.xlabel("Step size (h)")
    plt.ylabel("Absolute Error")
    plt.title(f"Integration Error Comparison - {name}")
    plt.grid(True, which="both")
    plt.legend()
    plt.tight_layout()

    os.makedirs("graphs", exist_ok=True)

    filename = name.replace("^", "").replace("(", "").replace(")", "")
    filename = filename.replace(" ", "_")

    graph_path = f"graphs/{filename}_integration_error.png"
    plt.savefig(graph_path)
    plt.close()

    print(f"\nLog-log error graph saved: {graph_path}")

# ============================================================
# MAIN MENU
# ============================================================

while True:

    print("\n" + "=" * 60)
    print("              NUMERICAL COMPUTING")
    print("=" * 60)

    print("1. Numerical Differentiation")
    print("2. Lagrange Interpolation")
    print("3. Newton Interpolation")
    print("4. Numerical Integration")
    print("5. Exit")

    print("=" * 60)

    choice = input("Enter your choice: ")

    if choice == "1":

        differentiation()

    elif choice == "2":

        lagrange_interpolation()

    elif choice == "3":

        newton_interpolation()

    elif choice == "4":

        numerical_integration()

    elif choice == "5":

        print("\nProgram finished.")
        break

    else:

        print("\nInvalid choice. Please enter 1 to 5.")
