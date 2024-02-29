import java.util.ArrayList;
import java.util.Collections;

class ArraySizeException extends Exception {
    public ArraySizeException() {}
    public String toString() {
        return "Exception occurred: Array size is less than the minimum allowed size.";
    }
}

class MaxNumberValueException extends Exception {
    public MaxNumberValueException() {}
    public String toString() {
        return "Exception occurred: Number exceeds the maximum value.";
    }
}

class SymbolContainedException extends Exception {
    public SymbolContainedException() {}
    public String toString() {
        return "Exception occurred: Number contains the specified symbol.";
    }
}

interface Constants {
    int MIN_SIZE = 5;
    int MAX_VALUE = 250;
}

interface NumberArrayOperations {
    void add(int number) throws MaxNumberValueException;
    void checkSize() throws ArraySizeException;
    void sort();
    void printSortedArray();
}

class NumberArrayHandler implements NumberArrayOperations {
    private ArrayList<Integer> array = new ArrayList<>();

    public void add(int number) throws MaxNumberValueException {
        if (number > Constants.MAX_VALUE) {
            throw new MaxNumberValueException();
        }

        array.add(number);
    }


    public void checkSize() throws ArraySizeException {
        if (array.size() < Constants.MIN_SIZE) {
            throw new ArraySizeException();
        }
    }

    public void sort() {
        Collections.sort(array);
    }

    public void printSortedArray() {
        System.out.println("Sorted Array:");
        for (Integer number : array) {
            System.out.print(number + " ");
        }
        System.out.println();
    }
}

public class Main {
    public static void main(String args[]) {
        NumberArrayHandler handler = new NumberArrayHandler();

        for (String arg : args) {
            try {

                if (arg.equals(";")) {
                    throw new SymbolContainedException();
                }
                handler.add(Integer.parseInt(arg));

            } catch (SymbolContainedException | MaxNumberValueException e) {
                System.out.println(e);
            }
        }

        try {
            handler.checkSize();
        } catch (ArraySizeException e) {
            System.out.println(e);
        }
        handler.sort();
        handler.printSortedArray();
    }
}
