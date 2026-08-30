class Differentiation:
    def __init__(self, x, h):
        self.x = x
        self.h = h

class ForwardDifference(Differentiation):
    def calculate(self, function):
        return (
            function(self.x + self.h)
            - function(self.x)
        ) / self.h

class BackwardDifference(Differentiation):
    def calculate(self, function):
        return (
            function(self.x)
            - function(self.x - self.h)
        ) / self.h

class CentralDifference(Differentiation):
    def calculate(self, function):
        return (
            function(self.x + self.h)
            - function(self.x - self.h)
        ) / (2 * self.h)

class RichardsonExtrapolation(Differentiation):
    def calculate(self, function):
        D_h = (
            function(self.x + self.h)
            - function(self.x - self.h)
        ) / (2 * self.h)

        h_half = self.h / 2
        D_half_h = (
            function(self.x + h_half)
            - function(self.x - h_half)
        ) / (2 * h_half)
        return (4 * D_half_h - D_h) / 3