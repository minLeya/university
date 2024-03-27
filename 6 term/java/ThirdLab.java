import java.io.*;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

// Класс для генерации событий
class EventGenerator {
    // Событие: обращение к потоку вывода на консоль
    public void consoleOutputEvent() {
        System.out.println("Событие: обращение к потоку вывода на консоль");
    }

    // Событие: равенство указанного объекта некоторому значению
    public void objectEqualityEvent(Object object, Object value) {
        if (object.equals(value)) {
            System.out.println("Событие: равенство объекта " + object + " значению " + value);
        }
    }

    // Событие: обращение к потоку вывода в указанный файл
    public void fileOutputEvent(String filePath, String journalFilePath) {
        try {
            PrintWriter writer = new PrintWriter(new FileWriter(journalFilePath));
            writer.println("Событие: обращение к потоку вывода в указанный файл");
            writer.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

class DataProcessor {
    private String inputFilePath;
    private String outputFilePath;

    public DataProcessor(String inputFilePath, String outputFilePath) {
        this.inputFilePath = inputFilePath;
        this.outputFilePath = outputFilePath;
    }

    public void processAndSaveData() {
        EventGenerator eventGenerator = new EventGenerator();

        try {
            // Чтение данных из файла
            File file = new File(inputFilePath);
            BufferedReader fileReader = new BufferedReader(new FileReader(file));
            String journalFilePath = fileReader.readLine(); // Путь к журнальному файлу
            String data;
            List<Integer> numbers = new ArrayList<>();
            while ((data = fileReader.readLine()) != null) {
                String[] tokens = data.split("\\s+");
                for (String token : tokens) {
                    numbers.add(Integer.parseInt(token));
                }
            }
            fileReader.close();

            // Генерация события: обращение к потоку вывода на консоль
            eventGenerator.consoleOutputEvent();

            // Сортировка списка чисел в порядке убывания
            Collections.sort(numbers, Collections.reverseOrder());

            // Вывод отсортированного списка чисел на консоль
            for (int num : numbers) {
                System.out.print(num + " ");
            }

            // Генерация события: обращение к потоку вывода в указанный файл
            eventGenerator.fileOutputEvent(outputFilePath, journalFilePath);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

public class ThirdLab {

    public static void main(String[] args) {
        try {
            BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

            // Ввод пути к файлу с данными
            System.out.println("Введите путь к файлу с данными:");
            String inputFilePath = reader.readLine();

            // Создание объекта DataProcessor с указанием путей к файлам
            DataProcessor dataProcessor = new DataProcessor(inputFilePath, null);

            // Вызов метода для обработки и сохранения данных
            dataProcessor.processAndSaveData();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
