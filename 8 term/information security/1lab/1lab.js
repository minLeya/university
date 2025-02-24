const math = require('mathjs');

let P = 10**(-4);
let V = 10;
let T = 5;
let A = 36;

let sStar = math.ceil((V * T) / P);
let L = math.ceil(math.log(sStar, A));

console.log("Нижняя граница: ", sStar);
console.log("Минимальная длина пароля: ", L);


function generatePassword(length) {
    alphabet = "0123456789abcdefghijklmnopqrstuvwxyz";
    let password = "";
    for (let i = 0; i < length; i++) {
        password += alphabet[Math.floor(Math.random() * alphabet.length)];
    }
    return password;
}

const result = [];
L = 4;
for (let i = 0; i < 20; i++) {
    result.push(generatePassword(L));
}

console.log(result);
