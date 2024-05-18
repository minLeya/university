import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

@WebServlet(urlPatterns = {"/OneServlet"})
public class OneServlet extends HttpServlet {
    static String ast;
    static boolean b;
    static long counter;
    static int cycle;
    static int textSize;
    static final int MIN_TEXT_SIZE = 8;
    static final int MAX_TEXT_SIZE = 16;

    public OneServlet() {
        OneServlet.ast = "a static var c=";
        OneServlet.b = false;
        OneServlet.counter = 0;
        OneServlet.cycle = 0;
        OneServlet.textSize = MAX_TEXT_SIZE;
    }

    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");

        // Получение параметров из запроса
        String resetSize = request.getParameter("resetSize"); // параметр для сброса размера текста
        String resetToSize = request.getParameter("resetToSize"); // параметр для установки размера текста
        String  studentName = request.getParameter("name");
        String studentGroup = request.getParameter("group");
        String numbers = request.getParameter("numbers");

        // Изменение размера текста
        if ("true".equalsIgnoreCase(resetSize)) {
            OneServlet.textSize = MAX_TEXT_SIZE; // Установка максимального размера текста
        } else if (OneServlet.textSize > MIN_TEXT_SIZE) {
            OneServlet.textSize--; // Уменьшение размера текста
        }

        // сброс размера текста 
        if (resetToSize != null) {
            try {
                int newSize = Integer.parseInt(resetToSize);
                if (newSize >= MIN_TEXT_SIZE && newSize <= MAX_TEXT_SIZE) {
                    OneServlet.textSize = newSize;
                }
            } catch (NumberFormatException e) {
                // Игнорируем неверные значения resetToSize
            }
        } else if ("true".equalsIgnoreCase(resetSize)) {
            OneServlet.textSize = MAX_TEXT_SIZE; // Установка максимального размера текста
        } else if (OneServlet.textSize > MIN_TEXT_SIZE) {
            OneServlet.textSize--; // Уменьшение размера текста
        }
        
        // Изменение триггера
        OneServlet.b = !OneServlet.b;
        OneServlet.counter++;
        OneServlet.cycle = (OneServlet.cycle % 5) + 1;

        try (PrintWriter out = response.getWriter()) {
            out.println("<!DOCTYPE html>");
            out.println("<html>");
            out.println("<head>");
            out.println("<title>Servlet OneServlet</title>");
            out.println("</head>");
            out.println("<body>");

            // Отображение фио и номера группы
            if (studentName != null && studentGroup != null) {
                out.println("<p>Ф.И.О: " + studentName + "</p>");
                out.println("<p>Группа: " + studentGroup + "</p>");
            }

            // Отображение состояния триггера
            out.println("<h1>Servlet OneServlet at " + request.getContextPath() + "</h1>");
            out.println("<h3>OneServlet.ast + OneServlet.b: " + OneServlet.ast + OneServlet.b + "</h3>");
            out.println("<h3>OneServlet.counter: " + OneServlet.counter + "</h3>");
            out.println("<h3>OneServlet.cycle: " + OneServlet.cycle + "</h3>");

            // Таблица результатов
            String[][] tbl = new String[3][3];
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    tbl[i][j] = Integer.toString(i + 1) + "&" + Integer.toString(j + 1);
                }
            }
            String prm1 = request.getParameter("prm1");
            String prm2 = request.getParameter("prm2");
            String prm3 = request.getParameter("prm3");

            out.println("<h" + OneServlet.cycle + "><table style='border:1px solid black; border-collapse:collapse; font-size:" + OneServlet.textSize + "px;'>"
                    + "<tr><td>" + tbl[0][0] + "</td><td>prm1=" + prm1 + "</td><td>1.3</td></tr>"
                    + "<tr><td>prm2=" + prm2 + "</td><td>pr2</td><td>2.3</td></tr>"
                    + "<tr><td>prm3=" + prm3 + "</td><td>3.2</td><td>" + tbl[2][2] + "</td></tr>"
                    + "</table></h" + OneServlet.cycle + ">");

            // Информирование о минимальном размере текста
            if (OneServlet.textSize <= MIN_TEXT_SIZE) {
                out.println("<p>Дальнейшее уменьшение размера текста невозможно</p>");
            }

            // Сортировка и вывод последовательности чисел
            if (numbers != null && !numbers.trim().isEmpty()) {
                String[] numberStrings = numbers.split(",");
                int[] numberArray = new int[numberStrings.length];
                for (int i = 0; i < numberStrings.length; i++) {
                    numberArray[i] = Integer.parseInt(numberStrings[i].trim());
                }
                Arrays.sort(numberArray);
                out.println("<p>Отсортированный список чисел: " + Arrays.toString(numberArray) + "</p>");
            }

            out.println("</body>");
            out.println("</html>");
        }
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }

    @Override
    public String getServletInfo() {
        return "Short description";
    }
}
