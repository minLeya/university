import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.util.Random;

public class Graphics {

    public static void main(String[] args) {

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
    private Choice speedChoice;
    private TextField idTF;
    private TextField speedChangeTF;
    private Button changeSpeedButton;

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

        Panel colorPanel = new Panel(new GridLayout(2, 1));
        Label colorLabel = new Label("Выбор заливки:");
        colorPanel.add(colorLabel);
        colorChoice = new Choice();
        colorChoice.addItem("Синий");
        colorChoice.addItem("Зелёный");
        colorChoice.addItem("Красный");
        colorChoice.addItem("Чёрный");
        colorChoice.addItem("Жёлтый");
        colorChoice.addItemListener(this);
        colorPanel.add(colorChoice);
        mainWindow.add(colorPanel);

        Panel figureChoicePanel = new Panel(new GridLayout(2, 1));
        Label figureChoiceLabel = new Label("Выбор фигуры: ");
        figureChoicePanel.add(figureChoiceLabel);
        figureChoice = new Choice();
        figureChoice.addItem("Круг");
        figureChoice.addItem("Овал");
        figureChoice.addItem("Треугольник");
        figureChoice.addItem("Квадрат");
        figureChoice.addItem("Прямоугольник");
        figureChoice.addItemListener(this);
        figureChoicePanel.add(figureChoice);
        mainWindow.add(figureChoicePanel);

        Panel speedChoicePanel = new Panel(new GridLayout(2, 1));
        Label speedChoiceLabel = new Label("Скорость: ");
        speedChoicePanel.add(speedChoiceLabel);
        speedChoice = new Choice();
        speedChoice.addItem("Очень медленно");
        speedChoice.addItem("Медленно");
        speedChoice.addItem("Средне");
        speedChoice.addItem("Быстро");
        speedChoice.addItem("Очень быстро");
        speedChoice.addItem("max");
        speedChoicePanel.add(speedChoice);
        mainWindow.add(speedChoicePanel);

        Panel idPanel = new Panel(new GridLayout(2, 1));
        Label idLabel = new Label("ID: ");
        idPanel.add(idLabel);
        idTF = new TextField();
        idPanel.add(idTF);
        mainWindow.add(idPanel);

        Panel speedChangePanel = new Panel(new GridLayout(2, 1));
        Label speedChangeLabel = new Label("Скорость: ");
        speedChangePanel.add(speedChangeLabel);
        speedChangeTF = new TextField();
        speedChangePanel.add(speedChangeTF);
        mainWindow.add(speedChangePanel);

        changeSpeedButton = new Button("Изменить скорость");
        changeSpeedButton.setActionCommand("ChangeSpeed");
        changeSpeedButton.addActionListener(this);
        mainWindow.add(changeSpeedButton);

        mainWindow.setVisible(true);
        this.setSize(500, 200);
        this.setVisible(true);
        this.setLocation(100, 150);
    }

    public void update(Observable o, Object arg) {
        Figure figure = (Figure) arg;
        System.out.println("x= " + figure.thread.getName() + figure.x);
        repaint();
    }

    public void paint(java.awt.Graphics g) {
        int figureCount = 0;
        for (Figure figure : LL) {
            if (figureCount < SIZE) {
                g.setColor(figure.color);
                if (figure.name.equals("Круг")) {
                    g.drawOval(figure.x, figure.y, 20, 20);
                    g.fillOval(figure.x, figure.y, 20, 20);
                } else if (figure.name.equals("Овал")) {
                    g.drawOval(figure.x, figure.y, 30, 20);
                    g.fillOval(figure.x, figure.y, 30, 20);
                } else if (figure.name.equals("Треугольник")) {
                    int[] xPoints = {figure.x + 10, figure.x + 20, figure.x};
                    int[] yPoints = {figure.y, figure.y + 20, figure.y + 20};
                    g.drawPolygon(xPoints, yPoints, 3);
                    g.fillPolygon(xPoints, yPoints, 3);
                } else if (figure.name.equals("Прямоугольник")) {
                    g.drawRect(figure.x, figure.y, 30, 20);
                    g.fillRect(figure.x, figure.y, 30, 20);
                } else if (figure.name.equals("Квадрат")) {
                    g.drawRect(figure.x, figure.y, 20, 20);
                    g.fillRect(figure.x, figure.y, 20, 20);
                }
                g.setColor(Color.BLACK);
                g.drawString(Integer.toString(figure.id), figure.x + 5, figure.y - 5);

                figureCount++;
            } else break;
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
                    addFigure("Круг");
                    break;
                case 1:
                    addFigure("Овал");
                    break;
                case 2:
                    addFigure("Треугольник");
                    break;
                case 3:
                    addFigure("Квадрат");
                    break;
                case 4:
                    addFigure("Прямоугольник");
                    break;
            }
        } else if (str.equals("ChangeSpeed")) {
            try {
                int figureId = Integer.parseInt(idTF.getText());
                int newSpeed = Integer.parseInt(speedChangeTF.getText());
                changeFigureSpeed(figureId, newSpeed);
            } catch (NumberFormatException | NullPointerException ex) {
                ex.printStackTrace();
            }
        }

        repaint();
    }

    private void changeFigureSpeed(int figureId, int newSpeed) {
        for (Figure figure : LL) {
            if (figure.id == figureId) {
                figure.setDelay(newSpeed);
                break;
            }
        }
    }

    private int getSpeed() {
        int delay = 0;
        switch (speedChoice.getSelectedIndex()) {
            case 0:
                delay = 100;
                break;
            case 1:
                delay = 50;
                break;
            case 2:
                delay = 20;
                break;
            case 3:
                delay = 10;
                break;
            case 4:
                delay = 5;
                break;
            case 5:
                delay = 3;
                break;
        }
        return delay;
    }

    private void addFigure(String name) {
        int delay = getSpeed();
        Figure figure = new Figure(color, name, delay);
        LL.add(figure);
        figure.addObserver(this);
    }
}

class Figure extends Observable implements Runnable {
    Thread thread;
    private boolean xplus;
    private boolean yplus;
    int x;
    int y;
    Color color;
    private int delay;
    String name;
    int id;
    private static int idCounter = 0;

    public Figure(Color color, String name, int delay) {
        xplus = true;
        yplus = true;
        x = 0;
        y = 30;
        this.color = color;
        this.name = name;
        this.delay = delay;
        id = idCounter;
        idCounter++;
        thread = new Thread(this, id + ":");
        thread.start();
    }

    public void run() {

        Random random = new Random();

        // случайные начальные координаты
        x = random.nextInt(30) + 20;
        y = random.nextInt(30) + 20;

        // случайные начальные направления
        xplus = random.nextBoolean();
        yplus = random.nextBoolean();

        while (true) {
            if (x == 475) xplus = false;
            if (x == 0) xplus = true;
            if (y == 175) yplus = false;
            if (y == 20) yplus = true;
            if (xplus) x++;
            else x--;
            if (yplus) y++;
            else y--;
            setChanged();
            notifyObservers(this);
            try {
                Thread.sleep(delay);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
    public void setDelay(int delay) {
        this.delay = delay;
    }
}

class WindowAdapter2 extends WindowAdapter {
    public void windowClosing(WindowEvent wE) {
        System.exit(0);
    }
}
