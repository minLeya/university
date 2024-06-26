package lab9;

import java.awt.*;
import java.awt.event.*;
import java.sql.*;
import javax.swing.*;
import javax.swing.table.DefaultTableModel;

public class CLassrooms extends JPanel implements ActionListener {

    private static final int WINDOW_WIDTH = 800;
    private static final int WINDOW_HEIGHT = 600;
    private static final String DB_URL = "jdbc:derby:class;create=true";
    private static final String USER_NAME = "db_user";
    private static final String USER_PASSWORD = "db_user";
    private Connection conn;
    private DefaultTableModel classroomTableModel;
    private DefaultTableModel responsibleTableModel;
    private JTable classroomTable;
    private JTable responsibleTable;
    
    // дефолтные занчения для таблицы CLASSROOM
    private static final String DEFAULT_BUILDING = "Default Building";
    private static final String DEFAULT_CLASSROOM_NUMBER = "000";
    private static final String DEFAULT_CLASSROOM_NAME = "Default Name";
    private static final int DEFAULT_SQUARE = 50;

    // дефолтные занчения для таблицы RESPONSIBLE 
    private static final String DEFAULT_SURNAME = "Default Surname";
    private static final String DEFAULT_NAME = "Default Name";
    private static final String DEFAULT_PATRONYMIC = "Default Patronymic";
    private static final String DEFAULT_POST = "Default Post";
    private static final int DEFAULT_TELEPHONE = 1234567890;
    private static final int DEFAULT_AGE = 30;

 
    // конструктор
    public CLassrooms() {
        setLayout(new BorderLayout());
        
        // Панель управления
        JPanel controlPanel = new JPanel(new FlowLayout());
        JButton showButton = new JButton("Показать все");
        JButton addButton = new JButton("Добавить");
        JButton editButton = new JButton("Редактировать");
        JButton deleteButton = new JButton("Удалить");
        JButton resetButton = new JButton("Дефолтные значения");
        JButton buildingSortButton = new JButton("Сортировать по зданиям");
        JButton phoneDirectoryButton = new JButton("Телефонный справочник");
        JButton averageAreaButton = new JButton("Средняя площадь ответственных");
        
        
        showButton.addActionListener(this);
        addButton.addActionListener(this);
        editButton.addActionListener(this);
        deleteButton.addActionListener(this);
        buildingSortButton.addActionListener(this);
        phoneDirectoryButton.addActionListener(this);
        averageAreaButton.addActionListener(this);
        resetButton.addActionListener(this);
        
        controlPanel.add(showButton);
        controlPanel.add(addButton);
        controlPanel.add(editButton);
        controlPanel.add(deleteButton);
        controlPanel.add(buildingSortButton);
        controlPanel.add(phoneDirectoryButton);
        controlPanel.add(averageAreaButton);
        controlPanel.add(resetButton);
        
        add(controlPanel, BorderLayout.NORTH);
        
        // Таблицы данных
        classroomTableModel = new DefaultTableModel(new String[] {"ID", "Здание", "Номер", "Название", "Площадь"}, 0);
        responsibleTableModel = new DefaultTableModel(new String[] {"ID", "Фамилия", "Имя", "Отчество", "Должность", "Телефон", "Возраст"}, 0);
        
        classroomTable = new JTable(classroomTableModel);
        responsibleTable = new JTable(responsibleTableModel);
        
        JSplitPane splitPane = new JSplitPane(JSplitPane.VERTICAL_SPLIT, new JScrollPane(classroomTable), new JScrollPane(responsibleTable));
        splitPane.setDividerLocation(300);
        
        add(splitPane, BorderLayout.CENTER);
        
        // Подключение к базе данных
        try {
            conn = DriverManager.getConnection(DB_URL, USER_NAME, USER_PASSWORD);
        } catch (SQLException e) {
            e.printStackTrace();
        }
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
            case "Сортировать по зданиям":
                buildingSort();
                break;
            case "Телефонный справочник":
                showPhoneDirectory();
                break;
            case "Средняя площадь ответственных":
                showAverageArea();
                break;
            case "Дефолтные значения":
                defaultValues();
                break;
        }
    }
    
    // вывод  всех записей - сделано
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
    
    // добавление записей - сделано
    private void showAddDialog() {
        JDialog dialog = new JDialog((Frame) null, "Добавить запись", true);
        dialog.setLayout(new GridLayout(0, 2));
        
        JTextField buildingField = new JTextField();
        JTextField classroomNumberField = new JTextField();
        JTextField classroomNameField = new JTextField();
        JTextField squareField = new JTextField();
        JTextField surnameField = new JTextField();
        JTextField nameField = new JTextField();
        JTextField patronymicField = new JTextField();
        JTextField postField = new JTextField();
        JTextField telephoneField = new JTextField();
        JTextField ageField = new JTextField();

        dialog.add(new JLabel("Здание:"));
        dialog.add(buildingField);
        dialog.add(new JLabel("Номер аудит.:"));
        dialog.add(classroomNumberField);
        dialog.add(new JLabel("Название:"));
        dialog.add(classroomNameField);
        dialog.add(new JLabel("Площадь:"));
        dialog.add(squareField);
        dialog.add(new JLabel("Фамилия:"));
        dialog.add(surnameField);
        dialog.add(new JLabel("Имя:"));
        dialog.add(nameField);
        dialog.add(new JLabel("Отчество:"));
        dialog.add(patronymicField);
        dialog.add(new JLabel("Должность:"));
        dialog.add(postField);
        dialog.add(new JLabel("Телефон:"));
        dialog.add(telephoneField);
        dialog.add(new JLabel("Возраст:"));
        dialog.add(ageField);
        
        JButton addButton = new JButton("Добавить");
        addButton.addActionListener(e -> {
            try {
                int classroomId = generateUniqueId("CLASSROOM", "ID_CLASSROOM");

                PreparedStatement stmt = conn.prepareStatement("INSERT INTO CLASSROOM (ID_CLASSROOM, BUILDING, CLASSROOM_NUMBER, CLASSROOM_NAME, SQUARE) VALUES (?, ?, ?, ?, ?)");
                stmt.setInt(1, classroomId);
                stmt.setString(2, buildingField.getText());
                stmt.setString(3, classroomNumberField.getText());
                stmt.setString(4, classroomNameField.getText());
                stmt.setInt(5, Integer.parseInt(squareField.getText()));
                stmt.executeUpdate();
                
                PreparedStatement stmtResponsible = conn.prepareStatement("INSERT INTO RESPONSIBLE (ID_RESPONSIBLE, SURNAME, NAME, PATRONYMIC, POST, TELEPHONE, AGE) VALUES (?, ?, ?, ?, ?, ?, ?)");
                stmtResponsible.setInt(1, classroomId);
                stmtResponsible.setString(2, surnameField.getText());
                stmtResponsible.setString(3, nameField.getText());
                stmtResponsible.setString(4, patronymicField.getText());
                stmtResponsible.setString(5, postField.getText());
                stmtResponsible.setInt(6, Integer.parseInt(telephoneField.getText()));
                stmtResponsible.setInt(7, Integer.parseInt(ageField.getText()));
                stmtResponsible.executeUpdate();
                
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

    private int generateUniqueId(String tableName, String columnName) throws SQLException {
        Statement stmt = conn.createStatement();
        ResultSet rs = stmt.executeQuery("SELECT MAX(" + columnName + ") FROM " + tableName);
        if (rs.next()) {
            return rs.getInt(1) + 1;
        } else {
            return 1;
        }
}

    // редактирование записи - сделано
    private void showEditDialog() {
        int selectedRow = classroomTable.getSelectedRow();
        if (selectedRow == -1) {
            JOptionPane.showMessageDialog(this, "Пожалуйста, выберите запись для редактирования", "Ошибка", JOptionPane.ERROR_MESSAGE);
            return;
        }

        int classroomId = Integer.parseInt(classroomTableModel.getValueAt(selectedRow, 0).toString());

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

        JTextField surnameField = new JTextField();
        JTextField nameField = new JTextField();
        JTextField patronymicField = new JTextField();
        JTextField postField = new JTextField();
        JTextField telephoneField = new JTextField();
        JTextField ageField = new JTextField();

        try {
            PreparedStatement stmt = conn.prepareStatement("SELECT * FROM RESPONSIBLE WHERE ID_RESPONSIBLE = ?");
            stmt.setInt(1, classroomId);
            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                surnameField.setText(rs.getString("SURNAME"));
                nameField.setText(rs.getString("NAME"));
                patronymicField.setText(rs.getString("PATRONYMIC"));
                postField.setText(rs.getString("POST"));
                telephoneField.setText(rs.getString("TELEPHONE"));
                ageField.setText(rs.getString("AGE"));
            }
        } catch (SQLException ex) {
            ex.printStackTrace();
        }

        dialog.add(new JLabel("Фамилия:"));
        dialog.add(surnameField);
        dialog.add(new JLabel("Имя:"));
        dialog.add(nameField);
        dialog.add(new JLabel("Отчество:"));
        dialog.add(patronymicField);
        dialog.add(new JLabel("Должность:"));
        dialog.add(postField);
        dialog.add(new JLabel("Телефон:"));
        dialog.add(telephoneField);
        dialog.add(new JLabel("Возраст:"));
        dialog.add(ageField);

        JButton editButton = new JButton("Сохранить");
        editButton.addActionListener(e -> {
            try {
                PreparedStatement stmtClassroom = conn.prepareStatement("UPDATE CLASSROOM SET BUILDING=?, CLASSROOM_NUMBER=?, CLASSROOM_NAME=?, SQUARE=? WHERE ID_CLASSROOM=?");
                stmtClassroom.setString(1, buildingField.getText());
                stmtClassroom.setString(2, classroomNumberField.getText());
                stmtClassroom.setString(3, classroomNameField.getText());
                stmtClassroom.setInt(4, Integer.parseInt(squareField.getText()));
                stmtClassroom.setInt(5, classroomId);
                stmtClassroom.executeUpdate();

                PreparedStatement stmtResponsible = conn.prepareStatement("UPDATE RESPONSIBLE SET SURNAME=?, NAME=?, PATRONYMIC=?, POST=?, TELEPHONE=?, AGE=? WHERE ID_RESPONSIBLE=?");
                stmtResponsible.setString(1, surnameField.getText());
                stmtResponsible.setString(2, nameField.getText());
                stmtResponsible.setString(3, patronymicField.getText());
                stmtResponsible.setString(4, postField.getText());
                stmtResponsible.setString(5, telephoneField.getText());
                stmtResponsible.setInt(6, Integer.parseInt(ageField.getText()));
                stmtResponsible.setInt(7, classroomId);
                stmtResponsible.executeUpdate();

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

    // удаление - сделано
    private void deleteSelectedData() {
            int selectedRow = classroomTable.getSelectedRow();
            int selectedRowResponsible = responsibleTable.getSelectedRow();
            if (selectedRow == -1 || selectedRowResponsible == -1) {
                JOptionPane.showMessageDialog(this, "Пожалуйста, выберите запись для удаления", "Ошибка", JOptionPane.ERROR_MESSAGE);
                return;
            }
            int idClassroom = (int) classroomTableModel.getValueAt(selectedRow, 0);
            int idResponsible = (int) responsibleTableModel.getValueAt(selectedRowResponsible, 0);
            try {
                if (idClassroom == idResponsible){
                    // Начало транзакции
                    conn.setAutoCommit(false);

                    PreparedStatement stmt = conn.prepareStatement("DELETE FROM CLASSROOM WHERE ID_CLASSROOM=?");
                    stmt.setInt(1, idClassroom);
                    stmt.executeUpdate();

                    PreparedStatement stmtResponsible = conn.prepareStatement("DELETE FROM RESPONSIBLE WHERE ID_RESPONSIBLE=?");
                    stmtResponsible.setInt(1, idResponsible);
                    stmtResponsible.executeUpdate();

                    // Завершение транзакции
                    conn.commit();

                    showAllData();
                }
                else {
                    JOptionPane.showMessageDialog(this, "Пожалуйста, выберите записи с одним ID", "Ошибка", JOptionPane.ERROR_MESSAGE);
                }

            } catch (SQLException ex) {
                try {
                    // Откат транзакции в случае ошибки
                    conn.rollback();
                } catch (SQLException rollbackEx) {
                    rollbackEx.printStackTrace();
                }
                ex.printStackTrace();
            } finally {
                try {
                    conn.setAutoCommit(true);
                } catch (SQLException ex) {
                    ex.printStackTrace();
                }
            }
        }
    
    // сортировка зданий - сделано
    private void buildingSort() {
        try {
            String query = "SELECT BUILDING FROM CLASSROOM ORDER BY BUILDING";
            PreparedStatement stmt = conn.prepareStatement(query);
            ResultSet rs = stmt.executeQuery();

            DefaultTableModel buildingTableModel = new DefaultTableModel(new String[]{"Здание"}, 0);

            while (rs.next()) {
                buildingTableModel.addRow(new Object[]{rs.getString("BUILDING")});
            }

            JTable buildingTable = new JTable(buildingTableModel);

            JScrollPane scrollPane = new JScrollPane(buildingTable);

            JDialog dialog = new JDialog((Frame) null, "Сортировка зданий", true);
            dialog.setLayout(new BorderLayout());
            dialog.add(scrollPane, BorderLayout.CENTER);

            dialog.setSize(300, 400);
            dialog.setVisible(true);

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
    
    // телефонный справочник - сделано
    private void showPhoneDirectory() {
        try {
            String query = "SELECT SURNAME, NAME, PATRONYMIC, TELEPHONE FROM RESPONSIBLE ORDER BY SURNAME, NAME, PATRONYMIC";
            PreparedStatement stmt = conn.prepareStatement(query);
            ResultSet rs = stmt.executeQuery();

            DefaultTableModel phoneDirectoryModel = new DefaultTableModel(new String[]{"Фамилия", "Имя", "Отчество", "Телефон"}, 0);

            while (rs.next()) {
                phoneDirectoryModel.addRow(new Object[]{
                    rs.getString("SURNAME"),
                    rs.getString("NAME"),
                    rs.getString("PATRONYMIC"),
                    rs.getString("TELEPHONE")
                });
            }

            JTable phoneDirectoryTable = new JTable(phoneDirectoryModel);

            JScrollPane scrollPane = new JScrollPane(phoneDirectoryTable);

            JDialog dialog = new JDialog((Frame) null, "Телефонный справочник", true);
            dialog.setLayout(new BorderLayout());
            dialog.add(scrollPane, BorderLayout.CENTER);

            dialog.setSize(500, 400);
            dialog.setVisible(true);

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    // средняя площадь - сделано
    private void showAverageArea() {
        try {
            Statement stmt = conn.createStatement();
            ResultSet rs = stmt.executeQuery("SELECT SQUARE FROM CLASSROOM");

            int totalSquare = 0;
            int responsibleCount = 0;

            while (rs.next()) {
                totalSquare += rs.getInt("SQUARE");
                responsibleCount++;
            }

            if (responsibleCount > 0) {
                double averageSquare = (double) totalSquare / responsibleCount;
                JOptionPane.showMessageDialog(this, "Средняя площадь, закрепленная за ответственными: " + averageSquare, "Средняя площадь", JOptionPane.INFORMATION_MESSAGE);
            } else {
                JOptionPane.showMessageDialog(this, "Нет данных о площадях, закрепленных за ответственными", "Средняя площадь", JOptionPane.INFORMATION_MESSAGE);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    // сброс к дефолтным значениям - сделано
    private void defaultValues() {
        int selectedClassroomRow = classroomTable.getSelectedRow();
        int selectedResponsibleRow = responsibleTable.getSelectedRow();

        if (selectedClassroomRow == -1  || selectedResponsibleRow == -1) {
            JOptionPane.showMessageDialog(this, "Пожалуйста, выберите запись для сброса", "Ошибка", JOptionPane.ERROR_MESSAGE);
            return;
        }

        try {
            if (selectedClassroomRow != -1) {
                int classroomId = (int) classroomTableModel.getValueAt(selectedClassroomRow, 0);

                String updateClassroomSQL = "UPDATE CLASSROOM SET BUILDING = ?, CLASSROOM_NUMBER = ?, CLASSROOM_NAME = ?, SQUARE = ? WHERE ID_CLASSROOM = ?";
                PreparedStatement stmtClassroom = conn.prepareStatement(updateClassroomSQL);
                stmtClassroom.setString(1, DEFAULT_BUILDING);
                stmtClassroom.setString(2, DEFAULT_CLASSROOM_NUMBER);
                stmtClassroom.setString(3, DEFAULT_CLASSROOM_NAME);
                stmtClassroom.setInt(4, DEFAULT_SQUARE);
                stmtClassroom.setInt(5, classroomId);
                stmtClassroom.executeUpdate();
            }

            if (selectedResponsibleRow != -1) {
                int responsibleId = (int) responsibleTableModel.getValueAt(selectedResponsibleRow, 0);

                String updateResponsibleSQL = "UPDATE RESPONSIBLE SET SURNAME = ?, NAME = ?, PATRONYMIC = ?, POST = ?, TELEPHONE = ?, AGE = ? WHERE ID_RESPONSIBLE = ?";
                PreparedStatement stmtResponsible = conn.prepareStatement(updateResponsibleSQL);
                stmtResponsible.setString(1, DEFAULT_SURNAME);
                stmtResponsible.setString(2, DEFAULT_NAME);
                stmtResponsible.setString(3, DEFAULT_PATRONYMIC);
                stmtResponsible.setString(4, DEFAULT_POST);
                stmtResponsible.setInt(5, DEFAULT_TELEPHONE);
                stmtResponsible.setInt(6, DEFAULT_AGE);
                stmtResponsible.setInt(7, responsibleId);
                stmtResponsible.executeUpdate();
            }

            showAllData();

            JOptionPane.showMessageDialog(this, "Запись сброшена к значениям по умолчанию", "Сброс значений", JOptionPane.INFORMATION_MESSAGE);
        } catch (SQLException e) {
            e.printStackTrace();
            JOptionPane.showMessageDialog(this, "Ошибка при сбросе значений по умолчанию", "Ошибка", JOptionPane.ERROR_MESSAGE);
        }
    }
}


/*
   private void deleteSelectedData() {
        try {
            // Удаляем все записи из таблицы CLASSROOM
            String deleteClassroomSQL = "DELETE FROM CLASSROOM";
            PreparedStatement stmtClassroom = conn.prepareStatement(deleteClassroomSQL);
            stmtClassroom.executeUpdate();

            // Удаляем все записи из таблицы RESPONSIBLE
            String deleteResponsibleSQL = "DELETE FROM RESPONSIBLE";
            PreparedStatement stmtResponsible = conn.prepareStatement(deleteResponsibleSQL);
            stmtResponsible.executeUpdate();

            // Обновление данных в таблицах на форме
            showAllData();

            JOptionPane.showMessageDialog(this, "Все записи удалены из обеих таблиц", "Удаление записей", JOptionPane.INFORMATION_MESSAGE);
        } catch (SQLException e) {
            e.printStackTrace();
            JOptionPane.showMessageDialog(this, "Ошибка при удалении записей", "Ошибка", JOptionPane.ERROR_MESSAGE);
        }
    }

*/
