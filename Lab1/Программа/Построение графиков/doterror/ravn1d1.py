import matplotlib.pyplot as plt

# Чтение данных из файла
x1 = []
y1 = []
x2 = []
y2 = []
x3 = []
y3 = []

with open('cheb2d1.txt', 'r') as file:
    for line in file:
        x, y = map(float, line.split(':'))
        x1.append(x)
        y1.append(y)


with open('cheb2d2.txt', 'r') as file:
    for line in file:
        x, y = map(float, line.split(':'))
        x2.append(x)
        y2.append(y)
with open('cheb2d3.txt', 'r') as file:
    for line in file:
        x, y = map(float, line.split(':'))
        x3.append(x)
        y3.append(y)
        
# Построение графика с тонкой линией и выбором цвета
plt.plot(x1, y1, linewidth=1, color='green', label='x=-1.5')
plt.plot(x2, y2, linewidth=1, color='red', label='x=-3.5')
plt.plot(x3, y3, linewidth=1, color='blue', label='x=0')

plt.xlabel('x')
plt.ylabel('y')
plt.title('ошибка в точках')

# Установка логарифмической шкалы для оси ординат
plt.yscale('log')

plt.grid(True)
plt.legend(loc='upper right')  # Добавление легенды


plt.show()
