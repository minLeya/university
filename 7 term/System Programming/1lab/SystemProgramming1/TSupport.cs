using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SystemProgramming1
{

   class TSupport
    {
       string program_name;
       public string error_message="";
       int endAddress = 0;   //Адрес точки входа в программу
       int startAddress = 0; // Адрес начала программы
       int addressCounter = 0;
       const int maxMemmoryAdr = 16777215; //максимальное значение адреса  оперативной памяти
         
       //| Метка| МКОП | Операнд1 | Операнд2 | Вспомогательная таблица
       List<List<string>> Support_table = new List<List<string>>();
       
       //| Метка| Адрес | Таблица символических имен
       List<List<string>> lable_table = new List<List<string>>();
       
       //Таблица исходного кода
       List<string> Binary_code = new List<string>();
       
       public void AddStringToSupportTable(string n1,string n2,string n3,string n4)
       {
           Support_table[0].Add(n1);
           Support_table[1].Add(n2);
           Support_table[2].Add(n3);
           Support_table[3].Add(n4);
       }

       public bool  MemoryCheck()
       {
           if (addressCounter < 0 || addressCounter > maxMemmoryAdr)
           {
               error_message = "Выход за границы доступной памяти";
               return false;
           }
           return true;
       }

       //передается массив, номер строки который надо разложить по переменным
       //проверяется допустимость введеных символов
       public bool GetRow(string[,] mas, int number, out string label, out string command, out string dir1, out string dir2)
        {
            label = mas[number, 0];
            command = mas[number, 1].ToUpper();
            dir1 = mas[number, 2];
            dir2 = mas[number, 3];

            if (Check.IsDirective(label)||Check.OnlyRegisters(label))
            {
                return false;
            }
            if (number > 0 && program_name == label.ToUpper())
                return false;

           
                if ((Check.OnlySymbolsAndNumbers(label)||label.Length==0) && (Check.OnlySymbolsAndNumbers(command)) && (Check.OnlySymbolsAndNumbers(dir2)||dir2.Length==0))
                {
                    return true;
                }
                else
                {
                    return false;
                }

                           
        }
       
       //Процедура проверяет таблицу кодов операций 
       public bool Check_operation_code_table(ref string[,] OperationCodeTable) //проверяем таблицу  операций
        {
           int rows = OperationCodeTable.GetLength(0);
           int colums = OperationCodeTable.GetLength(1);

           for (int i = 0; i < rows; i++)
           {
                            

               if (OperationCodeTable[i, 0] == "" || OperationCodeTable[i, 1] == "" || OperationCodeTable[i, 2] == "")
               {
                   error_message = "В таблице кодов операций пустая ячейка  недопустима";
                   return false;
               }

               if (OperationCodeTable[i, 0].Length > 6 || OperationCodeTable[i, 1].Length > 2 || OperationCodeTable[i, 2].Length > 1)
               {
                   error_message = "В таблице кодов операций ошибка в размере строки  (Команда (от 1 до 6),МКОП (от 1 до 2), Длина(не более 1))";
                   return false;
               }

                //тут
                if (OperationCodeTable[i, 2] == "1" || OperationCodeTable[i, 2] == "2" || OperationCodeTable[i, 2] == "4")
                { }
                else
                {
                    error_message = "Нет команды такого размера:" + OperationCodeTable[i, 2] + " байт";
                    return false;
                }

                if (!Check.OnlySymbolsAndNumbers(OperationCodeTable[i, 0]))
               {
                   error_message = "В поле команды недопустимый символ";
                   return false;
               }


               //проверяем поле МКОП команды, что там были только 16чные цифры
               if (Check.IsAdressPossible(OperationCodeTable[i, 1]))
               {

                   if (Check.IsDirective(OperationCodeTable[i, 0]) || Check.OnlyRegisters(OperationCodeTable[i, 0]))
                   {
                       error_message = "Поле код команды является зарезервированным словом";
                       return false;
                   }
                   //преобразуем их в число
                   int count = Converting.HexToDec(OperationCodeTable[i, 1]);
                   if (count > 63)
                   {
                       error_message = "Поле код команды не должен превышать 3F";
                       return false;
                   }
                   else
                   {
                       //если оно в пределах байта, но записано просто как ... "F" поправляем его на "0F"
                       if (OperationCodeTable[i, 1].Length == 1)
                           OperationCodeTable[i, 1] = Converting.ToTwoChars(OperationCodeTable[i, 1]);
                   }

               }
               else
               {
                       error_message = "Посторонние символы в поле МКОП";
                       return false;
               }


               int value = 0;
               if (Check.OnlyNumbers(OperationCodeTable[i, 2]))
               {
                   bool result = Int32.TryParse(OperationCodeTable[i, 2], out value);
                   if (result)
                   {
                       if (value <= 0 || value > 4)
                       {
                           error_message = "Проверьте размер команды (от 1 до 4)";
                           return false;
                       }
                   }
               }
                   else
                   {
                       error_message = "В поле размер операции недопустимый символ";
                       return false;
                   }
               
               
               //проверяем уникальность поля названия команды
               for (int k=i+1;k<rows;k++)
               {  
                   string cmp_str1 = OperationCodeTable[i,0];
                   string cmp_str2 = OperationCodeTable[k,0];
                   if (Equals(cmp_str1, cmp_str2))
                   {
                       error_message = "Найдены совпадения в команде";
                       return false;
                   }
               }
               //проверяем уникальность поля код операции
               for (int k=i+1;k<rows;k++)
               {
                   string cmp_str1 = Convert.ToString(Converting.HexToDec(OperationCodeTable[i, 1]));
                   string cmp_str2 = Convert.ToString(Converting.HexToDec(OperationCodeTable[k,1]));
                   if (Equals(cmp_str1, cmp_str2))
                   {
                       error_message = "Найдены совпадения в коде команды";
                       return false;
                   }
               }
           }

           return true;
        }

       //Метод проверяет каждую ячейку таблицы, имеются ли в ней записи, если в строке нет данных, то она удаляется
       public void Delete_empty_rows(DataGridView DBGrid_source_code)
       {
           for (int i = 0; i < DBGrid_source_code.Rows.Count - 1; i++)
           {
               bool empty = true;
               for (int j = 0; j < DBGrid_source_code.Rows[i].Cells.Count; j++)
                   if ((DBGrid_source_code.Rows[i].Cells[j].Value != null) && (DBGrid_source_code.Rows[i].Cells[j].Value.ToString() != ""))
                       empty = false;

               if (empty)
               {
                   DBGrid_source_code.Rows.Remove(DBGrid_source_code.Rows[i]);
               }
           }
       }

       //проверяет есть ли такая команда в массиве команд
       public int FindCodeInCodeTable(string label,string[,] code_table)
       {
           for (int i = 0; i < code_table.GetLength(0); i++)
           {
               if (label == code_table[i, 0])
                    return i;
           }
           return -1;
       }

       //проверяет есть ли такая метка в массиве меток
       public int FindLabelInLabelTable(string label)
       {
           for (int i = 0; i < lable_table[0].Count; i++)
           {
               if (label == lable_table[0][i])
                   return i;
           }
           return -1;
       }
       
       //проверка опреанда во втором проходе
       //Если в операнде метка - возращает адрес метки
       //Если в операнде регистр - возвращает номер регистра
       //Если там строка типа C"????" - возвращает ASCII код
       //Если там строка типа X"????" - возвращает строку
       //Если что-то в 10ричном формате - то вернет это же число в 16ричном формате
       //иначе возращает пустую строку
       public string CheckingOperandSecondPass(string operand1, out int error, out int label)
       {
           label = 0;
           string result = "";
           error = 0;
           if (operand1 != "")
           {
               //если там метка - то возвращаем адрес метки
               int LabelStringNum = FindLabelInLabelTable(operand1);
               if (LabelStringNum > -1)
               {
                   label = 1;
                   return result = lable_table[1][LabelStringNum];
               }
               else
               {
                   //если в операнде регистр
                   int regnum = Check.RegisterNumber(operand1);
                   if (regnum > -1)
                   {
                       return result = Converting.DecToHex(regnum);
                   }
                   else
                       //если в операнде только цифры
                       if (Check.OnlyNumbers(operand1))
                       {
                           return result = Converting.DecToHex(Convert.ToInt32(operand1));
                       }
                       else
                       {
                           string sentence = "";
                           sentence = Check.String(operand1);
                           if (sentence != "")
                           {
                               return Converting.ToASCII(sentence);
                           }
                           sentence = Check.ByteString(operand1);
                           if (sentence != "")
                           {
                               return sentence;
                           }

                           //Если перепробованы все комбинации, значит ошибка
                           error = 1;
                       }


               }
           }
           
           return result;
       }

       //Процедура проверяет таблицу исходного кода, ищет директиву Старт,End. Проверяет адрес памяти, не выходим ли за границу  и т.д.
       //какие символы используются для названия программы
       public bool First_pass(string[,] SourceCodeTable, string[,] operation_code_table, DataGridView dataGrid_supportTable,DataGridView dataGrid_symbol_table)
       {
          
           addressCounter = 0;
           startAddress = 0;
           endAddress = 0;
           //Добавляем "столбцы" в списки списков
           lable_table.Add(new List<string>());
           lable_table.Add(new List<string>());
           Support_table.Add(new List<string>());
           Support_table.Add(new List<string>());
           Support_table.Add(new List<string>());
           Support_table.Add(new List<string>());

           int rows = SourceCodeTable.GetLength(0)-1;
           int colums = SourceCodeTable.GetLength(1);
           int StartFlag=0; //флаг найденной директивы старт
           int EndFlag = 0;//флаг найденной директивы энд
            
           string[,] code_table_mas = operation_code_table;

           string label, MKOP, Operand1, Operand2;
           
 
           //ЗАПУСКАЕМ ЦИКЛ ОБРАБОТКИ КАЖДОЙ СТРОКИ ИСХОДНОГО КОДА
           for (int i = 0; i <= rows; i++)
           {
               //если директива старт найдена
               if (StartFlag == 1)
               {
                   //то адрес уже записан в переменную 
                   //и надо проверить чтобы он не выходил за диапазон
                   if (addressCounter > maxMemmoryAdr)
                   {
                       error_message = "Произошло переполнение";
                       return false;
                   }
               }

               //Проверяем, если директива END найдена, то можно выходить из цикла
               if (EndFlag == 1)
               {
                     break;
               }
               
               //берем строку из массива и сразу же проверяем корректность данных
               //строка состоит из Label MKOP Operand1 Operand2
               if (!GetRow(SourceCodeTable, i, out label, out MKOP, out Operand1, out Operand2))
               {
                   error_message = "Синтаксическая ошибка строка = " + (i+1);
                   return false;
               }
               
               // Смотрим сперва  на метку, есть ли она в таблице меток
               //number_in_LabelTable  - укажет на строку в которой она находится
               int number_in_LabelTable = FindLabelInLabelTable(label);
               if (number_in_LabelTable != -1)
               {
                   error_message = "Найдена уже существующая метка " + label;
                   return false;
               }
               // если не найдена,то добавляем её и смотрим на МКОП
               else
               {
                   //если метка это не пустая строка и встречена после директивы старт
                   //то добавляем её в таблицу меток
                   if (label != "" && StartFlag == 1)
                   {
                       lable_table[0].Add(label);
                       lable_table[1].Add(Converting.ToSixChars(Converting.DecToHex(addressCounter)));
                   }


                   if (Check.IsDirective(MKOP))
                       switch (MKOP)
                       {
                           case "START":
                               {
                                   //если у нас старт не в начале массива, и найден в массиве еще раз то ошибка
                                   if (i == 0 && StartFlag == 0)
                                   {
                                       StartFlag = 1;
                                       //смотрим на операнд, символы соответствуют 16ричной сс
                                       if (Check.IsAdressPossible(Operand1))
                                       {
                                           //если да то преобразуем 16ричное число в 10чное
                                           addressCounter = Converting.HexToDec(Operand1);

                                           startAddress = addressCounter;
                                           //адрес начала программы не может быть равен 0
                                           if (addressCounter == 0)
                                           {
                                               error_message = "Адрес начала программы не может быть равен 0";
                                               return false;
                                           }
                                           //адрес начала программы не может превышать объем памяти
                                           if (addressCounter > maxMemmoryAdr)
                                           {
                                               error_message = "Адрес  программы выходит за диапазон памяти";
                                               return false;
                                           }

                                           if (label == "")
                                           {
                                               error_message = "Не задано имя программы";
                                               return false;
                                           }
                                           if (label.Length > 10)
                                           {
                                               error_message = "Превышена длина имени программы(>10 символов)";
                                               return false;
                                           }

                                       
                                               //теперь помещаем это в выходной массив
                                               AddStringToSupportTable(label, MKOP, Converting.ToSixChars(Operand1), "");
                                           program_name = label;
                                           //выводим предупреждение если такое имеется
                                           if(Operand2.Length>0)
                                               error_message = error_message + "Второй операнд директивы START не рассматривается\n";

                                       }
                                       else
                                       {
                                           error_message = "Неверный адрес начала программы";
                                           return false;
                                       }

                                   }
                                   else
                                   {
                                       error_message = "Ошибка в директиве START";
                                       return false;
                                   }

                               }

                               break;
                           case "WORD":
                               {    
                                   int number;
                                   //В WORD у нас могут быть записаны только числа (в данной проге только положительные)
                                   //преобразовываем операнд в число
                                   if (int.TryParse(Operand1, out number))
                                   {
                                       if (number >= 0 && number <= maxMemmoryAdr)
                                       {
                                           if (addressCounter + 3 > maxMemmoryAdr)
                                           {
                                               error_message = "Произошло переполнение";
                                               return false;
                                           }
                                           if (!MemoryCheck())
                                           {
                                               return false;
                                           }

                                           AddStringToSupportTable(Converting.ToSixChars(Converting.DecToHex(addressCounter)), MKOP, Convert.ToString(number), "");
                                           addressCounter = addressCounter + 3;
                                           if (!MemoryCheck()) {return false;}
                                           if (addressCounter < 0 || addressCounter > maxMemmoryAdr)
                                           {
                                               error_message = "Выход за границы доступной памяти";
                                               return false;
                                           }


                                           if (Operand2.Length > 0)
                                               error_message = error_message + "Второй операнд директивы WORD не рассматривается\n";
                                       }
                                       else
                                       {
                                           error_message = "Отрицательное число, либо превышено максимальное значение числа";
                                           return false;
                                       }
                                   }
                                   else
                                   {
                                       //символ вопроса, резервирует 1 слово в памяти
                                       if (Operand1.Length == 1 && Operand1 == "?")
                                       {

                                           if (addressCounter + 3 > maxMemmoryAdr)
                                           {
                                               error_message = "Произошло переполнение";
                                               return false;
                                           }

                                           AddStringToSupportTable(Converting.ToSixChars(Converting.DecToHex(addressCounter)), MKOP, Operand1, "");
                                           addressCounter = addressCounter + 3;
                                           if (!MemoryCheck()) { return false; }

                                           if (Operand2.Length > 0)
                                               error_message = error_message + "Второй операнд директивы WORD не рассматривается\n";
                                       }
                                       else
                                       {
                                           error_message = "Невозможно выполнить преобразование в число " + Operand1;
                                           return false;
                                       }
                                   }
                               }
                               break;
                           case "BYTE":
                               {
                                   int number;
                                   //пытаемся преобразовать операнд в число (разрешено только положительное 0 до 255)
                                   
                                   if (int.TryParse(Operand1, out number))
                                   {
                                       if (number >= 0 && number <= 255)
                                       {

                                           if (addressCounter +1> maxMemmoryAdr)
                                           {
                                               error_message = "Произошло переполнение";
                                               return false;
                                           }
                                           //BYTE = 1 байт, увеличиваем адрес
                                           AddStringToSupportTable(Converting.ToSixChars(Converting.DecToHex(addressCounter)), MKOP, Convert.ToString(number), "");
                                           addressCounter = addressCounter + 1;
                                           if (!MemoryCheck()) { return false; }


                                           if (Operand2.Length > 0)
                                               error_message = error_message + "Второй операнд директивы BYTE не рассматривается\n";
                                       }
                                       
                                       else
                                       {
                                           error_message = "Отрицательное число, либо превышеноо максимальное значение числа";
                                           return false;
                                       }
                                   }
                                       //если преобразование в число не получилось, значит разбираем строку
                                   else
                                   {
                                       //первый символ 'C' второй и последний символ это кавычки и длина строки >3
                                       string symbols=Check.String(Operand1);
                                       if (symbols != "")
                                       {

                                           if (addressCounter+symbols.Length > maxMemmoryAdr)
                                           {
                                               error_message = "Произошло переполнение";
                                               return false;
                                           }

                                           AddStringToSupportTable(Converting.ToSixChars(Converting.DecToHex(addressCounter)), MKOP, Operand1, "");
                                           addressCounter = addressCounter + symbols.Length;
                                           if (!MemoryCheck()) { return false; }


                                           if (Operand2.Length > 0)
                                               error_message = error_message + "Второй операнд директивы BYTE не рассматривается\n";
                                           continue;
                                       }

                                       //первый символ 'X' второй и последний символ это кавычки и длина строки >3
                                       symbols = "";
                                       symbols = Check.ByteString(Operand1);
                                       if (symbols != "")
                                       {
                                           int lenght = symbols.Length;
                                           //1 символ = 1 байт = 2 цифры в 16ричной системе = четное число символов
                                           if ((lenght % 2) == 0)
                                               {
                                                   if (addressCounter + symbols.Length / 2 > maxMemmoryAdr)
                                                   {
                                                       error_message = "Произошло переполнение";
                                                       return false;
                                                   }

                                                   AddStringToSupportTable(Converting.ToSixChars(Converting.DecToHex(addressCounter)), MKOP, Operand1, "");
                                                   addressCounter = addressCounter + symbols.Length / 2;
                                                   if (!MemoryCheck()) { return false; }

                                                   if (Operand2.Length > 0)
                                                        error_message = error_message + "Второй операнд директивы BYTE не рассматривается \n";
                                                   continue;
                                               }
                                                else
                                                {
                                                    error_message = "Невозможно преобразовать BYTE нечетное количество символов";
                                                    return false;
                                                }
                                       }
 
                                       //если там всего один символ "?"
                                       if (Operand1.Length == 1 && Operand1 == "?")
                                          {
                                              if (addressCounter+1 > maxMemmoryAdr)
                                              {
                                                  error_message = "Произошло переполнение";
                                                  return false;
                                              }

                                              AddStringToSupportTable(Converting.ToSixChars(Converting.DecToHex(addressCounter)), MKOP, Operand1, "");
                                             addressCounter = addressCounter + 1;
                                             if (!MemoryCheck()) { return false; }

                                             if (Operand2.Length > 0)
                                                error_message = error_message + "Второй операнд директивы BYTE не рассматривается \n";
                                             continue;
                                          }
                                       else
                                          {
                                             error_message = "Неверный формат строки " + Operand1;
                                             return false;
                                          }
                                   }
                               }
                               break;

                           case "RESB":
                               {
                                   int number;
                                   if (int.TryParse(Operand1, out number))
                                   {
                                       if (number > 0)
                                       {
                                                                                     
                                           if (addressCounter > maxMemmoryAdr)
                                           {
                                               error_message = "Переполнение памяти";
                                               return false;
                                           }
                                           else
                                           {
                                               if (addressCounter +number> maxMemmoryAdr)
                                               {
                                                   error_message = "Произошло переполнение";
                                                   return false;
                                               }
                                               AddStringToSupportTable(Converting.ToSixChars(Converting.DecToHex(addressCounter)), MKOP, Convert.ToString(number), "");
                                               addressCounter = addressCounter + number;//WORD = 3 байта, увеличиваем адрес
                                               if (!MemoryCheck()) { return false; }

                                               if (Operand2.Length > 0)
                                                   error_message = error_message + "Второй операнд директивы RESB не рассматривается \n";
                                           }

                                       }
                                       else
                                       {
                                           error_message = "Количество байт равно нулю или меньше нуля";
                                           return false;
                                       }
                                   }
                                   else
                                   {
                                       error_message = "Невозможно выполнить преобразование в число " + Operand1;
                                       return false;
                                   }
                               }
                               break;
                           case "RESW":
                               {
                                   int number;
                                   if (int.TryParse(Operand1, out number))
                                   {
                                       if (number > 0)
                                       {

                                           if (addressCounter + number * 3 > maxMemmoryAdr)
                                           {
                                               error_message = "Произошло переполнение";
                                               return false;
                                           }
                                               AddStringToSupportTable(Converting.ToSixChars(Converting.DecToHex(addressCounter)), MKOP, Convert.ToString(number), "");
                                               //WORD = 3 байта, увеличиваем адрес
                                               addressCounter = addressCounter + number * 3;
                                               if (!MemoryCheck()) { return false; }
                                               if (addressCounter < 0 || addressCounter > maxMemmoryAdr)
                                               {
                                                   error_message = "Выход за границы доступной памяти";
                                                   return false;
                                               }
                                                   

                                               if (Operand2.Length > 0)
                                                   error_message = error_message + "Второй операнд директивы RESW не рассматривается \n";
                                          

                                       }
                                       else
                                       {
                                           error_message ="Количество слов равно нулю или меньше нуля";
                                           return false;
                                       }
                                   }
                                   else
                                   {
                                       error_message = "Невозможно выполнить преобразование в число " + Operand1;
                                       return false;
                                   }
                               }
                               break;

                           case "END":
                               {
                                   if (StartFlag == 1 && EndFlag == 0)
                                   {
                                       EndFlag = 1;
                                       if (Operand1.Length == 0)
                                       {
                                           endAddress = startAddress;
                                       }
                                       else
                                       {
                                           if (Check.IsAdressPossible(Operand1))
                                           {
                                               //если да то преобразуем 16ричное число в 10чное
                                              endAddress = Converting.HexToDec(Operand1);
                                              if (endAddress >= startAddress && endAddress <= addressCounter)
                                              {
                                                  AddStringToSupportTable(Converting.ToSixChars(Converting.DecToHex(addressCounter)), MKOP, Converting.ToSixChars(Operand1), "");
                                                  break;
                                              }
                                              else
                                              {
                                                  error_message = "Адрес точки входа неверен";
                                                  return false;
                                              }
    
                                           }
                                           else
                                           {
                                               error_message = "Неверный адрес входа в программу";
                                               return false;
                                           }
                                       }

                                   }
                                   else
                                   {
                                       error_message = "Ошибка в директиве END";
                                       return false;
                                   }
                               }
                               break;
                       }
                   //значит в строке команда, обрабатываем тут
                   else
                   {
                       //Если в строке МКОП что-то написано
                       if (MKOP.Length > 0)
                       {
                           //Смотрим есть такой МКОП в таблице
                           int num = FindCodeInCodeTable(MKOP,code_table_mas);
                           if (num > -1)
                           {
                               //если он есть, то смотрим на длину команды
                               //ДЛИНА КОМАНДЫ = 1
                               //например NOP, операндов нет, а если и есть то не смотрим на них
                               if (code_table_mas[num,2]=="1")
                               {
                                   if (addressCounter +1> maxMemmoryAdr)
                                   {
                                       error_message = "Произошло переполнение";
                                       return false;
                                   }
                                   int AddressationType = Converting.HexToDec(code_table_mas[num, 1]) * 4;
                                   AddStringToSupportTable(Converting.ToSixChars(Converting.DecToHex(addressCounter)), Converting.ToTwoChars(Converting.DecToHex(AddressationType)), "", "");
                                   addressCounter = addressCounter + 1;
                                   if (!MemoryCheck()) { return false; }

                                   if (Operand1.Length > 0 || Operand2.Length > 0)
                                       error_message = error_message + "Операнды не рассматриваются в команде " + code_table_mas[num, 0] + "\n";
                               }
                               else
                                   //ДЛИНА КОМАНДЫ = 2
                                   //ADD r1,r2   операнды это регистры, либо число //INT 200
                                   if (code_table_mas[num,2]=="2")
                                   {
                                       int number;
                                       //сначала пытаемся преобразовать первый операнд в число
                                       if (int.TryParse(Operand1, out number))
                                       {
                                           if (number >= 0 && number <= 255)
                                           {
                                               //так как операнд является числом, то это непосредственная адресация
                                               //просто  сдвигаем на два разряда влево
                                               int AddressationType = Converting.HexToDec(code_table_mas[num, 1]) * 4;
                                               if (addressCounter+2 > maxMemmoryAdr)
                                               {
                                                   error_message = "Произошло переполнение";
                                                   return false;
                                               }
                                               AddStringToSupportTable(Converting.ToSixChars(Converting.DecToHex(addressCounter)), Converting.ToTwoChars(Converting.DecToHex(AddressationType)), Operand1, "");
                                               addressCounter = addressCounter + 2;
                                               if (!MemoryCheck()) { return false; }

                                               if (Operand2.Length > 0)
                                                   error_message = error_message + "Второй операнд команды" + code_table_mas[num, 0] + " не рассматривается \n";
                                           }

                                           else
                                           {
                                               error_message = "Отрицательное число, либо превышено максимальное значение числа";
                                               return false;
                                           }
                                       }
                                       else
                                       {
                                           //если первый и второй операнд - регистры
                                           if (Check.OnlyRegisters(Operand1) && Check.OnlyRegisters(Operand2))
                                           {
                                               //так как оба операнда регистры то это регистровая(регистровой==непосредственной) адресация
                                               //просто  сдвигаем на два разряда влево
                                               int AddressationType = Converting.HexToDec(code_table_mas[num, 1]) * 4;
                                               if (addressCounter +2> maxMemmoryAdr)
                                               {
                                                   error_message = "Произошло переполнение";
                                                   return false;
                                               }
                                               AddStringToSupportTable(Converting.ToSixChars(Converting.DecToHex(addressCounter)), Converting.ToTwoChars(Converting.DecToHex(AddressationType)), Operand1, Operand2);
                                               addressCounter = addressCounter + 2;
                                               if (!MemoryCheck()) { return false; }
                                           }
                                           else
                                           {
                                               error_message = "Ошибка в команде " + code_table_mas[num, 0];
                                               return false;
                                           }

                                       }

                                   }
                                   else
                                       //ДЛИНА КОМАНДЫ = 3
                                       if (code_table_mas[num,2]=="3")
                                       {
                                           if (addressCounter +3> maxMemmoryAdr)
                                           {
                                               error_message = "Произошло переполнение";
                                               return false;
                                           }
                                           int AddressationType = Converting.HexToDec(code_table_mas[num, 1]) * 4+1;
                                           AddStringToSupportTable(Converting.ToSixChars(Converting.DecToHex(addressCounter)), Converting.ToTwoChars(Converting.DecToHex(AddressationType)), Operand1, Operand2);
                                           addressCounter = addressCounter + 3;
                                           if (!MemoryCheck()) { return false; }

                                           if (Operand2.Length > 0)
                                               error_message = error_message + "Второй операнд команды" + code_table_mas[num, 0] + " не рассматривается\n";

                                       }
                                       else
                                           //ДЛИНА КОМАНДЫ = 4
                                           if (code_table_mas[num, 2] == "4")
                                           {
                                               if (addressCounter+4 > maxMemmoryAdr)
                                               {
                                                   error_message = "Произошло переполнение";
                                                   return false;
                                               }
                                               int AddressationType = Converting.HexToDec(code_table_mas[num, 1]) * 4 + 1;
                                               AddStringToSupportTable(Converting.ToSixChars(Converting.DecToHex(addressCounter)), Converting.ToTwoChars(Converting.DecToHex(AddressationType)), Operand1, Operand2);
                                               addressCounter = addressCounter + 4;
                                               if (!MemoryCheck()) { return false; }

                                               if (Operand2.Length > 0)
                                                   error_message = error_message + "Второй операнд команды" + code_table_mas[num, 0] + " не рассматривается\n";
                                           }
                                           else
                                           {
                                               error_message = "Размер команды больше установленного";
                                               return false;
                                           }

                           }
                           else
                           {
                               error_message = "МКОП не найден в таблице кодов операций "+MKOP;
                               return false;
                           }
                       }
                       else
                       {
                           error_message = "Ошибка в МКОП";
                           return false;
                       }
                   }

               }

           }

           if (EndFlag == 0)
           {
               error_message =error_message+ "Не найдена точка входа в программу \n";
               return false;
           }

           //Помещаем сформированную Вспомагательную таблицу в датагрид
           for (int i = 0; i < Support_table[0].Count ; i++)
           {
               dataGrid_supportTable.Rows.Add();
               dataGrid_supportTable.Rows[i].Cells[0].Value = Support_table[0][i];
               dataGrid_supportTable.Rows[i].Cells[0].Value = Support_table[0][i];
               dataGrid_supportTable.Rows[i].Cells[1].Value = Support_table[1][i];
               dataGrid_supportTable.Rows[i].Cells[2].Value = Support_table[2][i];
               dataGrid_supportTable.Rows[i].Cells[3].Value = Support_table[3][i];
           }

           //Помещаем сформированную Таблицу вспомогательных имен в датагрид
               for (int j = 0; j < lable_table[1].Count; j++)
               {
                   dataGrid_symbol_table.Rows.Add();
                   dataGrid_symbol_table.Rows[j].Cells[0].Value = lable_table[0][j];
                   dataGrid_symbol_table.Rows[j].Cells[1].Value = lable_table[1][j];
               }


               return true;
        }

       //Второй проход
       public bool Second_pass(ListBox BinaryCode)
       {
           error_message="";
 

            //int rows = OperationCodeTable.GetLength(0);
            //int colums = OperationCodeTable.GetLength(1);
            //string memoryInOperationCode = "";

            //for (int i = 0; i < rows; i++)
            //{

            //    //тут
            //    if (OperationCodeTable[i, 2] == "1" || OperationCodeTable[i, 2] == "2" || OperationCodeTable[i, 2] == "4")
            //    {
            //        memoryInOperationCode = OperationCodeTable[i, 2];
            //    }
   
            //}

            //запускаем его для каждой строки Вспомогательной таблицы
            for (int i = 0; i < Support_table[0].Count; ++i)
            {
                string address = Support_table[0][i];
                string MKOP = Support_table[1][i];
                string operand1 = Support_table[2][i];
                string operand2 = Support_table[3][i];


                //Если строка первая, то это директива Старт
                if (i == 0)
                {
                    string str = Converting.EditingString("H", Support_table[0][0], Support_table[2][0], "", Convert.ToString(addressCounter - startAddress), "");
                    BinaryCode.Items.Add(str);
                }
                //Если строка не первая, то снова смотрим, команда там или директива. Интересуют RESB и  RESW, т.к. из значение операндов отражается только в длинне записи
                else
                {
                    int error, label1, label2;
                    string result1 = CheckingOperandSecondPass(operand1, out error, out label1);
                    if (error == 1) { error_message = error_message + "Ошибка в операнде,код отсутствует в ТСИ " + operand1; break; }
                    string result2 = CheckingOperandSecondPass(operand2, out error, out label2);
                    if (error == 1) { error_message = error_message + "Ошибка в операнде,код отсутствует в ТСИ " + operand2; break; }
                    if (Check.IsDirective(MKOP) == true)
                    {
                        if (MKOP == "RESB")
                        {
                            MKOP = "";
                            string str1 = Converting.EditingString("T", address, MKOP, result1, "", "");
                            BinaryCode.Items.Add(str1);
                            continue;
                        }

                        if (MKOP == "RESW")
                        {
                            MKOP = "";
                            string str2 = Converting.EditingString("T", address, MKOP, Converting.ToTwoChars(Converting.DecToHex(Convert.ToInt32(operand1) * 3)), "", "");
                            BinaryCode.Items.Add(str2);
                            continue;
                        }


                        if (MKOP == "BYTE")
                        {
                            MKOP = "";
                            string str2 = Converting.EditingString("T", address, MKOP, Converting.ToTwoChars(Converting.DecToHex(result1.Length + result2.Length)), result1, result2);
                            BinaryCode.Items.Add(str2);
                            continue;
                        }

                        if (MKOP == "WORD")
                        {
                            MKOP = "";
                            result1 = Converting.ToSixChars(result1);
                            string str2 = Converting.EditingString("T", address, MKOP, Converting.ToTwoChars(Converting.DecToHex(result1.Length + result2.Length)), result1, result2);
                           // Console.WriteLine($"address: {address}, result1.Length: {result1.Length}, result2.Length: {result2.Length}, Convert 2 char: {Converting.ToTwoChars(Converting.DecToHex(result1.Length + result2.Length))}, result1: {result1}, convert hex: {Converting.DecToHex(result1.Length + result2.Length)}");

                            BinaryCode.Items.Add(str2);
                            continue;
                        }


                        if (MKOP == "BYTE" && operand1 == "?")
                        {
                            MKOP = "";
                            string str2 = Converting.EditingString("T", address, MKOP, Converting.ToTwoChars(Converting.DecToHex(1)), "", "");
                            BinaryCode.Items.Add(str2);
                            continue;
                        }

                        if (MKOP == "WORD" && operand1 == "?")
                        {
                            MKOP = "";
                            string str2 = Converting.EditingString("T", address, MKOP, Converting.ToTwoChars(Converting.DecToHex(3)), "", "");
                            BinaryCode.Items.Add(str2);
                            continue;
                        }
                    }
                    else
                    {
                        // Проверяем что команда работает с тем, что разрешено адресацией
                        // сначала смотрим на тип адресации, если там  01 , значит это прямая
                        //и в операндах может быть только метка
                        int Type_of_adr = (byte)Converting.HexToDec(MKOP) & 0x03;
                        if (Type_of_adr == 1)
                        {
                            if (label1 != 1)
                            {
                                error_message = error_message + "Для данного типа адресации операнд должен быть меткой " + MKOP;
                                BinaryCode.Items.Clear();
                                return false;

                            }
                            if (result2 != "")
                            {
                                error_message = error_message + "Данный тип адрессации поддерживает 1 операнд";
                                BinaryCode.Items.Clear();
                                return false;
                            }
                        }

                        //if (memoryInOperationCode == "3")
                        //{
                        //    String RecordLength = Converting.ToTwoChars(Converting.DecToHex(MKOP.Length + result1.Length + result2.Length));
                        //    str5 = Converting.EditingString("T", address, MKOP, RecordLength, result1, result2);
                        //    Console.WriteLine($"MKOP: {MKOP}, Type_of_adr: {Type_of_adr}, address: {address}, RecordLength: {RecordLength}, result1.Length: {result1.Length}, result2.Length: {result2.Length}, MKOP.Length: {MKOP.Length}");

                        //}

                        String RecordLength = Converting.ToTwoChars(Converting.DecToHex(MKOP.Length + result1.Length + result2.Length));
                        string str5 = Converting.EditingString("T", address, MKOP, RecordLength, result1, result2);
                        Console.WriteLine($"MKOP: {MKOP}, Type_of_adr: {Type_of_adr}, address: {address}, RecordLength: {RecordLength}, result1.Length: {result1.Length}, result2.Length: {result2.Length}, MKOP.Length: {MKOP.Length}");

                      //  string str5 = Converting.EditingString("T", address, MKOP, Converting.ToTwoChars(Converting.DecToHex(result1.Length + result2.Length)), result1, result2);

                        BinaryCode.Items.Add(str5);

                    }

                }
            }

           
           string str3 = Converting.EditingString("E",Converting.ToSixChars(Converting.DecToHex(endAddress)),"", "", "","");
           BinaryCode.Items.Add(str3);

           if (error_message!="")
           BinaryCode.Items.Clear();

           return true;
       }

    }
}
