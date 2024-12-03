namespace SystemProgramming1
{
    partial class Form1
    {
        /// <summary>
        /// Требуется переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Обязательный метод для поддержки конструктора - не изменяйте
        /// содержимое данного метода при помощи редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.textBox_first_errors = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.tbSecondErrors = new System.Windows.Forms.TextBox();
            this.tbBinaryCode = new System.Windows.Forms.ListBox();
            this.label8 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.dataGrid_symbol_table = new System.Windows.Forms.DataGridView();
            this.Column5 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column6 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.label4 = new System.Windows.Forms.Label();
            this.dataGrid_supportTable = new System.Windows.Forms.DataGridView();
            this.dataGridViewTextBoxColumn4 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dataGridViewTextBoxColumn5 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column7 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column8 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.dataGrid_OperationCode = new System.Windows.Forms.DataGridView();
            this.dataGridViewTextBoxColumn1 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dataGridViewTextBoxColumn2 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dataGridViewTextBoxColumn3 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dataGrid_Source = new System.Windows.Forms.DataGridView();
            this.Column1 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column2 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column3 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column4 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            ((System.ComponentModel.ISupportInitialize)(this.dataGrid_symbol_table)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGrid_supportTable)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGrid_OperationCode)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGrid_Source)).BeginInit();
            this.SuspendLayout();
            // 
            // button1
            // 
            this.button1.BackColor = System.Drawing.SystemColors.ControlLight;
            this.button1.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.button1.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.button1.Font = new System.Drawing.Font("Trebuchet MS", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.button1.ForeColor = System.Drawing.SystemColors.ControlText;
            this.button1.Location = new System.Drawing.Point(72, 683);
            this.button1.Margin = new System.Windows.Forms.Padding(4);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(209, 44);
            this.button1.TabIndex = 8;
            this.button1.Text = "Первый проход";
            this.button1.UseVisualStyleBackColor = false;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.BackColor = System.Drawing.SystemColors.ControlLight;
            this.button2.Enabled = false;
            this.button2.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button2.Font = new System.Drawing.Font("Trebuchet MS", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.button2.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.button2.Location = new System.Drawing.Point(516, 683);
            this.button2.Margin = new System.Windows.Forms.Padding(4);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(208, 44);
            this.button2.TabIndex = 9;
            this.button2.Text = "Второй проход";
            this.button2.UseVisualStyleBackColor = false;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // textBox_first_errors
            // 
            this.textBox_first_errors.Location = new System.Drawing.Point(442, 611);
            this.textBox_first_errors.Margin = new System.Windows.Forms.Padding(4);
            this.textBox_first_errors.Multiline = true;
            this.textBox_first_errors.Name = "textBox_first_errors";
            this.textBox_first_errors.Size = new System.Drawing.Size(367, 64);
            this.textBox_first_errors.TabIndex = 10;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Trebuchet MS", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label5.Location = new System.Drawing.Point(511, 581);
            this.label5.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(245, 26);
            this.label5.TabIndex = 11;
            this.label5.Text = "Ошибки первого прохода";
            // 
            // label6
            // 
            this.label6.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Trebuchet MS", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label6.Location = new System.Drawing.Point(905, 579);
            this.label6.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(243, 26);
            this.label6.TabIndex = 7;
            this.label6.Text = "Ошибки второго прохода";
            this.label6.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // tbSecondErrors
            // 
            this.tbSecondErrors.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.tbSecondErrors.Location = new System.Drawing.Point(838, 609);
            this.tbSecondErrors.Margin = new System.Windows.Forms.Padding(4);
            this.tbSecondErrors.Multiline = true;
            this.tbSecondErrors.Name = "tbSecondErrors";
            this.tbSecondErrors.ReadOnly = true;
            this.tbSecondErrors.Size = new System.Drawing.Size(367, 66);
            this.tbSecondErrors.TabIndex = 6;
            // 
            // tbBinaryCode
            // 
            this.tbBinaryCode.BackColor = System.Drawing.SystemColors.ControlLightLight;
            this.tbBinaryCode.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.tbBinaryCode.FormattingEnabled = true;
            this.tbBinaryCode.ItemHeight = 16;
            this.tbBinaryCode.Location = new System.Drawing.Point(848, 35);
            this.tbBinaryCode.Margin = new System.Windows.Forms.Padding(4);
            this.tbBinaryCode.Name = "tbBinaryCode";
            this.tbBinaryCode.Size = new System.Drawing.Size(368, 320);
            this.tbBinaryCode.TabIndex = 17;
            this.tbBinaryCode.SelectedIndexChanged += new System.EventHandler(this.tbBinaryCode_SelectedIndexChanged_1);
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("Trebuchet MS", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label8.Location = new System.Drawing.Point(949, 5);
            this.label8.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(144, 26);
            this.label8.TabIndex = 16;
            this.label8.Text = "Двоичный код";
            this.label8.Click += new System.EventHandler(this.label8_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Trebuchet MS", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label3.Location = new System.Drawing.Point(511, 5);
            this.label3.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(250, 26);
            this.label3.TabIndex = 22;
            this.label3.Text = "Вспомогательная таблица";
            // 
            // dataGrid_symbol_table
            // 
            this.dataGrid_symbol_table.AllowUserToAddRows = false;
            this.dataGrid_symbol_table.AllowUserToDeleteRows = false;
            this.dataGrid_symbol_table.AllowUserToResizeColumns = false;
            this.dataGrid_symbol_table.AllowUserToResizeRows = false;
            this.dataGrid_symbol_table.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.dataGrid_symbol_table.AutoSizeRowsMode = System.Windows.Forms.DataGridViewAutoSizeRowsMode.AllCells;
            this.dataGrid_symbol_table.BackgroundColor = System.Drawing.SystemColors.ControlLightLight;
            this.dataGrid_symbol_table.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.dataGrid_symbol_table.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGrid_symbol_table.ColumnHeadersVisible = false;
            this.dataGrid_symbol_table.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.Column5,
            this.Column6});
            this.dataGrid_symbol_table.Location = new System.Drawing.Point(442, 388);
            this.dataGrid_symbol_table.Margin = new System.Windows.Forms.Padding(4);
            this.dataGrid_symbol_table.Name = "dataGrid_symbol_table";
            this.dataGrid_symbol_table.ReadOnly = true;
            this.dataGrid_symbol_table.RowHeadersBorderStyle = System.Windows.Forms.DataGridViewHeaderBorderStyle.None;
            this.dataGrid_symbol_table.RowHeadersVisible = false;
            this.dataGrid_symbol_table.RowHeadersWidth = 51;
            this.dataGrid_symbol_table.Size = new System.Drawing.Size(368, 179);
            this.dataGrid_symbol_table.TabIndex = 21;
            // 
            // Column5
            // 
            this.Column5.HeaderText = "Column5";
            this.Column5.MinimumWidth = 6;
            this.Column5.Name = "Column5";
            this.Column5.ReadOnly = true;
            // 
            // Column6
            // 
            this.Column6.HeaderText = "Column6";
            this.Column6.MinimumWidth = 6;
            this.Column6.Name = "Column6";
            this.Column6.ReadOnly = true;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Trebuchet MS", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label4.Location = new System.Drawing.Point(480, 361);
            this.label4.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(288, 26);
            this.label4.TabIndex = 23;
            this.label4.Text = "Таблица символических имен";
            this.label4.Click += new System.EventHandler(this.label4_Click_1);
            // 
            // dataGrid_supportTable
            // 
            this.dataGrid_supportTable.AllowUserToAddRows = false;
            this.dataGrid_supportTable.AllowUserToDeleteRows = false;
            this.dataGrid_supportTable.AllowUserToResizeColumns = false;
            this.dataGrid_supportTable.AllowUserToResizeRows = false;
            this.dataGrid_supportTable.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.dataGrid_supportTable.AutoSizeRowsMode = System.Windows.Forms.DataGridViewAutoSizeRowsMode.AllCells;
            this.dataGrid_supportTable.BackgroundColor = System.Drawing.SystemColors.ControlLightLight;
            this.dataGrid_supportTable.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.dataGrid_supportTable.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGrid_supportTable.ColumnHeadersVisible = false;
            this.dataGrid_supportTable.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.dataGridViewTextBoxColumn4,
            this.dataGridViewTextBoxColumn5,
            this.Column7,
            this.Column8});
            this.dataGrid_supportTable.Location = new System.Drawing.Point(427, 35);
            this.dataGrid_supportTable.Margin = new System.Windows.Forms.Padding(4);
            this.dataGrid_supportTable.Name = "dataGrid_supportTable";
            this.dataGrid_supportTable.ReadOnly = true;
            this.dataGrid_supportTable.RowHeadersVisible = false;
            this.dataGrid_supportTable.RowHeadersWidth = 51;
            this.dataGrid_supportTable.Size = new System.Drawing.Size(397, 309);
            this.dataGrid_supportTable.TabIndex = 20;
            // 
            // dataGridViewTextBoxColumn4
            // 
            this.dataGridViewTextBoxColumn4.HeaderText = "Column5";
            this.dataGridViewTextBoxColumn4.MinimumWidth = 6;
            this.dataGridViewTextBoxColumn4.Name = "dataGridViewTextBoxColumn4";
            this.dataGridViewTextBoxColumn4.ReadOnly = true;
            // 
            // dataGridViewTextBoxColumn5
            // 
            this.dataGridViewTextBoxColumn5.HeaderText = "Column6";
            this.dataGridViewTextBoxColumn5.MinimumWidth = 6;
            this.dataGridViewTextBoxColumn5.Name = "dataGridViewTextBoxColumn5";
            this.dataGridViewTextBoxColumn5.ReadOnly = true;
            // 
            // Column7
            // 
            this.Column7.HeaderText = "Column7";
            this.Column7.MinimumWidth = 6;
            this.Column7.Name = "Column7";
            this.Column7.ReadOnly = true;
            // 
            // Column8
            // 
            this.Column8.HeaderText = "Column8";
            this.Column8.MinimumWidth = 6;
            this.Column8.Name = "Column8";
            this.Column8.ReadOnly = true;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Trebuchet MS", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label2.Location = new System.Drawing.Point(80, 357);
            this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(241, 26);
            this.label2.TabIndex = 27;
            this.label2.Text = "Таблица кодов операций";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Trebuchet MS", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label1.Location = new System.Drawing.Point(67, 5);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(270, 26);
            this.label1.TabIndex = 26;
            this.label1.Text = "Исходный текст программы";
            // 
            // dataGrid_OperationCode
            // 
            this.dataGrid_OperationCode.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.dataGrid_OperationCode.AutoSizeRowsMode = System.Windows.Forms.DataGridViewAutoSizeRowsMode.AllCells;
            this.dataGrid_OperationCode.BackgroundColor = System.Drawing.SystemColors.ControlLightLight;
            this.dataGrid_OperationCode.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.dataGrid_OperationCode.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGrid_OperationCode.ColumnHeadersVisible = false;
            this.dataGrid_OperationCode.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.dataGridViewTextBoxColumn1,
            this.dataGridViewTextBoxColumn2,
            this.dataGridViewTextBoxColumn3});
            this.dataGrid_OperationCode.Location = new System.Drawing.Point(16, 387);
            this.dataGrid_OperationCode.Margin = new System.Windows.Forms.Padding(4);
            this.dataGrid_OperationCode.Name = "dataGrid_OperationCode";
            this.dataGrid_OperationCode.RowHeadersBorderStyle = System.Windows.Forms.DataGridViewHeaderBorderStyle.None;
            this.dataGrid_OperationCode.RowHeadersVisible = false;
            this.dataGrid_OperationCode.RowHeadersWidth = 51;
            this.dataGrid_OperationCode.Size = new System.Drawing.Size(368, 180);
            this.dataGrid_OperationCode.TabIndex = 25;
            // 
            // dataGridViewTextBoxColumn1
            // 
            this.dataGridViewTextBoxColumn1.HeaderText = "Column1";
            this.dataGridViewTextBoxColumn1.MinimumWidth = 6;
            this.dataGridViewTextBoxColumn1.Name = "dataGridViewTextBoxColumn1";
            // 
            // dataGridViewTextBoxColumn2
            // 
            this.dataGridViewTextBoxColumn2.HeaderText = "Column2";
            this.dataGridViewTextBoxColumn2.MinimumWidth = 6;
            this.dataGridViewTextBoxColumn2.Name = "dataGridViewTextBoxColumn2";
            // 
            // dataGridViewTextBoxColumn3
            // 
            this.dataGridViewTextBoxColumn3.HeaderText = "Column3";
            this.dataGridViewTextBoxColumn3.MinimumWidth = 6;
            this.dataGridViewTextBoxColumn3.Name = "dataGridViewTextBoxColumn3";
            // 
            // dataGrid_Source
            // 
            this.dataGrid_Source.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.dataGrid_Source.AutoSizeRowsMode = System.Windows.Forms.DataGridViewAutoSizeRowsMode.AllCells;
            this.dataGrid_Source.BackgroundColor = System.Drawing.SystemColors.ControlLightLight;
            this.dataGrid_Source.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.dataGrid_Source.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGrid_Source.ColumnHeadersVisible = false;
            this.dataGrid_Source.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.Column1,
            this.Column2,
            this.Column3,
            this.Column4});
            this.dataGrid_Source.Location = new System.Drawing.Point(16, 35);
            this.dataGrid_Source.Margin = new System.Windows.Forms.Padding(4);
            this.dataGrid_Source.Name = "dataGrid_Source";
            this.dataGrid_Source.RowHeadersVisible = false;
            this.dataGrid_Source.RowHeadersWidth = 51;
            this.dataGrid_Source.Size = new System.Drawing.Size(368, 309);
            this.dataGrid_Source.TabIndex = 28;
            // 
            // Column1
            // 
            this.Column1.FillWeight = 89.3401F;
            this.Column1.HeaderText = "Column1";
            this.Column1.MinimumWidth = 6;
            this.Column1.Name = "Column1";
            // 
            // Column2
            // 
            this.Column2.FillWeight = 89.3401F;
            this.Column2.HeaderText = "Column2";
            this.Column2.MinimumWidth = 6;
            this.Column2.Name = "Column2";
            // 
            // Column3
            // 
            this.Column3.FillWeight = 131.9797F;
            this.Column3.HeaderText = "Column3";
            this.Column3.MinimumWidth = 6;
            this.Column3.Name = "Column3";
            // 
            // Column4
            // 
            this.Column4.FillWeight = 89.3401F;
            this.Column4.HeaderText = "Column4";
            this.Column4.MinimumWidth = 6;
            this.Column4.Name = "Column4";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ControlLight;
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.ClientSize = new System.Drawing.Size(1245, 741);
            this.Controls.Add(this.dataGrid_Source);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.dataGrid_OperationCode);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.dataGrid_symbol_table);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.dataGrid_supportTable);
            this.Controls.Add(this.tbBinaryCode);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.tbSecondErrors);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.textBox_first_errors);
            this.Controls.Add(this.button1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Margin = new System.Windows.Forms.Padding(4);
            this.Name = "Form1";
            this.Text = "Лабораторная работа №1. Двухпросмотровый ассемблер для программ в абсолютном форм" +
    "ате";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dataGrid_symbol_table)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGrid_supportTable)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGrid_OperationCode)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGrid_Source)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.TextBox textBox_first_errors;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox tbSecondErrors;
        private System.Windows.Forms.ListBox tbBinaryCode;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.DataGridView dataGrid_symbol_table;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column5;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column6;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.DataGridView dataGrid_supportTable;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn4;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn5;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column7;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column8;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.DataGridView dataGrid_OperationCode;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn1;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn2;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn3;
        private System.Windows.Forms.DataGridView dataGrid_Source;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column1;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column2;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column3;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column4;
    }
}

