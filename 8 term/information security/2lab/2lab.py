import random

# 6 - субъектов, 4 - объектов доступа
subjects = ["admin", "user1", "user2", "user3", "user4", "user5", "user6"]
objects = ["lab1", "lab2", "lab3", "lab4"]

# Создание матрицы доступа
access_matrix = [
    [7, 7, 7, 7],  # admin имеет полные права на все объекты
    [random.randint(0, 7) for _ in range(len(objects))],  # user1
    [random.randint(0, 7) for _ in range(len(objects))],  # user2
    [random.randint(0, 7) for _ in range(len(objects))],  # user3
    [random.randint(0, 7) for _ in range(len(objects))],  # user4
    [random.randint(0, 7) for _ in range(len(objects))],  # user5
    [random.randint(0, 7) for _ in range(len(objects))]   # user6
]

# Функция для проверки прав доступа
def check_access(user_index, object_index, action):
    access_code = access_matrix[user_index][object_index]
    if action == "read":
        return (access_code & 4) != 0
    elif action == "write":
        return (access_code & 2) != 0
    elif action == "grant":
        return (access_code & 1) != 0
    return False

# Функция для передачи прав
def grant_rights(user_index, object_index, recipient_index, right):
    # Проверяем, имеет ли пользователь право на передачу прав (бит G)
    if not check_access(user_index, object_index, "grant"):
        return False

    # Проверяем, имеет ли пользователь право, которое он пытается передать
    if right == "read" and not check_access(user_index, object_index, "read"):
        return False
    elif right == "write" and not check_access(user_index, object_index, "write"):
        return False
    elif right == "grant" and not check_access(user_index, object_index, "grant"):
        return False

    # Если все проверки пройдены, передаем право
    access_code = access_matrix[recipient_index][object_index]
    if right == "read":
        access_matrix[recipient_index][object_index] = access_code | 4
    elif right == "write":
        access_matrix[recipient_index][object_index] = access_code | 2
    elif right == "grant":
        access_matrix[recipient_index][object_index] = access_code | 1
    return True

# Функция для отображения матрицы доступа
def show_access_matrix():
    print("МАТРИЦА ДОСТУПА СУБЪЕКТОВ К ОБЪЕКТАМ")
    print("| Объект / Субъект |", " | ".join(objects), "|")
    for i, subject in enumerate(subjects):
        row = [subject]
        for j in range(len(objects)):
            access_code = access_matrix[i][j]
            rights = []
            if access_code & 4:
                rights.append("R")
            if access_code & 2:
                rights.append("W")
            if access_code & 1:
                rights.append("G")
            if not rights:
                rights.append("-")
            row.append("".join(rights))
        print("|", " | ".join(row), "|")

# Функция для отображения справки
def show_help():
    print("Доступные команды:")
    print("  read - выполнить чтение объекта")
    print("  write - выполнить запись в объект")
    print("  grant - передать права на объект")
    print("  exit - выйти из системы")
    print("  help - показать эту справку")
    print("  matrix - показать матрицу доступа")

# Функция для получения индекса объекта по имени или номеру
def get_object_index(obj_input):
    if obj_input.isdigit():
        obj_index = int(obj_input) - 1
        if 0 <= obj_index < len(objects):
            return obj_index
    elif obj_input in objects:
        return objects.index(obj_input)
    return None

while True:
    user = input("User: ")
    if user not in subjects:
        print("Идентификация не удалась. Попробуйте снова.")
        continue

    user_index = subjects.index(user)
    print("Идентификация прошла успешно, добро пожаловать в систему")
    print("Перечень Ваших прав:")

    for i, obj in enumerate(objects):
        access_code = access_matrix[user_index][i]
        rights = []
        if access_code & 4:
            rights.append("Чтение")
        if access_code & 2:
            rights.append("Запись")
        if access_code & 1:
            rights.append("Передача прав")
        if not rights:
            rights.append("Запрет")
        print(f"{obj}: {', '.join(rights)}")


    while True:
        command = input("Жду ваших указаний > ")
        if command == "exit":
            print(f"Работа пользователя {user} завершена. До свидания.")
            break
        elif command == "read" or command == "write":
            obj_input = input("Над каким объектом производится операция? ")
            obj_index = get_object_index(obj_input)
            if obj_index is None:
                print("Неверный объект. Попробуйте снова.")
                continue
            if check_access(user_index, obj_index, command):
                print("Операция прошла успешно")
            else:
                print("Отказ в выполнении операции. У Вас нет прав для ее осуществления")
        elif command == "grant":
            obj_input = input("Право на какой объект передается? ")
            obj_index = get_object_index(obj_input)
            if obj_index is None:
                print("Неверный объект. Попробуйте снова.")
                continue
            right = input("Какое право передается? ")
            recipient = input("Какому пользователю передается право? ")
            if recipient not in subjects:
                print("Пользователь не найден.")
                continue
            recipient_index = subjects.index(recipient)
            if grant_rights(user_index, obj_index, recipient_index, right):
                print("Операция прошла успешно")
            else:
                print("Отказ в выполнении операции. У Вас нет прав для ее осуществления")
        elif command == "help":
            show_help()
        elif command == "matrix":
            show_access_matrix()
        else:
            print("Неизвестная команда. Введите 'help' для списка команд.")
