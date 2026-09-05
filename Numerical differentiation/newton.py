from interpolation import Interpolation


class NewtonInterpolation(Interpolation):

    def calculate(self, x):

        n = len(self.x_data)

        table = []

        for i in range(n):
            table.append([self.y_data[i]])

        for j in range(1, n):

            for i in range(n - j):

                value = (
                    table[i + 1][j - 1]
                    - table[i][j - 1]
                ) / (
                    self.x_data[i + j]
                    - self.x_data[i]
                )

                table[i].append(value)

        result = table[0][0]
        product = 1

        for j in range(1, n):

            product = product * (x - self.x_data[j - 1])

            result = result + table[0][j] * product

        return result