var n;
var p;
var result = 0;
n = WScript.arguments(0);
p = WScript.arguments(1);
function factorial(num)
{
    if (num <=1) {
        return 1;
    } 
    else {
        return num*factorial(num-1);
    }
}

for (var i = 1; i <=n; i++)
{
    result += (factorial(i) * Math.exp(i))/Math.pow(i, i+p);
}
WScript.Echo("result with ", n, " iterations and p = ", p, " ");
WScript.Echo(result);