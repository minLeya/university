from collections import Counter

def analyze_frequencies(text):
    """Возвращает частоту символов в тексте."""
    total_chars = len(text)
    counter = Counter(text)
    return {char: count / total_chars for char, count in counter.items()}

def create_substitution_map(encrypted_freqs, standard_freqs):
    """
    Создаёт таблицу соответствий между зашифрованными символами и стандартными.
    """
    sorted_encrypted = sorted(encrypted_freqs.items(), key=lambda x: x[1], reverse=True)
    sorted_standard = sorted(standard_freqs.items(), key=lambda x: x[1], reverse=True)

    substitution_map = {enc[0]: std[0] for enc, std in zip(sorted_encrypted, sorted_standard)}
    return substitution_map

def decrypt_text(text, substitution_map):
    """Расшифровывает текст, заменяя символы по таблице соответствий."""
    return ''.join(substitution_map.get(char, char) for char in text)

if __name__ == "__main__":
    # Чтение стандартного текста и зашифрованного текста из файлов
    with open("/content/Open text.txt", "r", encoding="windows-1251", errors="ignore") as f:
        standard_text = f.read().strip()

    with open("/content/encrypt13.txt", "r", encoding="windows-1251", errors="ignore") as f:
        encrypted_text = f.read().strip()

    standard_frequencies = analyze_frequencies(standard_text)
    encrypted_frequencies = analyze_frequencies(encrypted_text)

    # Создаём таблицу соответствий
    substitution_map = create_substitution_map(encrypted_frequencies, standard_frequencies)

    # Расшифровываем текст
    decrypted_text = decrypt_text(encrypted_text, substitution_map)

    # Записываем результат в файл
    with open("decrypted_text.txt", "w", encoding="windows-1251", errors="ignore") as f:
        f.write(decrypted_text)

    print("Расшифрованный текст сохранён в decrypted_text.txt")
