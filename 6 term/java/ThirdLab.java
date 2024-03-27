import java.io.*;
import java.util.Arrays;

// C:\Users\Лейсан\Desktop\input.txt

// Обращение к потоку вывода на консоль
interface IEventConsoleOutput {
    void Handler(String message, File output);
}

// Равенство указанного объекта некоторому значению
interface IEventEqual {
    void Handler(String message, File output);
}

// Обращение к потоку вывода в файл
interface IEventFileOutput {
    void Handler(String message, File output);
}

class SourceConsoleOutput {
    IEventConsoleOutput iEvent;
    SourceConsoleOutput(IEventConsoleOutput iEvent) {
        this.iEvent = iEvent;
    }
    void genEv(String message, File output){
        iEvent.Handler("Event Console Output: " + message, output);
    }
}

class SourceEqual {
    IEventEqual iEvent;
    SourceEqual(IEventEqual iEvent) {
        this.iEvent = iEvent;
    }
    void genEv(String message, File output) {
        iEvent.Handler("Event Equals 0: " + message, output);
    }
}

class SourceFileOutput {
    IEventFileOutput iEvent;

    SourceFileOutput(IEventFileOutput iEvent) {
        this.iEvent = iEvent;
    }
    void genEv(String message, File output) {
        iEvent.Handler("Event File Output: " + message, output);
    }
}

class ReceiverConsoleOutput implements IEventConsoleOutput {
    public void Handler(String message, File output){
        try {
            PrintWriter pw = new PrintWriter(new FileWriter(output.getAbsoluteFile(), true));
            pw.println(message);
            pw.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

class ReceiverEqual implements IEventEqual {
    public void Handler(String message, File output){
        try {
            PrintWriter pw = new PrintWriter(new FileWriter(output.getAbsoluteFile(), true));
            pw.println(message);
            pw.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

class ReceiverFileOutput implements IEventFileOutput {
    public void Handler(String message, File output){
        try {
            PrintWriter pw = new PrintWriter(new FileWriter(output.getAbsoluteFile(), true));
            pw.println(message);
            pw.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

class DataProcessor {
    private File input;
    private File output;
    SourceConsoleOutput eventConsoleOutput;
    SourceEqual eventEqual;
    SourceFileOutput eventFileOutput;

    public DataProcessor(SourceConsoleOutput eventConsoleOutput, SourceEqual eventEqual, SourceFileOutput eventFileOutput) {
        this.eventConsoleOutput = eventConsoleOutput;
        this.eventEqual = eventEqual;
        this.eventFileOutput = eventFileOutput;
    }

    private void setInputFile(File input) {
        this.input = input;
    }

    private void setOutputFile(File output) {
        this.output = output;
    }

    // Метод для создания новых/чтения уже существующих файлов.
    private void filesProcessing() {
        String filePath;
        File outputFile;
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        while (true) {
            try {
                String input = reader.readLine();
                if (!input.isEmpty()) {
                    filePath = input;
                    File inputFile = new File(filePath);
                    try (BufferedReader fileReader = new BufferedReader(new FileReader(inputFile))) {
                        String firstLine = fileReader.readLine();
                        if (!firstLine.isEmpty()) {
                            this.setInputFile(inputFile);
                            outputFile = new File(firstLine);
                            this.setOutputFile(outputFile);
                            return;
                        } else {
                            System.out.println("Error: The input data file does not contain the path of output file.");
                            eventConsoleOutput.genEv("Error: The input data file does not contain the path of output file.", this.output);
                        }
                    } catch (IOException e) {
                        System.out.println("Error reading the file: " + e.getMessage());
                        eventConsoleOutput.genEv("Error reading the file: ", this.output);
                    }

                } else {
                    System.out.print("The file is empty");
                    eventConsoleOutput.genEv("The file is empty", this.output);
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    // Метод для сортировки и генерации событий
    public void numberProcessing(String[] data) {
        int[] numbers = new int[data.length];
        boolean isContainZero = false;
        for (int i = 0; i < data.length; i++) {
            try {
                int num = Integer.parseInt(data[i]);
                numbers[i] = num;
                if (num == 0) {
                    isContainZero = true;
                }

            } catch (NumberFormatException e) {
                System.out.println("Unhandled exception happened.");
                eventConsoleOutput.genEv("Unhandled exception happened.", this.output);
            }
        }

        // Сортировка массива чисел по возрастанию
        Arrays.sort(numbers);

        // Событие - равенство указанного объекта некоторому значению
        if (isContainZero) {
            System.out.println("There is number that equals 0.");
            eventConsoleOutput.genEv("There is number that equals 0.", this.output);
            eventEqual.genEv("There is number that equals 0.", this.output);
        }

        // Вывод отсортированного массива
        System.out.println("Sorted array: " + Arrays.toString(numbers));
        eventConsoleOutput.genEv("Sorted array: " + Arrays.toString(numbers), this.output);
    }

    // Метод для обработки событий и инициализации файлов
    public void startProcessing() {
        System.out.print("Enter path of the input file: ");
        //eventConsoleOutput.genEv("Enter path of the input file: ", this.output);
        this.filesProcessing();

        if (this.output.length() != 0) {
            try {
                PrintWriter pw = new PrintWriter(new FileWriter(this.output, true));
                pw.println();
                pw.println("-NEW LOG-");
                pw.flush();
                eventFileOutput.genEv("Using of PrintWriter", this.output);
                System.out.println("Using of PrintWriter");
                eventConsoleOutput.genEv("Using of PrintWriter", this.output);
                pw.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        // Для данных из input
        StringBuilder sb_data = new StringBuilder();
        if (this.input.exists()) {
            try (BufferedReader br_data = new BufferedReader(new FileReader(this.input.getAbsoluteFile()))) {
                try {
                    br_data.readLine();

                    String my_data;
                    while ((my_data = br_data.readLine()) != null) {
                        sb_data.append(my_data);
                        sb_data.append("\n");
                    }
                } finally {
                    br_data.close();
                }
            } catch (IOException e) {
                throw new RuntimeException();
            }
        }

        // Преобразование sb_data в массив строк с пробелами
        this.numberProcessing(sb_data.toString().split("\\s+|\n"));
    }
}

public class ThirdLab {

    public static void main(String[] args) {
        ReceiverConsoleOutput receiverConsoleOutput = new ReceiverConsoleOutput();
        ReceiverEqual receiverEqual = new ReceiverEqual();
        ReceiverFileOutput receiverFileOutput = new ReceiverFileOutput();
        SourceEqual sourceEqual = new SourceEqual(receiverEqual);
        SourceConsoleOutput sourceConsoleOutput = new SourceConsoleOutput(receiverConsoleOutput);
        SourceFileOutput sourceFileOutput = new SourceFileOutput(receiverFileOutput);

        DataProcessor dataProcessor = new DataProcessor(sourceConsoleOutput, sourceEqual, sourceFileOutput);
        dataProcessor.startProcessing();
    }
}
