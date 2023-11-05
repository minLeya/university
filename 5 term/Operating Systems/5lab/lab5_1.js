var of; 
var shell=WScript.CreateObject("WScript.Shell"); 
    WScript.Echo("open notebook."); 
    shell.Run(shell.ExpandEnvironmentStrings("%windir%\\notepad.exe"),1,true);
