
include "lab3.inc"

domains
	list = INTEGER*

predicates

  removef(INTEGER, list, list).
  diff(list, list, list).
  
  belongs(list, INTEGER).

clauses
	belongs([X|_], X).
	belongs([_|T], X):-belongs(T, X).
	
	%������ �������
	%������ �������
	removef(El, [El|T], T):-!.

	%�������� ���
	removef(_, [], []):-!.
	
	%��������� ������� �� ����� ������ ���������������� ������
 	removef(El, [H|T], [H|Res]):-
  		removef(El, T, Res).
  

	%������ �������
	diff([], _, []):-!.
 	%������� ���� �� ������ ���������.
  	diff([HA|TA], B, Result):-
  		belongs(B, HA), !,
  		removef(HA, B, NewB),
  		diff(TA, NewB, Result).
  	%������� ����������� �� ������ ���������.
 	diff([HA|TA], B, [HA|Result]):-
  		diff(TA, B, Result).
goal

  	write("�������� ������ [3,3,3,1,2,3,3,3,4,8,6], ������� 3. ��������:"),
  	nl,
  	removef(3, [3,3,3,1,2,3,3,3,4,8,6], Result),
  	write(Result), 
  	nl, nl,
  	fail;
  
  	write("�������� ������ ������ [3,3,3,1,2,3,3,1,3,4,1,8,6], ������� 1. ��������:"), 
  	nl,
  	removef(1, [3,3,3,1,2,3,3,1,3,4,1,8,6], Result),
  	write(Result),
  	nl, nl,
  	fail;
  
  
  	write("�������� ���������: [1,2,3,4,5,6,7,10] � [10,1,5,2,8]. ��������:"),
  	nl,
  	diff([1,2,3,4,5,6,7,10], [10,1,5,2,8], Result),
  	write(Result),
  	nl, nl,
  	fail;
  
  	write("�������� ���������: [1,2,3,4,5,6,7,10] � [10,7,8,9]. ��������:"),
  	nl,
  	diff([1,2,3,4,5,6,7,10], [10,7,8,9], Result),
  	write(Result),
  	nl, nl,
  	fail.
  

