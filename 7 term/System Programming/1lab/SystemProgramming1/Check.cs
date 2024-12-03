//реализация двухпросмот-го ассемблера для программы в абсолютном формате
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SystemProgramming1
{
    class Check
    {
        public static int RegisterNumber(string str)
        {
            str = str.ToUpper();
            string[] reg = { "R0", "R1", "R2", "R3", "R4", "R5", "R6", "R7", "R8", "R9", "R10", "R11", "R12", "R13", "R14", "R15" };
                    return Array.IndexOf(reg, str);

        }

        public static bool OnlyRegisters(string str)
        {
            str = str.ToUpper();
            string[] reg = { "R0", "R1", "R2", "R3", "R4", "R5", "R6", "R7", "R8", "R9", "R10", "R11", "R12", "R13", "R14", "R15" };
            for (int i = 0; i < reg.Length - 1; i++)
            {
                if (Array.IndexOf(reg, str) == -1)
                {
                    return false;
                }

            }
            return true;
        }

        public static bool OnlyNumbers(string str)
        {
            char[] numbers = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
            for (int i = 0; i < str.Length ; i++)
            {
                if (Array.IndexOf(numbers, str[i]) == -1)
                {
                    return false;
                }
                
            }
                return true;
        }

        public static bool OnlySymbols(string str)
        {
            str = str.ToUpper();
            char[] numbers = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
            for (int i = 0; i < str.Length; i++)
            {
                if (Array.IndexOf(numbers, str[i]) == -1)
                {
                    return false;
                }
            }
            return true;
        }

        public static bool OnlySymbolsAndNumbers(string str)
        {
            str = str.ToUpper();
            char[] numbers = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
            for (int i = 0; i < str.Length ; i++)
            {
                if (Array.IndexOf(numbers, str[i]) == -1)
                {
                    return false;
                }
            }
            return true;
        }

        public static bool OnlySymbolsAndNumbersAndSpecial(string str)
        {
            str = str.ToUpper();
            char[] numbers = {'*', ' ','A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '"', '?', '!', '/', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
            for (int i = 0; i < str.Length - 1; i++)
            {
                if (Array.IndexOf(numbers, str[i]) == -1)
                {
                    return false;
                }
            }
            return true;
        }

        //проверяет соответствует ли переданная строка какой-либо директиве
        public static bool IsDirective(string name)
        {
            string[] system_directives = { "START", "END", "BYTE", "WORD", "RESB", "RESW" };

            if (Array.IndexOf(system_directives, name.ToUpper()) > -1)
                return true;
            else
                return false;
        }

        public static bool IsAdressPossible(string str)
        {
            if (str.Length > 0)
            {
                str = str.ToUpper();
                char[] numbers = { 'A', 'B', 'C', 'D', 'E', 'F', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
                for (int i = 0; i < str.Length; i++)
                {
                    if (Array.IndexOf(numbers, str[i]) == -1)
                    {
                        return false;
                    }
                }
                return true;
            }
            else
                return false;

        }

        public static string String(string Operand1)
        {
            if ((Operand1.Length > 3) && (Operand1[0] == 'C') && (Operand1[1] == '"') && (Operand1[Operand1.Length - 1] == '"'))
            {
              //  string text = Operand1.TrimStart('C');
                //text = text.Trim('"');
              //  string text =;
                return  Operand1.Substring(2, Operand1.Length - 3);
            }
            return "";
        }

        public static string ByteString(string Operand1)
        {
            if ((Operand1.Length > 3) && (Operand1[0] == 'X') && (Operand1[1] == '"') && (Operand1[Operand1.Length - 1] == '"'))
            {
               // string text = Operand1.TrimStart('X');
               // text = text.Trim('"');
               string text = Operand1.Substring(2, Operand1.Length - 3);
                if (!Check.IsAdressPossible(text))
                    return "";
                return text;
            }
            return "";
        }

    }
}
