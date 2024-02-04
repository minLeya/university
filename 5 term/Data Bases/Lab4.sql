-- проверка существования базы данных и таблицы
EXEC sp_helpdb ShopDB
EXEC sp_help 'ShopDB.dbo.Goods'

USE ShopDB
GO
CREATE TABLE Departments(
	DeptID INT NOT NULL CHECK(DeptID >=1 AND DeptID <= 10) PRIMARY KEY,
	DeptName VARCHAR(50) NOT NULL
)
/* 5. Заполните таблицу Departments (Отделы) в БД ShopDB, пользуясь командой
INSERT, таким образом, чтобы в ней оказались только те номера отделов, которые
есть в таблице Goods, а названия отделов DeptName заполнялись бы пустой
строкой.*/
INSERT INTO ShopDB.dbo.Departments
	SELECT DISTINCT DeptID, '' FROM ShopDB.dbo.Goods
-- 6. Вывод данных таблицы Departments
SELECT * FROM ShopDB.dbo.Departments

-- 7. Выведите декартово произведение таблиц Departments и Goods, т.е. всевозможные сочетания их строк
SELECT * FROM ShopDB.dbo.Departments CROSS JOIN ShopDB.dbo.Goods

-- 8 и 9 одинаковы
-- 8. Добавьте в предыдущую команду условие соединения по столбцу DeptID и снова выполните команду.
-- Условие соединения формулируйте с помощью WHERE
SELECT * FROM ShopDB.dbo.Departments CROSS JOIN ShopDB.dbo.Goods WHERE Departments.DeptID = Goods.DeptID

-- 9. Выполните внутреннее соединение таблиц Departments и Goods по столбцу
-- DeptID, используя синтаксис соединенных таблиц (JOIN).
SELECT * FROM ShopDB.dbo.Departments INNER JOIN ShopDB.dbo.Goods ON Departments.DeptID = Goods.DeptID

-- 10. Добавьте новый отдел в таблицу Departments.
INSERT INTO ShopDB.dbo.Departments VALUES(4, 'Спорт и отдых')

-- 11. Выполните левое внешнее соединение (LEFT JOIN) таблиц Departments и Goods по столбцу DeptID. 
SELECT * FROM ShopDB.dbo.Departments LEFT OUTER JOIN ShopDB.dbo.Goods ON Departments.DeptID = Goods.DeptID
-- появляется 9 строка - (4, спорт и отдых), другие значение null

-- 12. Добавьте теперь новый товар в таблицу Goods, продающийся в отделе, которого нет в таблице Departments.
INSERT INTO ShopDB.dbo.Goods (DeptID, GName, Descr, Price, GCount) VALUES
	(5, 'мяч', 'баскетбольный', 97, 120)

SELECT * FROM ShopDB.dbo.Goods

-- 13.  Выполните правое внешнее соединение (RIGHT JOIN) таблиц Departments и Goods по столбцу DeptID
SELECT * FROM ShopDB.dbo.Departments RIGHT OUTER JOIN ShopDB.dbo.Goods ON Departments.DeptID = Goods.DeptID

-- 14. Выполните полное соединение (FULL JOIN) таблиц Departments и Goods по столбцу DeptID
SELECT * FROM ShopDB.dbo.Departments FULL JOIN ShopDB.dbo.Goods ON Departments.DeptID = Goods.DeptID

-- 15. Выведите все отделы и все товары, для которых не найдено соответствия в другой таблице.
SELECT * FROM ShopDB.dbo.Departments FULL JOIN ShopDB.dbo.Goods ON Departments.DeptID = Goods.DeptID
	EXCEPT SELECT * FROM ShopDB.dbo.Departments INNER JOIN ShopDB.dbo.Goods ON Departments.DeptID = Goods.DeptID

-- 16.  Выведите все отделы (номера и наименования), в которых продается хотя бы 1 товар.
-- 1 способ:
SELECT a.DeptID, a.DeptName
	FROM (ShopDB.dbo.Departments AS a INNER JOIN ShopDB.dbo.Goods AS b ON a.DeptID = b.DeptID)
	GROUP BY a.DeptID, a.DeptName HAVING COUNT(b.GName) >= 1

-- 2 способ:
SELECT a.DeptID, a.DeptName FROM ShopDB.dbo.Departments AS a 
	WHERE a.DeptID IN 
	(SELECT b.DeptID FROM ShopDB.dbo.Goods AS b 
	GROUP BY b.DeptID HAVING COUNT(b.GName) >= 1)

SELECT a.DeptID, a.DeptName FROM ShopDB.dbo.Departments AS a
	WHERE EXISTS 
	(SELECT b.DeptID FROM ShopDB.dbo.Goods AS b 
	WHERE a.DeptID = b.DeptID 
	GROUP BY b.DeptID HAVING COUNT (b.GName) >= 1)

-- 3 способ:
SELECT a.DeptID, a.DeptName FROM ShopDB.dbo.Departments AS a
	WHERE a.DeptID = ANY 
	(SELECT b.DeptID FROM ShopDB.dbo.Goods AS b
	GROUP BY b.DeptID HAVING COUNT(b.GName) >= 1)

SELECT a.DeptID, a.DeptName FROM ShopDB.dbo.Departments AS a
	WHERE a.DeptID = SOME
	(SELECT b.DeptID FROM ShopDB.dbo.Goods AS b
	GROUP BY b.DeptID HAVING COUNT(b.GName) >= 1)

-- 17. Для каждого отдела вычислите суммарную стоимость проданного товара и выведите номера и названия этих отделов.
-- 1: общая сумма проданных товаров
SELECT a.DeptID, a.DeptName, SUM(b.Price * b.GCount) AS SumCost
	FROM (ShopDB.dbo.Departments AS a INNER JOIN ShopDB.dbo.Goods AS b ON a.DeptID = b.DeptID)
	GROUP BY a.DeptID, a.DeptName

-- 2: с уточнением товара 
SELECT a.DeptID, a.DeptName, b.GName, SUM(b.Price * b.GCount) AS SumCost
	FROM (ShopDB.dbo.Departments AS a INNER JOIN ShopDB.dbo.Goods AS b ON a.DeptID = b.DeptID)
	GROUP BY a.DeptID, a.DeptName, b.GName

-- 18. Выведите номер и название отдела, где суммарная стоимость проданного товара максимальна.
SELECT TOP(1) a.DeptID, a.DeptName, SUM(b.Price * b.GCount) AS SumCost
	FROM (ShopDB.dbo.Departments AS a INNER JOIN ShopDB.dbo.Goods AS b ON a.DeptID = b.DeptID)
	GROUP BY a.DeptID, a.DeptName
	ORDER BY SumCost DESC

-- 19. Выведите два отдела (номера и названия) с наибольшими суммами проданного товара.
SELECT TOP(2) a.DeptID, a.DeptName, SUM(b.Price * b.GCount) AS SumCost
	FROM (ShopDB.dbo.Departments AS a INNER JOIN ShopDB.dbo.Goods AS b ON a.DeptID = b.DeptID)
	GROUP BY a.DeptID, a.DeptName
	ORDER BY SumCost DESC

/*20. Вычислите для каждого товара процентное отношение его стоимости от суммарной
стоимости товаров в соответствующем отделе. Выведите код, наименование товара
и вычисленный процент.*/
SELECT a1.GoodID, a1.GName, a1.Descr, (a1.Price / SUM(a2.Price) * 100) AS PercentageOfSumCost
	FROM ((ShopDB.dbo.Goods AS a1 INNER JOIN ShopDB.dbo.Departments AS b ON a1.DeptID = b.DeptID)
		LEFT OUTER JOIN ShopDB.dbo.Goods AS a2 ON a1.DeptID = a2.DeptID)
	GROUP BY a1.GoodID, a1.GName, a1.Descr, a1.Price

/*21. Повысьте цены на все товары на 10% относительно средней цены на товар по всей
таблице Goods (используя команду UPDATE).*/
SELECT AVG(Price) AS AVGPrice FROM ShopDB.dbo.Goods
UPDATE ShopDB.dbo.Goods
	SET Price = Price + (SELECT AVG(Price) FROM ShopDB.dbo.Goods) / 100 * 10
SELECT * FROM ShopDB.dbo.Goods

/* 22. В новую таблицу Discount запишите все сведения о товарах, а также сумму скидки,
которая вычисляется в зависимости от цены товара:
если цена<10р, то скидка=20% от цены;
если 10р<=цена<=50р, то скидка=10% от цены;
если цена>50р, то скидка=5% от цены.*/
USE ShopDB
CREATE TABLE Discount
	(GoodID int NOT NULL PRIMARY KEY,
	GName varchar(20) NOT NULL,
    Descr varchar(50) NULL,
	UNIQUE (GName, Descr),
    Price smallmoney NOT NULL CHECK (Price > 0),
    DiscountAmount smallmoney NOT NULL CHECK (DiscountAmount > 0))

INSERT INTO ShopDB.dbo.Discount
	SELECT GoodID, GName, Descr, Price,
		CASE
			WHEN Price < 10 THEN Price * 0.2
			WHEN Price BETWEEN 10 AND 50 THEN Price * 0.1
			ELSE Price * 0.05
		END AS DiscountAmount
	FROM ShopDB.dbo.Goods

SELECT * FROM Discount

/* 23.  Свяжите таблицы Departments и Goods по ключу DeptID.
Внешний ключ необходимо добавить в таблицу Goods с ссылкой на первичный ключ таблицы Departments */
ALTER TABLE ShopDB.dbo.Goods
	ADD CONSTRAINT FK_Goods_DeptID FOREIGN KEY (DeptID)
	REFERENCES ShopDB.dbo.Departments(DeptID)
/* выводится ошибка из-за того, что в Goods DeptID=5 ссылается на несуществующий DeptID=5 в таблице Departments 
- исправляется добавлением отдела с айди 5 в таблицу Departments*/
INSERT INTO ShopDB.dbo.Departments VALUES (5, 'Игрушки')
SELECT * FROM ShopDB.dbo.Departments