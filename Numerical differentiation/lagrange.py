from interpolation import Interpolation


class LagrangeInterpolation(Interpolation):

    def calculate(self, x):

        result = 0
        n = len(self.x_data)

        for i in range(n):

            term = self.y_data[i]

            for j in range(n):

                if i != j:
                    term = term * (
                        (x - self.x_data[j]) /
                        (self.x_data[i] - self.x_data[j])
                    )

            result = result + term

        return result