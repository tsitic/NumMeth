import matplotlib.pyplot as plt

# Чтение данных из файла
x_values = []
y_values = []

with open('cheb1.txt', 'r') as file:
    for line in file:
        x, y = map(float, line.split(':'))
        x_values.append(x)
        y_values.append(y)

# Построение графика с тонкой линией и выбором цвета
plt.plot(x_values, y_values, linewidth=1, color='green')

plt.xlabel('x')
plt.ylabel('y')
plt.title('Норма ошибки (1) функции')

# Установка логарифмической шкалы для оси ординат
plt.yscale('log')

plt.grid(True)
plt.legend(['Норма ошибки'])  # Добавление легенды
plt.show()

