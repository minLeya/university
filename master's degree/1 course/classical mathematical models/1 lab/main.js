const fs = require('fs');
const math = require('mathjs');

// ---------------- Регрессии -----------------
function calculateDirectLinearRegression(pairs) {
    const xi = pairs.map(p => p.x);
    const yi = pairs.map(p => p.y);
    const n = pairs.length;

    const sumX = math.sum(xi);
    const sumY = math.sum(yi);
    const sumXY = math.sum(xi.map((x,i) => x*yi[i]));
    const sumX2 = math.sum(xi.map(x => x**2));

    const a0 = (sumY * sumX2 - sumX * sumXY) / (n * sumX2 - sumX**2);
    const a1 = (n * sumXY - sumX * sumY) / (n*sumX2 - sumX**2);

    const yPredictions = xi.map(x => a0 + a1*x);
    const yMean = math.mean(yi);
    const R_squared = math.sum(yPredictions.map(y => (y - yMean)**2)) / math.sum(yi.map(y => (y - yMean)**2));

    const prediction = a0 + a1 * (n + 1);

    return {
        yValues: yi,
        yPredictions,
        R_squared,
        a0,
        a1,
        prediction };
}

function calculateExponentialRegression(pairs) {
    const xi = pairs.map(p => p.x);
    const yi = pairs.map(p => p.y);
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

    const ssTotal = math.sum(yi.map(y => (y - yMean) ** 2));
    const ssRegression = math.sum(yPredictions.map(y => (y - yMean) ** 2));
    const R_squared = ssRegression / ssTotal;

    const prediction = a0 * Math.exp(a1 * (n + 1));

    return {
        yValues: yi,
        yPredictions,
        R_squared,
        a0,
        a1,
        prediction
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

    const prediction = a0 + a1 / (n + 1);

    return {
        yValues: yi,
        yPredictions,
        R_squared,
        a0,
        a1,
        prediction
    };
}


function calculateParabolicRegression(pairs) {
    const xi = pairs.map(p => p.x);
    const yi = pairs.map(p => p.y);
    const n = pairs.length;

    const xi2 = xi.map(x => x ** 2);
    const xi3 = xi.map(x => x ** 3);
    const xi4 = xi.map(x => x ** 4);
    const yiXi2 = yi.map((y, i) => y * xi2[i]);

    // Формируем матрицы A и B для решения методом Гаусса
    const A = [
        [n, math.sum(xi), math.sum(xi2)],
        [math.sum(xi), math.sum(xi2), math.sum(xi3)],
        [math.sum(xi2), math.sum(xi3), math.sum(xi4)]
    ];
    const B = [
        math.sum(yi),
        math.sum(yi.map((y, i) => y * xi[i])),
        math.sum(yiXi2)
    ];

    // Решаем систему 
    const solution = math.lusolve(A, B);
    const [a0, a1, a2] = solution.map(arr => arr[0]);

    // Предсказанные значения
    const yPredictions = xi.map((x, i) => a0 + a1 * x + a2 * xi2[i]);
    const yMean = math.mean(yi);

    // Суммы квадратов для R^2
    const ssTotal = math.sum(yi.map(y => (y - yMean) ** 2));
    const ssRegression = math.sum(yPredictions.map(yPred => (yPred - yMean) ** 2));

    const R_squared = ssRegression / ssTotal;

    const prediction = a0 + a1 * (n + 1) + a2 * (n + 1)**2;

    return {
        yValues: yi,
        yPredictions,
        R_squared,
        a0,
        a1,
        a2,
        prediction
    };
}

// ---------------- Вывод в файл -----------------
function writeResultsToFile(title, results, isParabolic=false){
    let output=`\n\t\t${title}\n`;
    output+=`yValues: ${results.yValues.join(', ')}\n`;
    output+=`yPredictions: ${results.yPredictions.map(y=>y.toFixed(4)).join(', ')}\n`;
    output+=`R_squared: ${results.R_squared.toFixed(4)}\n`;
    output+=`a0: ${results.a0.toFixed(4)}\n`;
    output+=`a1: ${results.a1.toFixed(4)}\n`;
    if(isParabolic) output+=`a2: ${results.a2.toFixed(4)}\n`;
    output+=`30.09.2025: ${results.prediction.toFixed(4)}\n`;
    fs.appendFileSync('output.txt', output);
    console.log(`${title} успешно записана.`);
}


// ---------------- Загрузка данных -----------------
function loadPairs(){
    return new Promise((resolve,reject)=>{
        fs.readFile('input.txt','utf8',(err,data)=>{
            if(err) reject(err);
            else {
                const lines=data.split('\n').filter(l=>l.trim()!=='');
                const pairs=lines.map((line,i)=>{
                    const [dateStr,valueStr]=line.split(',').map(s=>s.trim());
                    const x=i+1;
                    const y=parseFloat(valueStr.replace(',','.'));
                    return {x,y,date:dateStr};
                });
                resolve(pairs);
            }
        });
    });
}

// ---------------- Генерация HTML -----------------
function generateHTML(pairs, resultsMap){
    const sortedPairs=[...pairs].sort((a,b)=>a.x-b.x);
    const datasets=[];
    for(const [label,res] of Object.entries(resultsMap)){
        const yData=sortedPairs.map(p=>{
            const idx=pairs.findIndex(orig=>orig.x===p.x);
            return res.yPredictions[idx];
        });
        datasets.push({
            label,
            data:yData,
            borderColor:`hsl(${Math.random()*360},50%,50%)`,
            fill:false,
            pointRadius:3,
            lineTension:0.1
        });
    }
    datasets.unshift({label:'Исходные данные', data:sortedPairs.map(p=>p.y), borderColor:'black', pointRadius:4, showLine:false});
    const data={labels:sortedPairs.map(p=>p.date), datasets};
    return `
<!DOCTYPE html>
<html lang="ru">
<head>
<meta charset="UTF-8">
<title>Графики регрессий</title>
<script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
<style>body,html{margin:0;padding:0;height:100%;}canvas{display:block;width:100vw;height:100vh;}</style>
</head>
<body>
<canvas id="chart"></canvas>
<script>
const ctx=document.getElementById('chart').getContext('2d');
new Chart(ctx,{type:'line',data:${JSON.stringify(data)},options:{responsive:true,maintainAspectRatio:false}});
</script>
</body>
</html> `;
}

// ---------------- Главный блок -----------------
loadPairs().then(pairs=>{
    fs.writeFileSync('output.txt',''); // очистка файла
    const linear=calculateDirectLinearRegression(pairs);
    const hyper=calculateHyperbolicRegression(pairs);
    const exp=calculateExponentialRegression(pairs);
    const parabol=calculateParabolicRegression(pairs);

    writeResultsToFile('Линейная регрессия',linear);
    writeResultsToFile('Гиперболическая регрессия',hyper);
    writeResultsToFile('Экспоненциальная регрессия',exp);
    writeResultsToFile('Параболическая регрессия',parabol,true);

    const html=generateHTML(pairs,{
        'Линейная':linear,
        'Гиперболическая':hyper,
        'Экспоненциальная':exp,
        'Параболическая':parabol,
    });
    fs.writeFileSync('task.html',html);
    console.log('HTML файл task.html создан успешно.');
}).catch(err=>console.error(err));
