
import math
from matrix import Matrix


class PowerMethod(Matrix):

    def __init__(self, A):
        n = A.rows
        square_data = [row[:n] for row in A.data]

        super().__init__(data=square_data)

    def calculate(self):

        if not self.is_square():
            raise ValueError("Matrix must be square.")

        A = self.data
        n = self.rows

        # Initial vector
        x = [1.0] * n

        tolerance = 1e-8
        old_value = None
        history = []

        # Power Method iterations
        for iteration in range(1, 1001):

            # Step 1: Multiply matrix by vector
            y = [
                sum(A[i][j] * x[j] for j in range(n))
                for i in range(n)
            ]

            # Step 2: Calculate vector length
            norm = math.sqrt(sum(v * v for v in y))

            if norm < 1e-15:
                raise ValueError("Zero vector obtained.")

            # Step 3: Normalize vector
            x_new = [v / norm for v in y]

            # Step 4: Calculate A*x
            Ax = [
                sum(A[i][j] * x_new[j] for j in range(n))
                for i in range(n)
            ]

            # Step 5: Calculate eigenvalue
            denominator = sum(v * v for v in x_new)

            eigenvalue = (
                sum(x_new[i] * Ax[i] for i in range(n))
                / denominator
            )

            # Step 6: Calculate error
            error = (
                None if old_value is None
                else abs(eigenvalue - old_value)
            )

            # Step 7: Calculate residual
            residual = math.sqrt(
                sum(
                    (Ax[i] - eigenvalue * x_new[i]) ** 2
                    for i in range(n)
                )
            )

            # Store iteration results
            history.append(
                (iteration, eigenvalue, error, residual)
            )

            # Step 8: Check convergence
            if (
                error is not None
                and error < tolerance
                and residual < tolerance * max(1.0, abs(eigenvalue))
            ):
                return eigenvalue, x_new, history, True

            # Prepare for next iteration
            x = x_new
            old_value = eigenvalue

        return eigenvalue, x_new, history, False
