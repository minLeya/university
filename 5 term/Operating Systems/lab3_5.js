var input_text;
input_text = WScript.arguments(0);

function  findWords(word) {
    var message = word.split(/[ ,.]/);
    var numberOfWords = 0;
    for (var i = 0; i < message.length; i++)
    {
       if (message[i].charAt(0) == "e" ||
           message[i].charAt(0) == "y" ||
           message[i].charAt(0) == "u" ||
           message[i].charAt(0) == "i" ||
           message[i].charAt(0) == "o" ||
           message[i].charAt(0) == "a" )
        {
            WScript.Echo(message[i]);
            ++numberOfWords;
        }
    }

    return numberOfWords;
}

WScript.Echo("text: " + input_text);
var numberOfFoundWords = findWords(input_text);
WScript.Echo("number of words: " + numberOfFoundWords);