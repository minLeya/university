import java.util.ArrayList;
import java.util.Collections;
//Дана последовательность целых чисел.
// Вывести отсортированный список в порядке возрастания.

class ArraySizeException extends Exception {
    public ArraySizeException(String message) {
        super(message);
    }
}

// Класс исключения, выбрасываемый при превышении максимального значения числа
class MaxNumberValueException extends Exception {
    public MaxNumberValueException(String message) {
        super(message);
    }
}

// Класс исключения, выбрасываемый при наличии определенного символа в строке
class SymbolContainedException extends Exception {
    public SymbolContainedException(String message) {
        super(message);
    }
}

interface Constants
{
    int MIN_SIZE = 5;
    int MAX_VALUE = 250;
    char SYMBOL = ';';
}

interface NumberArrayOperations
{
    void add(int number) throws MaxNumberValueException, SymbolContainedException;
    void checkSize() throws ArraySizeException;
    void sort();
    void printSortedArray();
}

class NumberArrayHandler implements NumberArrayOperations
{
    private ArrayList<Integer> array = new ArrayList<>();

    // Метод добавления числа в массив с проверкой на исключения
    public void add(int number) throws MaxNumberValueException, SymbolContainedException {
        if (number > Constants.MAX_VALUE) {
            throw new MaxNumberValueException("Number exceeds the maximum value.");
        }
        if (String.valueOf(number).contains(String.valueOf(Constants.SYMBOL))) {
            throw new SymbolContainedException("Number contains the specified symbol.");
        }
        array.add(number);
    }

    public void checkSize() throws ArraySizeException
    {
        if (array.size() < Constants.MIN_SIZE) {
            throw new ArraySizeException("Array size is less than the minimum allowed size.");
        }
    }

    public void sort()
    {
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


public class Second {
    public static void main(String args[]) {
        NumberArrayHandler handler = new NumberArrayHandler();

        for (String arg : args) {
            try {
                // Проверяем наличие символа ';' в строке
                if (arg.contains(";")) {
                    throw new SymbolContainedException("Number contains the specified symbol.");
                }
                handler.add(Integer.parseInt(arg));
            } catch (SymbolContainedException e) {
                System.out.println("Exception occurred: " + e.getMessage());
            } catch (MaxNumberValueException e) {
                System.out.println("Exception occurred: " + e.getMessage());
            }
        }

        try {
            handler.checkSize();
            
        } catch (ArraySizeException e) {
            System.out.println("Exception occurred: " + e.getMessage());
        }
        handler.sort();
            handler.printSortedArray();
    }
}
