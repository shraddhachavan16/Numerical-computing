
from matrix import Matrix
from power_method import PowerMethod

# Read matrix
M = Matrix()
M.read_from_file("input.txt")

print("Input matrix size:", M.rows, "x", M.cols)

# Get square coefficient matrix
A = M.get_coefficient_matrix()

# Run Power Method
power = PowerMethod(A)
eigenvalue, eigenvector, history, converged = power.calculate()

# Print iteration table
print("\nIteration Table")
print("-" * 85)

print(
    f"{'Iteration':<12}"
    f"{'Eigenvalue':<20}"
    f"{'Absolute Value':<20}"
    f"{'Error':<16}"
    f"{'Residual':<16}"
)

print("-" * 85)

for iteration, value, error, residual in history:
    error_text = "N/A" if error is None else f"{error:.4e}"

    print(
        f"{iteration:<12}"
        f"{value:<20.10f}"
        f"{abs(value):<20.10f}"
        f"{error_text:<16}"
        f"{residual:.4e}"
    )

print("-" * 85)

# Print final results
print("\nFinal Results")
print(f"Eigenvalue (lambda): {eigenvalue:.10f}")
print(f"Absolute Eigenvalue: {abs(eigenvalue):.10f}")
print("Iterations:", len(history))
print("Converged:", "Yes" if converged else "No")
print(f"Final residual: {history[-1][3]:.4e}")

# Print eigenvector
print("\nEigenvector:")
for i, value in enumerate(eigenvector, start=1):
    print(f"x{i} = {value:.10f}")
