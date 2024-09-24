import matplotlib.pyplot as plt

# Чтение данных из файла
x5 = []
y5 = []
x7 = []
y7 = []
x10 = []
y10 = []
with open('ravn2_5.txt', 'r') as file:
    for line in file:
        x, y = map(float, line.split(':'))
        x5.append(x)
        y5.append(y)

with open('ravn2_7.txt', 'r') as file:
    for line in file:
        x, y = map(float, line.split(':'))
        x7.append(x)
        y7.append(y)

with open('ravn2_10.txt', 'r') as file:
    for line in file:
        x, y = map(float, line.split(':'))
        x10.append(x)
        y10.append(y)
        
# Построение графика с еще более тонкой линией и выбором цвета
plt.plot(x5, y5, linewidth=1, color='green', label='5 узлов')
plt.plot(x7, y7, linewidth=1, color='red', label='7 узлов')
plt.plot(x10, y10, linewidth=1, color='blue', label='10 узлов')


plt.xlabel('x')
plt.ylabel('y')
plt.title('поточечная ошибка на функции(2) на равномерной сетки')

plt.grid(True)
plt.legend(loc='upper right')  # Добавление легенды
plt.show()

