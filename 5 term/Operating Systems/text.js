//объявление объектов
/* var shell = WScript.CreateObject("WScript.Shell");
var fso = WScript.CreateObject("Scripting.FileSystemObject");

var source = WScript.Arguments(0); //путь исходного файла
var filename = WScript.Arguments(1); // имя исходного файла
var result = WScript.Arguments(2); //путь результирующего файла
var fileresult = WScript.Arguments(3); // имя файла-результата

//создание блокнота для записи текста
fso.CreateTextFile(source + "\\" + filename, true);
shell.Run(('notepad.exe "'+ source  + '\\' + filename + '"'), 1, true);

// чтение текста из исходного файла
var file = fso.GetFile(source + "\\" + filename);
var text = file.OpenAsTextStream(1).ReadAll();
var text_result = text; */ // переписываем текст в переменную для вывода результата

//sub_string = new String("aoeiuy");
/*string = new String("We all have some things we do every day or almost every day in a particular order. Let me tell you about my daily routine.");
word = new String(""); */

//WScript.Echo('Исходный текст: "' + text_result + '"\n');


/* function print_word(string,i){
	word = "";
	while (true){
		word = word.concat(string.charAt(i));
		i += 1;
		if (string.charAt(i) == " " || string.charAt(i) == "." || string.charAt(i) == ",")
			break;
	}
	WScript.Echo(word);
	return 1;
}

function find_words(string,sub_string){
	var n = string.length;
	var i;
	var count=0;
	for (i=1;i<=n;i++){
		if (string.charAt(i) == " ")
			if (sub_string.lastIndexOf(string.charAt(i+1)) != -1)
				{print_word(string,i+1);
				count+=1;}
	}
	//WScript.Echo("number of words: " + count);
	return 1;
}
WScript.Echo(text_result);
find_words(text_result,sub_string);

if (result && fileresult)
{
	var outfile = fso.CreateTextFile(result +"\\" + fileresult, true);
	outfile.WriteLine('text: "' + text_result + '"\n');
    //outfile.WriteLine('words: ' + strResult.words +'\n');
}


 */

var fso = WScript.CreateObject("Scripting.FileSystemObject");
var shell = WScript.CreateObject("WScript.Shell");

var source = WScript.Arguments(0); // исходный каталог
var filename = WScript.Arguments(1); // название файла
var result = WScript.Arguments(2); // результирующий каталог
var resultFile = WScript.Arguments(3); // файл с результатами

fso.CreateFolder(source); // Создать исходный каталог
shell.Run("%WINDIR%\\notepad.exe " + source + filename, 1, true); // Создать исходный файл с помощью Блокнота
var file = fso.GetFile(source + "\\" + filename);
var text = file.OpenAsTextStream(1).ReadAll();
var text_result = text;

WScript.Echo('text: "' + text_result + '"\n');

sub_string = new String("aoeiuy");

function print_word(string,i){
	word = "";
	while (true){
		word = word.concat(string.charAt(i));
		i += 1;
		if (string.charAt(i) == " " || string.charAt(i) == "." || string.charAt(i) == ",")
			break;
	}
	WScript.Echo(word);
	return 1;
}

/* function find_words(string,sub_string){
	var n = string.length;
	var i;
	var count=0;
	for (i=1;i<=n;i++){
		if (string.charAt(i) == " ")
			if (sub_string.lastIndexOf(string.charAt(i+1)) != -1){
				print_word(string,i+1);
				count+=1;
			}
	}
	WScript.Echo("number of words: " + count);
} */


function find_words(string, sub_string) {
    var n = string.length;
    var i;
    var count = 0;
    var words = "";

    for (i = 0; i < n; i++) {
        if (string.charAt(i) == " ") {
            if (sub_string.indexOf(string.charAt(i + 1)) != -1) {
                var word = print_word(string, i + 1);
                words += word + '\n';
                count += 1;
            }
        }
    }
    return words;
}
WScript.Echo(text_result);
find_words(text_result,sub_string);


/* if (result && resultFile)
{
	var outfile = fso.CreateTextFile(result +"\\" + resultFile, true);
	outfile.Write('text: "' + text_result + '"\n');

	var words = find_words(text_result, sub_string, outfile); // Вызываем функцию и передаем файл для записи результата

	outfile.Write(words); // Записываем слова в файл
	outfile.Close(); // Закрываем файл
} */