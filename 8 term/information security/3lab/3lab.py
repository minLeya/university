import random

# Уровни конфиденциальности
SECURITY_LEVELS = {
    0: "NONCONFIDENTIAL",
    1: "CONFIDENTIAL",
    2: "SECRET",
    3: "TOP_SECRET"
}

# Функция для случайного выбора уровня конфиденциальности
def get_random_security_level():
    return random.choice(list(SECURITY_LEVELS.keys()))

# Класс для представления объекта
class Object:
    def __init__(self, name):
        self.name = name
        self.security_level = get_random_security_level()

    def __str__(self):
        return f"{self.name} : {SECURITY_LEVELS[self.security_level]}"

# Класс для представления субъекта
class Subject:
    def __init__(self, name, is_admin=False):
        self.name = name
        self.is_admin = is_admin
        if is_admin:
            self.security_level = 3  # Администратор всегда имеет TOP_SECRET
        else:
            self.security_level = get_random_security_level()
        self.original_security_level = self.security_level  # Сохраняем исходный уровень

    def __str__(self):
        return f"{self.name} : {SECURITY_LEVELS[self.security_level]}"

    def change_security_level(self, new_level):
        if new_level <= self.original_security_level:
            self.security_level = new_level
            return True
        return False

# Функция для проверки доступа на чтение
def can_read(subject, obj):
    return subject.security_level >= obj.security_level

# Функция для проверки доступа на запись
def can_write(subject, obj):
    return subject.security_level <= obj.security_level

# Функция для вывода справки
def show_help():
    print("Доступные команды:")
    print("  read - чтение объекта")
    print("  write - запись в объект")
    print("  change - изменение уровня доступа субъекта")
    print("  exit - выход из системы")
    print("  help - показать справку")

# Основная функция программы
def main():
    # Создаем объекты - 4  и субъекты - 7
    objects = [Object(f"Объект {i+1}") for i in range(4)]  # 3 объекта
    subjects = [
        Subject("admin", is_admin=True),
        Subject("user1"),
        Subject("user2"),
        Subject("user3"),
        Subject("user4"),
        Subject("user5"),
        Subject("user6")
    ]

    # Выводим начальные данные
    print("OBJECTS:")
    for obj in objects:
        print(obj)
    print("SUBJECTS:")
    for subject in subjects:
        print(subject)

    # Основной цикл программы
    while True:
        login = input("Логин: ")
        if login.lower() == "exit":
            break

        # Ищем субъекта по логину
        current_user = None
        for subject in subjects:
            if subject.name.lower() == login.lower():
                current_user = subject
                break

        if not current_user:
            print("Пользователь не найден.")
            continue

        print(f"Добро пожаловать, {current_user.name}!")
        show_help()  # Показываем справку при входе
        while True:
            command = input("Команда> ").strip().lower()
            if command == "exit":
                break
            elif command == "read":
                obj_index = int(input("У какого объекта? ")) - 1
                if 0 <= obj_index < len(objects):
                    if can_read(current_user, objects[obj_index]):
                        print("Чтение успешно")
                    else:
                        print("Чтение запрещено")
                else:
                    print("Неверный индекс объекта")
            elif command == "write":
                obj_index = int(input("У какого объекта? ")) - 1
                if 0 <= obj_index < len(objects):
                    if can_write(current_user, objects[obj_index]):
                        print("Запись успешна")
                    else:
                        print("Запись запрещена")
                else:
                    print("Неверный индекс объекта")
            elif command == "change":
                new_level = input("Введите уровень доступа: ").strip().upper()
                level_found = False
                for key, value in SECURITY_LEVELS.items():
                    if value == new_level:
                        if current_user.change_security_level(key):
                            print(f"{current_user.name} теперь имеет уровень {SECURITY_LEVELS[key]}")
                        else:
                            print("Невозможно повысить уровень доступа выше исходного.")
                        level_found = True
                        break
                if not level_found:
                    print("Неверный уровень доступа")
            elif command == "help":
                show_help()
            else:
                print("Неизвестная команда")

# Запуск программы
if __name__ == "__main__":
    main()
