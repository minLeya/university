if (WScript.Arguments.count() == 3) {
    var command = WScript.Arguments(0);
    var path = WScript.Arguments(1);
    var filename = WScript.Arguments(2);
 
    var shell = WScript.CreateObject("WScript.Shell");
    var strCommand = "%COMSPEC% /C help " + command + " > \"" + path + filename + "\"";
    WScript.Echo(strCommand);
    shell.Run(strCommand);
} else if (WScript.Arguments.count() == 1) {
    var command = WScript.Arguments(0);
    var shell = WScript.CreateObject("WScript.Shell");
    shell.Run("%COMSPEC% /K help " + command);
} else {
    var shell = WScript.CreateObject("WScript.Shell");
    shell.Run("%COMSPEC% /K help");}
