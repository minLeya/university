var main = function () {
    "use strict";
    var toDos = [
        "Закончить писать эту книгу",
        "Вывести Грейси на прогулку в парк",
        "Ответить на электронные письма",
        "Подготовиться к лекции в понедельник",
        "Обновить несколько новых задач",
        "Купить продукты"
    ];
    $(".tabs a span").toArray().forEach(function (element) {
        $(element).on("click", function () {
            var $element = $(element),
                $content;
            $(".tabs a span").removeClass("active");
            $element.addClass("active");
            $("main .content").empty();
            if ($element.parent().is(":nth-child(1)")) {
                var i;
                $content = $("<ul>");
                for (i = toDos.length; i > -1; i--) {
                    $content.append($("<li>").text(toDos[i]));
                }
            } else if ($element.parent().is(":nth-child(2)")) {
                $content = $("<ul>");
                toDos.forEach(function (todo) {
                    $content.append($("<li>").text(todo));
                });
            } else if ($element.parent().is(":nth-child(3)")) {
                $content = $("<div>");
                $content.append($("<p>").text("Добавьте новую задачу"));
                var $input = $("<input>"),
                    $button = $("<button>");
                $content.append($input);
                $content.append($button.text("+"));
                var addTaskFromInputBox = function () {
                    if ($input.val() !== "") {
                        toDos.push($input.val());
                        $input.val("");
                    }
                };
                $button.on("click", function (event) {
                    addTaskFromInputBox();
                });
                $input.on("keypress", function (event) {
                    if (event.keyCode === 13) {
                        addTaskFromInputBox();
                    }
                });
            }
            $("main .content").append($content);
            return false;
        });
    });
    $(".tabs a:first-child span").trigger("click");
};
$(document).ready(main);