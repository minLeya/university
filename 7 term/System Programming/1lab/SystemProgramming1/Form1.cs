using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;


namespace SystemProgramming1
{
    public partial class Form1 : Form
    {

        bool firstPassError=false;

        public Form1()
        {
            InitializeComponent();
        }

        TSupport support;
        

        private void button1_Click(object sender, EventArgs e)
        {
          firstPassError = true;
          support = new TSupport();
          Clear_tables();
          support.Delete_empty_rows(dataGrid_Source);
           //создаем динамический массив куда помещаем нашу таблицу исходного кода
          string[,] source_code = new string[dataGrid_Source.RowCount-1, dataGrid_Source.Columns.Count];
          for (int i = 0; i < dataGrid_Source.RowCount-1;i++ )
              for (int j = 0; j < dataGrid_Source.Columns.Count; j++)
                   source_code[i, j] = Convert.ToString(dataGrid_Source.Rows[i].Cells[j].Value);
          //создаем динамический массив куда помещаем нашу таблицу кодов операций
          string[,] OperationCode = new string[dataGrid_OperationCode.RowCount - 1, dataGrid_OperationCode.Columns.Count];
          for (int i = 0; i < dataGrid_OperationCode.RowCount - 1; i++)
              for (int j = 0; j < dataGrid_OperationCode.Columns.Count; j++)
              {
                  OperationCode[i, j] = Convert.ToString(dataGrid_OperationCode.Rows[i].Cells[j].Value);
                  OperationCode[i, j] = OperationCode[i, j].ToUpper();
              }
        //проверяем таблицу кодов операций
          if (support.Check_operation_code_table(ref OperationCode))
          {
              //делаем первый проход
              if (support.First_pass(source_code, OperationCode,dataGrid_supportTable, dataGrid_symbol_table))
              {
                  firstPassError = false;
                  button2.Enabled = true;
                  Add_error(textBox_first_errors, support.error_message);
              }
              else
              {
                  Add_error(textBox_first_errors, support.error_message);
                  button2.Enabled = false;
                }
          }
          else
          {
              Add_error(textBox_first_errors, support.error_message);
          }
       
            
       
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            dataGrid_Source.Rows.Add("PROG", "START", "100", "");
            dataGrid_Source.Rows.Add("", "JMP", "L1", "");
            dataGrid_Source.Rows.Add("A1", "RESB", "10", "");
            dataGrid_Source.Rows.Add("A2", "RESW", "20", "");
            dataGrid_Source.Rows.Add("B1", "WORD", "4096", "");
            dataGrid_Source.Rows.Add("B2", "BYTE", "X" + '"' + "2F40008A" + '"', "");
            dataGrid_Source.Rows.Add("B3", "BYTE", "C" + '"' + "Hello!" + '"', "");
            dataGrid_Source.Rows.Add("B4", "BYTE", "128", "");
            dataGrid_Source.Rows.Add("L1", "LOADR1", "B1", "");
            dataGrid_Source.Rows.Add("", "LOADR2", "B4", "");
            dataGrid_Source.Rows.Add("", "ADD", "R1", "R2");
            dataGrid_Source.Rows.Add("", "SAVER1", "B1", "");
            dataGrid_Source.Rows.Add("", "END", "100", "");

            dataGrid_OperationCode.Rows.Add("JMP", "01", "4");
            dataGrid_OperationCode.Rows.Add("LOADR1", "02", "4");
            dataGrid_OperationCode.Rows.Add("LOADR2", "03", "4");
            dataGrid_OperationCode.Rows.Add("ADD", "04", "2");
            dataGrid_OperationCode.Rows.Add("SAVER1", "05", "4");
            

            dataGrid_Source.Update();
            dataGrid_OperationCode.Update();
        }

        void Clear_tables()
        {
            dataGrid_supportTable.Rows.Clear();
            dataGrid_symbol_table.Rows.Clear();
            textBox_first_errors.Clear();
            tbSecondErrors.Clear();
            tbBinaryCode.Items.Clear();
          //  dataGridView1.Rows.Clear();
        }

        void Add_error(TextBox textBox_first_errors, string message)
        {
            textBox_first_errors.Text += message + Environment.NewLine;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            tbBinaryCode.Items.Clear();
            tbSecondErrors.Clear();
            if (dataGrid_symbol_table.Rows.Count > 0)
            {

                String hexValue1 = Convert.ToString(dataGrid_supportTable.Rows[dataGrid_supportTable.Rows.Count - 1].Cells[0].Value);
                String hexValue2 = Convert.ToString(dataGrid_supportTable.Rows[1].Cells[0].Value);
                int startint = int.Parse(hexValue1, System.Globalization.NumberStyles.HexNumber) - int.Parse(hexValue2, System.Globalization.NumberStyles.HexNumber);
                String name = Convert.ToString(dataGrid_supportTable.Rows[0].Cells[0].Value);
                String start = Converting.ToSixChars(Converting.DecToHex(startint));
                String stop = Convert.ToString(dataGrid_supportTable.Rows[dataGrid_supportTable.Rows.Count - 1].Cells[0].Value); ;

              //  dataGridView1.Rows.Add(name, start, stop);
            }
                if (firstPassError == false)
                    if (support.Second_pass(tbBinaryCode))
                    {
                        Add_error(tbSecondErrors, support.error_message);
                    }
                    else
                    {
                        Add_error(tbSecondErrors, support.error_message);
                    }
                else
                    MessageBox.Show("Выполните первый проход");
            

        }

        private void dataGrid_Source_CellBeginEdit(object sender, DataGridViewCellCancelEventArgs e)
        {
            Clear_tables();
            button2.Enabled = false;
        }

        private void dataGrid_symbol_table_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void label4_Click(object sender, EventArgs e)
        {

        }

        private void tbBinaryCode_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void button3_Click(object sender, EventArgs e)
        {
            dataGrid_Source.Rows.Clear();
            dataGrid_OperationCode.Rows.Clear();
            Clear_tables();
            var adr = "100";
            dataGrid_Source.Rows.Add("PROG", "START", adr, "");
            dataGrid_Source.Rows.Add("", "JMP", "L1", "");
            dataGrid_Source.Rows.Add("A1", "RESB", "10", "");
            dataGrid_Source.Rows.Add("A2", "RESW", "20", "");
            dataGrid_Source.Rows.Add("B1", "WORD", "4096", "");
            dataGrid_Source.Rows.Add("B2", "BYTE", "X" + '"' + "2F40008A" + '"', "");
            dataGrid_Source.Rows.Add("B3", "BYTE", "C" + '"' + "Hello!" + '"', "");
            dataGrid_Source.Rows.Add("B4", "BYTE", "128", "");
            dataGrid_Source.Rows.Add("L1", "LOADR1", "B1", "");
            dataGrid_Source.Rows.Add("", "LOADR2", "B4", "");
            dataGrid_Source.Rows.Add("", "ADD", "R1", "R2");
            dataGrid_Source.Rows.Add("", "SAVER1", "B1", "");
            dataGrid_Source.Rows.Add("", "END", adr, "");

            dataGrid_OperationCode.Rows.Add("JMP", "01", "4");
            dataGrid_OperationCode.Rows.Add("LOADR1", "02", "4");
            dataGrid_OperationCode.Rows.Add("LOADR2", "03", "4");
            dataGrid_OperationCode.Rows.Add("ADD", "04", "2");
            dataGrid_OperationCode.Rows.Add("SAVER1", "05", "4");
            

            dataGrid_Source.Update();
            dataGrid_OperationCode.Update();
        }

        private void label4_Click_1(object sender, EventArgs e)
        {

        }

        private void tbBinaryCode_SelectedIndexChanged_1(object sender, EventArgs e)
        {

        }

        private void label8_Click(object sender, EventArgs e)
        {

        }
    }
}
