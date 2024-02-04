// wscript.js – создание объекта Internet Explorer и открытие указанного
//сайта
if(WScript.Arguments.Count()==1)
{

var iexplorer=WScript.CreateObject("InternetExplorer.Application");
 iexplorer.Visible=true;
 iexplorer.Navigate(WScript.Arguments(0));
}else
 WScript.Echo("Usage: cscript //nologo "+WScript.ScriptFullName+
" http://www.rsdn.ru/"); 