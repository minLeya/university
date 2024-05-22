package lab9;

import java.awt.*;
import java.awt.event.*;
import java.sql.*;
import javax.swing.*;
import javax.swing.table.DefaultTableModel;

public class CLassrooms extends JPanel implements ActionListener {

    private static final int WINDOW_WIDTH = 800;
    private static final int WINDOW_HEIGHT = 600;
    private static final String DB_URL = "jdbc:derby:Classrooms;create=true";
    private static final String USER_NAME = "db_user";
    private static final String USER_PASSWORD = "db_user";
    private Connection conn;
    private DefaultTableModel classroomTableModel;
    private DefaultTableModel responsibleTableModel;
    private JTable classroomTable;
    private JTable responsibleTable;
    private JTextField searchField;
    
    public CLassrooms() {
        setLayout(new BorderLayout());
        
        // Панель управления
        JPanel controlPanel = new JPanel(new FlowLayout());
        JButton showButton = new JButton("Показать все");
        JButton addButton = new JButton("Добавить");
        JButton editButton = new JButton("Редактировать");
        JButton deleteButton = new JButton("Удалить");
        searchField = new JTextField(20);
        JButton searchButton = new JButton("Поиск");
        
        showButton.addActionListener(this);
        addButton.addActionListener(this);
        editButton.addActionListener(this);
        deleteButton.addActionListener(this);
        searchButton.addActionListener(this);
        
        controlPanel.add(showButton);
        controlPanel.add(addButton);
        controlPanel.add(editButton);
        controlPanel.add(deleteButton);
        controlPanel.add(searchField);
        controlPanel.add(searchButton);
        
        add(controlPanel, BorderLayout.NORTH);
        
        // Таблицы данных
        classroomTableModel = new DefaultTableModel(new String[] {"ID", "Здание", "Номер", "Название", "Площадь"}, 0);
        responsibleTableModel = new DefaultTableModel(new String[] {"ID", "Фамилия", "Имя", "Отчество", "Должность", "Телефон", "Возраст", "ID Аудитории"}, 0);
        
        classroomTable = new JTable(classroomTableModel);
        responsibleTable = new JTable(responsibleTableModel);
        
        JSplitPane splitPane = new JSplitPane(JSplitPane.VERTICAL_SPLIT, new JScrollPane(classroomTable), new JScrollPane(responsibleTable));
        splitPane.setDividerLocation(300);
        
        add(splitPane, BorderLayout.CENTER);
        
        // Подключение к базе данных
        try {
            conn = DriverManager.getConnection(DB_URL, USER_NAME, USER_PASSWORD);
            initializeDatabase();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
    
    private void initializeDatabase() throws SQLException {
        Statement stmt = conn.createStatement();
        stmt.executeUpdate("CREATE TABLE CLASSROOM (ID_CLASSROOM INT PRIMARY KEY, BUILDING VARCHAR(30) NOT NULL, CLASSROOM_NUMBER VARCHAR(4) NOT NULL, CLASSROOM_NAME VARCHAR(30) NOT NULL, SQUARE INT NOT NULL)");
        stmt.executeUpdate("CREATE TABLE RESPONSIBLE (ID_RESPONSIBLE INT PRIMARY KEY, SURNAME VARCHAR(30) NOT NULL, NAME VARCHAR(30) NOT NULL, PATRONYMIC VARCHAR(30) NOT NULL, POST VARCHAR(30) NOT NULL, TELEPHONE INT UNIQUE NOT NULL, AGE INT NOT NULL, CLASSROOM_ID INT, FOREIGN KEY (CLASSROOM_ID) REFERENCES CLASSROOM(ID_CLASSROOM))");
    }
    
    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            JFrame frame = new JFrame("Classrooms Management");
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
            frame.add(new CLassrooms());
            frame.setVisible(true);
        });
    }
    
    @Override
    public void actionPerformed(ActionEvent e) {
        String command = e.getActionCommand();
        
        switch (command) {
            case "Показать все":
                showAllData();
                break;
            case "Добавить":
                showAddDialog();
                break;
            case "Редактировать":
                showEditDialog();
                break;
            case "Удалить":
                deleteSelectedData();
                break;
            case "Поиск":
                searchInTable();
                break;
        }
    }
    
    private void showAllData() {
        try {
            classroomTableModel.setRowCount(0);
            responsibleTableModel.setRowCount(0);
            
            Statement stmt = conn.createStatement();
            ResultSet rs = stmt.executeQuery("SELECT * FROM CLASSROOM");
            
            while (rs.next()) {
                classroomTableModel.addRow(new Object[] {
                    rs.getInt("ID_CLASSROOM"),
                    rs.getString("BUILDING"),
                    rs.getString("CLASSROOM_NUMBER"),
                    rs.getString("CLASSROOM_NAME"),
                    rs.getInt("SQUARE")
                });
            }
            
            rs = stmt.executeQuery("SELECT * FROM RESPONSIBLE");
            
            while (rs.next()) {
                responsibleTableModel.addRow(new Object[] {
                    rs.getInt("ID_RESPONSIBLE"),
                    rs.getString("SURNAME"),
                    rs.getString("NAME"),
                    rs.getString("PATRONYMIC"),
                    rs.getString("POST"),
                    rs.getInt("TELEPHONE"),
                    rs.getInt("AGE"),
                    rs.getInt("CLASSROOM_ID")
                });
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
    
    private void showAddDialog() {
        JDialog dialog = new JDialog((Frame) null, "Добавить запись", true);
        dialog.setLayout(new GridLayout(0, 2));
        
        JTextField idField = new JTextField();
        JTextField buildingField = new JTextField();
        JTextField classroomNumberField = new JTextField();
        JTextField classroomNameField = new JTextField();
        JTextField squareField = new JTextField();
        
        dialog.add(new JLabel("ID:"));
        dialog.add(idField);
        dialog.add(new JLabel("Здание:"));
        dialog.add(buildingField);
        dialog.add(new JLabel("Номер:"));
        dialog.add(classroomNumberField);
        dialog.add(new JLabel("Название:"));
        dialog.add(classroomNameField);
        dialog.add(new JLabel("Площадь:"));
        dialog.add(squareField);
        
        JButton addButton = new JButton("Добавить");
        addButton.addActionListener(e -> {
            try {
                PreparedStatement stmt = conn.prepareStatement("INSERT INTO CLASSROOM (ID_CLASSROOM, BUILDING, CLASSROOM_NUMBER, CLASSROOM_NAME, SQUARE) VALUES (?, ?, ?, ?, ?)");
                stmt.setInt(1, Integer.parseInt(idField.getText()));
                stmt.setString(2, buildingField.getText());
                stmt.setString(3, classroomNumberField.getText());
                stmt.setString(4, classroomNameField.getText());
                stmt.setInt(5, Integer.parseInt(squareField.getText()));
                stmt.executeUpdate();
                dialog.dispose();
                showAllData();
            } catch (SQLException ex) {
                ex.printStackTrace();
            }
        });
        
        dialog.add(addButton);
        dialog.pack();
        dialog.setVisible(true);
    }
    
    private void showEditDialog() {
        int selectedRow = classroomTable.getSelectedRow();
        if (selectedRow == -1) {
            JOptionPane.showMessageDialog(this, "Пожалуйста, выберите запись для редактирования", "Ошибка", JOptionPane.ERROR_MESSAGE);
            return;
        }
        
        JDialog dialog = new JDialog((Frame) null, "Редактировать запись", true);
        dialog.setLayout(new GridLayout(0, 2));
        
        JTextField idField = new JTextField(classroomTableModel.getValueAt(selectedRow, 0).toString());
        JTextField buildingField = new JTextField(classroomTableModel.getValueAt(selectedRow, 1).toString());
        JTextField classroomNumberField = new JTextField(classroomTableModel.getValueAt(selectedRow, 2).toString());
        JTextField classroomNameField = new JTextField(classroomTableModel.getValueAt(selectedRow, 3).toString());
        JTextField squareField = new JTextField(classroomTableModel.getValueAt(selectedRow, 4).toString());
        
        dialog.add(new JLabel("ID:"));
        dialog.add(idField);
        dialog.add(new JLabel("Здание:"));
        dialog.add(buildingField);
        dialog.add(new JLabel("Номер:"));
        dialog.add(classroomNumberField);
        dialog.add(new JLabel("Название:"));
        dialog.add(classroomNameField);
        dialog.add(new JLabel("Площадь:"));
        dialog.add(squareField);
        
        JButton editButton = new JButton("Сохранить");
        editButton.addActionListener(e -> {
            try {
                PreparedStatement stmt = conn.prepareStatement("UPDATE CLASSROOM SET BUILDING=?, CLASSROOM_NUMBER=?, CLASSROOM_NAME=?, SQUARE=? WHERE ID_CLASSROOM=?");
                stmt.setString(1, buildingField.getText());
                stmt.setString(2, classroomNumberField.getText());
                stmt.setString(3, classroomNameField.getText());
                stmt.setInt(4, Integer.parseInt(squareField.getText()));
                stmt.setInt(5, Integer.parseInt(idField.getText()));
                stmt.executeUpdate();
                dialog.dispose();
                showAllData();
            } catch (SQLException ex) {
                ex.printStackTrace();
            }
        });
        
        dialog.add(editButton);
        dialog.pack();
        dialog.setVisible(true);
    }
    
    private void deleteSelectedData() {
        int selectedRow = classroomTable.getSelectedRow();
        if (selectedRow == -1) {
            JOptionPane.showMessageDialog(this, "Пожалуйста, выберите запись для удаления", "Ошибка", JOptionPane.ERROR_MESSAGE);
            return;
        }
        
        try {
            int id = (int) classroomTableModel.getValueAt(selectedRow, 0);
            PreparedStatement stmt = conn.prepareStatement("DELETE FROM CLASSROOM WHERE ID_CLASSROOM=?");
            stmt.setInt(1, id);
            stmt.executeUpdate();
            showAllData();
        } catch (SQLException ex) {
            ex.printStackTrace();
        }
    }
    
    private void searchInTable() {
        String searchText = searchField.getText();
        
        try {
            classroomTableModel.setRowCount(0);
            responsibleTableModel.setRowCount(0);
            
            PreparedStatement stmt = conn.prepareStatement("SELECT * FROM CLASSROOM WHERE BUILDING LIKE ? OR CLASSROOM_NUMBER LIKE ? OR CLASSROOM_NAME LIKE ? OR SQUARE LIKE ?");
            String queryText = "%" + searchText + "%";
            stmt.setString(1, queryText);
            stmt.setString(2, queryText);
            stmt.setString(3, queryText);
            stmt.setString(4, queryText);
            ResultSet rs = stmt.executeQuery();
            
            while (rs.next()) {
                classroomTableModel.addRow(new Object[] {
                    rs.getInt("ID_CLASSROOM"),
                    rs.getString("BUILDING"),
                    rs.getString("CLASSROOM_NUMBER"),
                    rs.getString("CLASSROOM_NAME"),
                    rs.getInt("SQUARE")
                });
            }
            
            stmt = conn.prepareStatement("SELECT * FROM RESPONSIBLE WHERE SURNAME LIKE ? OR NAME LIKE ? OR PATRONYMIC LIKE ? OR POST LIKE ? OR TELEPHONE LIKE ? OR AGE LIKE ? OR CLASSROOM_ID LIKE ?");
            stmt.setString(1, queryText);
            stmt.setString(2, queryText);
            stmt.setString(3, queryText);
            stmt.setString(4, queryText);
            stmt.setString(5, queryText);
            stmt.setString(6, queryText);
            stmt.setString(7, queryText);
            rs = stmt.executeQuery();
            
            while (rs.next()) {
                responsibleTableModel.addRow(new Object[] {
                    rs.getInt("ID_RESPONSIBLE"),
                    rs.getString("SURNAME"),
                    rs.getString("NAME"),
                    rs.getString("PATRONYMIC"),
                    rs.getString("POST"),
                    rs.getInt("TELEPHONE"),
                    rs.getInt("AGE"),
                    rs.getInt("CLASSROOM_ID")
                });
            }
        } catch (SQLException ex) {
            ex.printStackTrace();
        }
    }
}
