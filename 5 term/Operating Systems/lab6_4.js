// fsoCreateText.js - создание файла с таблицей умножения
if(WScript.Arguments.Count()==1)
{
    var fso=WScript.CreateObject("Scripting.FileSystemObject");
    var tf=fso.CreateTextFile(WScript.Arguments(0),true);
    tf.WriteLine("Таблица Пифагора:");
    var i;
    tf.Write(" |");
    for(i=1;i<10;i++)
    {
        tf.Write(" "+i+"|");
    }
    tf.WriteLine("");
    tf.WriteLine("-+--+--+--+--+--+--+--+--+--+");
    var j;
    for(i=1;i<10;i++)
    {
        tf.Write(i);
        for(j=1;j<10;j++)
        {
            tf.Write("|");
            if(i*j<10)
            77
            tf.Write(" ");
            tf.Write(i*j);
        }
        tf.WriteLine("|");
    }
    tf.WriteLine("-+--+--+--+--+--+--+--+--+--+");
    tf.Close();
}else
WScript.Echo("Использование: cscript //nologo "+WScript.ScriptFullName+ " pifagor.txt");