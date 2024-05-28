const express = require("express");

const app = express();
app.use(express.json());

app.use(express.static("public"));
// условная база данных
const users = [];
let id = 1; // для установки идентификаторов
// вспомогательная функция для поиска индекса пользователя по id
function findUserIndexById(id){
    for(let i=0; i < users.length; i++){
        if(users[i].id==id) return i;
    }
    return -1;
}
app.get("/api/users", function(_, res){

    res.send(users);
});
// получение одного пользователя по id
app.get("/api/users/:id", function(req, res){

    const id = req.params.id; // получаем id
    // находим в массиве пользователя по id
    const index = findUserIndexById(id);
    // отправляем пользователя
    if(index > -1){
        res.send(users[index]);
    }
    else{
        res.status(404).send("User not found");
    }
});
// получение отправленных данных
app.post("/api/users", function (req, res) {

    if(!req.body) return res.sendStatus(400);

    const userName = req.body.name;
    const userAge = req.body.age;
    const user = {name: userName, age: userAge};
    // присваиваем идентификатор из переменной id и увеличиваем ее на единицу
    user.id = id++;
    // добавляем пользователя в массив
    users.push(user);
    res.send(user);
});
// удаление пользователя по id
app.delete("/api/users/:id", function(req, res){

    const id = req.params.id;
    const index = findUserIndexById(id);
    if(index > -1){
        // удаляем пользователя из массива по индексу
        const user = users.splice(index, 1)[0];
        res.send(user);
    }
    else{
        res.status(404).send("User not found");
    }
});
// изменение пользователя
app.put("/api/users", function(req, res){

    if(!req.body) return res.sendStatus(400);

    const id = req.body.id;
    const userName = req.body.name;
    const userAge = req.body.age;

    const index = findUserIndexById(id);
    if(index > -1){
        // изменяем данные у пользователя
        const user = users[index];
        user.age = userAge;
        user.name = userName;
        res.send(user);
    }
    else{
        res.status(404).send("User not found");
    }
});

app.listen(3000, function(){
    console.log("Сервер ожидает подключения...");
});