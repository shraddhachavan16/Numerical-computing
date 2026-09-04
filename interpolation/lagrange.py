# lagrange.py


class LagrangeInterpolation:

    # Constructor
    def __init__(self, x_values, y_values):
        self.x_values = x_values
        self.y_values = y_values
        self.n = len(x_values)

    # Calculate Lagrange basis polynomial
    def basis(self, i, x):

        result = 1.0

        for j in range(self.n):

            if i != j:
                result = result * (
                    (x - self.x_values[j])
                    / (self.x_values[i] - self.x_values[j])
                )

        return result

    # Calculate interpolated value
    def interpolate(self, x):

        result = 0.0

        for i in range(self.n):

            result = result + (
                self.y_values[i] * self.basis(i, x)
            )

        return result