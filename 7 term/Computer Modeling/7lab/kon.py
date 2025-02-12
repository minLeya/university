import numpy as np
import matplotlib.pyplot as plt
import time
from adjustText import adjust_text
import random

class Kohonen:
    def __init__(self, input_dim, dim=10, sigma=None, learning_rate=0.1, tay2=1000):
      # input_dim - размерность входных данных (данные с 10 признаками)
      # dim - размер сетки. Количество нейронов по одной стороне
      # sigma - начальное значение радиуса соседства. Это параметр, который определяет
      # насколько далеко от победившего нейрона будут обновляться веса соседних нейронов. По умолчанию половина dim
      # learning_rate - начальная скорость обучения. Определяет, насколько сильно будут обновляться веса нейронов на каждом шагу обучения
      # tay2 - насколько быстро будет уменьшаться скорость обучения
      # tay1 - насколько быстро будет уменьшаться радиус соседства
      # minisigma - минимальное значение радиуса соседства, до которого может уменьшаться
      # w - веса нейронов. Инициализируются случайными значениями в диапазоне от -1 до 1
      # positions - координаты нейронов на сетке
        if not sigma:
            sigma = dim / 2
        self.dim = dim
        self.learning_rate = learning_rate
        self.sigma = sigma
        self.tay1 = 1000 / np.log(sigma)
        self.minsigma = sigma * np.exp(-1000 / (1000 / np.log(sigma)))
        self.tay2 = tay2

        # Инициализация весов и позиций
        self.w = np.random.uniform(-1, 1, (dim * dim, input_dim))
        self.positions = np.array([[i, j] for i in range(dim) for j in range(dim)])

    # Вычисление расстояния до всех нейронов сети и возврат индекса победителя
    def competition(self, input_vector):
        distances = np.sum((input_vector - self.w) ** 2, axis=1)
        return np.argmin(distances)

    # Один шаг обучения для карты Кохонена
    def train_step(self, input_vector, iteration):
        # Определяем нейрона-победителя на основе входного вектора
        winner_idx = self.competition(input_vector)
        # Получаем координаты нейрона-победителя на сетке
        winner_position = self.positions[winner_idx]

        # Вычисялем евклидовы расстояния от всех нейронов до нейрона победителя
        distances = np.sqrt(np.sum((self.positions - winner_position) ** 2, axis=1))

        # Обновляем радиус соседства. Если итерация больше 1000, используется minisigma
        # Если меньше, радиус соседства уменьшается экспоненциально
        sigma = self.minsigma if iteration > 1000 else self.sigma * np.exp(-iteration / self.tay1)
        # Функция соседства - гауссова функция.
        tnh = np.exp(-np.square(distances) / (2 * sigma ** 2))

        # Обновляем скорость обучения
        lr = self.learning_rate * np.exp(-iteration / self.tay2)
        lr = max(lr, 0.01)

        # Вычисляем значение для обновления весов
        # Каждый элемент матрицы (input_vector - self.w) размером  (dim * dim, input_dim)
        # Будет умножен на соответствующий элемент матрицы lr * tnh[:, np.newaxis] размером (dim * dim, 1)
        delta = lr * tnh[:, np.newaxis] * (input_vector - self.w)
        # Обновляем веса
        self.w += delta 

    # Получение текущих весов нейронов сетки в удобном для визуализации формате
    # self.dim - количество строк/столбцов в новой форме массива
    # -1 - автоматическое определение размера последней оси
    # Преобразование двумерного массива в трехмерный
    def get_weights(self):
        return self.w.reshape(self.dim, self.dim, -1)

    # Возвращает координаты победителя для входного вектора
    def get_winner_position(self, input_vector):
        winner_idx = self.competition(input_vector)
        # Позиция победителя на сетке
        return self.positions[winner_idx] 

def add_random_offset(x, y, offset_range=1):
    return x + random.uniform(-offset_range, offset_range), y + random.uniform(-offset_range, offset_range)

def test_Kohonen_region():
    # Данные
    data = [
        ['Белгородская область', 183457, 74275, 1353, 16, 19101, 11173, 26219, 19255, 133205, 40528],
        ['Брянская область', 98933, 10225, 2462, 0, 8086, 1228, 5745, 1245, 81098, 7715],
        ['Владимирская область', 166906, 22560, 1937, 279, 20194, 1290, 11467, 633, 130677, 19680],
        ['Воронежская область', 335345, 46734, 6763, 6, 35224, 5481, 37913, 5811, 246059, 34288],
        ['Ивановская область', 82643, 17876, 320, 0, 7195, 722, 5845, 238, 67662, 16810],
        ['Калужская область', 118554, 16904, 2692, 0, 19137, 2428, 11819, 3606, 83391, 10630],
        ['Костромская область', 114779, 5799, 1194, 0, 4493, 912, 12383, 351, 52165, 4089],
        ['Курская область', 94131, 9969, 697, 114, 7838, 1146, 10871, 546, 71931, 7505],
        ['Липецкая область', 117387, 34757, 1884, 0, 10166, 6207, 15058, 16734, 85929, 9186],
        ['Московская область', 1239984, 221853, 14083, 1008, 157590, 39181, 69230, 15541, 979379, 164832],
        ['Орловская область', 72981, 5558, 383, 0, 5054, 731, 4459, 122, 61588, 4559],
        ['Рязанская область', 129056, 16045, 1338, 0, 14382, 3032, 15646, 3491, 96009, 9466],
        ['Смоленская область', 92677, 16981, 1464, 26, 12508, 3044, 6825, 4415, 70174, 9223],
        ['Тамбовская область', 87790, 6847, 1976, 17, 7492, 678, 4535, 78, 70395, 5303],
        ['Тверская область', 133520, 13825, 1275, 0, 13342, 996, 12266, 1379, 104989, 11202],
        ['Тульская область', 196925, 26293, 1419, 386, 45399, 9322, 13762, 1760, 133280, 14127],
        ['Ярославская область', 163112, 29817, 2375, 0, 17518, 3370, 13616, 2036, 126943, 23673],
        ['г. Москва', 12902217, 10490236, 250595, 83945, 2764720, 1557668, 4764114, 3375354, 4373312, 2937432],
        ['Республика Карелия', 67964, 6947, 751, 16, 4849, 798, 3876, 205, 56706, 5870],
        ['Республика Коми', 103983, 12538, 201, 0, 5436, 1421, 4056, 1922, 91753, 9097],
        ['Архангельская область', 160347, 13576, 1764, 16, 32029, 976, 6162, 1370, 117767, 11129],
        ['Ненецкий автономный округ', 8678, 302, 157, 0, 658, 3, 677, 0, 7051, 299],
        ['Вологодская область', 124723, 104088, 2482, 0, 11247, 4424, 17624, 85076, 91245, 14286],
        ['Калининградская область', 129891, 43330, 1869, 938, 18521, 8919, 9282, 2071, 97797, 30803],
        ['Ленинградская область', 160278, 23495, 929, 13, 12326, 6909, 24120, 5872, 121367, 9044],
        ['Мурманская область', 132237, 19688, 1577, 75, 9000, 5337, 6596, 2385, 112724, 11799],
        ['Новгородская область', 55209, 7795, 860, 0, 5217, 2274, 4782, 147, 43583, 5333],
        ['Псковская область', 52773, 6093, 987, 0, 4576, 812, 4517, 987, 42168, 4258],
        ['г. Санкт-Петербург', 2004689, 737975, 39166, 3712, 453428, 142272, 339143, 87380, 1069782, 454911],
        ['Республика Адыгея (Адыгея)', 18236, 966, 64, 0, 1351, 89, 504, 62, 15711, 815],
        ['Республика Калмыкия', 9774, 614, 103, 0, 821, 9, 342, 0, 8231, 605],
        ['Республика Крым', 18082, 0, 10037, 0, 367, 0, 777, 0, 6836, 0],
        ['Краснодарский край', 545206, 108534, 14912, 173, 60630, 12345, 37017, 8618, 417466, 86775],
        ['Астраханская область', 70337, 8737, 919, 32, 6838, 1791, 2086, 174, 58273, 6703],
        ['Волгоградская область', 213234, 31838, 3916, 418, 20908, 7153, 13350, 893, 169757, 22948],
        ['Ростовская область', 372873, 66206, 9060, 413, 47887, 16322, 26934, 2680, 279316, 43419],
        ['г. Севастополь', 6738, 1, 145, 0, 1199, 0, 184, 0, 5179, 1],
        ['Республика Дагестан', 61663, 3386, 481, 0, 7453, 985, 1785, 290, 50704, 2088],
        ['Республика Ингушетия', 6985, 385, 52, 0, 2656, 115, 538, 0, 3669, 270],
        ['Кабардино-Балкарская Республика', 33202, 3321, 489, 0, 3959, 289, 1278, 0, 26832, 2274],
        ['Карачаево-Черкесская Республика', 15622, 611, 166, 0, 1235, 12, 583, 0, 13307, 599],
        ['Республика Северная Осетия - Алания', 37234, 2063, 496, 1, 3306, 33, 550, 0, 32318, 1756],
        ['Чеченская Республика', 24162, 1192, 914, 0, 6677, 281, 7067, 0, 9226, 454],
        ['Ставропольский край', 244185, 30058, 3703, 15, 24818, 2118, 17623, 3315, 190782, 21968],
        ['Республика Башкортостан', 359900, 43526, 3515, 50, 43271, 4541, 63216, 2967, 242701, 34406],
        ['Республика Марий Эл', 55068, 4775, 452, 7, 7285, 768, 5179, 531, 41394, 3449],
        ['Республика Мордовия', 43918, 4132, 991, 0, 3593, 566, 4499, 179, 33961, 3382],
        ['Республика Татарстан (Татарстан)', 625538, 104974, 11456, 206, 113756, 14926, 172833, 3505, 314909, 62178],
        ['Удмуртская Республика', 158369, 15806, 1273, 3, 46787, 2089, 21880, 278, 85743, 11746],
        ['Чувашская Республика - Чувашия', 103198, 12929, 774, 0, 9321, 1465, 8820, 1722, 82626, 9209],
        ['Пермский край', 296350, 67044, 3460, 3, 38184, 18237, 24124, 8224, 223754, 40348],
        ['Кировская область', 101653, 9467, 1542, 0, 11072, 558, 10575, 691, 75658, 7883],
        ['Нижегородская область', 416736, 69294, 9825, 49, 69177, 9947, 44970, 3942, 285370, 49035],
        ['Оренбургская область', 145698, 19604, 2841, 0, 17282, 3814, 11236, 1158, 110871, 14553],
        ['Пензенская область', 109867, 8008, 3969, 0, 12775, 1011, 6544, 205, 83918, 6325],
        ['Самарская область', 429939, 123337, 3129, 3, 59370, 13093, 39209, 13865, 324253, 95163],
        ['Саратовская область', 194208, 33022, 2929, 2, 26014, 5574, 13323, 2013, 147872, 25372],
        ['Ульяновская область', 125831, 24014, 1185, 0, 24156, 13661, 6148, 1281, 92202, 8993],
        ['Курганская область', 49997, 3507, 1247, 1, 7248, 226, 2561, 103, 37326, 3017],
        ['Свердловская область', 656714, 108337, 12490, 84, 108803, 21561, 91414, 7766, 414382, 77000],
        ['Тюменская область', 629834, 189849, 5073, 6, 111630, 6364, 109551, 29434, 391092, 153517],
        ['Ханты-Мансийский автономный округ - Югра', 298807, 133343, 838, 2, 43005, 3181, 49849, 2242, 199950, 127524],
        ['Ямало-Ненецкий автономный округ', 105080, 5935, 828, 0, 19019, 1201, 13582, 0, 69753, 4734],
        ['Челябинская область', 308825, 55454, 8004, 101, 41629, 7684, 28984, 6455, 223943, 38074],
        ['Республика Алтай', 7516, 298, 118, 0, 386, 19, 294, 25, 6557, 253],
        ['Республика Бурятия', 49573, 8471, 1248, 0, 4316, 257, 2399, 4163, 39440, 3999],
        ['Республика Тыва', 8381, 185, 126, 0, 698, 0, 285, 0, 6780, 185],
        ['Республика Хакасия', 28645, 2709, 427, 0, 1891, 107, 915, 0, 24436, 2563],
        ['Алтайский край', 177038, 25040, 2936, 17, 15828, 3871, 22719, 8212, 131769, 12800],
        ['Забайкальский край', 69602, 3605, 1627, 0, 6022, 605, 2896, 314, 57046, 2678],
        ['Красноярский край', 330955, 37921, 10815, 4297, 52191, 6160, 25732, 989, 221621, 25602],
        ['Иркутская область', 287720, 61691, 4806, 15, 25991, 6156, 57959, 31976, 191668, 22302],
        ['Кемеровская область', 247097, 41454, 2754, 0, 24367, 6121, 18417, 9937, 196157, 23642],
        ['Новосибирская область', 411032, 59674, 6516, 16, 40957, 7175, 31733, 6816, 314137, 43507],
        ['Омская область', 159081, 20951, 3274, 0, 22260, 1397, 13350, 1920, 116142, 17032],
        ['Томская область', 136150, 19300, 2665, 315, 15632, 1736, 22482, 2108, 91920, 14683],
        ['Республика Саха (Якутия)', 102547, 6512, 2677, 310, 13936, 1920, 14874, 707, 67565, 3558],
        ['Камчатский край', 59929, 8759, 1226, 0, 8044, 2162, 3717, 604, 45417, 5715],
        ['Приморский край', 226002, 45162, 4294, 156, 32756, 9803, 12797, 4107, 171259, 30613],
        ['Хабаровский край', 220249, 84141, 3184, 20, 26968, 2250, 23443, 61343, 161911, 20419],
        ['Амурская область', 71326, 6946, 1815, 12, 7750, 726, 3855, 949, 54946, 5090],
        ['Магаданская область', 39311, 14403, 381, 3, 3486, 5320, 4786, 6349, 29762, 2706],
        ['Сахалинская область', 195672, 16729, 6412, 0, 35240, 4309, 62260, 866, 87268, 11476],
        ['Еврейская автономная область', 10585, 754, 86, 0, 464, 14, 215, 181, 9519, 554],
        ['Чукотский автономный округ', 10884, 190, 634, 0, 845, 12, 624, 28, 8376, 149],
        ['ЗА ПРЕДЕЛАМИ РОССИЙСКОЙ ФЕДЕРАЦИИ', 13120, 60816, 0, 4, 6045, 25664, 6487, 27615, 588, 6657],
    ]

    columns = ['Районы',
               'Средства клиентов в рублях',
               'Средства клиентов в иностранной валюте и драгоценных металлах',
               'Средства на счетах государственных организаций в рублях',
               'Средства на счетах государственных организаций в иностранной валюте',
               'Средства на счетах негосударственных организаций в рублях',
               'Средства на счетах негосударственных организаций в иностранной валюте',
               'Депозиты юридических лиц в рублях',
               'Депозиты юридических лиц в иностранной валюте и драгоценных металлах',
               'Депозиты физических лиц в рублях',
               'Депозиты физических лиц в иностранной валюте и драгоценных металлах']

    # Преобразуем числовые данные в массив, исключая первый столбец 
    numeric_data = np.array([row[1:] for row in data])
    # Размер сетки
    som_dim = 10 
    # Создаем экземпляр классса с начальным значением радиуса соседства = 3
    Kohonen_som = Kohonen(input_dim=10, dim=som_dim, sigma=3)
    # Вывод начального состояния весов
    original_weights = Kohonen_som.get_weights()


    # Для каждого параметра вектора создаем отдельную визуализацию
    for i in range(10): 
        # Каждый график на отдельном окне
        plt.figure(figsize=(10, 7))  
        plt.imshow(original_weights[..., i].reshape(som_dim, som_dim), cmap='Spectral', aspect="auto")
        plt.title(f"Начальное состояние весов. Параметр {columns[i+1]}")
        plt.axis("off")

        # Вывод названия обалсти
        texts1 = []
        for idx, row in enumerate(data):
            region = row[0]
            # Преобразуем индекс области в соответствующую координату сетки
            x, y = Kohonen_som.get_winner_position(numeric_data[idx])
            x, y = add_random_offset(x, y)
            text1 = plt.text(y, x, region, color='white', fontsize=8, ha='center', va='center')  # Выводим название области
            texts1.append(text1)

        adjust_text(texts1, arrowprops=dict(arrowstyle='-', color='white'))
        plt.show()

    # Обучение
    start = time.time()
    for i, vector_data in enumerate(numeric_data):
        Kohonen_som.train_step(vector_data, i)
        if i % 500 == 0:
            print(f"Итерация: {i}")
    end = time.time()
    print(f"Время обучения: {end - start:.2f} секунд")

    # Конечное состояние весов
    final_weights = Kohonen_som.get_weights()

    # Для каждого параметра вектора создаем отдельную визуализацию
    for i in range(10):
        plt.figure(figsize=(10, 7))
        plt.imshow(final_weights[..., i].reshape(som_dim, som_dim), cmap='Spectral', aspect="auto")
        plt.title(f"Состояние весов после обучения. Параметр {columns[i+1]}")
        plt.axis("off")

        texts = []
        # Добавляем названия областей
        for idx, row in enumerate(data):
            region = row[0]
            # Преобразуем индекс области в соответствующую координату сетки 
            # Для каждого вектора параметров высчитывается нейрон-победитель для каждой области
            x, y = Kohonen_som.get_winner_position(numeric_data[idx]) 
            x, y = add_random_offset(x, y)
            text = plt.text(y, x, region, color='white', fontsize=8, ha='center', va='center')
            texts.append(text)

        adjust_text(texts, arrowprops=dict(arrowstyle='-', color='white'))
        plt.show()

# Вызов основной функции
test_Kohonen_region()