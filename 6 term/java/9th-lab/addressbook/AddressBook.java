package addressbook;

import java.awt.Dialog;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.ResultSet;
import javax.swing.BorderFactory;
import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;
import javax.swing.table.DefaultTableModel;

public class AddressBook extends JPanel implements ActionListener {

    private final int width_window = 400;
    private final int delta_size_dialog = 20;
    private static JFrame mainFrame = null;
    private static String dbURL
            = "jdbc:derby://localhost:1527/databases/AddressBook";
    private static String user_name = "db_user";
    private static String user_password = "db_user";
    private static Connection conn = null;
    private static ResultSet rs = null;
    private static Statement stmt = null;
    private static String SQL = null;
    private JPanel panelControl, panelFind, panelShow;
    private JButton buttonShow;
    private JButton buttonCreate;
    private JButton buttonEdit;
    private JButton buttonDelete;
    private JButton buttonFind;
    private JTextField textFieldFind;
    private DefaultTableModel tableShowModel;
    private JTable tableShow;
    private Object[][] data;
    private JLabel labelFindCol;

    public AddressBook() {
        super();
        try {
            DriverManager.registerDriver(new org.apache.derby.jdbc.EmbeddedDriver());
        } catch (SQLException e) {
        }
        setLayout(new BoxLayout(this, BoxLayout.PAGE_AXIS));
//Создание панели "Управление".
        panelControl = new JPanel();
        panelControl.setPreferredSize(new Dimension(width_window, 60));
        panelControl.setBorder(BorderFactory.createTitledBorder("\"Управление\""));
        add(Box.createRigidArea(new Dimension(0, 10))); // Отступ 10 пикселей
        panelControl.setLayout(new FlowLayout());
        buttonShow = new JButton("Просмотреть");
        buttonShow.addActionListener(this);
        buttonCreate = new JButton("Создать");
        buttonCreate.addActionListener(this);
        buttonEdit = new JButton("Редактировать");
        buttonEdit.addActionListener(this);
        buttonDelete = new JButton("Удалить");
        buttonDelete.addActionListener(this);
        panelControl.add(buttonShow);
        panelControl.add(buttonCreate);
        panelControl.add(buttonEdit);
        panelControl.add(buttonDelete);
        add(panelControl);
//Создание панели "Поиск".
        panelFind = new JPanel();
        panelFind.setPreferredSize(new Dimension(width_window, 50));
        panelFind.setBorder(BorderFactory.createTitledBorder("\"Поиск\""));
        panelFind.setLayout(new GridLayout());
        textFieldFind = new JTextField();
        buttonFind = new JButton("Поиск");
        buttonFind.addActionListener(this);
        panelFind.add(textFieldFind);
        panelFind.add(buttonFind);
        add(Box.createRigidArea(
                new Dimension(0, 10))); // Отступ сверху вниз на 10 пикселей
        add(panelFind);
//Создание панели "Список контактов".
        panelShow = new JPanel();
        panelShow.setPreferredSize(new Dimension(width_window, 130));
        panelShow.setLayout(new BoxLayout(panelShow, BoxLayout.Y_AXIS));
        panelShow.setBorder(BorderFactory.createTitledBorder("\"Список контактов\""));
        add(Box.createRigidArea(
                new Dimension(0, 10))); // Отступ сверху вниз на 10 пикселей
        data = new Object[][]{};
        tableShowModel = new DefaultTableModel(new Object[]{"ФИО", "Телефон"}, 0) {
// Disabling User Edits in a JTable with DefaultTableModel
            @Override
            public boolean isCellEditable(int row, int column) {
                return false;
            }
        ;
        };
tableShow = new JTable();
        tableShow.setModel(tableShowModel);
        panelShow.add(new JScrollPane(tableShow));
        labelFindCol = new JLabel("Найдено записей: 0");
        panelShow.add(labelFindCol);
        add(panelShow);
        try {
            conn = DriverManager.getConnection(dbURL, user_name, user_password);
            stmt = conn.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE,
                    ResultSet.CONCUR_READ_ONLY);
        } catch (SQLException err) {
            System.out.println(err.getMessage());
        }
    }

    private static void createAndShowGUI() {
        JFrame frame = new JFrame("Адресная книга");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        mainFrame = frame;
        JComponent componentPanelAddressBook = new AddressBook();
        frame.setContentPane(componentPanelAddressBook);
        frame.pack();
        frame.setVisible(true);
    }

    public static void main(String[] args) {
//Schedule a job for the event-dispatching thread:
//creating and showing this application's GUI.
        javax.swing.SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                createAndShowGUI();
            }
        });
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        String command = e.getActionCommand();
        int dataToSize = 7;
        String[] dataTo = new String[dataToSize];
        for (int i = 0; i < dataToSize; i++) {
            dataTo[i] = "";
        }
        if ("Создать".equals(command)) {
            JDialog dialogContact = new JDialog(mainFrame,
                    "Новый контакт...", JDialog.DEFAULT_MODALITY_TYPE);
            PanelContact panelContact = new PanelContact(command, dataTo);
            dialogContact.setBounds(
                    delta_size_dialog, delta_size_dialog,
                    panelContact.getContactPanelWidth() + 3 * delta_size_dialog,
                    panelContact.getContactPanelHeight() + delta_size_dialog);
            dialogContact.add(panelContact);
            dialogContact.setVisible(true);
        }
        try {
            if (("Редактировать".equals(command) || "Просмотреть".equals(command))
                    && rs != null && tableShow.getSelectedRow() > -1) {
                rs.first();
                do {
                    if (rs.getString("PHONENUMBER").
                            equals(tableShowModel
                                    .getValueAt(tableShow.getSelectedRow(), 1)
                                    .toString())) {
                        dataTo[0] = rs.getString("ID_CONTACTS");
                        dataTo[1] = rs.getString("FIRSTNAME");
                        dataTo[2] = rs.getString("LASTNAME");
                        dataTo[3] = rs.getString("MIDLENAME");
                        dataTo[4] = rs.getString("TELEPHONE");
                        dataTo[5] = rs.getString("ID_PHONENUMBER");
                        dataTo[6] = rs.getString("PHONENUMBER");
                        String title = "";
                        if ("Редактировать".equals(command)) {
                            title = "Изменить контакт...";
                        }
                        if ("Просмотреть".equals(command)) {
                            title = "Просмотреть контакт...";
                        }
                        JDialog dialogContact = new JDialog(mainFrame,
                                title, JDialog.DEFAULT_MODALITY_TYPE);
                        PanelContact panelContact = new PanelContact(command, dataTo);
                        dialogContact.setBounds(
                                delta_size_dialog, delta_size_dialog,
                                panelContact.getContactPanelWidth()
                                + 3 * delta_size_dialog,
                                panelContact.getContactPanelHeight()
                                + delta_size_dialog);
                        dialogContact.add(panelContact);
                        dialogContact.setVisible(true);
                        break;
                    }
                } while (rs.next());
            }
        } catch (SQLException err1) {
            System.out.println(err1.getMessage());
        }
        if ("Поиск".equals(command)) {
            findByString(textFieldFind.getText());
        }
        try {
            if ("Удалить".equals(command)
                    && rs != null && tableShow.getSelectedRow() > -1) {
                rs.first();
                do {
                    if (rs.getString("PHONENUMBER").
                            equals(tableShowModel
                                    .getValueAt(tableShow.getSelectedRow(), 1)
                                    .toString())) {
                        String SQL_UpdateContacts
                                = "DELETE FROM CONTACTS WHERE TELEPHONE = "
                                + rs.getString("TELEPHONE");
                        String SQL_updatePhoneNumbers
                                = "DELETE FROM PHONENUMBERS WHERE ID_PHONENUMBER = "
                                + rs.getString("ID_PHONENUMBER");
                        PreparedStatement updateContacts = null;
                        PreparedStatement updatePhoneNumbers = null;
                        conn.setAutoCommit(false);
                        updateContacts = conn.prepareStatement(SQL_UpdateContacts);
                        updatePhoneNumbers = conn.prepareStatement(
                                SQL_updatePhoneNumbers);
                        int executeUpdate = updateContacts.executeUpdate();
                        executeUpdate = updatePhoneNumbers.executeUpdate();
                        conn.commit();
                        if (updateContacts != null) {
                            updateContacts.close();
                        }
                        if (updatePhoneNumbers != null) {
                            updatePhoneNumbers.close();
                        }
                        conn.setAutoCommit(true);
                        findByString("");
                        break;
                    }
                } while (rs.next());
            }
        } catch (SQLException err1) {
            try {
                conn.rollback();
                conn.setAutoCommit(true);
                JOptionPane.showMessageDialog(this,
                        "Транзакция на удаление не выполнена.\n"
                        + "Смотрите сообщения в консоли.");
                System.out.println(err1.getMessage());
            } catch (SQLException err2) {
                System.out.println(err2.getMessage());
            }
        }
    }

    private void findByString(String textFind) {
        try {
            while (tableShowModel.getRowCount() > 0) {
                tableShowModel.removeRow(0);
            }
            SQL
                    = "SELECT CONTACTS.*, PHONENUMBERS.* "
                    + "FROM CONTACTS, PHONENUMBERS "
                    + "WHERE CONTACTS.TELEPHONE = PHONENUMBERS.ID_PHONENUMBER "
                    + "AND CONTACTS.FIRSTNAME LIKE '"
                    + textFind + "%'";
            rs = stmt.executeQuery(SQL);
            while (rs.next()) {
                String fio
                        = rs.getString("FIRSTNAME") + " "
                        + rs.getString("LASTNAME") + " "
                        + rs.getString("MIDLENAME");
                String phonenumber = rs.getString("PHONENUMBER");
                tableShowModel.addRow(new Object[]{fio, phonenumber});
            }
            labelFindCol.setText("Найдено записей: " + tableShowModel.getRowCount());
        } catch (SQLException err) {
            System.out.println(err.getMessage());
        }
    }

    class PanelContact extends JPanel implements ActionListener {

        private final int width_window = 300;//Кратно трём
        private final int height_window = 143;
        private final int height_button_panel = 40;
        private final int height_gap = 3;
        private String mode;
        private String dataTo[];
        private JPanel panelUp, panelLabel, panelText, panelButton;
        private JLabel labelFirstName;
        private JLabel labelLastName;
        private JLabel labelMidleName;
        private JLabel labelPhoneNumber;
        private JTextField txtFieldFirstName;
        private JTextField txtFieldLastName;
        private JTextField txtFieldMidleName;
        private JTextField txtPhoneNumber;
        private JButton buttonApplay;
        private JButton buttonCancel;

        public PanelContact(String mode, String[] dataTo) {
            super();
            this.mode = mode;
            this.dataTo = dataTo;
            setLayout(new BoxLayout(this, BoxLayout.PAGE_AXIS));
            setPreferredSize(new Dimension(width_window, height_window));
            panelUp = new JPanel();//Панель для размещения панелей
            panelLabel = new JPanel();
            panelText = new JPanel();
            panelButton = new JPanel();
            labelFirstName = new JLabel("Фамилия");
            labelLastName = new JLabel("Имя");
            labelMidleName = new JLabel("Отчество");
            labelPhoneNumber = new JLabel("Номер тел.");
            txtFieldFirstName = new JTextField(dataTo[1]);
            txtFieldLastName = new JTextField(dataTo[2]);
            txtFieldMidleName = new JTextField(dataTo[3]);
            txtPhoneNumber = new JTextField(dataTo[6]);
            buttonApplay = new JButton("Принять");
            buttonApplay.addActionListener(this);
            buttonCancel = new JButton("Отменить");
            buttonCancel.addActionListener(this);
            panelUp.setPreferredSize(new Dimension(width_window, height_window
                    - height_button_panel - height_gap));
            panelUp.setBorder(BorderFactory.createBevelBorder(1));
            add(panelUp);
            panelUp.setLayout(new BoxLayout(panelUp, BoxLayout.LINE_AXIS));
            panelLabel.setPreferredSize(new Dimension(width_window / 3, height_window
                    - height_button_panel - height_gap));
            panelLabel.setBorder(BorderFactory.createBevelBorder(1));
            panelLabel.setLayout(new GridLayout(4, 1));
            panelLabel.add(labelFirstName);
            panelLabel.add(labelLastName);
            panelLabel.add(labelMidleName);
            panelLabel.add(labelPhoneNumber);
            panelText.setPreferredSize(new Dimension(2 * width_window / 3, height_window
                    - height_button_panel - height_gap));
            panelText.setBorder(BorderFactory.createBevelBorder(1));
            panelText.setLayout(new GridLayout(4, 1));
            panelText.add(txtFieldFirstName);
            panelText.add(txtFieldLastName);
            panelText.add(txtFieldMidleName);
            panelText.add(txtPhoneNumber);
            panelUp.add(panelLabel);
            panelUp.add(panelText);
            add(Box.createRigidArea(
                    new Dimension(0, height_gap))); // Отступ 10 пикселей
            panelButton.setPreferredSize(
                    new Dimension(width_window, height_button_panel));
            panelButton.setBorder(BorderFactory.createBevelBorder(1));
            add(panelButton);
            panelButton.setLayout(new FlowLayout());
            panelButton.add(buttonApplay);
            panelButton.add(buttonCancel);
            if ("Просмотреть".equals(mode)) {
                buttonApplay.setEnabled(false);
                txtFieldFirstName.setEditable(false);
                txtFieldLastName.setEditable(false);
                txtFieldMidleName.setEditable(false);
                txtPhoneNumber.setEditable(false);
            }
        }

        public int getContactPanelWidth() {
            return width_window;
        }

        public int getContactPanelHeight() {
            return height_window;
        }

        @Override
        public void actionPerformed(ActionEvent e) {
            String command = e.getActionCommand();
            JDialog dialog = (JDialog) SwingUtilities.getWindowAncestor(this);
            if ("Отменить".equals(command)) {
                dialog.dispose();
            }
            if ("Принять".equals(command)) {
                if (isTelephone(txtPhoneNumber.getText(), 5, 12)
                        && isFromFIO(txtFieldFirstName.getText(), 1, 30)
                        && isFromFIO(txtFieldLastName.getText(), 1, 30)
                        && isFromFIO(txtFieldMidleName.getText(), 1, 30)) {
                    String SQL_Update_TBL_PhoneNumbers = null;
                    String SQL_Update_TBL_Contacts = null;
                    if ("Создать".equals(mode)) {
//Переписать на поиск первого свободного ID
                        int r[] = findMaxID();
                        SQL_Update_TBL_PhoneNumbers
                                = "INSERT INTO PHONENUMBERS (ID_PHONENUMBER, PHONENUMBER) "
                                + "VALUES (" + (r[0] + 1) + ", "
                                + "'" + txtPhoneNumber.getText() + "')";
                        SQL_Update_TBL_Contacts = "INSERT INTO CONTACTS"
                                + " (ID_CONTACTS, FIRSTNAME,"
                                + " LASTNAME, MIDLENAME, TELEPHONE) "
                                + "VALUES (" + (r[1] + 1) + ", "
                                + "'" + txtFieldFirstName.getText() + "', "
                                + "'" + txtFieldLastName.getText() + "', "
                                + "'" + txtFieldMidleName.getText() + "', "
                                + (r[0] + 1) + ")";
                    }
                    if ("Редактировать".equals(mode)) {
                        SQL_Update_TBL_PhoneNumbers
                                = "UPDATE PHONENUMBERS SET "
                                + "PHONENUMBER = '" + txtPhoneNumber.getText() + "' "
                                + "WHERE ID_PHONENUMBER = " + dataTo[5] + "";
                        SQL_Update_TBL_Contacts
                                = "UPDATE CONTACTS SET "
                                + "FIRSTNAME = '" + txtFieldFirstName.getText() + "', "
                                + "LASTNAME = '" + txtFieldLastName.getText() + "', "
                                + "MIDLENAME = '" + txtFieldMidleName.getText() + "' "
                                + "WHERE ID_CONTACTS = " + dataTo[0] + "";
                    }
                    try {
                        PreparedStatement createPhoneNumber = null;
                        PreparedStatement createContact = null;
                        conn.setAutoCommit(false);
                        createPhoneNumber = conn.prepareStatement(
                                SQL_Update_TBL_PhoneNumbers);
                        int executeUpdate = createPhoneNumber.executeUpdate();
                        createContact = conn.prepareStatement(SQL_Update_TBL_Contacts);
                        executeUpdate = createContact.executeUpdate();
                        conn.commit();
                        if (createPhoneNumber != null) {
                            createPhoneNumber.close();
                        }
                        if (createContact != null) {
                            createContact.close();
                        }
                        conn.setAutoCommit(true);
                    } catch (SQLException err1) {
                        try {
                            conn.rollback();
                            conn.setAutoCommit(true);
                            JOptionPane.showMessageDialog(this,
                                    "Транзакция на создание контакта не выполнена.\n"
                                    + "Смотрите сообщения в консоли.");
                            System.out.println(err1.getMessage());
                        } catch (SQLException err2) {
                            System.out.println(err2.getMessage());
                        }
                    }
                    findByString("");
                    dialog.dispose();
                } else {
                    JOptionPane.showMessageDialog(this, "Исправьте введённые данные.\n"
                            + "Допустимо:\n"
                            + "номер телефона - от 5 до 12 цифр,\n"
                            + "фамилия, имя, отчество - каждое от 1 до 30 символов.");
                }
            }
        }

        private int[] findMaxID() {
            int[] r = {0, 0};
            try {
                SQL
                        = "SELECT CONTACTS.*, PHONENUMBERS.* "
                        + "FROM CONTACTS, PHONENUMBERS "
                        + "WHERE CONTACTS.TELEPHONE = PHONENUMBERS.ID_PHONENUMBER "
                        + "AND CONTACTS.FIRSTNAME LIKE '%'";
                rs = stmt.executeQuery(SQL);
                int max_ID_PHONENUMBER = r[0],
                        max_ID_CONTACTS = r[1];
                int tmp;
                while (rs.next()) {
                    tmp = new Integer(rs.getString("ID_PHONENUMBER"));
                    if (tmp > max_ID_PHONENUMBER) {
                        max_ID_PHONENUMBER = tmp;
                    }
                    tmp = new Integer(rs.getString("ID_CONTACTS"));
                    if (tmp > max_ID_CONTACTS) {
                        max_ID_CONTACTS = tmp;
                    }
                    r[0] = max_ID_PHONENUMBER;
                    r[1] = max_ID_CONTACTS;
                }
            } catch (SQLException err) {
                System.out.println(err.getMessage());
            }
            return r;
        }

        private Boolean isTelephone(String s, int min_length, int max_length) {
            if (s.length() < min_length || max_length < s.length()) {
                return false;
            }
            for (int i = 0; i < s.length(); i++) {
                if (Character.isDigit(s.charAt(i))) {
                } else {
                    return false;
                }
            }
            return true;
        }

        private Boolean isFromFIO(String s, int min_length, int max_length) {
            if (s.length() < min_length || max_length < s.length()) {
                return false;
            }
            for (int i = 0; i < s.length(); i++) {
                if (Character.isLetter(s.charAt(i))) {
                } else {
                    return false;
                }
            }
            return true;
        }
    }
}
