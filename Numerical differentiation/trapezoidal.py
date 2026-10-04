from integration import Integration


class TrapezoidalRule(Integration):

    def calculate(self, f):
        h = (self.b - self.a) / self.n
        result = f(self.a) + f(self.b)

        for i in range(1, self.n):
            x = self.a + i * h
            result = result + 2 * f(x)

        return (h / 2) * result