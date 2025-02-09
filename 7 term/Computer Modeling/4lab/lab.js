const fs = require('fs');
const math = require('mathjs');

function calculateDirectLinearRegression(pairs, a0, a1) {
    const xi = pairs.map(pair => pair.x);
    const yi = pairs.map(pair => pair.y);
    const n = pairs.length;
    const sumYi = math.sum(yi);
    const yMean = sumYi / n;

    const yPredictions = xi.map(x => a0 + a1 * x);
    const numerators = yPredictions.map(yPred => (yPred - yMean) ** 2);
    const denominators = yi.map(y => (y - yMean) ** 2);

    const R_squared = math.sum(numerators) / math.sum(denominators);

    return {
        xValues: xi,
        yPredictions,
        yMean,
        R_squared,
        a0,
        a1
    };
}

function calculateReverseLinearRegression(pairs, b0, b1) {
    const xi = pairs.map(pair => pair.x);
    const yi = pairs.map(pair => pair.y);
    const n = pairs.length;
    const sumXi = math.sum(xi);
    const xMean = sumXi / n;

    const xPredictions = yi.map(y => b0 + b1 * y);
    const numerators = xPredictions.map(xPred => (xPred -xMean) ** 2);
    const denominators = xi.map(x => (x - xMean) ** 2);

    const R_squared = math.sum(numerators) / math.sum(denominators);

    return {
        yValues: yi,
        xPredictions,
        xMean,
        R_squared,
        b0,
        b1
    };
}

function calculateExponentialRegression(pairs) {
    const xi = pairs.map(pair => pair.x);
    const yi = pairs.map(pair => pair.y);
    const n = pairs.length;

    const lnYi = yi.map(y => Math.log(y));
    const sumXi = math.sum(xi);
    const sumLnYi = math.sum(lnYi);
    const sumXiLnYi = math.sum(xi.map((x, i) => x * lnYi[i]));
    const sumXiSquared = math.sum(xi.map(x => x ** 2));

    const b1 = (n * sumXiLnYi - sumXi * sumLnYi) / (n * sumXiSquared - sumXi ** 2);
    const b0 = (sumLnYi - b1 * sumXi) / n;

    const a0 = Math.exp(b0);
    const a1 = b1;

    const yMean = math.mean(yi);
    const yPredictions = xi.map(x => a0 * Math.exp(a1 * x));
    const numerators = yPredictions.map(yPred => (Math.log(yPred) - Math.log(yMean)) ** 2);
    const denominators = lnYi.map(lnY => (lnY - Math.log(yMean)) ** 2);

    const R_squared = math.sum(numerators) / math.sum(denominators);

    return {
        xValues: xi,
        yPredictions,
        yMean,
        R_squared,
        a0,
        a1
    };
}

function calculateHyperbolicRegression(pairs) {
    const xi = pairs.map(pair => pair.x);
    const yi = pairs.map(pair => pair.y);
    const n = pairs.length;

    const zi = xi.map(x => 1 / x);
    const ziSquared = zi.map(z => z ** 2);
    const yiZi = yi.map((y, index) => y * zi[index]);

    // Вычисляем коэффициенты регрессии
    const a1 = (n * math.sum(yiZi) - math.sum(yi) * math.sum(zi)) / (n * math.sum(ziSquared) - math.square(math.sum(zi)));
    const a0 = (math.sum(yi) - a1 * math.sum(zi)) / n;

    const yMean = math.mean(yi);

    const yPredictions = zi.map(z => a0 + a1 * z);

    const numerators = yPredictions.map(yPred => (yPred - yMean) ** 2);
    const denominators = yi.map(y => (y - yMean) ** 2);

    const R_squared = math.sum(numerators) / math.sum(denominators);

    return {
        xValues: xi,
        yPredictions,
        yMean,
        R_squared,
        a0,
        a1
    };
}

function gauss(A, B) {
    const n = A.length;

    // Прямой ход (приведение к верхней треугольной матрице)
    for (let i = 0; i < n; i++) {
        // Поиск строки с максимальным элементом
        let maxRow = i;
        for (let r = i + 1; r < n; r++) {
            if (Math.abs(A[r][i]) > Math.abs(A[maxRow][i])) {
                maxRow = r;
            }
        }

        // Меняем строки местами
        [A[i], A[maxRow]] = [A[maxRow], A[i]];
        [B[i], B[maxRow]] = [B[maxRow], B[i]];

        // Приведение к нулю элементов ниже главной диагонали
        for (let j = i + 1; j < n; j++) {
            const ratio = A[j][i] / A[i][i];
            for (let k = i; k < n; k++) {
                A[j][k] -= ratio * A[i][k];
            }
            B[j] -= ratio * B[i];
        }
    }

    // Обратный ход (вычисление переменных)
    const X = Array(n).fill(0);
    for (let i = n - 1; i >= 0; i--) {
        X[i] = B[i] / A[i][i];
        for (let j = i - 1; j >= 0; j--) {
            B[j] -= A[j][i] * X[i];
        }
    }

    return X;
}

function calculateParabolicRegression(pairs) {
    const xi = pairs.map(pair => pair.x);
    const yi = pairs.map(pair => pair.y);
    const n = pairs.length;

    const xiSquared = xi.map(x => x ** 2);
    const xiCubed = xi.map(x => x ** 3);
    const xiQuarter = xi.map(x => x ** 4);
    const yiXiSquared = yi.map((y, index) => y * xiSquared[index]);

    // Формируем матрицы A и B
    const A = [
        [n, math.sum(xi), math.sum(xiSquared)],
        [math.sum(xi), math.sum(xiSquared), math.sum(xiCubed)],
        [math.sum(xiSquared), math.sum(xiCubed), math.sum(xiQuarter)]
    ];
    const B = [
        math.sum(yi),
        math.sum(yi.map((y, index) => y * xi[index])),
        math.sum(yiXiSquared)
    ];

    // Вычисляем коэффициенты методом Гаусса
    const [a0, a1, a2] = gauss(A, B);

    const yMean = math.mean(yi);
    const yPredictions = xi.map((x, index) => a0 + a1 * x + a2 * xiSquared[index]);

    const numerators = yPredictions.map(yPred => (yPred - yMean) ** 2);
    const denominators = yi.map(y => (y - yMean) ** 2);

    const R_squared = math.sum(numerators) / math.sum(denominators);

    return {
        xValues: xi,
        yPredictions,
        yMean,
        R_squared,
        a0,
        a1,
        a2
    };
}


function calculatePowerRegression(pairs) {
    const xi = pairs.map(pair => pair.x);
    const yi = pairs.map(pair => pair.y);
    const n = pairs.length;

    const lnXi = xi.map(x => Math.log(x));
    const lnYi = yi.map(y => Math.log(y));
    const lnYiLnXi = lnYi.map((lnY, index) => lnY * lnXi[index]);

    const b1 = (n * math.sum(lnYiLnXi) - math.sum(lnYi) * math.sum(lnXi)) / 
               (n * math.sum(lnXi.map(x => x ** 2)) - math.square(math.sum(lnXi)));
    const b0 = (math.sum(lnYi) - b1 * math.sum(lnXi)) / n;

    const a0 = Math.exp(b0);
    const a1 = b1;

    const yMean = math.mean(yi);
    const lnYPredictions = lnXi.map(x => b0 + b1 * x);

    const numerators = lnYPredictions.map(pred => (pred - Math.log(yMean)) ** 2);
    const denominators = lnYi.map(y => (y - Math.log(yMean)) ** 2);

    const R_squared = math.sum(numerators) / math.sum(denominators);

    return {
        xValues: xi,
        yPredictions: lnYPredictions.map(Math.exp), // Преобразуем обратно из логарифмов
        yMean,
        R_squared,
        a0,
        a1
    };
}

function calculateLogarithmicRegression(pairs) {
    const xi = pairs.map(pair => pair.x);
    const yi = pairs.map(pair => pair.y);
    const n = pairs.length;

    const lnXi = xi.map(x => Math.log(x));
    const yiLnXi = yi.map((y, index) => y * lnXi[index]);

    const a1 = (n * math.sum(yiLnXi) - math.sum(yi) * math.sum(lnXi)) / 
               (n * math.sum(lnXi.map(x => x ** 2)) - math.square(math.sum(lnXi)));
    const a0 = (math.sum(yi) - a1 * math.sum(lnXi)) / n;

    const yMean = math.mean(yi);
    const yPredictions = lnXi.map(x => a0 + a1 * x);

    const numerators = yPredictions.map(yPred => (yPred - yMean) ** 2);
    const denominators = yi.map(y => (y - yMean) ** 2);

    const R_squared = math.sum(numerators) / math.sum(denominators);

    return {
        xValues: xi,
        yPredictions,
        yMean,
        R_squared,
        a0,
        a1
    };
}

fs.readFile('input.txt', 'utf8', (err, data) => {
    if (err) {
        console.error('Ошибка чтения файла:', err);
        return;
    }

    // Преобразуем строки файла в массив объектов с y и x
    const lines = data.split('\n').filter(line => line.trim() !== '');
    const pairs = lines.map(line => {
        const [y, x] = line.split(',').map(Number);
        return { y, x };
    });

    clearFile('output.txt', (err) => {
        if(!err) {
        // Линейная регрессия
        const linearResults = calculateDirectLinearRegression(pairs, 2.87, 20.61);
        writeResultsToFile(linearResults, 'Линейная регрессия');
        // Линейная обратная регрессия
        const linearReverseResults = calculateReverseLinearRegression(pairs, 0.115, 0.00538);
        writeResultsToFileReverse(linearReverseResults, 'Линейная обратная регрессия');
        // Гиперболическая регрессия
        const hyperbolicResults = calculateHyperbolicRegression(pairs);
        writeResultsToFile(hyperbolicResults, 'Гиперболическая регрессия')
        // Экспоненциальная регрессия
        const exponentialResults = calculateExponentialRegression(pairs);
        writeResultsToFile(exponentialResults, 'Экспоненциальная регрессия');
        // Параболическая регрессия
        const parabolicResults = calculateParabolicRegression(pairs);
        writeResultsToFileParabol(parabolicResults, 'Параболическая регрессия');
        // Степенная регрессия
        const powerResults = calculatePowerRegression(pairs);
        writeResultsToFile(powerResults, 'Степенная регрессия')
        // Логарифмическая регрессия
        const logarithmicResults = calculateLogarithmicRegression(pairs);
        writeResultsToFile(logarithmicResults, 'Логарифмическая регрессия');
        }
    })
   
});

function writeResultsToFileParabol(results, title) {
    let output = `\t\t\t${title}\n`;
    output += `Значения х: ${results.xValues.join(', ')}\n`;
    output += `Предсказанные значения y: ${results.yPredictions.map(y => y.toFixed(4)).join(', ')}\n`;
    output += `Среднее значение y: ${results.yMean.toFixed(4)}\n`;
    output += `Коэффициент детерминации R^2: ${results.R_squared.toFixed(4)}\n`;
    output += `a0: ${results.a0.toFixed(4)}\n`;
    output += `a1: ${results.a1.toFixed(4)}\n`;
    output += `a2: ${results.a2.toFixed(4)}\n`;

    fs.appendFile('out.txt', output, (err) => {
        if (err) {
            console.error('Ошибка записи в файл:', err);
            return;
        }
        console.log(`${title} успешно записана в файл out_data.txt`);
    });
}

function clearFile(filePath, callback) {
    fs.writeFile(filePath, '', (err) => {
        if (err) {
            console.error('Ошибка очистки файла:', err);
            if (callback) callback(err);
            return;
        }
        console.log(`Файл ${filePath} успешно очищен.`);
        if (callback) callback(null);
    });
}

function writeResultsToFileReverse(results, title) {
    let output = `\t\t\t${title}\n`;
    output += `Значения y: ${results.yValues.join(', ')}\n`;
    output += `Предсказанные значения x: ${results.xPredictions.map(x => x.toFixed(4)).join(', ')}\n`;
    output += `Среднее значение x: ${results.xMean.toFixed(4)}\n`;
    output += `Коэффициент детерминации R^2: ${results.R_squared.toFixed(4)}\n\n`;

    fs.appendFile('output.txt', output, (err) => {
        if (err) {
            console.error('Ошибка записи в файл:', err);
            return;
        }
        console.log(`${title} успешно записана в файл output_data.txt`);
    });
}

function writeResultsToFile(results, title) {
    let output = `\t\t\t${title}\n`;
    output += `Значения х: ${results.xValues.join(', ')}\n`;
    output += `Предсказанные значения y: ${results.yPredictions.map(y => y.toFixed(4)).join(', ')}\n`;
    output += `Среднее значение y: ${results.yMean.toFixed(4)}\n`;
    output += `Коэффициент детерминации R^2: ${results.R_squared.toFixed(4)}\n`;
    output += `a0: ${results.a0.toFixed(4)}\n`;
    output += `a1: ${results.a1.toFixed(4)}\n`;

    fs.appendFile('output.txt', output, (err) => {
        if (err) {
            console.error('Ошибка записи в файл:', err);
            return;
        }
        console.log(`${title} успешно записана в файл output_data.txt`);
    });
}

function clearFile(filePath, callback) {
    fs.writeFile(filePath, '', (err) => {
        if (err) {
            console.error('Ошибка очистки файла:', err);
            if (callback) callback(err);
            return;
        }
        console.log(`Файл ${filePath} успешно очищен.`);
        if (callback) callback(null);
    });
}

// графики
// Загрузка данных из input.txt
function loadData() {
    return new Promise((resolve, reject) => {
        fs.readFile('input.txt', 'utf8', (err, data) => {
            if (err) {
                reject('Ошибка чтения файла');
            } else {
                const lines = data.split('\n').filter(line => line.trim() !== '');
                const pairs = lines.map(line => {
                    const [y, x] = line.split(',').map(Number);
                    return { y, x };
                });
                resolve(pairs);
            }
        });
    });
}

// Генерация HTML с графиками
function loadData() {
    return new Promise((resolve, reject) => {
        fs.readFile('in.txt', 'utf8', (err, data) => {
            if (err) {
                reject('Ошибка чтения файла');
            } else {
                const lines = data.split('\n').filter(line => line.trim() !== '');
                const pairs = lines.map(line => {
                    const [y, x] = line.split(',').map(Number);
                    return { y, x };
                });
                resolve(pairs);
            }
        });
    });
}


    function generateHTML(pairs, linearResults, hyperbolicResults, exponentialResults, powerResults, parabolResults, logarithmicResults) {
        // Сортируем пары данных по X
        const sortedPairs = pairs.slice().sort((a, b) => a.x - b.x);
    
        const sortedPredictionsLinear = sortedPairs.map(pair => {
            const index = pairs.findIndex(p => p.x === pair.x);
            return linearResults.yPredictions[index];
        });

        const sortedPredictionsExponential = sortedPairs.map(pair => {
            const index = pairs.findIndex(p => p.x === pair.x);
            return exponentialResults.yPredictions[index];
        });

        const sortedPredictionsLogarithmic = sortedPairs.map(pair => {
            const index = pairs.findIndex(p => p.x === pair.x);
            return logarithmicResults.yPredictions[index];
        });
        
        
        // Сортируем предсказания по X
        const sortedPredictionsHyper = sortedPairs.map(pair => {
            const index = pairs.findIndex(p => p.x === pair.x);
            return hyperbolicResults.yPredictions[index];
        });

        const sortedPredictionsPower = sortedPairs.map(pair => {
            const index = pairs.findIndex(p => p.x === pair.x);
            return powerResults.yPredictions[index];
        });
    
        const sortedPredictionsParabol = sortedPairs.map(pair => {
            const index = pairs.findIndex(p => p.x === pair.x);
            return parabolResults.yPredictions[index];
        });
        const data = {
            labels: sortedPairs.map(pair => pair.x), // X значения в отсортированном порядке
            datasets: [
                {
                    label: 'Исходные данные',
                    data: sortedPairs.map(pair => pair.y), // Y значения в отсортированном порядке
                    borderColor: 'rgba(75, 192, 192, 1)',
                    backgroundColor: 'rgba(75, 192, 192, 0.2)',
                    pointRadius: 5,
                    showLine: false, 
                },
                {
                    label: 'Гиперболическая регрессия',
                    data: sortedPredictionsHyper, // Предсказания в порядке X
                    borderColor: 'rgba(153, 102, 255, 1)',
                    backgroundColor: 'rgba(153, 102, 255, 0.2)',
                    fill: false,
                    lineTension: 0.1,
                },
                {
                    label: 'Степенная регрессия',
                    data: sortedPredictionsPower, // Предсказания в порядке X
                    borderColor: 'rgba(100, 100, 100, 1)',
                    backgroundColor: 'rgba(100, 100, 100, 0.2)',
                    fill: false,
                    lineTension: 0.1,
                },
                {
                    label: 'Пароболическая регрессия',
                    data: sortedPredictionsParabol, // Предсказания в порядке X
                    borderColor: 'rgba(200, 100, 100, 1)',
                    backgroundColor: 'rgba(200, 100, 100, 0.2)',
                    fill: false,
                    lineTension: 0.1,
                },
                {
                    label: 'Линейная регрессия',
                    data: sortedPredictionsLinear, // Предсказания в порядке X
                    borderColor: 'rgba(0, 0, 0, 1)',
                    backgroundColor: 'rgba(0, 0, 0, 0.2)',
                    fill: false,
                    lineTension: 0.1,
                },
                {
                    label: 'Экспоненциальная регрессия',
                    data: sortedPredictionsExponential, // Предсказания в порядке X
                    borderColor: 'rgba(150, 150, 150, 1)',
                    backgroundColor: 'rgba(150, 150, 150, 0.2)',
                    fill: false,
                    lineTension: 0.1,
                },
                {
                    label: 'Логарифмическая регрессия',
                    data: sortedPredictionsLogarithmic, // Предсказания в порядке X
                    borderColor: 'rgba(20, 15, 15, 1)',
                    backgroundColor: 'rgba(20, 15, 15, 0.2)',
                    fill: false,
                    lineTension: 0.1,
                },
            ]
        };
    
        return `
            <!DOCTYPE html>
            <html lang="ru">
            <head>
                <meta charset="UTF-8">
                <meta name="viewport" content="width=device-width, initial-scale=1.0">
                <title>Графики регрессий</title>
                <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
                <style>
                    body, html {
                        margin: 0;
                        padding: 0;
                        height: 100%;
                        overflow: hidden;
                    }
                    canvas {
                        display: block;
                        width: 100vw;
                        height: 100vh;
                    }
                </style>
            </head>
            <body>
                <h1 style="position: absolute; top: 10px; left: 10px; z-index: 10; color: white;">Графики регрессий</h1>
                <canvas id="regressionChart"></canvas>
                <script>
                    const ctx = document.getElementById('regressionChart').getContext('2d');
                    const chart = new Chart(ctx, {
                        type: 'line',
                        data: ${JSON.stringify(data)},
                        options: {
                            responsive: true,
                            maintainAspectRatio: false,
                            scales: {
                                x: { 
                                    title: { display: true, text: 'X' }
                                },
                                y: {
                                    title: { display: true, text: 'Y' }
                                }
                            },
                            plugins: {
                                legend: {
                                    position: 'top',
                                },
                            }
                        }
                    });
                </script>
            </body>
            </html>
        `;
    }
    

// Создание HTML страницы с графиками
loadData().then(pairs => {
   
    const hyperbolicResults = calculateHyperbolicRegression(pairs);
    const powerResults = calculatePowerRegression(pairs);
    const parabolResults = calculateParabolicRegression(pairs);
    const linearResults = calculateDirectLinearRegression(pairs);
    const expResults = calculateExponentialRegression(pairs);
    const logResults = calculateLogarithmicRegression(pairs);

  

    const htmlContent = generateHTML(
        pairs,
        hyperbolicResults,
        powerResults,
        parabolResults,
        linearResults,
        expResults,
        logResults

    );

    fs.writeFileSync('task.html', htmlContent);
    console.log('HTML файл с графиками успешно создан: task.html');
}).catch(err => {
    console.error('Ошибка загрузки данных:', err);
});