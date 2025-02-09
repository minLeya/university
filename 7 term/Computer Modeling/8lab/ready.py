import numpy as np
import matplotlib.pyplot as plt

# Функции принадлежности
# Трапеция
def trapmf(x, a, b, c, d):
    # Условие x < a
    condition1 = np.where(x < a, 0, 1)

    # Условие a <= x <= b
    condition2 = np.where((a <= x) & (x <= b), (x - a) / (b - a), 0)

    # Условие b <= x <= c
    condition3 = np.where((b <= x) & (x <= c), 1, 0)

    # Условие c <= x <= d
    condition4 = np.where((c <= x) & (x <= d), (d - x) / (d - c), 0)

    # Условие x > d
    condition5 = np.where(x > d, 0, 1)

    # Объединяем условия
    result = condition1 + condition2 + condition3 + condition4 + condition5
    return result

# Треугольник

def trimf(x, a, b, c):
    # Условие x < a
    condition1 = np.where(x < a, 0, 0)

    # Условие a <= x <= b
    condition2 = np.where((a <= x) & (x <= b), (x - a) / (b - a), 0)

    # Условие b < x <= c
    condition3 = np.where((b < x) & (x <= c), (c - x) / (c - b), 0)

    # Условие x > c
    condition4 = np.where(x > c, 0, 0)

    # Объединяем условия
    result = condition1 + condition2 + condition3 + condition4

    return result


def linemf(x, a, b):
    # Условие x < a
    condition1 = np.where(x < a, 1, 0)

    # Условие a <= x <= b
    condition2 = np.where((a <= x) & (x <= b), (b - x) / (b - a), 0)

    # Объединяем условия
    result = condition1 + condition2

    return result


def traplineStart(x, a, b, c):
    # Условие x < a
    condition1 = np.where(x < a, 0, 0)

    # Условие a <= x <= b
    condition2 = np.where((a <= x) & (x <= b), 1, 0)

    # Условие b < x <= c
    condition3 = np.where((b < x) & (x <= c), (c - x) / (c - b), 0)

    # Условие c < x <= d
    # x > c
    #condition4 = np.where((c < x) & (x <= d), 0, 0)
    condition4 = np.where(x > c, 0, 0)

    # Условие x > d
    # condition5 = np.where(x > d, 0, 0)

    # Объединяем условия
    result = condition1 + condition2 + condition3 + condition4

    return result


def traplineEnd(x, a, b, c):
    # Условие x < a
    condition1 = np.where(x < a, 0, 0)

    # Условие a <= x <= b
    condition2 = np.where((a <= x) & (x <= b), (x - a) / (b - a), 0)

    # Условие b < x <= c
    condition3 = np.where((b < x) & (x <= c), 1, 0)

    # Условие x > c
    condition4 = np.where(x > c, 0, 0)

    # Объединяем условия
    result = condition1 + condition2 + condition3 + condition4

    return result


# Функция для численного интегрирования методом прямоугольников
# func - функция, которую нужно интегрировать.
# a - нижний предел интегрирования.
# b - верхний предел интегрирования.
# num_rectangles - количество прямоугольников для численного интегрирования 
def integrate(func, a, b, num_rectangles=1000):
    # ширина каждого прямоугольника
    width = (b - a) / num_rectangles
    # Сумма высот прямоугольников 
    total_sum = 0
    for i in range(num_rectangles):
        y = a + i * width
        # вычисляет значение y для текущего прямоугольника
        # y - это левая граница текущего прямоугольника.
        total_sum += func(y)
    # Возвращаем площадь
    return total_sum * width

# Функция дефаззификации по методу центра тяжести
# membership_function - функция принадлежности, которую нужно дефаззифицировать.
# min_val - нижний предел интегрирования.
# max_val - верхний предел интегрирования.
# num_rectangles - количество прямоугольников для численного интегрирования 
def defuzzify(membership_function, min_val, max_val, num_rectangles=1000):
    # функция, которая возвращает произведение текущего значения y на степень принадлежности,
    # заданную функцией membership_function(y).
    numerator = integrate(lambda y: y * membership_function(y), min_val, max_val, num_rectangles)
    
    # суммf всех степеней принадлежности по интервалу.
    denominator = integrate(membership_function, min_val, max_val, num_rectangles)

    if denominator == 0:
        raise ValueError("Знаменатель равен нулю, проверьте функцию принадлежности и интервал интегрирования.")
    y_star = numerator / denominator
    return y_star

temp_diff_universe = np.arange(0, 35, 1)
temp_change_speed_universe = np.arange(0, 0.35, 0.01)
compressor_speed_universe = np.arange(0, 150, 1)

# Определяем границы функций принадлежности
# График разности температур
temp_diff_low = linemf(temp_diff_universe, 0, 15)
temp_diff_medium = trimf(temp_diff_universe, 0, 15, 30)
temp_diff_high = traplineEnd(temp_diff_universe, 15, 30, 35)

# График скорости изменения температуры
temp_change_low = linemf(temp_change_speed_universe, 0, 0.15)
temp_change_medium = trimf(temp_change_speed_universe, 0, 0.15, 0.3)
temp_change_high = traplineEnd(temp_change_speed_universe, 0.15, 0.3, 0.35)

# График частоты вращения компрессора
comp_speed_very_low = traplineStart(compressor_speed_universe, 0, 1.5, 25.5)
comp_speed_low = trimf(compressor_speed_universe, 15, 35, 35+20)
comp_speed_medium = trimf(compressor_speed_universe, 68-20, 68, 68+20)
comp_speed_high = trimf(compressor_speed_universe, 101-20, 101, 101+20)
comp_speed_very_high = traplineEnd(compressor_speed_universe, 134-20, 134, 134+20)

# Входные данные
input_temp_diff = 18
input_temp_change_speed = 0.09

# Вычисляем степени принадлежности, то есть то, с каким значением входное значение принадлежит каждой области (малая, средняя, большая)
# Тут будут значения справа
temp_diff_memberships = {
    "low": np.interp(input_temp_diff, temp_diff_universe, temp_diff_low),
    "medium": np.interp(input_temp_diff, temp_diff_universe, temp_diff_medium),
    "high": np.interp(input_temp_diff, temp_diff_universe, temp_diff_high),
}

temp_change_memberships = {
    "low": np.interp(input_temp_change_speed, temp_change_speed_universe, temp_change_low),
    "medium": np.interp(input_temp_change_speed, temp_change_speed_universe, temp_change_medium),
    "high": np.interp(input_temp_change_speed, temp_change_speed_universe, temp_change_high),
}

# Правила
rules = [
    ("low", "low", "very_low"),
    ("low", "medium", "low"),
    ("low", "high", "medium"),
    ("medium", "low", "low"),
    ("medium", "medium", "medium"),
    ("medium", "high", "high"),
    ("high", "low", "medium"),
    ("high", "medium", "high"),
    ("high", "high", "very_high"),
]

# Применяем правила
# output_membership представляет собой итоговую функцию принадлежности, которая показана на последнем графике
# То есть степень принадлежности для каждого значения по оси compressor_speed_universe
output_membership = np.zeros_like(compressor_speed_universe)
# Проходимся по каждому правилу в списке rules
for temp_key, speed_key, output_key in rules:
    # Берем минимум из степеней принадлежности входного данного к каждой области графика разности температур
    # и к каждой области графика скорости изменения температуры (см. выше)
    activation = min(temp_diff_memberships[temp_key], temp_change_memberships[speed_key])
    # для каждого элемента в output_membership мы берем максимальное значение между текущим значением 
    # и произведением степени активации на каждую функцию принадлежности
    if output_key == "very_low":
        output_membership = np.maximum(output_membership, activation * comp_speed_very_low)
    elif output_key == "low":
        output_membership = np.maximum(output_membership, activation * comp_speed_low)
    elif output_key == "medium":
        output_membership = np.maximum(output_membership, activation * comp_speed_medium)
    elif output_key == "high":
        output_membership = np.maximum(output_membership, activation * comp_speed_high)
    elif output_key == "very_high":
        output_membership = np.maximum(output_membership, activation * comp_speed_very_high)

# Центр тяжести
# Дефаззификация
output = defuzzify(lambda y: np.interp(y, compressor_speed_universe, output_membership), 0, 150)

# Построение графиков
fig, axes = plt.subplots(10, 3, figsize=(15, 25), constrained_layout=True)

first_column_values = []
# Первый столбец - разность температур


# Первый столбец: разность температур (low, medium, high)
first_column_values = []
for i, membership in enumerate([temp_diff_low, temp_diff_medium, temp_diff_high]):
    idx = i * 3  # Идем по строкам в 3-х кратном шаге
    for j in range(3):
        axes[idx + j, 0].plot(temp_diff_universe, membership, color='black')
        axes[idx + j, 0].axvline(input_temp_diff, color='red', linestyle='--')
        axes[idx + j, 0].fill_between(temp_diff_universe, 0, 
                                      np.minimum(membership, temp_diff_memberships[list(temp_diff_memberships.keys())[i]]), 
                                      color='lightsteelblue', alpha=0.6)
        first_column_values.append(temp_diff_memberships[list(temp_diff_memberships.keys())[i]])
        axes[idx + j, 0].set_ylim(-0.05, 1.05)

# Второй столбец: скорость изменения температуры (low, medium, high)
second_column_values = []
second_memberships = [temp_change_low, temp_change_medium, temp_change_high]  # Список всех функций принадлежности
for i in range(3):  # Три группы по 3 графика (low, medium, high)
    idx = i * 3
    for j in range(3):
        membership = second_memberships[j]  # Чередуем low, medium, high
        axes[idx + j, 1].plot(temp_change_speed_universe, membership, color='black')
        axes[idx + j, 1].axvline(input_temp_change_speed, color='red', linestyle='--')
        axes[idx + j, 1].fill_between(temp_change_speed_universe, 0, 
                                      np.minimum(membership, temp_change_memberships[list(temp_change_memberships.keys())[j]]), 
                                      color='plum', alpha=0.6)
        second_column_values.append(temp_change_memberships[list(temp_change_memberships.keys())[j]])
        axes[idx + j, 1].set_ylim(-0.03, 1.03)

# Третий столбец - выходные функции принадлежности
# Просто вывод графиков согласно правилам
output_graphs = [comp_speed_very_low, comp_speed_low, comp_speed_medium, comp_speed_low, 
                 comp_speed_medium, comp_speed_high, comp_speed_medium, comp_speed_high, comp_speed_very_high]
combined_output = np.zeros_like(compressor_speed_universe)

# Третий столбец - выходные функции принадлежности
for i, membership in enumerate(output_graphs):
    # Отображаем текущий график
    axes[i, 2].plot(compressor_speed_universe, membership, color='black')

    # Находим минимальное значение между first_column_values[i] и second_column_values[i]
    min_activation = min(first_column_values[i], second_column_values[i])

    # Закрашиваем область для текущего графика
    axes[i, 2].fill_between(compressor_speed_universe, 0, 
                            np.minimum(membership, min_activation), 
                            color='slateblue', alpha=0.7)

    # Обновляем итоговый объединённый выход
    combined_output = np.maximum(combined_output, np.minimum(membership, min_activation))

# Последний, десятый график: итоговое объединение всех предыдущих
axes[9, 2].plot(compressor_speed_universe, combined_output, color='black', linewidth=1) 
axes[9, 2].fill_between(compressor_speed_universe, 0, combined_output, color='slateblue', alpha=0.7)
axes[9, 2].axvline(output, color='red', linestyle='--')  # Линия выхода
axes[9, 2].set_title(f"Combined Output = {output:.2f}")

axes[9, 2].set_ylim(-0.05, 1.05)

plt.show()
