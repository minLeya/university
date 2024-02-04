var source = WScript.Arguments(0); //путь исходного файла
var filename = WScript.Arguments(1); // имя исходного файла
var result = WScript.Arguments(2); //путь результирующего файла
var fileresult = WScript.Arguments(3); // имя файла-результата

var shell = WScript.CreateObject("WScript.Shell");
var fso = WScript.CreateObject("Scripting.FileSystemObject");

fso.CreateTextFile(source + "\\" + filename, true);
shell.Run(('notepad.exe "'+ source  + '\\' + filename + '"'), 1, true);

// чтение текста из исходного файла
var file =fso.GetFile(source + "\\" + filename);
var text = file.OpenAsTextStream(1).ReadAll();
var text_result = text; // переписываем текст в переменную для вывода результата

WScript.Echo('Text: "' + text_result + '"\n');
text = text.replace(/[.,?<>'\\/#!$%\^&\*;:{}=\-_`~()]/g,""); // Удаление знаков пунктуации в тексте
var stroka = text.split("\n"); // "нарезаем" текст в массив построчно

    function getWords (text) {
        var newstroka = text.replace( /[\r\n]+/gm, "" );
        var arr = newstroka.split(' ');
        
        var i,
            result = {
                count: 0,
                words: []
            };       
        for (i = 0; i < arr.length; i += 1) {     
            if (arr[i] == 'e' || arr[i] == 'y' || arr[i] == 'u' || arr[i] == 'i' || arr[i] == 'o'
            || arr[i] == 'a') {         
                result.count += 1;
                result.words.push(arr[i]);          
            }      
        }      
        return result;    
    } 
        
    var strResult = getWords(text); 
    var outfile = fso.CreateTextFile(result +"\\" + fileresult, true);

    WScript.Echo('Text: "' + text_result + '"\n');
    WScript.Echo('Found: '+strResult.count+'\n');
    WScript.Echo('Words: ' + strResult.words +'\n');

    // возможность перенаправления результатов выполнение в файл.
    outfile.WriteLine('Text: "' + text_result + '"\n');
    outfile.WriteLine('Found: '+strResult.count+'\n');	
    outfile.WriteLine('Words: ' + strResult.words +'\n');


