predicates

  parent(STRING, STRING).
  woman(STRING).
  man(STRING).
  married_couple(STRING, STRING).
  
  son(STRING, STRING).
  nephew(STRING, STRING).
  sibling(STRING, STRING)
  check_any_cousin_brother(STRING, STRING, INTEGER)
  %n-������� ����
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
  	%��������, ��� N-������� ���� �������� ����. �������� ������ ��������� � �������� �� ���� ��������.
  	check_any_cousin_brother(N_Brother, Child, N):-
  		man(N_Brother),
  		any_cousin_brother(N_Brother, Child, N).
  
%N-������� ����.
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
%1)��������� �� ������� a � ��������� R � ��������� b?[���: R(a, b)]
	write("�������� �� ������ ����� ����"), nl,
	son("Mihail", "Julia"),
	write("������ - ��� ����"),
	nl, nl,
	fail;
	
	write("�������� �� ����� ����������� �������"), nl,
	nephew("Pavel", "Kirill"),
	write("����� - ��������� �������."),
	nl, nl,
	fail;

	write("�������� �� ����� ���������� ������ �������?"), nl,
	check_any_cousin_brother("Danil", "Mihail", 3),
	write("����� - ���������� ���� �������."),
	nl, nl,
	fail;
	
	write("�������� �� ���� ���������� ����������� ������?"), nl,
	second_cousin_nephew("Vlad", "Ksenia"),
	write("���� - ���������� ��������� ������."),
	nl, nl,
	fail;
	
	write("�������� �� ���� ��������� ���������?"), nl,
	shoot("Rada", "Anastasia", 4),
	write("���� - ������� ���������."),
	nl, nl,
	fail;

	write("�������� �� ���� ����� �����?"), nl,
	daughters_husband("Mark", "Nelly"),
	write("���� - ���� �����."),
	nl, nl,
	fail;
	
%2)��� ��������� � ��������� R � ��������� a?[���: R(a, Y), R(X, b)]
	write("��� �������� ���������� ������?"), nl,
	parent(Parent, "Ksenia"),
	write(Parent), 
	nl,
	fail;

	nl,
	write("��� �������� ����� �������?"), nl,
	daughters_husband("Alexey", Daughters_parent),
	write(Daughters_parent),
	nl,
	fail;

	nl,
	write("��� �������� ����� �����?"), nl,
	son(Son, "Alice"),
	write(Son),
	nl,
	fail;
	
%3)����� ��� ���� ���������, ����������� � ��������� R. [���: R(X,Y)]".
	nl,
	write("������ ���� ������� ���:"), nl,
	married_couple(Woman, Man),
	write(Woman, " � ",Man),
	nl,
	fail;
	
	nl,
	write ("������ ���� �����������:"), nl,
	nephew(Nephew, Uncle),
	write(Nephew, " ��� ",Uncle),
	nl,
	fail;
	
	nl,
	write ("������ ���� ���������� �����������:"), nl,
	second_cousin_nephew(Second_cousin_nephew, Second_cousin_uncle),
	write(Second_cousin_nephew, " ��� ",Second_cousin_uncle),
	nl,
	fail;
	
	nl,
	write ("������ ���� ���������� �������:"), nl,
	check_any_cousin_brother(X, Y, 3),
	write(X, " ��� ", Y),
	nl,
	fail.
goal
	run().
  

  	
  	
  	

