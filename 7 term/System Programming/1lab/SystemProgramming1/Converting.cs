//1реализация двухпросмот-го ассемблера для программы в абсолютном формате
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SystemProgramming1
{
    class Converting
    {

        public static string DecToHex(int decNumber)
        {
                  
            string hexNumber = "";
            char[] hexMass = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
            int tempNumber = decNumber;
            var mod = new List<int>();
            if (tempNumber < 16 && tempNumber > 0) 
            {
                hexNumber += hexMass[tempNumber];
            }
            else
            {

                while (tempNumber >= 1)
                {
                    tempNumber = tempNumber / 16;
                    mod.Add(decNumber % 16);
                    decNumber = decNumber / 16;


                }
               
                for (int i = mod.Count - 1; i >= 0; i--)
                {
                    hexNumber += hexMass[mod[i]];
                }
            }

            return hexNumber;
        }

        public static string DecToHexSign(int decNumber,int sign)
        {
            string hexNumber = "";
            char[] hexMass = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
            int div = decNumber;
            var mod = new List<int>();
            if (div < 16 && div > 0) 
            {
                hexNumber += hexMass[div];
            }
            else
            {

                while (div >= 16)
                {
                    div = div / 16;
                    mod.Add(decNumber % 16);


                }
                hexNumber += div;
                for (int i = mod.Count - 1; i >= 0; i--)
                {
                    hexNumber += hexMass[mod[i]];
                }
            }

            return hexNumber;
        }

        public static int HexToDec(string hexNumber)
        {
            int decNumber = 0;
            hexNumber = hexNumber.ToUpper();
            var hexNumbers = new List<char>
            {
                '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'
            };

            var chrs = hexNumber.ToCharArray();

            double k = 0;
            for (int i = chrs.Length - 1; i >= 0; i--)
            {

                decNumber += hexNumbers.IndexOf(chrs[i]) * (int)(Math.Pow(16, k));

                k++;
            }

            return decNumber;
        }

        public static string ToSixChars (string number)
        {
            const int lenghtNumber = 6;
            var chrs = number.ToCharArray();
            var sum = new char[lenghtNumber];
            string convertNumber = "";
            if (number == "")
                return "";
            if (chrs.Length <= lenghtNumber)
            {
                int needZero = lenghtNumber - chrs.Length;

                for (int i = lenghtNumber - 1; i >= needZero; i--)
                {
                    sum[i] = chrs[i - needZero];
                }
                for (int i = 0; i < needZero; i++)
                {
                    sum[i] = '0';
                }

                foreach (var s in sum)
                {
                    convertNumber += s;
                }
            }
            return convertNumber;
        }

        public static string ToTwoChars(string number)
        {
            const int lenghtNumber = 2;
            var chrs = number.ToCharArray();
            var sum = new char[lenghtNumber];
            string convertNumber = "";
            if (number == "")
                return "";
            if (chrs.Length <= lenghtNumber)
            {
                int needZero = lenghtNumber - chrs.Length;

                for (int i = lenghtNumber - 1; i >= needZero; i--)
                {
                    sum[i] = chrs[i - needZero];
                }
                for (int i = 0; i < needZero; i++)
                {
                    sum[i] = '0';
                }

                foreach (var s in sum)
                {
                    convertNumber += s;
                }
            }
            return convertNumber;
        }

        public static string ToASCII(string str)
        {
            string result="";
            byte[] textBytes = Encoding.ASCII.GetBytes(str);
            for (int i = 0; i < textBytes.Length; i++)
            {
                result = result + Converting.DecToHex(Convert.ToInt32(textBytes[i]));
            }
            return result;
        }


        public static string EditingString(string symbol, string address, string command, string length, string operand1, string operand2)
        {
            string final = "";
            if (symbol == "H")
            {
                final = final + "H";
                final = final + "  " + address;
                final = final+"  "+ command ;
                final = final + "  " + Converting.ToSixChars(Converting.DecToHex(Convert.ToInt32(operand1)));
                return final;
            }
            else
                if (symbol == "T")
                {
                    final = final + "T"+"  ";
                    if (address.Length > 0)
                    final = final + address+"  ";
                    final = final + length + "   ";
                    final = final + command;
                    
                    if (operand1.Length > 0)
                    final = final + operand1;
                    if (operand2.Length > 0)
                    final = final + operand2;
                    return final;
                }
                else
                    if (symbol == "E")
                    {
                        final = final + "E";
                        final = final + "  " + address;

                        return final;
                    }
            return final;
        }

    }
}
