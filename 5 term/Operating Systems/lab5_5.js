var address = WScript.Arguments(0) + '\\';  
var name_p = WScript.Arguments(1); 
var mode = WScript.Arguments(2); 
var Shell = WScript.CreateObject("WScript.Shell");  
Shell.Run('%WINDIR%\\notepad.exe "' + address + name_p + '"', 1, true);  
if (mode == "cmd") 
{
    WScript.Echo('%COMSCPEC% /K cscript "' + address + name_p + '"');
    Shell.Run('%COMSPEC% /K cscript "' + address + name_p + '"');  
}
else if (mode == "window")
{
    WScript.Echo('%COMSPEC% /K wscript "' + address + name_p); 
    Shell.Run('%COMSPEC% /c wscript "' + address + name_p + '"'); 
}
else 
    WScript.Echo("Ошибка выбора режима запуска процедуры");