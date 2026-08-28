from abc import ABC, abstractmethod


# Base class for numerical differentiation
class Differentiation(ABC):

    def __init__(self, x, h):
        self.x = x
        self.h = h

    @abstractmethod
    def calculate(self, function):
        pass


# Forward Difference
class ForwardDifference(Differentiation):

    def __init__(self, x, h):
        super().__init__(x, h)

    def calculate(self, function):
        return (
            function(self.x + self.h) - function(self.x)
        ) / self.h


# Backward Difference
class BackwardDifference(Differentiation):

    def __init__(self, x, h):
        super().__init__(x, h)

    def calculate(self, function):
        return (
            function(self.x) - function(self.x - self.h)
        ) / self.h


# Central Difference
class CentralDifference(Differentiation):

    def __init__(self, x, h):
        super().__init__(x, h)

    def calculate(self, function):
        return (
            function(self.x + self.h)
            - function(self.x - self.h)
        ) / (2 * self.h)