import matplotlib.pyplot as plt

# Чтение данных из файла
data = []
with open('data.txt', 'r') as file:
    for line in file:
        parts = line.split()
        e, x1, e1, x2, e2 = map(float, parts)
        data.append((e, x1, x2))

e_values = [row[0] for row in data]
e1_values = [row[1] for row in data]
e2_values = [row[2] for row in data]

plt.figure(figsize=(10, 6))
plt.plot(e_values, e1_values, label="Хойна")
plt.plot(e_values, e2_values, label="Адамса-Моултона")

plt.xscale('log', base=10)
plt.xlabel("Зданая точность")
plt.ylabel("координата")
plt.title("Зависимость координаты ошибки от точности")
plt.legend()
plt.grid(True)

plt.show()

