var express = require("express"),
    http = require("http"),
    app = express(),
    services = [
        {
            "category": "Стрижка",
            "master": "Иванов Иван Иванович",
            "title": "Мужская стрижка",
            "price": "500",
            "datetime": ["2024-06-01 10:00", "2024-06-02 14:00"]
        },
        {
            "category": "Стрижка",
            "master": "Петрова Мария Романовна",
            "title": "Женская стрижка",
            "price": "500",
            "datetime": ["2024-06-03 11:00", "2024-06-04 15:00"]
        },
        {
            "category": "Окрашивание",
            "master": "Сидоров Алексей Андреевич",
            "title": "Окрашивание длинных волос",
            "price": "1500",
            "datetime": ["2024-06-05 12:00", "2024-06-06 16:00"]
        }
    ];

app.use(express.static(__dirname + "/client"));
app.use(express.urlencoded({ extended: true }));
app.use(express.json());

http.createServer(app).listen(3000);

app.get("/services.json", function (req, res) {
    res.json(services);
});

app.post("/services", function (req, res) {
    console.log("Данные были отправлены на сервер!");
    var newService = req.body;
    services.push(newService);
    res.json({ "message": "Вы размещаетесь на сервере!" });
});
