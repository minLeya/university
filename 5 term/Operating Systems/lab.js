var source = WScript.Arguments(0);
var fileOrCons = WScript.Arguments(1);

//создание объектов
var fso = WScript.CreateObject("Scripting.FileSystemObject");
var shell = WScript.CreateObject("WScript.Shell");

//создание файла в блокноте
var originalText = fso.CreateTextFile((source),true);
originalText.Close();
shell.Run("%windir%\\notepad.exe " + source,1,true);

// запись текста в переменную
originalText = fso.OpenTextFile((source),1);
var temp = originalText.ReadAll();

//если заканчивается точкой
if (temp.charAt(temp.length-1) == '.')
{
    temp2 = temp.replace(/(\s)+/g,' ');
    //если 1 - запись в результирующий файл
    if(WScript.Arguments(1)==1)
    {
        var reformedText = fso.OpenTextFile(WScript.Arguments(2),2,true);
        reformedText.Write("Before: " + temp + "\n");
        reformedText.Write("After: " + temp2);
        reformedText.Close();
    }
    //вывод в консошль
    else if(WScript.Arguments(1)==2)
    {
        WScript.Echo('\n'+"Before: "+temp+'\n');
        WScript.Echo("After: "+temp2);
    }
}
