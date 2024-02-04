var fso = WScript.CreateObject("Scripting.FileSystemObject");
var shell = WScript.CreateObject("WScript.Shell");

var fromDir = WScript.Arguments(0); // исходный каталог
var filename = WScript.Arguments(1); // название файла
var toDir = WScript.Arguments(2); // результирующий каталог
var resultFile = WScript.Arguments(3); // файл с результатами

fso.CreateFolder(fromDir); // Создать исходный каталог
shell.Run("%WINDIR%\\notepad.exe " + fromDir + filename, 1, true); // Создать исходный файл с помощью Блокнота
fso.CreateFolder(toDir); // Создать результирующий каталог
fso.MoveFile(fromDir + filename, toDir + filename); // Переместить исходный файл в результирующий каталог
shell.Run('%WINDIR%\\notepad.exe ' + toDir + filename, 1, true); // Запустить Блокнот для редактирования файла в результирующем каталоге
var fileContents = fso.OpenTextFile(toDir + filename).ReadAll(); // Получить содержимое файла

if (resultFile) {
    var result = fso.CreateTextFile(toDir + resultFile); // Создать файл с результатами
    result.Write(fso.OpenTextFile(toDir + filename).ReadAll()); // Записать содержимое исходного файла в файл с результатами
    result.Close();
}
else {
    WScript.Echo(fileContents); // Вывести содержимое файла
}

