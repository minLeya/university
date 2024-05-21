
package app;


import java.util.Arrays;

public class SortBean {
    private String sequence;
    private int[] sortedNumbers;

    public String getSequence() {
        return sequence;
    }

    public void setSequence(String sequence) {
        this.sequence = sequence;
        processSequence();
    }

    private void processSequence() {
        if (sequence != null && !sequence.isEmpty()) {
            String[] numberStrings = sequence.split(",");
            sortedNumbers = new int[numberStrings.length];
            for (int i = 0; i < numberStrings.length; i++) {
                sortedNumbers[i] = Integer.parseInt(numberStrings[i].trim());
            }
            Arrays.sort(sortedNumbers);
        }
    }

    public int[] getSortedNumbers() {
        return sortedNumbers;
    }
}
