import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;

interface IEventConsoleOutput {
    void Handler(String message, File output);
}

interface IEventEqual {
    void Handler(String message, File output);
}

interface IEventFileOutput {
    void Handler(String message, File output);
}

class SourceConsoleOutput {
    IEventConsoleOutput iEvent;
    SourceConsoleOutput(IEventConsoleOutput iEvent) {
        this.iEvent = iEvent;
    }
    void genEv(String message, File output){
        iEvent.Handler("Event " + message, output);
    }
}

class SourceEqual {
    IEventEqual iEvent;
    SourceEqual(IEventEqual iEvent) {
        this.iEvent = iEvent;
    }
    void genEv(String message, File output) {
        iEvent.Handler("Event " + message, output);
    }
}

class SourceFileOutput {
    IEventFileOutput iEvent;

    SourceFileOutput(IEventFileOutput iEvent) {
        this.iEvent = iEvent;
    }
    void genEv(String message, File output) {
        iEvent.Handler("Event " + message, output);
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
    public void Handler(String message, File log_file){
        try {
            PrintWriter pw = new PrintWriter(new FileWriter(log_file.getAbsoluteFile(), true));
            pw.println(message);
            pw.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

class ReceiverFileOutput implements IEventFileOutput {
    public void Handler(String message, File log_file){
        try {
            PrintWriter pw = new PrintWriter(new FileWriter(log_file.getAbsoluteFile(), true));
            pw.println(message);
            pw.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

class DataProcessor {
    ArrayList<Integer> array;
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
                    if (!inputFile.exists()) {
                        System.out.println("The input file does not exist. Path: " + inputFile.getAbsolutePath());
                        System.out.print("Enter another path of input data file: ");
                    } else {
                        try (BufferedReader fileReader = new BufferedReader(new FileReader(inputFile))) {
                            String firstLine = fileReader.readLine();
                            if (!firstLine.isEmpty()) {
                                System.out.println("O: First line of the input data file is the path to the log file. Path: " + firstLine);
                                this.setInputFile(inputFile);
                                outputFile = new File(firstLine);
                                this.setOutputFile(outputFile);
                                if (!outputFile.exists()) {
                                    outputFile.createNewFile();
                                    System.out.println("O: Log file created successfully: " + outputFile.getAbsolutePath());
                                    eventConsoleOutput.genEv("O: Log file created successfully: " + outputFile.getAbsolutePath(), outputFile);
                                    System.out.println("O: The log file can be succesfully opened for logging.");
                                    eventConsoleOutput.genEv("O: The log file can be succesfully opened for logging.", outputFile);
                                }
                                return;
                            } else {
                                System.out.println("O: Error: The input data file does not contain the path of log file. Search another input data file.");
                                System.out.print("I/O: Path of input data file: ");
                            }
                        } catch (IOException e) {
                            System.out.println("O: Error reading the file: " + e.getMessage());
                        }
                    }
                } else {
                    System.out.print("O: The file path was not retrieved correctly. Re-enter: ");
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    public void numberProcessing(String[] data) {
        int[] numbers = new int[data.length];
        for (int i = 0; i < data.length; i++) {
            try {
                int num = Integer.parseInt(data[i]);
                numbers[i] = num;
            } catch (NumberFormatException e) {
                System.out.println("O: Unhandled exception happened.");
                eventConsoleOutput.genEv("O: Unhandled exception happened.", this.output);
                System.exit(1);
            }
        }

        // Сортировка массива чисел по возрастанию
        Arrays.sort(numbers);

        // Вывод отсортированного массива
        System.out.println("Sorted array: " + Arrays.toString(numbers));
        eventConsoleOutput.genEv("O: Sorted array: " + Arrays.toString(numbers), this.output);
    }

    public void startProcessing() {
        System.out.print("I/O: Enter the absolute path of the input file: ");
        this.filesProcessing();

        if (this.output.length() != 0) {
            try {
                PrintWriter pw = new PrintWriter(new FileWriter(this.output, true));
                pw.println();
                pw.println("/*New log to the same file:*/");
                pw.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

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
