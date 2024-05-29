var main = function () {
    "use strict";
    $(".tabs a span").toArray().forEach(function (element) {
        $(element).on("click", function () {
            var $element = $(element),
                $content;
            $(".tabs a span").removeClass("active");
            $element.addClass("active");
            $("main .content").empty();
            // Новые -> Старые.
            if ($element.parent().is(":nth-child(1)")) {
                fetch("api/services", {
                    method: "GET",
                    headers: { "Accept": "application/json" }
                })
                    .then(function (response) {
                        if (response.ok) {
                            return response.json();
                        } else {
                            throw new Error('Ошибка получения данных');
                        }
                    })
                    .then(function (services) {
                        $content = $("<div>");
                        services.reverse();
                        services.forEach(function (item) {
                            var $infoClassDiv = $("<div>").addClass("infoClass");

                            $infoClassDiv.append($("<h4>").text("Категория: " + item.category));
                            $infoClassDiv.append($("<h4>").text("Мастер: " + item.master));
                            $infoClassDiv.append($("<h4>").text("Название услуги: " + item.title));
                            $infoClassDiv.append($("<h4>").text("Цена: " + item.price));
                            $infoClassDiv.append($("<h4>").text("Дата и время: " + item.datetime));

                            $content.append($infoClassDiv);
                        });
                        $("main .content").append($content);
                    })
                    .catch(function (error) {
                        console.error('Произошла ошибка при получении данных:', error);
                    });
            // Старые -> Новые.
            } else if ($element.parent().is(":nth-child(2)")) {
                fetch("api/services", {
                    method: "GET",
                    headers: { "Accept": "application/json" }
                })
                    .then(function (response) {
                        if (response.ok) {
                            return response.json();
                        } else {
                            throw new Error('Ошибка получения данных');
                        }
                    })
                    .then(function (services) {
                        $content = $("<div>");
                        services.forEach(function (item) {
                            var $infoClassDiv = $("<div>").addClass("infoClass");

                            $infoClassDiv.append($("<h4>").text("Категория: " + item.category));
                            $infoClassDiv.append($("<h4>").text("Мастер: " + item.master));
                            $infoClassDiv.append($("<h4>").text("Название услуги: " + item.title));
                            $infoClassDiv.append($("<h4>").text("Цена: " + item.price));
                            $infoClassDiv.append($("<h4>").text("Дата и время: " + item.datetime));

                            $content.append($infoClassDiv);
                        });
                        $("main .content").append($content);
                    })
                    .catch(function (error) {
                        console.error('Произошла ошибка при получении данных:', error);
                    });
            // Группировка по категории.
            } else if ($element.parent().is(":nth-child(3)")) {
                fetch("api/services", {
                    method: "GET",
                    headers: { "Accept": "application/json" }
                })
                    .then(function (response) {
                        if (response.ok) {
                            return response.json();
                        } else {
                            throw new Error('Ошибка получения данных');
                        }
                    })
                    .then(function (services) {
                        var categories = {};
                        services.forEach(function (item) {
                            if (categories.hasOwnProperty(item.category)) {
                                categories[item.category].push(item);
                            } else {
                                categories[item.category] = [item];
                            }
                        });

                        $content = $("<div>");
                        for (var category in categories) {
                            if (categories.hasOwnProperty(category)) {
                                var $categoryClassDiv = $("<div>").addClass("categoryClass");
                                $categoryClassDiv.append($("<p>").text("Категория: " + category));
                                var $innerContent = $("<div>");
                                categories[category].forEach(function (service) {
                                    var $infoClassDiv = $("<div>").addClass("infoClass");
                                    $infoClassDiv.append($("<h4>").text("Мастер: " + service.master));
                                    $infoClassDiv.append($("<h4>").text("Название услуги: " + service.title));
                                    $infoClassDiv.append($("<h4>").text("Цена: " + service.price));
                                    $infoClassDiv.append($("<h4>").text("Дата и время: " + service.datetime));
                                    $innerContent.append($infoClassDiv);
                                });
                                $categoryClassDiv.append($innerContent);
                                $content.append($categoryClassDiv);
                            }
                        }
                        $("main .content").append($content);
                    })
                    .catch(function (error) {
                        console.error('Произошла ошибка при получении данных:', error);
                    });
            // Группировка по мастеру.
            } else if ($element.parent().is(":nth-child(4)")) {
                fetch("api/services", {
                    method: "GET",
                    headers: { "Accept": "application/json" }
                })
                    .then(function (response) {
                        if (response.ok) {
                            return response.json();
                        } else {
                            throw new Error('Ошибка получения данных');
                        }
                    })
                    .then(function (services) {
                        var masters = {};

                        services.forEach(function (item) {
                            if (masters.hasOwnProperty(item.master)) {
                                masters[item.master].push(item);
                            } else {
                                masters[item.master] = [item];
                            }
                        });

                        $content = $("<div>");
                        for (var master in masters) {
                            if (masters.hasOwnProperty(master)) {
                                var $masterClassDiv = $("<div>").addClass("masterClass");
                                $masterClassDiv.append($("<p>").text("Мастер: " + master));

                                masters[master].forEach(function (service) {
                                    var $infoClassDiv = $("<div>").addClass("infoClass");
                                    $infoClassDiv.append($("<h4>").text("Название услуги: " + service.title));
                                    $infoClassDiv.append($("<h4>").text("Цена: " + service.price));
                                    $infoClassDiv.append($("<h4>").text("Дата и время: " + service.datetime));
                                    $masterClassDiv.append($infoClassDiv);
                                });
                                $content.append($masterClassDiv);
                            }
                        }
                        $("main .content").append($content);
                    })
                    .catch(function (error) {
                        console.error('Произошла ошибка при получении данных:', error);
                    });
            } else if ($element.parent().is(":nth-child(5)")) {
                fetch("api/services", {
                    method: "GET",
                    headers: { "Accept": "application/json" }
                })
                    .then(function (response) {
                        if (response.ok) {
                            return response.json();
                        } else {
                            throw new Error('Ошибка получения данных');
                        }
                    })
                    .then(function (services) {
                        var dateTimes = {};
            
                        services.forEach(function (item) {
                            if (dateTimes.hasOwnProperty(item.datetime)) {
                                dateTimes[item.datetime].push(item);
                            } else {
                                dateTimes[item.datetime] = [item];
                            }
                        });
            
                        $content = $("<div>");
                        for (var datetime in dateTimes) {
                            if (dateTimes.hasOwnProperty(datetime)) {
                                var $datetimeClassDiv = $("<div>").addClass("datetimeClass");
                                $datetimeClassDiv.append($("<p>").text("Дата и время: " + datetime));
            
                                dateTimes[datetime].forEach(function (service) {
                                    var $infoClassDiv = $("<div>").addClass("infoClass");
                                    $infoClassDiv.append($("<h4>").text("Мастер: " + service.master));
                                    $infoClassDiv.append($("<h4>").text("Название услуги: " + service.title));
                                    $infoClassDiv.append($("<h4>").text("Цена: " + service.price));
                                    $datetimeClassDiv.append($infoClassDiv);
                                });
                                $content.append($datetimeClassDiv);
                            }
                        }
                        $("main .content").append($content);
                    })
                    .catch(function (error) {
                        console.error('Произошла ошибка при получении данных:', error);
                    });
            } else if ($element.parent().is(":nth-child(6)")) {
                $("main .content").empty();
                // Форма ввода.
                const $form = $("<form>").attr("id", "dataForm");
                $form.append(
                    $("<label>").text("Категория:"),
                    $("<input>").attr({ type: "text", id: "category", name: "category" }),
                    $("<br>"),
                    $("<label>").text("Мастер:"),
                    $("<input>").attr({ type: "text", id: "master", name: "master" }),
                    $("<br>"),
                    $("<label>").text("Название услуги:"),
                    $("<input>").attr({ type: "text", id: "title", name: "title" }),
                    $("<br>"),
                    $("<label>").text("Цена:"),
                    $("<input>").attr({ type: "number", id: "price", name: "price" }),
                    $("<br>"),
                    $("<label>").text("Дата и время:"),
                    $("<input>").attr({ type: "text", id: "datetime", name: "datetime" }),
                    $("<br>"),
                    $("<button>").attr({ type: "button", id: "saveBtn" }).addClass("btn").text("Сохранить"),
                    $("<button>").attr({ type: "button", id: "resetBtn" }).addClass("btn").text("Сбросить")
                );
                // Таблица.
                const $table = $("<table>").attr("id", "dataTable");
                $table.append(
                    $("<thead>").append(
                        $("<tr>").append(
                            $("<th>").text("Категория"),
                            $("<th>").text("Мастер"),
                            $("<th>").text("Название услуги"),
                            $("<th>").text("Цена"),
                            $("<th>").text("Дата и время"),
                            $("<th>").text("Действия")
                        )
                    ),
                    $("<tbody>")
                );
                
                $("main .content").append($form, $("<h2>").text("Записи в базе данных"), $table);

                // Функция для загрузки данных в таблицу.
                function loadData() {
                    fetch("api/services", {
                        method: "GET",
                        headers: { "Accept": "application/json" }
                    })
                        .then(response => {
                            if (response.ok) {
                                return response.json();
                            } else {
                                throw new Error('Ошибка получения данных');
                            }
                        })
                        .then(services => {
                            const $tbody = $("#dataTable tbody");
                            $tbody.empty();

                            services.forEach(service => {
                                const $tr = $("<tr>");
                                $tr.append(
                                    $("<td>").text(service.category),
                                    $("<td>").text(service.master),
                                    $("<td>").text(service.title),
                                    $("<td>").text(service.price),
                                    $("<td>").text(service.datetime),
                                    $("<td>").append(
                                        $("<button>").addClass("btn deleteBtn").text("Удалить").data("id", service._id)
                                    )
                                );
                                $tbody.append($tr);
                            });
                        })
                        .catch(error => console.error('Произошла ошибка при загрузке данных:', error));
                }

                // Загрузка данных при инициализации.
                loadData();

                // Сохранение данных.
                $("#saveBtn").on("click", function () {
                    const data = {
                        category: $("#category").val(),
                        master: $("#master").val(),
                        title: $("#title").val(),
                        price: $("#price").val(),
                        datetime: $("#datetime").val()
                    };

                    fetch("api/services", {
                        method: "POST",
                        headers: {
                            "Content-Type": "application/json"
                        },
                        body: JSON.stringify(data)
                    })
                        .then(response => {
                            if (response.ok) {
                                // Очистка формы после успешного добавления данных.
                                $("#category").val("");
                                $("#master").val("");
                                $("#title").val("");
                                $("#price").val("");
                                $("#datetime").val("");
                                // Перезагрузка таблицы.
                                loadData();
                            } else {
                                throw new Error('Ошибка добавления данных');
                            }
                        })
                        .catch(error => console.error('Произошла ошибка при добавлении данных:', error));
                });

                // Удаление данных.
                $("#dataTable").on("click", ".deleteBtn", function () {
                    const serviceId = $(this).data("id");

                    fetch(`api/services/${serviceId}`, {
                        method: "DELETE",
                        headers: { "Accept": "application/json" }
                    })
                        .then(response => {
                            if (response.ok) {
                                // Перезагрузка таблицы после успешного удаления данных.
                                loadData();
                            } else {
                                throw new Error('Ошибка удаления данных');
                            }
                        })
                        .catch(error => console.error('Произошла ошибка при удалении данных:', error));
                });

                // Сброс данных формы.
                $("#resetBtn").on("click", function () {
                    $("#category").val("");
                    $("#master").val("");
                    $("#title").val("");
                    $("#price").val("");
                    $("#datetime").val("");
                });
            }
            return false;
        });
    });
    $(".tabs a:first-child span").trigger("click");
};
$(document).ready(main);
