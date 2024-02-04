var input_text = new String("The text is in english.");

function  findWords(word) {
    var message = word.split(/[ ,.]/);
    var numberOfWords = 0;
    for (var i = 0; i < message.length; i++)
    {
       if (message[i].charAt(0) == "a" ||
           message[i].charAt(0) == "e" ||
           message[i].charAt(0) == "y" ||
           message[i].charAt(0) == "u" ||
           message[i].charAt(0) == "o" ||
           message[i].charAt(0) == "i")
        {
            WScript.Echo(message[i]);
            ++numberOfWords;
        }
    }

    return numberOfWords;
}


WScript.Echo("text: " + input_text);
var numberOfFoundWords = findWords(input_text);
WScript.Echo("number of found words: " + numberOfFoundWords);

// WScript.Echo("The text: " + input_text + "\nwords " + result +  
// "\nThe number of words: " +  result.length);
