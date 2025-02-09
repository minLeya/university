const fs = require('fs');

//начальные условия
let delta_e = 15, gamma = 2, omega_x1 = 7;
let t = 0, dt = 0.01, t_max = 10;
let epsilon = 1e-3; //точность для остановки, когда gamma почти 0 

//массивы для хранения результатов
let t_arr = [];
let delta_e_arr = [];
let gamma_arr = [];
let omega_x1_arr = [];

//функции
function f1(t, delta_e, gamma, omega_x1) {
    return (-10 * delta_e - 10.74 * omega_x1 - 66.97 * gamma);
}

function f2(t, delta_e, gamma, omega_x1) {
    return omega_x1;
}

function f3(t, delta_e, gamma, omega_x1) {
    return (-omega_x1 + 5 * delta_e);
}

//метод рунге-кутта 4-го порядка
function rungeKuttaMethod() {
    while (t < t_max) {
        t_arr.push(t);
        delta_e_arr.push(delta_e);
        gamma_arr.push(gamma);
        omega_x1_arr.push(omega_x1);

        let K1i = dt * f1(t, delta_e, gamma, omega_x1);
        let M1i = dt * f2(t, delta_e, gamma, omega_x1);
        let L1i = dt * f3(t, delta_e, gamma, omega_x1);

        let K2i = dt * f1(t + 0.5 * dt, delta_e + 0.5 * K1i, gamma + 0.5 * M1i, omega_x1 + 0.5 * L1i);
        let M2i = dt * f2(t + 0.5 * dt, delta_e + 0.5 * K1i, gamma + 0.5 * M1i, omega_x1 + 0.5 * L1i);
        let L2i = dt * f3(t + 0.5 * dt, delta_e + 0.5 * K1i, gamma + 0.5 * M1i, omega_x1 + 0.5 * L1i);

        let K3i = dt * f1(t + 0.5 * dt, delta_e + 0.5 * K2i, gamma + 0.5 * M2i, omega_x1 + 0.5 * L2i);
        let M3i = dt * f2(t + 0.5 * dt, delta_e + 0.5 * K2i, gamma + 0.5 * M2i, omega_x1 + 0.5 * L2i);
        let L3i = dt * f3(t + 0.5 * dt, delta_e + 0.5 * K2i, gamma + 0.5 * M2i, omega_x1 + 0.5 * L2i);

        let K4i = dt * f1(t + dt, delta_e + K3i, gamma + M3i, omega_x1 + L3i);
        let M4i = dt * f2(t + dt, delta_e + K3i, gamma + M3i, omega_x1 + L3i);
        let L4i = dt * f3(t + dt, delta_e + K3i, gamma + M3i, omega_x1 + L3i);

        // Обновление значений
        t += dt;
        delta_e += 1 / 6 * (K1i + 2 * K2i + 2 * K3i + K4i);
        gamma += 1 / 6 * (M1i + 2 * M2i + 2 * M3i + M4i);
        omega_x1 += 1 / 6 * (L1i + 2 * L2i + 2 * L3i + L4i);

        //проверка на установившееся состояние - если gamma близко к нулю
        if (Math.abs(gamma) < epsilon) {
            console.log("Установившееся значение для gamma достигнуто.");
            t_arr.push(t);
            delta_e_arr.push(delta_e);
            gamma_arr.push(gamma);
            omega_x1_arr.push(omega_x1);
            break;
        }
    }
}

//вызываем метод
rungeKuttaMethod();


//графическое отображение
let trace1 = {
    x: t_arr,
    y: delta_e_arr,
    mode: 'lines',
    name: 'delta_e',
    line: {color: 'blue', width: 2}
};

let trace2 = {
    x: t_arr,
    y: gamma_arr,
    mode: 'lines',
    name: 'gamma',
    line: {color: 'red', width: 2, dash: 'dash'}
};

let trace3 = {
    x: t_arr,
    y: omega_x1_arr,
    mode: 'lines',
    name: 'omega_x1',
    line: {color: 'green', width: 2, dash: 'dot'}
};

let data = [trace1, trace2, trace3];

let layout = {
    title: 'Решение системы дифференциальных уравнений методом Рунге-Кутта 4 порядка',
    xaxis: {title: 'Время'},
    yaxis: {title: 'Значения переменных'},
    showlegend: true
};


//создаем страницу html для графика
const graphDiv = `
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>График</title>
    <script src="https://cdn.plot.ly/plotly-latest.min.js"></script>
</head>
<body>
    <div id="myDiv" style="width:100%;height:100vh;"></div>
    <script>
        var data = ${JSON.stringify(data)};
        var layout = ${JSON.stringify(layout)};
        Plotly.newPlot('myDiv', data, layout);
    </script>
</body>
</html>
`;

fs.writeFileSync('graph.html', graphDiv);
console.log("График сохранен в файл graph.html");


//запись значений переменных в текстовый файл
let textData = 't\t\tdelta_e\t\tgamma\t\tomega_x1\n';
for (let i = 0; i < t_arr.length; i++) {
    textData += `${t_arr[i].toFixed(8)}\t${delta_e_arr[i].toFixed(8)}\t${gamma_arr[i].toFixed(8)}\t${omega_x1_arr[i].toFixed(8)}\n`;
}
fs.writeFileSync('results.txt', textData);
console.log("Значения сохранены в файл results.txt");