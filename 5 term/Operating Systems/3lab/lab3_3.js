var n;
var x;
n = WScript.arguments(0);
x = WScript.arguments(1);

WScript.Echo("data: n = "+n+" and x = " + x);
function factorial(n)
{
	if (n==0) return 1;
	else return (n*factorial(n-1));
}
var result = (Math.pow(n, 2)*Math.pow(x, n))/(factorial(2*n + 1));
result = result.toFixed(6);
WScript.Echo(result);