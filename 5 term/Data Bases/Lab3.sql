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
	(1, '�����', '���������', 2, 100),
	(1, '�����', '�������', 10, 50),
	(1, '��������', '�������', 5, 200),
	(1, '��������', '������������', 10, 30),
	(2, '����', '�������������', 6, 200),
	(2, '����', '�������', 7, 150),
	(2, '�������', '"������ �����"', 50, 7)

SELECT * FROM ShopDB.dbo.Goods

INSERT INTO ShopDB.dbo.Goods (DeptID, GName, Descr, Price, GCount) VALUES
	(3, '����', '��������', 20, 30),
	(DEFAULT, '�����', NULL, 15, 40)

SELECT * FROM ShopDB.dbo.Goods

-- 7. ��������� �������� DELETE, ������� �� ������� Goods �� ������,
-- � ������� �� ������ ��������
DELETE FROM ShopDB.dbo.Goods WHERE Descr is NULL

-- 8. ��������� �������� UPDATE, �������� ������� Goods � ��������� ���� �� ���
-- ������ �� 10%
UPDATE ShopDB.dbo.Goods SET Price = Price + Price * 0.1

--9. ��������� �������� SELECT, �������� ������� Goods
SELECT * FROM ShopDB.dbo.Goods

--10. �������� ��� ������ (�� �����, ��� � ��������), ������� ��������� � ������ ������:
SELECT GoodID, GName, Descr FROM ShopDB.dbo.Goods WHERE (DeptID = 1)

-- 11. �������� ��� �������� � ������� � ������� ��������� �� 10 �� 30 ������, ��������� �������� BETWEEN
SELECT * FROM ShopDB.dbo.Goods WHERE (Price BETWEEN 10 AND 30)

-- 12.  �������� ��� �������� � ������� ������� � �������� ������, ��������� �������� IN
SELECT * FROM ShopDB.dbo.Goods WHERE DeptID IN (1, 3)

-- 13.  �������� ��� �������� � �������, ��� ������� ���������� �� ��, ��������� �������� LIKE
SELECT * FROM ShopDB.dbo.Goods WHERE (GName LIKE '�%')

-- 14. �������� ��� �������� � �������, � ����� ������� ����������� ������ �_�, ��������� �������� LIKE
SELECT * FROM ShopDB.dbo.Goods WHERE (GName LIKE '%\_%' ESCAPE '\')

-- 15. �������� ������������ ���� �������
SELECT GName FROM ShopDB.dbo.Goods

-- 16. �������� ������������ ���� ������� ��� ����������
SELECT DISTINCT GName FROM ShopDB.dbo.Goods

-- 17. �������� ��� �������� � ������� ���� ����������� ������� � ���������
-- ������� ������ (���� * ����������)
SELECT *, Price * GCount AS Sum FROM ShopDB.dbo.Goods

-- 18. �������� �����������, �������, ������������ ���� �� ���� �������.
SELECT MIN(Price) AS minimun, AVG(Price) AS average, MAX(Price) AS maximum FROM ShopDB.dbo.Goods

-- 19. �������� ���������� ������������ �������, ����������� � ������ ������
SELECT COUNT(GName) FROM ShopDB.dbo.Goods WHERE DeptID = 1

-- 20. �������� ���������� �������, ��� ������� ������ �������� (Descr �� null)
SELECT COUNT(*) FROM ShopDB.dbo.Goods WHERE Descr IS NOT NULL

-- 21. �������� ��������� ��������� ������� �� ������� ������
SELECT SUM(Price) FROM ShopDB.dbo.Goods WHERE DeptID = 2

-- 22. �������� ��� ������, ������������ �� ������.
SELECT * FROM ShopDB.dbo.Goods ORDER BY GName

-- 23. �������� ��� ������, ������������ �� ������� � �� �������� ����.
SELECT * FROM ShopDB.dbo.Goods ORDER BY DeptID, Price DESC

-- 24. ��������� ��������� ���������� ������ �� ������� ������.
SELECT DeptID, SUM(Price * GCount) FROM ShopDB.dbo.Goods GROUP BY DeptID

-- 25. ��������� ������� ���� ������ �� ��� �������, ���� ������� ��������� 9 ������
SELECT AVG(Price) AS average FROM ShopDB.dbo.Goods WHERE Price > 9

-- 26. ��������� ������������ ���� �� ������� ������������ ������.
SELECT GName, MAX(Price) AS maximum FROM ShopDB.dbo.Goods GROUP BY GName

-- 27. �������� ������ �������, ��� ��������� ����� ���� ������������ �������.
SELECT DeptID FROM ShopDB.dbo.Goods GROUP BY DeptID HAVING COUNT(GName) > 2