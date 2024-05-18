<%-- 
    Document   : result
    Created on : 18 мая 2024 г., 22:29:11
    Author     : Лейсан
--%>

<%@ page contentType="text/html" pageEncoding="UTF-8" %>
<%@ page import="app.SortBean" %>
<jsp:useBean id="sortBean" class="app.SortBean" scope="session" />
<!DOCTYPE html>
<html>
<head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    <title>Три</title>
</head>
<body>
    <h1>Результаты</h1>
    <%
        String sequence = request.getParameter("sequence");
        sortBean.setSequence(sequence);
    %>
    <p>Отсортированный список: </p>
    <%
        int[] sortedNumbers = sortBean.getSortedNumbers();
        for (int number : sortedNumbers) {
            out.println(number + "<br>");
        }
    %>
    <a href="main.jsp">Возврат</a>
</body>
</html>
