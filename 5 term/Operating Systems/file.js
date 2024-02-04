var source = WScript.Arguments(0); //путь исходного файла
var filename = WScript.Arguments(1); // имя исходного файла
var symbol = WScript.Arguments(2); // буква, которая должна быть в слове, но не в конце слова
var result = WScript.Arguments(3); //путь результирующего файла
var fileresult = WScript.Arguments(4); // имя файла-результата
// Объявление объектов
var shell = WScript.CreateObject("WScript.Shell");
var fso = WScript.CreateObject("Scripting.FileSystemObject");
//условия для задачи
var NL = 100; // максимальная длина текста
var NS = 30; // максимальная длина строки
var NW = 10; // максимальная длина слова

WScript.Echo("Задача: Задан исходный текст на русском языке. \nДлина текста - не более " + NL + 
" символов, длина строки - не более " + NS + " символов, длина слова – не более " + NW + " символов\n" +
"Исходный текст должен заканчиваться точкой. \nСоставить процедуру, которая в заданном тексте находит слова заданной длины\n" +
"В качестве результата вывести исходный текст, найденные слова и их количество.\n");
// Создание исходного текста на русском языке в текстовом файле произвести в процедуре путем вызова Блокнота.
fso.CreateTextFile(source + "\\" + filename, true);
shell.Run(('notepad.exe "'+ source  + '\\' + filename + '"'), 1, true);

// чтение текста из исходного файла
var file =fso.GetFile(source + "\\" + filename);
var text = file.OpenAsTextStream(1).ReadAll();
var text_result = text; // переписываем текст в переменную для вывода результата

WScript.Echo('Исходный текст: "' + text_result + '"\n');

var checktext = text;

var checkNP = 1; // проверка точки в конце
var checkNL = 1; var checkNS = 1; var checkNW = 1; // проверки длина текста / строки / слова

    // Проверка на точку в конце текста
    if(text.match(/.$/) == "." ){
        WScript.Echo('Проверка 1 - УСПЕШНО: В конце есть точка');
    }   
    else {
        WScript.Echo('Проверка 1 - НЕУСПЕШНО: В конце нет точки. Текст не будет прочитан');
        checkNP = 0;
    }
                
    // Проверка на длину текста NL
    if (text.length > NL) {
        WScript.Echo('Проверка 2 - НЕУСПЕШНО: Длина текста (' + text.length +') больше максимальной возможной (' + NL +'). Текст не будет прочитан');
        checkNL = 0;
    }
    else {
        WScript.Echo('Проверка 2 - УСПЕШНО: Длина текста (' + text.length +') в допустимых пределах (не более ' + NL +')');
    }
    
    text = text.replace(/[.,?<>'\\/#!$%\^&\*;:{}=\-_`~()]/g,""); // Удаление знаков пунктуации в тексте
    
    var stroka = text.split("\n"); // "нарезаем" текст в массив построчно
    
    for (var i=0; i<stroka.length; i++) {
        if (stroka[i].length > NS) {
            WScript.Echo('Проверка 3 - НЕУСПЕШНО: Длина строки (' + stroka[i].length + ') больше максимальной возможной (' + NS +'). Текст не будет прочитан');
            checkNS = 0;
            break;
        }
        var slova = stroka.join(" ");
        slova = slova.split(" "); // разбиваем строку на слова
        for (var j=0; j<slova.length; j++) {
            if (checkNW == 1) if (slova[j].length > NW) {
                WScript.Echo('Проверка 4 - НЕУСПЕШНО: Длина слова '+ slova[j] + ' больше максимальной возможной (' + NW +'). Текст не будет прочитан');
                checkNW = 0;
                break;
            }
            
        }   
    }
    if (checkNS == 1) {
        WScript.Echo('Проверка 3 - УСПЕШНО: Длины всех строк в допустимых пределах (не более ' + NS + ')');
    }
    if (checkNW == 1) {
        WScript.Echo('Проверка 4 - УСПЕШНО: Длины всех слов в допустимых пределах (не более ' + NW + ')\n');
    }
            
if ((checkNP == 1) && (checkNL == 1) && (checkNS == 1) && (checkNW == 1)){
    // Создание файла с результатами
    var outfile = fso.CreateTextFile(result +"\\" + fileresult, true);

    // вывод сообщений пользователю
    WScript.Echo ('Ищем слова содержащие ' + symbol + ' букву\n');

    function getWords(text, symbol) {
        var newstroka = text.replace(/[\r\n]+/gm, "");
        var arr = newstroka.split(' ');
    
        var result = {
            count: 0,
            words: []
        };
    
       for (var i = 0; i < arr.length; i++) {
            if (arr[i].indexOf(symbol) !== -1 && arr[i].lastIndexOf(symbol) !== arr[i].length - 1) {
                result.count += 1;
                result.words.push(arr[i]);
            }
        }
    
        return result;
    }   
    var strResult = getWords(text, symbol); 

    WScript.Echo('Исходный текст: "' + text_result + '"\n');
    WScript.Echo('Найдено '+strResult.count+' слов(а), содержащих '+symbol+' букву');
    WScript.Echo('Слова: ' + strResult.words +'\n');
    // возможность перенаправления результатов выполнение в файл.
    outfile.WriteLine('Исходный текст: "' + text_result + '"\n');
    outfile.WriteLine('Найдено '+strResult.count+' слов(а), содержащих '+symbol+' букву');  
    outfile.WriteLine('Слова: ' + strResult.words +'\n');
}
else {
    WScript.Echo('\nЗапустите программу заново и введите корректный текст!!!\n');
}
