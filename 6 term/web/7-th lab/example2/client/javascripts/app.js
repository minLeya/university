var main = function (toDoObjects) {
    "use strict";
    var toDos = toDoObjects.map(function (toDo) {
        return toDo.description;
    });
    var organizeByTags = function (toDoObjects) {
        //console.log("organizeByTags вызвана - 0");
        var toArr = [];
        var toTags = [];
        toDoObjects.forEach(function (e1) {
            //console.log(e);
            e1.tags.forEach(function (tag) {
                if (toArr.indexOf(tag) === -1) {
                    //console.log(tag);
                    toArr.push(tag);
                    toTags.push({
                        "name": tag,
                        "toDos": [e1.description]
                    });
                } else {
                    toTags.forEach(function (e2) {
                        if (e2.name === tag) {
                            e2.toDos.push(e1.description);
                        }
                    });
                }
            });
        });
        //console.log(toTags);
        return toTags;
    };
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
                //console.log("Щелчок на вкладке Теги");
                //console.log(organizeByTags(toDoObjects));
                var organizedByTag = organizeByTags(toDoObjects);
                organizedByTag.forEach(function (tag) {
                    var $tagName = $("<h3>").text(tag.name),
                        $content = $("<ul>");
                    tag.toDos.forEach(function (description) {
                        var $li = $("<li>").text(description);
                        $content.append($li);
                    });
                    $("main .content").append($tagName);
                    $("main .content").append($content);
                });
            } else if ($element.parent().is(":nth-child(4)")) {
                $content = $("<div>");
                $content.append($("<p>").text("Добавьте новую задачу"));
                var $input = $("<input>");
                var $button = $("<button>");
                $content.append($input);
                $content.append("<p>Теги</p>");
                var $input_tags = $("<input>");
                $content.append($input_tags);
                $content.append($button.text("+"));
                var description = $input.val();
                var tags = $input_tags.val().split(",");
                var addTaskFromInputBox = function () {
                    if ($input.val() !== "") {
                        var newToDo = {
                            "description": $input.val(),
                            "tags": $input_tags.val().split(",")
                        };
                        $.post("todos", newToDo, function (response) {
                            console.log("Мы отправили данные и получили ответ сервера!");
                            console.log(response);
                            toDos.push($input.val());
                            toDoObjects.push({
                                "description": $input.val(),
                                "tags": $input_tags.val().split(",")
                            });
                            $input.val("");
                            $input_tags.val("");
                        });
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
                //console.log(toDoObjects);
            }
            $("main .content").append($content);
            return false;
        });
    });
    $(".tabs a:first-child span").trigger("click");
};
$(document).ready(function () {
    $.getJSON("todos.json", function (toDoObjects) {
        // вызываем функцию main с задачами в качестве аргумента
        main(toDoObjects);
    });
});