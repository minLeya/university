class Point {
    constructor(x1, x2) {
        this.x1 = x1;
        this.x2 = x2;
    }
}

// Функция для вычисления значения целевой функции F в точке
function F(p) {
    return(2 * p.x1**2 + 2 * p.x2**2 + 2 * p.x1 * p.x2 - 14 * p.x1 - 12 * p.x2 + 29);
}

// Вывод заголовка таблицы
function printTableHeader() {
    console.log("Итерация".padEnd(10) + "Точка".padEnd(10) + "x1".padEnd(15) + "x2".padEnd(15) + "F(X)".padEnd(15));
}

// Вывод строки таблицы
function printTableRow(step, label, point, fValue) {
    console.log(step.padEnd(10), label.padEnd(10), point.x1.toFixed(9).padEnd(10),point.x2.toFixed(9).padEnd(10), fValue.toFixed(9).padEnd(10));
}

// Вывод строки с текущими точками
function printCurrentPoints(points, fValues) {
    points.forEach((point, index) => {
        printTableRow("", `X${index}`, point, fValues[index]);
    });
}

// Поиск индекса вершины с максимальным значением функции
function searchPointMaxValue(fValues) {
    return fValues.indexOf(Math.max(...fValues));
}

// Поиск индекса вершины с минимальным значением функции
function searchPointMinValue(fValues) {
    return fValues.indexOf(Math.min(...fValues));
}

// Центр тяжести всех вершин, кроме Xh
function centroidH(points, h) {
    let nPlus2 = new Point(0, 0);
    points.forEach((point, i) => {
        if (i !== h) {
            nPlus2.x1 += point.x1;
            nPlus2.x2 += point.x2;
        }
    });
    nPlus2.x1 /= points.length - 1;
    nPlus2.x2 /= points.length - 1;
    return nPlus2;
}

// Отражение вершины Xh через центр тяжести
function reflection(nPlus2, xh, alpha) {
    return new Point(
        nPlus2.x1 + alpha * (nPlus2.x1 - xh.x1),
        nPlus2.x2 + alpha * (nPlus2.x2 - xh.x2)
    );
}

// Растяжение вектора X(n+3)-X(n+2)
function stretching(nPlus3, nPlus2, gamma) {
    return new Point(
        nPlus2.x1 + gamma * (nPlus3.x1 - nPlus2.x1),
        nPlus2.x2 + gamma * (nPlus3.x2 - nPlus2.x2)
    );
}

// Сжатие вектора Xh-X(n+2)
function compression(xh, nPlus2, beta) {
    return new Point(
        nPlus2.x1 + beta * (xh.x1 - nPlus2.x1),
        nPlus2.x2 + beta * (xh.x2 - nPlus2.x2)
    );
}

// Редукция всех векторов Xj-XL в 2 раза
function reduction(points, xL) {
    return points.map(point => new Point(
        xL.x1 + (point.x1 - xL.x1) / 2,
        xL.x2 + (point.x2 - xL.x2) / 2
    ));
}

// Проверка критерия окончания поиска
function checkFinished(points, fValues, fNPlus2, epsilon) {
    const accuracy = Math.sqrt(fValues.reduce((sum, fValue) => sum + Math.pow(fValue - fNPlus2, 2), 0) / points.length);
    if (accuracy <= epsilon) {
        console.log("Точность поиска достигнута.");
        return true;
    }
    return false;
}

// Основная функция поиска по деформируемому многограннику
function searchByDeformablePolyhedron(epsilon, alpha, beta, gamma) {
    const points = [new Point(6, 3), new Point(9, 3), new Point(7, 4)];
    let fValues = points.map(F);

    printTableHeader();
    printCurrentPoints(points, fValues);

    let step = 0;

    while (true) {
        const h = searchPointMaxValue(fValues);
        const L = searchPointMinValue(fValues);

        const nPlus2 = centroidH(points, h);
        const fNPlus2 = F(nPlus2);

        if (checkFinished(points, fValues, fNPlus2, epsilon)) break;

        const nPlus3 = reflection(nPlus2, points[h], alpha);
        const fNPlus3 = F(nPlus3);
        let compress = true;

        points.forEach((_, j) => {
            if (j !== h && fNPlus3 <= fValues[j]) compress = false;
        });

        if (fNPlus3 < fValues[h] && !compress) {
            const nPlus4 = stretching(nPlus3, nPlus2, gamma);
            const fNPlus4 = F(nPlus4);
            if (fNPlus4 < fValues[L] && fNPlus4 < fNPlus3) {
                console.log(`После шага ${step} выполнено отражение->растяжение.`);
                points[h] = nPlus4;
                fValues[h] = fNPlus4;
                printCurrentPoints(points, fValues);
                step++;
                continue;
            } else {
                console.log(`После шага ${step} выполнено отражение.`);
                points[h] = nPlus3;
                fValues[h] = fNPlus3;
                printCurrentPoints(points, fValues);
                step++;
                continue;
            }
        }

        if (compress) {
            console.log(`После шага ${step} выполнено сжатие.`);
            points[h] = compression(points[h], nPlus2, beta);
            fValues[h] = F(points[h]);
            printCurrentPoints(points, fValues);
            step++;
            continue;
        }

        if (fNPlus3 > fValues[h]) {
            console.log(`После шага ${step} выполнена редукция.`);
            points = reduction(points, points[L]);
            fValues = points.map(F);
            printCurrentPoints(points, fValues);
            step++;
            continue;
        }
    }
}

// Параметры
searchByDeformablePolyhedron(0.01, 1, 0.5, 2);
