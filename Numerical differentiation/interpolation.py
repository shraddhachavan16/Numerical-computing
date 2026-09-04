class Interpolation:

    def __init__(self, x, y):
        self.x = x
        self.y = y


class LagrangeInterpolation(Interpolation):

    def calculate(self, value):

        result = 0
        n = len(self.x)

        for i in range(n):

            term = self.y[i]

            for j in range(n):

                if i != j:
                    term = term * (
                        (value - self.x[j])
                        / (self.x[i] - self.x[j])
                    )

            result = result + term

        return result