import string

class GSubstitutionCipher:
    def __init__(self, key, alphabets):
        self.key = [int(digit) - 1 for digit in str(key)]  # Преобразуем ключ в индексы (от 0)
        self.alphabets = alphabets
        self.reverse_alphabets = [self._create_reverse_mapping(abc) for abc in alphabets]

    def _create_reverse_mapping(self, alphabet):
        """Создает обратную таблицу подстановок"""
        return {char: i for i, char in enumerate(alphabet)}

    def encrypt(self, text):
        encrypted_text = []
        key_length = len(self.key)

        for i, char in enumerate(text):
            if char in string.ascii_lowercase:  # Используем только буквы для шифрования
                abc_index = self.key[i % key_length]  # Выбираем алфавит по ключу
                original_index = string.ascii_lowercase.index(char)
                encrypted_text.append(self.alphabets[abc_index][original_index])
            else:
                encrypted_text.append(char)  # Не шифруем символы вне алфавита

        return "".join(encrypted_text)

    def decrypt(self, text):
        decrypted_text = []
        key_length = len(self.key)

        for i, char in enumerate(text):
            if char in string.ascii_lowercase:
                abc_index = self.key[i % key_length]  # Выбираем алфавит по ключу
                original_index = self.reverse_alphabets[abc_index][char]
                decrypted_text.append(string.ascii_lowercase[original_index])
            else:
                decrypted_text.append(char)

        return "".join(decrypted_text)

# Пример использования
standard_alphabet = string.ascii_lowercase  # Обычный алфавит
alphabet_1 = standard_alphabet[-5:] + standard_alphabet[:-5]  # Сдвиг на 5 вправо
alphabet_2 = standard_alphabet[-10:] + standard_alphabet[:-10]  # Сдвиг на 10
alphabet_3 = standard_alphabet[-3:] + standard_alphabet[:-3]  # Сдвиг на 3
alphabet_4 = standard_alphabet[-7:] + standard_alphabet[:-7]  # Сдвиг на 7

key = 13243
alphabets = [alphabet_1, alphabet_3, alphabet_2, alphabet_4]

cipher = GSubstitutionCipher(key, alphabets)

message = "hello, worldtgtbthb"
encrypted = cipher.encrypt(message)
decrypted = cipher.decrypt(encrypted)

print("Encrypted:", encrypted)
print("Decrypted:", decrypted)

