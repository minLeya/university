predicates

  parent(STRING, STRING).
  woman(STRING).
  man(STRING).
  married_couple(STRING, STRING).
  
  son(STRING, STRING).
  nephew(STRING, STRING).
  sibling(STRING, STRING)
  check_any_cousin_brother(STRING, STRING, INTEGER)
  %n-юродный брат
  any_cousin_brother(STRING, STRING, INTEGER).
  second_cousin_nephew(STRING, STRING).
  shoot(STRING, STRING, INTEGER).
  daughters_husband(STRING, STRING).
  
  run().
  
clauses
  woman("Anastasia").
  woman("Tatiana").
  woman("Katerina").
  woman("Alice").
  woman("Rada").
  woman("Nelly").
  woman("Julia").
  woman("Ksenia").
  
  man("Anatoliy").
  man("Kirill").
  man("Alexey").
  man("Pavel").
  man("Nikolay").
  man("Danil").
  man("Vlad").
  man("Mark").
  man("Mihail").

  married_couple("Anastasia", "Anatoliy").
  married_couple("Tatiana", "Alexey").
  married_couple("Katerina", "Nikolay").
  married_couple("Alice", "Danil").
  married_couple("Nelly", "Kirill").
  married_couple("Julia", "Mark").
  
  parent("Anastasia", "Tatiana").
  parent("Anatoliy", "Tatiana").
  parent("Anastasia", "Kirill").
  parent("Anatoliy", "Kirill").
  
  
  parent("Tatiana", "Pavel").
  parent("Alexey", "Pavel").
  parent("Tatiana", "Katerina").
  parent("Alexey", "Katerina").
  
 
  parent("Katerina", "Danil").
  parent("Nikolay", "Danil").
   
  
  parent("Danil", "Rada").
  parent("Alice", "Rada").
  parent("Danil", "Vlad").
  parent("Alice", "Vlad").
  
  
  parent("Kirill", "Julia").
  parent("Nelly", "Julia").
  
 
  parent("Julia", "Ksenia").
  parent("Mark", "Ksenia").
  parent("Julia", "Mihail").
  parent("Mark", "Mihail").
  
  /*A is son of B*/
  son(A, B):-man(A), parent(B,A).  
  /*A is nephew of B*/
  /*same parents for B and D, D is parent of A, A i male*/
  nephew(A, B):-
  	man(A),
  	parent(D, A),
  	parent(E, D),
  	parent(E, B),
  	B<>D.
  	
  	sibling(X, Y):-
   		parent(Parent, X), parent(Parent, Y), not(X = Y), !. 
  	%Проверка, что N-юродный брат мужского пола. Отделяет первое вхождение в рекурсию от всей рекурсии.
  	check_any_cousin_brother(N_Brother, Child, N):-
  		man(N_Brother),
  		any_cousin_brother(N_Brother, Child, N).
  
%N-юродный брат.
  	any_cousin_brother(X, Y, 1):-
   		sibling(X, Y).
  	any_cousin_brother(N_Brother, Child, N):-
   		N > 1,
   		parent(Parent_N_Brother, N_Brother),
   		parent(Parent_Child, Child),
   		M = N - 1,
   		any_cousin_brother(Parent_N_Brother, Parent_Child, M).
  
  /*A is second_cousin_nephew for B)*/
  second_cousin_nephew(A, B):-
  	parent(N, A),
  	parent(F, N),
  	parent(E, F),
  	parent(D, E),
  	parent(D, C),
  	parent(C, M),
  	parent(M, B),
  	E<>C,
  	man(A).
  
  %shoot
  shoot(X,Y,0):-X=Y.
  shoot(X,Y,N):-
  	N>0,
  	parent(Y, Z),
  	M=N-1,
  	shoot(X, Z, M).
  
  daughters_husband(A, B):-
  	man(A),
  	woman(C),
  	married_couple(C, A),
  	parent(B, C).
  
run():-
%1)Находится ли субъект a в отношении R с субъектом b?[тип: R(a, b)]
	write("Является ли Михаил сыном Юлии"), nl,
	son("Mihail", "Julia"),
	write("Михаил - сын Юлии"),
	nl, nl,
	fail;
	
	write("Является ли Павел племянником Кирилла"), nl,
	nephew("Pavel", "Kirill"),
	write("Павел - племянник Кирилла."),
	nl, nl,
	fail;

	write("Является ли Данил троюродным братом Михаила?"), nl,
	check_any_cousin_brother("Danil", "Mihail", 3),
	write("Данил - троюродный брат Михаила."),
	nl, nl,
	fail;
	
	write("Является ли Влад троюродным племянником Ксении?"), nl,
	second_cousin_nephew("Vlad", "Ksenia"),
	write("Влад - троюродный племянник Ксении."),
	nl, nl,
	fail;
	
	write("Является ли Рада отпрыском Анастасии?"), nl,
	shoot("Rada", "Anastasia", 4),
	write("Рада - отпрыск Анастасии."),
	nl, nl,
	fail;

	write("Является ли Марк зятем Нелли?"), nl,
	daughters_husband("Mark", "Nelly"),
	write("Марк - зять Нелли."),
	nl, nl,
	fail;
	
%2)Кто находится в отношении R с субъектом a?[тип: R(a, Y), R(X, b)]
	write("Кто является родителями Ксении?"), nl,
	parent(Parent, "Ksenia"),
	write(Parent), 
	nl,
	fail;

	nl,
	write("Кто является зятем Алексея?"), nl,
	daughters_husband("Alexey", Daughters_parent),
	write(Daughters_parent),
	nl,
	fail;

	nl,
	write("Кто является сыном Алисы?"), nl,
	son(Son, "Alice"),
	write(Son),
	nl,
	fail;
	
%3)Найти все пары субъектов, находящихся в отношении R. [тип: R(X,Y)]".
	nl,
	write("Список всех женатых пар:"), nl,
	married_couple(Woman, Man),
	write(Woman, " и ",Man),
	nl,
	fail;
	
	nl,
	write ("Список всех племянников:"), nl,
	nephew(Nephew, Uncle),
	write(Nephew, " для ",Uncle),
	nl,
	fail;
	
	nl,
	write ("Список всех троюродных племянников:"), nl,
	second_cousin_nephew(Second_cousin_nephew, Second_cousin_uncle),
	write(Second_cousin_nephew, " для ",Second_cousin_uncle),
	nl,
	fail;
	
	nl,
	write ("Список всех троюродных братьев:"), nl,
	check_any_cousin_brother(X, Y, 3),
	write(X, " для ", Y),
	nl,
	fail.
goal
	run().
  

  	
  	
  	

