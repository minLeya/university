const mongoose = require("mongoose");
const express = require("express");
const Schema = mongoose.Schema;
const app = express();
app.use(express.static("client"));
app.use(express.json());

const serviceSchema = new Schema({
    category: String,
    master: String,
    title: String,
    price: Number,
    datetime: [String]
}); 

// Исправленная опечатка в имени модели (Service вместо Servise)
const Service = mongoose.model("Service", serviceSchema);

async function main() {
    try {
        await mongoose.connect("mongodb://127.0.0.1:27017/servicedb");
        app.listen(3000);
        console.log("Сервер ожидает подключения...");
    }
    catch (err) {
        return console.log(err);
    }
}

app.get("/api/services", async (req, res) => {
    const services = await Service.find({}); // Заменил Servise на Service
    res.send(services);
});

app.get("/api/services/:id", async (req, res) => {
    const id = req.params.id;
    const service = await Service.findById(id); // Заменил Servise на Service
    if (service) res.send(service);
    else res.sendStatus(404);
});

app.post("/api/services", async (req, res) => {
    if (!req.body) return res.sendStatus(400);
    const { category, master, title, price, datetime } = req.body; // Деструктуризация
    const service = new Service({ 
        category,
        master,
        title,
        price,
        datetime
    });
    await service.save();
    res.send(service);
});

app.delete("/api/services/:id", async (req, res) => {
    const id = req.params.id;
    const service = await Service.findByIdAndDelete(id); // Заменил Servise на Service
    if (service) res.send(service);
    else res.sendStatus(404);
});

app.put("/api/services/:id", async (req, res) => {
    if (!req.body) return res.sendStatus(400);
    const id = req.params.id;
    const { category, master, title, price, datetime } = req.body; // Деструктуризация
    const newService = { 
        category,
        master,
        title,
        price,
        datetime
    };
    const service = await Service.findOneAndUpdate({ _id: id }, newService, { new: true }); // Заменил Servise на Service
    if (service) res.send(service);
    else res.sendStatus(404);
});

main();

// прослушиваем прерывание работы программы (ctrl-c)
process.on("SIGINT", async () => {
    await mongoose.disconnect();
    console.log("Приложение завершило работу");
    process.exit();
});
