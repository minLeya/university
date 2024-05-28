let main = function (serviceObjects) {
    "use strict";

    let services = serviceObjects.map(function (service) {
        return { 
            category: service.category, 
            master: service.master, 
            title: service.title, 
            price: service.price,
            datetime: service.datetime
        };
    });

    let organizeByProperty = function (serviceObjects, property) {
        let organizedData = {};

        serviceObjects.forEach(function (service) {
            let key = service[property];
            if (!organizedData.hasOwnProperty(key)) {
                organizedData[key] = [];
            }

            organizedData[key].push(service);
        });

        return organizedData;
    };

    let organizeByDateTime = function (serviceObjects) {
        let servicesByDateTime = {};

        serviceObjects.forEach(function (service) {
            service.datetime.forEach(function (datetime) {
                if (!servicesByDateTime.hasOwnProperty(datetime)) {
                    servicesByDateTime[datetime] = [];
                }
                servicesByDateTime[datetime].push(service);
            });
        });

        return servicesByDateTime;
    };

    let $content;

    let organizeAndDisplay = function (serviceObjects, property) {
        let organizedData;
        if (property === 'datetime') {
            organizedData = organizeByDateTime(serviceObjects);
        } else {
            organizedData = organizeByProperty(serviceObjects, property);
        }

        $content = $("<ul>");
        for (let key in organizedData) {
            $content.append($("<h2>").text(key));

            organizedData[key].forEach(function(service) {
                let info;
                if (property === 'category') {
                    info = service.title + ", " + service.master + ", " + service.price + " руб.";
                } else if (property === 'master') {
                    info = service.title + ", " + service.category + ", " + service.price + " руб.";
                } else if (property === 'datetime') {
                    info = service.title + ", " + service.master + ", " + service.category + ", " + service.price + " руб.";
                }
                $content.append($("<li>").text(info));
            });
        }
    };

    $(".tabs a span").toArray().forEach(function (element) {
        $(element).on("click", function () {
            let $element = $(element);

            $(".tabs a span").removeClass("active");
            $element.addClass("active");
            $("main .content").empty();

            if ($element.parent().is(":nth-child(1)")) {
                $content = $("<ul>");
                for (let i = services.length - 1; i >= 0; i--) {
                    let service = services[i];
                    let info = service.category + ", " + service.master + ", " + service.title + ", " + service.price + " руб.";
                    $content.append($("<li>").text(info));
                }
            } else if ($element.parent().is(":nth-child(2)")) {
                $content = $("<ul>");
                services.forEach(function (service) {
                    let info = service.category + ", " + service.master + ", " + service.title + ", " + service.price + " руб.";
                    $content.append($("<li>").text(info));
                });
            } else if ($element.parent().is(":nth-child(3)")) {
                organizeAndDisplay(serviceObjects, 'category');
            } else if ($element.parent().is(":nth-child(4)")) {
                organizeAndDisplay(serviceObjects, 'master');
            } else if ($element.parent().is(":nth-child(5)")) {
                organizeAndDisplay(serviceObjects, 'datetime');
            } else if ($element.parent().is(":nth-child(6)")) {
                $content = $("<div>");
                $content.append($("<p>").text("Добавьте новую услугу"));

                $content.append($("<div>").text("Название услуги:"));
                let $titleInput = $("<input>");
                $content.append($titleInput);

                $content.append($("<div>").text("Категория:"));
                let $categoryInput = $("<input>");
                $content.append($categoryInput);

                $content.append($("<div>").text("ФИО мастера:"));
                let $masterInput = $("<input>");
                $content.append($masterInput);

                $content.append($("<div>").text("Цена:"));
                let $priceInput = $("<input>");
                $content.append($priceInput);

                $content.append($("<div>").text("Дата и время:"));
                let $dateTimeInput = $("<input>");
                $content.append($dateTimeInput);

                $content.append($("<div>"));
                let $button = $("<button>");
                $content.append($button.text("Добавить"));

                let addService = function() {
                    if ($titleInput.val() === "" || $categoryInput.val() === "" ||
                        $masterInput.val() === "" || $priceInput.val() === "" || $dateTimeInput.val() === "") {
                        return;
                    }

                    let newService = { 
                        category: $categoryInput.val(),
                        master: $masterInput.val(),
                        title: $titleInput.val(),
                        price: $priceInput.val(),
                        datetime: $dateTimeInput.val().split(",")
                    };
                    services.push(newService);
                    serviceObjects.push(newService);

                    $categoryInput.val("");
                    $masterInput.val("");
                    $titleInput.val("");
                    $priceInput.val("");
                    $dateTimeInput.val("");
                };

                $button.on("click", function (event) {
                    addService();
                });
            }
            $("main .content").append($content);
            return false;
        });
    });
    $(".tabs a:first-child span").trigger("click");
};

$(document).ready(function () {
    $.getJSON("services.json", function (serviceObjects) {
        main(serviceObjects);
    });
});