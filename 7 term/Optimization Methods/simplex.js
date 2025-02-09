class Point {
    constructor(x1, x2) {
        this.x1 = x1;
        this.x2 = x2;
    }
}

function F(p) {
    return(2 * p.x1**2 + 2 * p.x2**2 + 2 * p.x1 * p.x2 - 14 * p.x1 - 12 * p.x2 + 29);
}

function printTableHeader() {
    console.log("Итерация".padEnd(10) + "Точка".padEnd(10) + "x1".padEnd(15) + "x2".padEnd(15) + "F(X)".padEnd(15));
}

function printTableRow(pointName, p, fValue) {
    console.log(
        pointName.padEnd(10) +
        p.x1.toFixed(10).padEnd(15) +
        p.x2.toFixed(10).padEnd(15) +
        fValue.toFixed(10).padEnd(15)
    );
}

// вычисление двух точек по базовой точке
function calculatePointByX0(X0, d1, d2, number) {
    let x1 = number === 1 ? X0.x1 + d1 : X0.x1 + d2;
    let x2 = number === 2 ? X0.x2 + d1 : X0.x2 + d2;
    return new Point(x1, x2);
}

// основная функция
function searchByCorrectSimplex(epsilon, t) {
    const n = 2;
    let d1 = t / (n * Math.sqrt(2)) * (Math.sqrt(n+1) + n - 1);
    let d2 = t / (n * Math.sqrt(2)) * (Math.sqrt(n+1) - 1);

    let X0 = new Point(2.6666, 1.6666);
    let simplex = [
        X0,
        calculatePointByX0(X0, d1, d2, 1),
        calculatePointByX0(X0, d1, d2, 2)
    ];

    // шаг 1. массив со значениями функции в каждой точке из simplex
    let fValues = simplex.map(p => F(p));
    let step = 0;
    printTableHeader();

    while (true) {
        // шаг 2. сортировка по возрастанию значений функции
        simplex.sort((a, b) => F(a) - F(b));
        fValues = simplex.map(p => F(p));

        // вывод на консоль
        console.log(`Шаг ${step}, t = ${t}`);
        simplex.forEach((p, index) => printTableRow("\t\t\tX" + index, p, fValues[index]));

        // шаг 3. проверка на точность
        // сумма квадратов разностей между каждым значением функции и первым значением fValues
        let sum = fValues.reduce((acc, f) => acc + Math.pow(f - fValues[0], 2), 0);
        let accuracy = sum / n;
        if (accuracy < epsilon) {
            console.log("Точность достигнута.");
            break;
        }

        // шаг 4. отражение по центроиду вершины X^n
        let c = centroid(simplex);
        let xr = reflect(c, simplex[simplex.length - 1]);
        let fXr = F(xr);

        // шаг 4. сравнение новой и прошлой точек
        if (fXr < fValues[fValues.length - 1]) {
            simplex[simplex.length - 1] = xr;
            step++;
            continue;
        }

        // шаг 5. отражение по центроиду вершины X^n-1
        c = centroid_n_1(simplex);
        xr = reflect(c, simplex[simplex.length - 2]); 
        fXr = F(xr);

        if (fXr < fValues[fValues.length - 2]) { 
            simplex[simplex.length - 1] = xr; 
            step++; 
            continue;
        }        

        // шаг 6. построение нового симплекса с вдвое меньше ребром
        t /= 2;
        for (let i = 1; i < simplex.length; i++) {
            simplex[i].x1 = (simplex[i].x1 + simplex[0].x1) / 2;
            simplex[i].x2 = (simplex[i].x2 + simplex[0].x2) / 2;
        }

        step++;
    }
}

function centroid(simplex) {
    let c = new Point(0, 0);
    // суммируем координаты x1 и x2 без последней
    for (let i = 0; i < simplex.length - 1; i++) {
        c.x1 += simplex[i].x1; 
        c.x2 += simplex[i].x2;
    }
    // находим среднее значение
    c.x1 /= (simplex.length - 1); 
    c.x2 /= (simplex.length - 1); 

    return c;
}

function centroid_n_1(simplex) {
    let c = new Point(0, 0);
    for (let i = 0; i < simplex.length; i++) {
        if (i !== simplex.length - 2) {
            c.x1 += simplex[i].x1;
            c.x2 += simplex[i].x2;
        }
    }
    c.x1 /= (simplex.length - 1);
    c.x2 /= (simplex.length - 1);
    return c;
}

// функция для отражения точки
function reflect(centroid, worst) {
    return new Point(2 * centroid.x1 - worst.x1, 2 * centroid.x2 - worst.x2);
}

searchByCorrectSimplex(0.01, 1.0);