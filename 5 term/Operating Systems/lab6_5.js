var fromDir = WScript.Arguments(0); //исходный каталог
var filename = WScript.Arguments(1); //что
var toDir = WScript.Arguments(2); //куда
var resultFile = WScript.Arguments(3);

var fso = WScript.CreateObject("Scripting.FileSystemObject");
var shell = WScript.CreateObject("WScript.Shell");

//5.1 create folder
if (!fso.FolderExists(fromDir))
{
    fso.CreateFolder(fromDir);
}

//5.2 use blocknote to create source file 
fso.CreateTextFile(fromDir + filename, true);
shell.Run(('notepad.exe "'+ fromDir + filename + '"'), 1, true)

//5.3 create result folder
if (!fso.FolderExists(toDir))
{
    fso.CreateFolder(toDir);
}

//5.4 move sourse file to rusult folder
fso.MoveFile(fromDir + filename, toDir);

//5.5 run blocknote to edit file in result folder
shell.Run(shell.ExpandEnvironmentStrings('"%WINDIR%\\notepad.exe" "' + toDir +'\\'+ filename + '"'),1,true);

//5.5 show 
var file = fso.GetFile(toDir+"\\"+filename); 
file = fso.OpenTextFile(file.Path, 1); 

//input to the file
fso.CreateTextFile(toDir + resultFile, true);
