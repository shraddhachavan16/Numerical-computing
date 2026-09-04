# main.py

from lagrange import LagrangeInterpolation


# =====================================================
# Question 1
# =====================================================

x1 = [0, 1, 2]
y1 = [1, 3, 7]

lagrange1 = LagrangeInterpolation(x1, y1)

result1 = lagrange1.interpolate(1.5)

print("========================================")
print("Question 1")
print("========================================")

print("Data:")
print("x  =", x1)
print("f(x) =", y1)

print("\nf(1.5) =", result1)


# =====================================================
# Question 2
# =====================================================

x2 = [1, 2, 3, 4]
y2 = [2.0, 4.5, 8.0, 13.5]

lagrange2 = LagrangeInterpolation(x2, y2)

result2_1 = lagrange2.interpolate(2.5)
result2_2 = lagrange2.interpolate(3.5)

print("\n========================================")
print("Question 2")
print("========================================")

print("Data:")
print("x  =", x2)
print("f(x) =", y2)

print("\nf(2.5) =", result2_1)
print("f(3.5) =", result2_2)


# =====================================================
# Question 3
# =====================================================

x3 = [0, 0.5, 1.5, 3]
y3 = [1.000, 1.125, 1.875, 4.000]

lagrange3 = LagrangeInterpolation(x3, y3)

result3_1 = lagrange3.interpolate(1)
result3_2 = lagrange3.interpolate(2)

print("\n========================================")
print("Question 3")
print("========================================")

print("Data:")
print("x  =", x3)
print("f(x) =", y3)

print("\nf(1) =", result3_1)
print("f(2) =", result3_2)


# =====================================================
# Question 4
# =====================================================

x4 = [2, 3, 5, 7]
y4 = [5, 10, 26, 50]

lagrange4 = LagrangeInterpolation(x4, y4)

result4_1 = lagrange4.interpolate(4)
result4_2 = lagrange4.interpolate(6)
result4_3 = lagrange4.interpolate(8)

print("\n========================================")
print("Question 4")
print("========================================")

print("Data:")
print("x  =", x4)
print("f(x) =", y4)

print("\nf(4) =", result4_1)
print("f(6) =", result4_2)
print("f(8) =", result4_3)