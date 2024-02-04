-- �������� ������������� ���� ������ � �������
EXEC sp_helpdb ShopDB
EXEC sp_help 'ShopDB.dbo.Goods'

USE ShopDB
GO
CREATE TABLE Departments(
	DeptID INT NOT NULL CHECK(DeptID >=1 AND DeptID <= 10) PRIMARY KEY,
	DeptName VARCHAR(50) NOT NULL
)
/* 5. ��������� ������� Departments (������) � �� ShopDB, ��������� ��������
INSERT, ����� �������, ����� � ��� ��������� ������ �� ������ �������, �������
���� � ������� Goods, � �������� ������� DeptName ����������� �� ������
�������.*/
INSERT INTO ShopDB.dbo.Departments
	SELECT DISTINCT DeptID, '' FROM ShopDB.dbo.Goods
-- 6. ����� ������ ������� Departments
SELECT * FROM ShopDB.dbo.Departments

-- 7. �������� ��������� ������������ ������ Departments � Goods, �.�. ������������ ��������� �� �����
SELECT * FROM ShopDB.dbo.Departments CROSS JOIN ShopDB.dbo.Goods

-- 8 � 9 ���������
-- 8. �������� � ���������� ������� ������� ���������� �� ������� DeptID � ����� ��������� �������.
-- ������� ���������� ������������ � ������� WHERE
SELECT * FROM ShopDB.dbo.Departments CROSS JOIN ShopDB.dbo.Goods WHERE Departments.DeptID = Goods.DeptID

-- 9. ��������� ���������� ���������� ������ Departments � Goods �� �������
-- DeptID, ��������� ��������� ����������� ������ (JOIN).
SELECT * FROM ShopDB.dbo.Departments INNER JOIN ShopDB.dbo.Goods ON Departments.DeptID = Goods.DeptID

-- 10. �������� ����� ����� � ������� Departments.
INSERT INTO ShopDB.dbo.Departments VALUES(4, '����� � �����')

-- 11. ��������� ����� ������� ���������� (LEFT JOIN) ������ Departments � Goods �� ������� DeptID. 
SELECT * FROM ShopDB.dbo.Departments LEFT OUTER JOIN ShopDB.dbo.Goods ON Departments.DeptID = Goods.DeptID
-- ���������� 9 ������ - (4, ����� � �����), ������ �������� null

-- 12. �������� ������ ����� ����� � ������� Goods, ����������� � ������, �������� ��� � ������� Departments.
INSERT INTO ShopDB.dbo.Goods (DeptID, GName, Descr, Price, GCount) VALUES
	(5, '���', '�������������', 97, 120)

SELECT * FROM ShopDB.dbo.Goods

-- 13.  ��������� ������ ������� ���������� (RIGHT JOIN) ������ Departments � Goods �� ������� DeptID
SELECT * FROM ShopDB.dbo.Departments RIGHT OUTER JOIN ShopDB.dbo.Goods ON Departments.DeptID = Goods.DeptID

-- 14. ��������� ������ ���������� (FULL JOIN) ������ Departments � Goods �� ������� DeptID
SELECT * FROM ShopDB.dbo.Departments FULL JOIN ShopDB.dbo.Goods ON Departments.DeptID = Goods.DeptID

-- 15. �������� ��� ������ � ��� ������, ��� ������� �� ������� ������������ � ������ �������.
SELECT * FROM ShopDB.dbo.Departments FULL JOIN ShopDB.dbo.Goods ON Departments.DeptID = Goods.DeptID
	EXCEPT SELECT * FROM ShopDB.dbo.Departments INNER JOIN ShopDB.dbo.Goods ON Departments.DeptID = Goods.DeptID

-- 16.  �������� ��� ������ (������ � ������������), � ������� ��������� ���� �� 1 �����.
-- 1 ������:
SELECT a.DeptID, a.DeptName
	FROM (ShopDB.dbo.Departments AS a INNER JOIN ShopDB.dbo.Goods AS b ON a.DeptID = b.DeptID)
	GROUP BY a.DeptID, a.DeptName HAVING COUNT(b.GName) >= 1

-- 2 ������:
SELECT a.DeptID, a.DeptName FROM ShopDB.dbo.Departments AS a 
	WHERE a.DeptID IN 
	(SELECT b.DeptID FROM ShopDB.dbo.Goods AS b 
	GROUP BY b.DeptID HAVING COUNT(b.GName) >= 1)

SELECT a.DeptID, a.DeptName FROM ShopDB.dbo.Departments AS a
	WHERE EXISTS 
	(SELECT b.DeptID FROM ShopDB.dbo.Goods AS b 
	WHERE a.DeptID = b.DeptID 
	GROUP BY b.DeptID HAVING COUNT (b.GName) >= 1)

-- 3 ������:
SELECT a.DeptID, a.DeptName FROM ShopDB.dbo.Departments AS a
	WHERE a.DeptID = ANY 
	(SELECT b.DeptID FROM ShopDB.dbo.Goods AS b
	GROUP BY b.DeptID HAVING COUNT(b.GName) >= 1)

SELECT a.DeptID, a.DeptName FROM ShopDB.dbo.Departments AS a
	WHERE a.DeptID = SOME
	(SELECT b.DeptID FROM ShopDB.dbo.Goods AS b
	GROUP BY b.DeptID HAVING COUNT(b.GName) >= 1)

-- 17. ��� ������� ������ ��������� ��������� ��������� ���������� ������ � �������� ������ � �������� ���� �������.
-- 1: ����� ����� ��������� �������
SELECT a.DeptID, a.DeptName, SUM(b.Price * b.GCount) AS SumCost
	FROM (ShopDB.dbo.Departments AS a INNER JOIN ShopDB.dbo.Goods AS b ON a.DeptID = b.DeptID)
	GROUP BY a.DeptID, a.DeptName

-- 2: � ���������� ������ 
SELECT a.DeptID, a.DeptName, b.GName, SUM(b.Price * b.GCount) AS SumCost
	FROM (ShopDB.dbo.Departments AS a INNER JOIN ShopDB.dbo.Goods AS b ON a.DeptID = b.DeptID)
	GROUP BY a.DeptID, a.DeptName, b.GName

-- 18. �������� ����� � �������� ������, ��� ��������� ��������� ���������� ������ �����������.
SELECT TOP(1) a.DeptID, a.DeptName, SUM(b.Price * b.GCount) AS SumCost
	FROM (ShopDB.dbo.Departments AS a INNER JOIN ShopDB.dbo.Goods AS b ON a.DeptID = b.DeptID)
	GROUP BY a.DeptID, a.DeptName
	ORDER BY SumCost DESC

-- 19. �������� ��� ������ (������ � ��������) � ����������� ������� ���������� ������.
SELECT TOP(2) a.DeptID, a.DeptName, SUM(b.Price * b.GCount) AS SumCost
	FROM (ShopDB.dbo.Departments AS a INNER JOIN ShopDB.dbo.Goods AS b ON a.DeptID = b.DeptID)
	GROUP BY a.DeptID, a.DeptName
	ORDER BY SumCost DESC

/*20. ��������� ��� ������� ������ ���������� ��������� ��� ��������� �� ���������
��������� ������� � ��������������� ������. �������� ���, ������������ ������
� ����������� �������.*/
SELECT a1.GoodID, a1.GName, a1.Descr, (a1.Price / SUM(a2.Price) * 100) AS PercentageOfSumCost
	FROM ((ShopDB.dbo.Goods AS a1 INNER JOIN ShopDB.dbo.Departments AS b ON a1.DeptID = b.DeptID)
		LEFT OUTER JOIN ShopDB.dbo.Goods AS a2 ON a1.DeptID = a2.DeptID)
	GROUP BY a1.GoodID, a1.GName, a1.Descr, a1.Price

/*21. �������� ���� �� ��� ������ �� 10% ������������ ������� ���� �� ����� �� ����
������� Goods (��������� ������� UPDATE).*/
SELECT AVG(Price) AS AVGPrice FROM ShopDB.dbo.Goods
UPDATE ShopDB.dbo.Goods
	SET Price = Price + (SELECT AVG(Price) FROM ShopDB.dbo.Goods) / 100 * 10
SELECT * FROM ShopDB.dbo.Goods

/* 22. � ����� ������� Discount �������� ��� �������� � �������, � ����� ����� ������,
������� ����������� � ����������� �� ���� ������:
���� ����<10�, �� ������=20% �� ����;
���� 10�<=����<=50�, �� ������=10% �� ����;
���� ����>50�, �� ������=5% �� ����.*/
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

/* 23.  ������� ������� Departments � Goods �� ����� DeptID.
������� ���� ���������� �������� � ������� Goods � ������� �� ��������� ���� ������� Departments */
ALTER TABLE ShopDB.dbo.Goods
	ADD CONSTRAINT FK_Goods_DeptID FOREIGN KEY (DeptID)
	REFERENCES ShopDB.dbo.Departments(DeptID)
/* ��������� ������ ��-�� ����, ��� � Goods DeptID=5 ��������� �� �������������� DeptID=5 � ������� Departments 
- ������������ ����������� ������ � ���� 5 � ������� Departments*/
INSERT INTO ShopDB.dbo.Departments VALUES (5, '�������')
SELECT * FROM ShopDB.dbo.Departments