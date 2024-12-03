const fs = require('fs');

function myFunction(x) {
	return (-26 + 1295 * x - 152968 * Math.pow(x, 3)
		+ 6812171 * Math.pow(x, 5) - 14 * Math.pow(0.56, 3) - 5 * Math.pow(0.56, 5) - 55);
}

function firstDerivative(x) {
    return (34060855 * x**4 - 458904 * x**2 + 1295);
}

function secondDeriative(x) {
    return (136243420 * x**3 - 917808 * x);
}

function convergenceCondition(x)
{
    return (myFunction(x) * secondDeriative(x));
}

function nextForNewtonMethod(lastX) {
    let functionValue = myFunction(lastX);
    let denominator = firstDerivative(lastX);
    return (lastX - functionValue / denominator);
}

function newtonMethod(lastX, epsilon, delta)
{
    let currentIteration = 0;
    let iterations = [];
    let keepGoing = true;
    while(keepGoing) {
        let fDerivative = firstDerivative(lastX);
        if (fDerivative != 0) {
            let nextX = nextForNewtonMethod(lastX);
            let xDifferense = Math.abs(nextX - lastX);
            let functionValue = Math.abs(myFunction(nextX));

            lastX = nextX;

            ++currentIteration;
            iterations.push({
                currentIteration: currentIteration,
                lastX: lastX,
                nextX: nextX,
                xDifferense: xDifferense
            })
            
            if(xDifferense <= epsilon && functionValue <= delta) {
                keepGoing = false;
            }
        }
        else {
            console.log("Первая производная равна 0!");
        }
        
    }

    let lastIteration = iterations[iterations.length - 1];
    let finalX = lastIteration.lastX;

    saveToFile(iterations, finalX);
    console.log("Найденный приближенный корень:");
    console.log("x =", lastX);
}

function saveToFile(iterations, finalX) {

    let csvContent = "итерация,x_k,x_k+1,|x_k+1 - x_k|\n";
    iterations.forEach(element => {
        csvContent += `${element.currentIteration},${element.lastX},${element.nextX},${element.xDifferense}\n`;
    });
    csvContent += `Макс. допустимое содержание Fe в питьевой воде: ${finalX} мг/л\n`;

    fs.writeFileSync('newtonMethod.csv', csvContent);
    console.log("Результаты в файле");
}

let firstX = -0.1;
let epsilon = 1e-3;
let delta = 1e-3;
let check = convergenceCondition(firstX); 
console.log(check);
if (check > 0) {
    newtonMethod(firstX, epsilon, delta);
}
else {
    console.log("Не выполняется условие сходимости метода Ньютона!");
}

