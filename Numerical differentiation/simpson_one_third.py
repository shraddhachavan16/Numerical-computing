from integration import Integration


class Simpson13Rule(Integration):

    def calculate(self, f):

        if self.n % 2 != 0:
            raise ValueError("Simpson 1/3 needs even n.")

        h = (self.b - self.a) / self.n

        result = f(self.a) + f(self.b)

        for i in range(1, self.n):

            x = self.a + i * h

            if i % 2 == 0:
                result = result + 2 * f(x)
            else:
                result = result + 4 * f(x)

        return (h / 3) * result