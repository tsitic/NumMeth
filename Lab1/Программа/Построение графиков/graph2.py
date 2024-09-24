import numpy as np
import matplotlib.pyplot as plt



def f(x):
    return (x**3-3*(x**2)+2*abs(x))


def poly(coeffs, set, dot):
    rez = 0
    for i in range(len(coeffs)):
        term = coeffs[i]
        for j in range(i):
            term *= (dot - set[j])
        rez += term
    return rez

file_path = r'dot.txt'
with open(file_path, 'r') as file:
    points = [float(line.strip()) for line in file]

coeffs_file_path = r'coeffs.txt'
with open(coeffs_file_path, 'r') as coeffs_file:
    coeffs = [float(line.strip()) for line in coeffs_file]

x = np.linspace(-4, 1, 10000)

y_f = f(x)
y_p = [poly(coeffs, points, dot) for dot in x]

plt.figure(figsize=(8, 6))

plt.plot(x, y_f, label=r'$f(x) = x \cdot \log(1 + x^2)$')

plt.plot(x, y_p, color='green', label='Функция poly')

plt.scatter(points, f(np.array(points)), color='red', label='Точки сетки')

plt.xlabel('x')
plt.ylabel('f(x)')
plt.title('Графики функций')
plt.grid(True)
plt.legend()
plt.show()
