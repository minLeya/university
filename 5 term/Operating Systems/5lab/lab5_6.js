// Входные параметры 
var fromDir = WScript.Arguments(0); // исходный каталог
var filename = WScript.Arguments(1); // название файла
var toDir = WScript.Arguments(2); // результирующий каталог

var shell = WScript.CreateObject("WScript.Shell");

//5.1. Создать исходный каталог 
shell.Run('%COMSPEC% /C mkdir ' + fromDir);

//5.2. Создать исходный файл с помощью Блокнота 
shell.Run(shell.ExpandEnvironmentStrings("%WINDIR%\\notepad.exe " + fromDir + filename),1,true);

//5.3. Создать результирующий каталог 
shell.Run('%COMSPEC% /C mkdir ' + toDir);
 
//5.4. Переместить исходный файл в результирующий каталог;
shell.Run('%COMSPEC% /k move "'+ fromDir +'\\'+ filename + '" "' + toDir +'\\'+ filename + '"');
 
//5.5. Запустить Блокнот для редактирования файла в результирующем каталоге
shell.Run(shell.ExpandEnvironmentStrings('"%WINDIR%\\notepad.exe" "' + toDir +'\\'+ filename+ '"'),1,true);

shell.Run('%COMSPEC% /K comp "' + fromDir + '\\' + filename)