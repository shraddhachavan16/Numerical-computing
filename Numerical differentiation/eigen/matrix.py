
class Matrix:

    def __init__(self, data=None):
        self.data = data if data is not None else []
        self.rows = len(self.data)
        self.cols = len(self.data[0]) if self.data else 0

    def read_from_file(self, filename):
        with open(filename, "r") as file:
            lines = [line.strip() for line in file if line.strip()]

        rows, cols = map(int, lines[0].split())

        values = []
        for line in lines[1:]:
            values.extend(map(float, line.split()))

        if len(values) != rows * cols:
            raise ValueError("Incorrect matrix dimensions.")

        self.data = [
            values[i * cols:(i + 1) * cols]
            for i in range(rows)
        ]

        self.rows = rows
        self.cols = cols

    def is_square(self):
        return self.rows == self.cols

    def get_coefficient_matrix(self):
        return Matrix(
            data=[row[:self.rows] for row in self.data]
        )
