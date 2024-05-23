package app;

import java.util.Arrays;

public class SortBean {
    private int counter;
    private String sequence;
    private int[] sortedNumbers;

    public SortBean() {
        counter = 0;
    }

    public int getCounter() {
        return counter;
    }

    // Метод для установки значения счетчика
    public void setCounter(int counter) {
        this.counter = counter;
    }

    public String getSequence() {
        return sequence;
    }

    public void setSequence(String sequence) {
        this.sequence = sequence;
        processSequence();
    }

    // обработка последовательности
    private void processSequence() {
        if (sequence != null && !sequence.isEmpty()) {
            String[] numberStrings = sequence.split(",");
            sortedNumbers = new int[numberStrings.length];
            for (int i = 0; i < numberStrings.length; i++) {
                sortedNumbers[i] = Integer.parseInt(numberStrings[i].trim());
            }
            Arrays.sort(sortedNumbers);
            counter++;
        }
    }

    // отсортированные числа
    public int[] getSortedNumbers() {
        return sortedNumbers;
    }
}
