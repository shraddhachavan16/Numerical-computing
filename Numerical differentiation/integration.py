# Base class for all integration methods

class Integration:

    def __init__(self, a, b, n):
        self.a = a
        self.b = b
        self.n = n


# Trapezoidal Rule
class TrapezoidalRule(Integration):

    def calculate(self, f):

        h = (self.b - self.a) / self.n

        result = f(self.a) + f(self.b)

        for i in range(1, self.n):
            x = self.a + i * h
            result = result + 2 * f(x)

        return (h / 2) * result


# Simpson's 1/3 Rule
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


# Simpson's 3/8 Rule
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
