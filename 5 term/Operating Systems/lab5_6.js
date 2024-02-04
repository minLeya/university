if (WScript.Arguments.Count() == 3) {
    var fromDir = WScript.Arguments(0); // исходный каталог
    var filename = WScript.Arguments(1); // название файла
    var toDir = WScript.Arguments(2); // результирующий каталог

    var shell = WScript.CreateObject("WScript.Shell");
    //5.1. Создать исходный каталог 
    var strFromDir = '%COMSPEC% /C mkdir ' + fromDir;
    shell.Run(strFromDir);

    //5.2. Создать исходный файл с помощью Блокнота 
    var strFilename = "%WINDIR%\\notepad.exe " +  fromDir + filename;
    shell.Run(shell.ExpandEnvironmentStrings(strFilename),1,true);

    //5.3. Создать результирующий каталог 
    var strToDir = '%COMSPEC% /C mkdir ' + toDir;
    shell.Run(strToDir);
    
    //5.4. Переместить исходный файл в результирующий каталог;
    var strMove = '%COMSPEC% /k move "'+ fromDir + filename + '" "' + toDir + filename + '"';
    shell.Run(strMove);
    
    //5.5. Запустить Блокнот для редактирования файла в результирующем каталоге
    var strEdit = '"%WINDIR%\\notepad.exe" "' + toDir + filename+ '"';
    shell.Run(shell.ExpandEnvironmentStrings(strEdit),1,true);

    //5.6. Вывести содержимое файла результирующего каталога;
    var strToDirFileContents = "%COMSPEC% /K type " +  toDir + filename;
    shell.run(strToDirFileContents);
}
else {
    // Входные параметры 
    var fromDir = WScript.Arguments(0); // исходный каталог
    var filename = WScript.Arguments(1); // название файла
    var toDir = WScript.Arguments(2); // результирующий каталог
    var resultFile = WScript.Arguments(3); //файл с результатами

    var shell = WScript.CreateObject("WScript.Shell");
    //5.1. Создать исходный каталог 
    var strFromDir = '%COMSPEC% /C mkdir ' + fromDir;
    shell.Run(strFromDir);

    //5.2. Создать исходный файл с помощью Блокнота 
    var strFilename = "%WINDIR%\\notepad.exe " +  fromDir + filename;
    shell.Run(shell.ExpandEnvironmentStrings(strFilename),1,true);

    //5.3. Создать результирующий каталог 
    var strToDir = '%COMSPEC% /C mkdir ' + toDir;
    shell.Run(strToDir);
    
    //5.4. Переместить исходный файл в результирующий каталог;
    var strMove = '%COMSPEC% /k move "'+ fromDir + filename + '" "' + toDir + filename + '"';
    shell.Run(strMove);
    
    //5.5. Запустить Блокнот для редактирования файла в результирующем каталоге
    var strEdit = '"%WINDIR%\\notepad.exe" "' + toDir + filename+ '"';
    shell.Run(shell.ExpandEnvironmentStrings(strEdit),1,true);

    //создание файла с результатами
    var strResFile = "%WINDIR%\\notepad.exe " + toDir + resultFile;
    shell.Run(shell.ExpandEnvironmentStrings(strResFile),1,true);

    // 5.6. Создать файл с результатами и записать в него содержимое исходного файла
    var strResultFile = '%COMSPEC% /C echo|set /p="' + filename + toDir + resultFile + '"';
    shell.Run(strResultFile);

    var strCopyContents = '%COMSPEC% /C type "' + toDir + filename + '" >> "' + toDir + resultFile + '"';
    shell.Run(strCopyContents);
}