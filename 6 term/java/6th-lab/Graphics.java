import java.awt.*;
import java.awt.event.*;
import java.util.*;

public class Graphics {
    static int count;

    public static void main(String[] args) {
        count = 0;
        Figures figures = new Figures();
    }
}

class Figures extends Frame implements Observer, ActionListener, ItemListener {
    private final int SIZE = 7;

    private LinkedList<Figure> LL = new LinkedList<>();
    private Color color;
    private Frame mainWindow;
    private Button button;
    private Choice colorChoice;
    private Choice figureChoice;
    private Choice fillChoice;
    private TextField tf;

    Figures() {
        this.addWindowListener(new WindowAdapter2());
        mainWindow = new Frame();
        mainWindow.setSize(new Dimension(300, 100));
        mainWindow.setTitle("Контроль");
        mainWindow.setLayout(new GridLayout());
        mainWindow.addWindowListener(new WindowAdapter2());
        
        button = new Button("Пуск");
        button.setSize(new Dimension(10, 40));
        button.setActionCommand("OK");
        button.addActionListener(this);
        mainWindow.add(button, new Point(20, 20));
        
        colorChoice = new Choice();
        colorChoice.addItem("Синий");
        colorChoice.addItem("Зелёный");
        colorChoice.addItem("Красный");
        colorChoice.addItem("Чёрный");
        colorChoice.addItem("Жёлтый");
        colorChoice.addItemListener(this);
        mainWindow.add(colorChoice, new Point(60, 20));

        figureChoice = new Choice();
        figureChoice.addItem("Круг");
        figureChoice.addItem("Овал");
        figureChoice.addItem("Треугольник");
        figureChoice.addItem("Квадрат");
        figureChoice.addItem("Прямоугольник");
        figureChoice.addItemListener(this);
        mainWindow.add(figureChoice, new Point(60, 20));

        fillChoice = new Choice();
        fillChoice.addItem("Синий");
        fillChoice.addItem("Зелёный");
        fillChoice.addItem("Красный");
        fillChoice.addItem("Чёрный");
        fillChoice.addItem("Жёлтый");
        mainWindow.add(fillChoice, new Point(60, 40));

        tf = new TextField();
        mainWindow.add(tf);
        mainWindow.setVisible(true);
        this.setSize(500, 200);
        this.setVisible(true);
        this.setLocation(100, 150);
    }

    public void update(Observable o, Object arg) {
        Figure figure = (Figure) arg;
        System.out.println("x= " + figure.thr.getName() + figure.x);
        repaint();
    }

    public void paint(java.awt.Graphics g) {
        int figureCount = 0;
        for (Figure figure : LL) {
            if (figureCount < SIZE) {
                g.setColor(figure.color);
                if (figure.name.equals("Круг")) {
                    g.drawOval(figure.x, figure.y, 20, 20);
                }
                else if (figure.name.equals("Овал")) {
                    g.drawOval(figure.x, figure.y, 30, 20);
                }
                else if (figure.name.equals("Треугольник")) {
                    int[] xPoints = {figure.x + 10, figure.x + 20, figure.x};
                    int[] yPoints = {figure.y, figure.y + 20, figure.y + 20};
                    g.drawPolygon(xPoints, yPoints, 3);
                }
                else if (figure.name.equals("Прямоугольник")) {
                    g.drawRect(figure.x, figure.y, 30, 20);
                }
                else if (figure.name.equals("Квадрат")){
                    g.drawRect(figure.x, figure.y, 20, 20);
                }
                figureCount++;
            }
            else break;
        }
    }

    public void itemStateChanged(ItemEvent iE) {
    }

    public void actionPerformed(ActionEvent aE) {
        String str = aE.getActionCommand();
        if (str.equals("OK")) {
            switch (colorChoice.getSelectedIndex()) {
                case 0:
                    color = Color.blue;
                    break;
                case 1:
                    color = Color.green;
                    break;
                case 2:
                    color = Color.red;
                    break;
                case 3:
                    color = Color.black;
                    break;
                case 4:
                    color = Color.yellow;
                    break;
            }
            switch (figureChoice.getSelectedIndex()) {
                case 0:
                    addBall("Круг");
                    break;
                case 1:
                    addBall("Овал");
                    break;
                case 2:
                    addBall("Треугольник");
                    break;
                case 3:
                    addBall("Квадрат");
                    break;
                case 4:
                    addBall("Прямоугольник");
                    break;

            }
        }
        repaint();
    }

    private void addBall(String name) {
        Figure figure = new Figure(color, this.tf.getText(), name);
        LL.add(figure);
        figure.addObserver(this);
    }
}

class Figure extends Observable implements Runnable {
    Thread thr;
    private boolean xplus;
    private boolean yplus;
    int x;
    int y;
    Color color;
    String name;

    public Figure(Color color, String text, String name) {
        xplus = true;
        yplus = true;
        x = 0;
        y = 30;
        this.color = color;
        this.name = name;
        Graphics.count++;
        thr = new Thread(this, Graphics.count + ":" + text + ":");
        thr.start();
    }

    public void run() {
        while (true) {
            if (x == 475) xplus = false;
            if (x == -1) xplus = true;
            if (y == 175) yplus = false;
            if (y == 29) yplus = true;
            if (xplus) x++;
            else x--;
            if (yplus) y++;
            else y--;
            setChanged();
            notifyObservers(this);
            try {
                Thread.sleep(10);
            } catch (InterruptedException e) {
            }
        }
    }
}

class WindowAdapter2 extends WindowAdapter {
    public void windowClosing(WindowEvent wE) {
        System.exit(0);
    }
}
