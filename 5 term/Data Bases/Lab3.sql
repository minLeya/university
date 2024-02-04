CREATE DATABASE ShopDB
GO
USE ShopDB
GO
CREATE TABLE Goods(
	DeptID INT NOT NULL DEFAULT 1 CHECK (DeptID >= 1 AND DeptID <= 10),
	GoodID INT NOT NULL IDENTITY (10, 10) PRIMARY KEY,
	GName VARCHAR(20) NOT NULL,
	Descr VARCHAR(50) NULL,
	UNIQUE(GName, Descr), 
	Price SMALLMONEY NOT NULL CHECK(Price > 0),
	GCount INT NOT NULL CHECK(GCount > 0))

INSERT INTO ShopDB.dbo.Goods (DeptID, GName, Descr, Price, GCount) VALUES
	(1, 'ручка', 'шариковая', 2, 100),
	(1, 'ручка', 'гелевая', 10, 50),
	(1, 'карандаш', 'простой', 5, 200),
	(1, 'карандаш', 'механический', 10, 30),
	(2, 'мыло', 'хозяйственное', 6, 200),
	(2, 'мыло', 'детское', 7, 150),
	(2, 'шампунь', '"Чистая линия"', 50, 7)

SELECT * FROM ShopDB.dbo.Goods

INSERT INTO ShopDB.dbo.Goods (DeptID, GName, Descr, Price, GCount) VALUES
	(3, 'хлеб', 'сельский', 20, 30),
	(DEFAULT, 'ручка', NULL, 15, 40)

SELECT * FROM ShopDB.dbo.Goods

-- 7. Пользуясь командой DELETE, удалите из таблицы Goods те товары,
-- у которых не задано описание
DELETE FROM ShopDB.dbo.Goods WHERE Descr is NULL

-- 8. Пользуясь командой UPDATE, обновите таблицу Goods – увеличьте цены на все
-- товары на 10%
UPDATE ShopDB.dbo.Goods SET Price = Price + Price * 0.1

--9. Пользуясь командой SELECT, выведите таблицу Goods
SELECT * FROM ShopDB.dbo.Goods

--10. Выведите все товары (их номер, имя и описание), которые продаются в первом отделе:
SELECT GoodID, GName, Descr FROM ShopDB.dbo.Goods WHERE (DeptID = 1)

-- 11. Выведите все сведения о товарах в ценовом диапазоне от 10 до 30 рублей, используя предикат BETWEEN
SELECT * FROM ShopDB.dbo.Goods WHERE (Price BETWEEN 10 AND 30)

-- 12.  Выведите все сведения о товарах первого и третьего отдела, используя предикат IN
SELECT * FROM ShopDB.dbo.Goods WHERE DeptID IN (1, 3)

-- 13.  Выведите все сведения о товарах, имя которых начинается на ‘р’, используя предикат LIKE
SELECT * FROM ShopDB.dbo.Goods WHERE (GName LIKE 'р%')

-- 14. Выведите все сведения о товарах, в имени которых встречается символ ‘_’, используя предикат LIKE
SELECT * FROM ShopDB.dbo.Goods WHERE (GName LIKE '%\_%' ESCAPE '\')

-- 15. Выведите наименования всех товаров
SELECT GName FROM ShopDB.dbo.Goods

-- 16. Выведите наименования всех товаров без повторений
SELECT DISTINCT GName FROM ShopDB.dbo.Goods

-- 17. Выведите все сведения о товарах плюс вычисляемый столбец – стоимость
-- каждого товара (цена * количество)
SELECT *, Price * GCount AS Sum FROM ShopDB.dbo.Goods

-- 18. Выведите минимальную, среднюю, максимальную цену по всем товарам.
SELECT MIN(Price) AS minimun, AVG(Price) AS average, MAX(Price) AS maximum FROM ShopDB.dbo.Goods

-- 19. Выведите количество наименований товаров, продающихся в первом отделе
SELECT COUNT(GName) FROM ShopDB.dbo.Goods WHERE DeptID = 1

-- 20. Выведите количество товаров, для которых задано описание (Descr не null)
SELECT COUNT(*) FROM ShopDB.dbo.Goods WHERE Descr IS NOT NULL

-- 21. Выведите суммарную стоимость товаров по второму отделу
SELECT SUM(Price) FROM ShopDB.dbo.Goods WHERE DeptID = 2

-- 22. Выведите все товары, упорядочивая по именам.
SELECT * FROM ShopDB.dbo.Goods ORDER BY GName

-- 23. Выведите все товары, упорядочивая по отделам и по убыванию цены.
SELECT * FROM ShopDB.dbo.Goods ORDER BY DeptID, Price DESC

-- 24. Вычислите стоимость проданного товара по каждому отделу.
SELECT DeptID, SUM(Price * GCount) FROM ShopDB.dbo.Goods GROUP BY DeptID

-- 25. Вычислите среднюю цену только по тем товарам, цена которых превышает 9 рублей
SELECT AVG(Price) AS average FROM ShopDB.dbo.Goods WHERE Price > 9

-- 26. Вычислите максимальную цену по каждому наименованию товара.
SELECT GName, MAX(Price) AS maximum FROM ShopDB.dbo.Goods GROUP BY GName

-- 27. Выведите номера отделов, где продается более двух наименований товаров.
SELECT DeptID FROM ShopDB.dbo.Goods GROUP BY DeptID HAVING COUNT(GName) > 2