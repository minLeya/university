import java.util.ArrayList;
import java.util.Collections;
//Дана последовательность целых чисел.
// Вывести отсортированный список в порядке возрастания.
public class Main {
    public static void main(String args[])
    {
        ArrayList<Integer> list = new ArrayList<>();
        for (String x : args)
        {
            list.add(Integer.parseInt(x));
        }
        Collections.sort(list);
        System.out.println(list);
    }
}
