USE AdventureWorks2022;

SELECT * FROM Sales.Customer
SELECT * FROM Sales.SalesOrderHeader

SELECT Cust.CustomerID CustID, SalesOrderID
FROM Sales.Customer Cust JOIN Sales.SalesOrderHeader [Order]
ON Cust.CustomerID = [Order].CustomerID
ORDER BY Cust.CustomerID
FOR XML RAW

SELECT Cust.CustomerID CustID, SalesOrderID
FROM Sales.Customer Cust JOIN Sales.SalesOrderHeader [Order]
ON Cust.CustomerID = [Order].CustomerID
ORDER BY Cust.CustomerID
FOR XML RAW, ELEMENTS

SELECT Cust.CustomerID CustID, SalesOrderID
FROM Sales.Customer Cust JOIN Sales.SalesOrderHeader [Order]
ON Cust.CustomerID = [Order].CustomerID
ORDER BY Cust.CustomerID
FOR XML RAW('Order'), ROOT('Orders')

SELECT Cust.CustomerID CustID, SalesOrderID
FROM Sales.Customer Cust JOIN Sales.SalesOrderHeader [Order]
ON Cust.CustomerID = [Order].CustomerID
ORDER BY Cust.CustomerID
FOR XML AUTO

SELECT Cust.CustomerID CustID, SalesOrderID
FROM Sales.Customer Cust JOIN Sales.SalesOrderHeader [Order]
ON Cust.CustomerID = [Order].CustomerID
ORDER BY Cust.CustomerID
FOR XML AUTO, ELEMENTS

SELECT Cust.CustomerID CustID, SalesOrderID
FROM Sales.Customer Cust JOIN Sales.SalesOrderHeader [Order]
ON Cust.CustomerID = [Order].CustomerID
ORDER BY Cust.CustomerID
FOR XML AUTO, ELEMENTS, ROOT('Orders')

SELECT 1 AS Tag,
NULL AS Parent,
SalesOrderID AS [Invoice!1!InvoiceNo],
OrderDate AS [Invoice!1!Date!Element]
FROM Sales.SalesOrderHeader
FOR XML EXPLICIT

SELECT * FROM Person.BusinessEntityContact
SELECT * FROM Person.ContactType

SELECT Person.Person.BusinessEntityID AS "@EmpID",
       Person.Person.FirstName AS "EmpName/First",
       Person.Person.LastName AS "EmpName/Last"
FROM Person.Person
INNER JOIN HumanResources.Employee ON Person.Person.BusinessEntityID = HumanResources.Employee.BusinessEntityID
FOR XML PATH

SELECT Person.Person.BusinessEntityID AS "@EmpID",
       Person.Person.FirstName AS "EmpName/First",
       Person.Person.LastName AS "EmpName/Last"
FROM Person.Person
INNER JOIN HumanResources.Employee ON Person.Person.BusinessEntityID = HumanResources.Employee.BusinessEntityID
FOR XML PATH('Employee')

SELECT Cust.CustomerID CustID, SalesOrderID
FROM Sales.Customer Cust JOIN Sales.SalesOrderHeader [Order]
ON Cust.CustomerID = [Order].CustomerID
ORDER BY Cust.CustomerID
FOR XML AUTO

SELECT Name CategoryName,
(SELECT Name SubCategoryName
FROM Production.ProductSubCategory SubCategory
WHERE SubCategory.ProductCategoryID=Category.ProductCategoryID
FOR XML AUTO, TYPE, ELEMENTS)
FROM Production.ProductCategory Category
FOR XML AUTO

SELECT 1 AS Tag,
	NULL AS Parent,
	SalesOrderID AS [Invoice!1!InvoiceNo],
	OrderDate AS [Invoice!1!Date!Element],
	NULL AS [LineItem!2!ProductID],
	NULL AS [LineItem!2]
FROM Sales.SalesOrderHeader
UNION ALL
SELECT 2 AS Tag,
	1 AS Parent,
	OrderDetail.SalesOrderID,
	NULL,
	OrderDetail.ProductID,
	Product.Name
FROM Sales.SalesOrderDetail OrderDetail JOIN
	Sales.SalesOrderHeader OrderHeader
		ON OrderDetail.SalesOrderID = OrderHeader.SalesOrderID
	JOIN Production.Product Product
		ON OrderDetail.ProductID = Product.ProductID
ORDER BY [Invoice!1!InvoiceNo], [LineItem!2!ProductID]
FOR XML EXPLICIT
