<%-- 
    Document   : main
    Created on : 18 мая 2024 г., 22:27:58
    Author     : Лейсан
--%>

<%@ page contentType="text/html" pageEncoding="UTF-8" %>
<%@ page import="app.SortBean" %>
<jsp:useBean id="sortBean" class="app.SortBean" scope="session" />
<!DOCTYPE html>
<html>
<head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    <title>Два</title>
</head>
<body>
    <h1>Главная страница</h1>
    <form action="result.jsp" method="POST">
        Введите последовательность целых чисел через запятую: 
        <input type="text" name="sequence" required>
        <input type="submit" value="Сортировать">
    </form>
    <%
        Integer counter = (Integer) session.getAttribute("counter");
        if (counter == null) {
            counter = 0;
        }
        counter++;
        session.setAttribute("counter", counter);

        Boolean trigger = (Boolean) session.getAttribute("trigger");
        if (trigger == null) {
            trigger = Boolean.TRUE;
        } else {
            trigger = !trigger;
        }
        session.setAttribute("trigger", trigger);
    %>
    <p>Счётчик посещений: <jsp:getProperty name="sortBean" property="counter" /> </p>
</body>
</html>