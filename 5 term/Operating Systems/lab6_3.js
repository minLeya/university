// fsoCreateText.js - создание файла с деревом каталогов
var of;
function ProcessDirectory(dir,prefix)
{
    var foldPrefix=prefix+"-";
    prefix+="|";
    var newPrefix=prefix+" ";
    var fc = new Enumerator(dir.SubFolders);
    while(!fc.atEnd())
    {
        of.WriteLine(foldPrefix+fc.item().Name);
        ProcessDirectory(fc.item(),newPrefix);
        fc.moveNext();
    }
    fc = new Enumerator(dir.Files);
    while(!fc.atEnd())
    {
        of.WriteLine(prefix+fc.item().Name);
        fc.moveNext();
    }
}
if(WScript.Arguments.Count()==2)
{
    var fso=WScript.CreateObject("Scripting.FileSystemObject");
    var of=fso.CreateTextFile(WScript.Arguments(0),true);
    ProcessDirectory(fso.GetFolder(WScript.Arguments(1)),"")
    of.Close()
}else
    WScript.Echo("Использование: cscript //nologo "+WScript.ScriptFullName+" tree.txt c:\\windows\\temp");