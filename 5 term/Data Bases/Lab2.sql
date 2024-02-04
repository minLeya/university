CREATE DATABASE BookshopDB
GO 

EXEC sp_helpdb BookshopDB

USE BookshopDB 
GO

CREATE TABLE Authors(
	AuthorID INT IDENTITY NOT NULL,
	FirstName VARCHAR(30) NOT NULL DEFAULT 'unknown',
	LastName VARCHAR(30) NULL,
	YearBorn CHAR(4) NULL,
	YearDied CHAR(4) NOT NULL DEFAULT 'no')

EXEC sp_help Authors

ALTER TABLE Authors ADD Descr VARCHAR(200) NOT NULL
GO

USE BookshopDB 
GO
CREATE TABLE Books(
	BookID INT NOT NULL PRIMARY KEY,
	Title VARCHAR(100) NOT NULL,
	Genre VARCHAR(50) NULL)

USE BookshopDB 
GO
CREATE TABLE BookAuthor(
	BookID INT NOT NULL,
	AuthorID INT NOT NULL)

ALTER TABLE BookAuthor ADD PRIMARY KEY (BookID, AuthorID)

ALTER TABLE BookAuthor ADD CONSTRAINT BookAndAuthor
FOREIGN KEY (BookID) REFERENCES Books(BookID)

ALTER TABLE Authors ADD PRIMARY KEY (AuthorID)

ALTER TABLE BookAuthor ADD CONSTRAINT BookAndAuthor_Author
FOREIGN KEY (AuthorID) REFERENCES Authors(AuthorID)

ALTER TABLE Authors ADD CONSTRAINT check_YearBorn
CHECK (YearBorn LIKE '[1-2][0,6-9][0-9][0-9]')

ALTER TABLE Authors ADD CONSTRAINT check_YearDied
CHECK (YearDied LIKE '[1-2][0,6-9][0-9][0-9]' or YearDied LIKE 'no')

ALTER TABLE Authors ADD CONSTRAINT check_if_YearDied_is_Greater
CHECK (YearDied > YearBorn)

INSERT INTO Authors (FirstName, LastName, YearBorn, YearDied, Descr)
VALUES ('Александр', 'Пушкин', '1799', '1837', 'русский поэт, драматург и прозаик')

INSERT INTO Authors (FirstName, LastName, YearBorn, YearDied, Descr)
VALUES ('Сергей', 'Есенин', '1895', '1925', 'русский поэт и писатель')

INSERT INTO Books VALUES (1, 'Капитанская дочка', 'историческая проза')
INSERT INTO Books VALUES (2, 'Руслан и Людмила','поэма')
INSERT INTO Books VALUES (3, 'Евгений Онегин','роман в стихах')
INSERT INTO Books VALUES (4, 'Исповедь хулигана', 'поэзия')

INSERT INTO BookAuthor VALUES(1, 1)
INSERT INTO BookAuthor VALUES(2, 1)
INSERT INTO BookAuthor VALUES(3, 1)
INSERT INTO BookAuthor VALUES(4, 2)
