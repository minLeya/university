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
	%первая часть задания
	%дети Асхата
	%parent("Askhat", X).
	%ребенок и внук Алсу
	%parent("Alsu", X), parent(X, Y).
	%бабушка и дедушка и родители Камиля
	%parent(X, Y), parent(Y, "Kamil").
	%является ли Лейсян матерью Камиля
	%parent("Leysyan", "Kamil").


	%вторая часть задания
	%отец Айсылу
	%parent(X, "Aisulu"), man(X).
	%бабушка Камиля со стороны отца
	%parent(Y, X), parent(X, "Kamil"), woman(Y), man(X).
	%дедушки Камиля
	parent(X, Y), parent(Y, "Kamil"), man(X).

	