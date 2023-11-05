var command, dos_command, option
var Shell = WScript.CreateObject("WScript.Shell");
// Команда вызова командного процессора
command = "%COMSPEC% /K ";
// Команда получения справки о командах MS-DOS
dos_command = "help ";
// Использование постраничного вывода
option = "| more"
// Исполнить команду.
Shell.Run(command + dos_command + option);
