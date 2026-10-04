from integration import Integration


class Simpson38Rule(Integration):

    def calculate(self, f):

        if self.n % 3 != 0:
            raise ValueError("Simpson 3/8 needs n divisible by 3.")

        h = (self.b - self.a) / self.n

        result = f(self.a) + f(self.b)

        for i in range(1, self.n):

            x = self.a + i * h

            if i % 3 == 0:
                result = result + 2 * f(x)
            else:
                result = result + 3 * f(x)

        return (3 * h / 8) * result