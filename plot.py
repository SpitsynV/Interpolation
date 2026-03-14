import matplotlib.pyplot as plt
import numpy as np

# Загружаем данные (пропускаем строки, начинающиеся с #)
data = np.loadtxt('plot_data.txt', comments='#')
x = data[:, 0]
exact = data[:, 1]
approx = data[:, 2]

plt.figure(figsize=(10, 6))
plt.plot(x, exact, 'b-', label='Exact function', linewidth=2)
plt.plot(x, approx, 'r--', label='Chebyshev approximation', linewidth=2)
plt.xlabel('x')
plt.ylabel('f(x)')
plt.title(f'Approximation with n nodes')
plt.legend()
plt.grid(True)
plt.show()