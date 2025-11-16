import numpy as np
import matplotlib.pyplot as plt

# общее время полета
t_total = 60
# шаг интегрирования, мин     
dt = 0.1
t = np.arange(0, t_total, dt)

# воздушная скорость (м/с)
V = 100 
# скорость ветра (м/с)
W = 25 
# угол сноса, из градусов в радианы  
US = np.deg2rad(10)    
# угол ветра, 
UV = np.deg2rad(45)   

# Путевая скорость (истинная)
Vp_true = V * np.cos(US) + W * np.cos(UV)

# Модель полета по формуле Эйлера
y_true = np.zeros_like(t)
for i in range(1, len(t)):
    y_true[i] = y_true[i-1] + Vp_true * dt

# Модель полета с ошибкой 2%
error_rate = 0.02  
y_error = np.zeros_like(t)
for i in range(1, len(t)):
    y_error[i] = y_error[i-1] + Vp_true * (1 + error_rate) * dt

# Модель полета с комплексированием (коррекцией)
# время видимости спутника, мин
tau = 1
# спутник появляется каждые 20 мин
sat_period = 20 
# из условия "потребуем, чтобы запомненная ошибка составляла не менее 95%"
correction_fraction = 0.95

y_corrected = y_error.copy()
k = 0;
for i in range(len(t)):
    # Проверяем, пришло ли время спутниковой коррекции
    if int(t[i]) % sat_period == 0 and t[i] != 0:
        error_current = y_true[i] - y_corrected[i] # текущая ошибка
        q = correction_fraction * error_current # желаемая величина коррекции
        # вычисляем k 
        k = -np.log(1 - q / error_current) / tau
        # Корректируем последующие значения
        y_corrected[i:] += q

# Вычисление ошибок
error_no_correction = y_error - y_true
error_corrected = y_corrected - y_true

# график
plt.figure(figsize=(10,6))
plt.plot(t, y_true, label='Истинный путь', linewidth=2)
plt.plot(t, y_error, '--', label='Без комплексирования')
plt.plot(t, y_corrected, label='С комплексированием')
plt.xlabel('Время, мин')
plt.ylabel('Пройденный путь')
plt.title('Моделирование пути БЛА и влияние коррекции')
plt.legend()
plt.grid(True)
plt.show()

# график ошибок
plt.figure(figsize=(10,6))
plt.plot(t, error_no_correction, '--', label='Ошибка без коррекции', color='orange')
plt.plot(t, error_corrected, label='Ошибка с коррекцией', color='green')
plt.xlabel('Время, мин')
plt.ylabel('Ошибка (условные ед.)')
plt.title('Накопление и коррекция ошибки навигации')
plt.legend()
plt.grid(True)
plt.show()

print(f"Параметр комплексирования k = {k:.3f}")
print(f"За время tau = {tau} мин запоминается {100*(1 - np.exp(-k*tau)):.1f}% ошибки")
