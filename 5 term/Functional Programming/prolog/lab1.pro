predicates
	parent(STRING, STRING).
	woman(STRING).
	man(STRING).
clauses
	parent("Askhat", "Leysyan").
	parent("Alsu", "Leysyan").
	parent("Askhat", "Aisulu").
	parent("Alsu", "Aisulu").
	
	parent("Aisulu", "Kamil").
	parent("Ildar", "Kamil").
	
	parent("Sveta", "Ildar").
	parent("Shamil", "Ildar").
	
	woman("Alsu").
	woman("Aisulu").
	woman("Leysyan").
	woman("Sveta").
	
	man("Askhat").
	man("Ildar").
	man("Kamil").
	man("Shamil").
	
goal

	%write("Hello, World!"), nl.
	%������ ����� �������
	%���� ������
	%parent("Askhat", X).
	%������� � ���� ����
	%parent("Alsu", X), parent(X, Y).
	%������� � ������� � �������� ������
	%parent(X, Y), parent(Y, "Kamil").
	%�������� �� ������ ������� ������
	%parent("Leysyan", "Kamil").


	%������ ����� �������
	%���� ������
	%parent(X, "Aisulu"), man(X).
	%������� ������ �� ������� ����
	%parent(Y, X), parent(X, "Kamil"), woman(Y), man(X).
	%������� ������
	parent(X, Y), parent(Y, "Kamil"), man(X).

	