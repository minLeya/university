
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
	
	%первое задание
	%первый элемент
	removef(El, [El|T], T):-!.

	%элемента нет
	removef(_, [], []):-!.
	
	%удаляемый элемент не равен голове рассматриваемого списка
 	removef(El, [H|T], [H|Res]):-
  		removef(El, T, Res).
  

	%второе задание
	diff([], _, []):-!.
 	%элемент есть во втором множестве.
  	diff([HA|TA], B, Result):-
  		belongs(B, HA), !,
  		removef(HA, B, NewB),
  		diff(TA, NewB, Result).
  	%элемент отсутствует во втором множестве.
 	diff([HA|TA], B, [HA|Result]):-
  		diff(TA, B, Result).
goal

  	write("Исходный список [3,3,3,1,2,3,3,3,4,8,6], удалить 3. Получили:"),
  	nl,
  	removef(3, [3,3,3,1,2,3,3,3,4,8,6], Result),
  	write(Result), 
  	nl, nl,
  	fail;
  
  	write("Исходный список список [3,3,3,1,2,3,3,1,3,4,1,8,6], удалить 1. Получили:"), 
  	nl,
  	removef(1, [3,3,3,1,2,3,3,1,3,4,1,8,6], Result),
  	write(Result),
  	nl, nl,
  	fail;
  
  
  	write("Исходные множества: [1,2,3,4,5,6,7,10] и [10,1,5,2,8]. Получили:"),
  	nl,
  	diff([1,2,3,4,5,6,7,10], [10,1,5,2,8], Result),
  	write(Result),
  	nl, nl,
  	fail;
  
  	write("Исходные множества: [1,2,3,4,5,6,7,10] и [10,7,8,9]. Получили:"),
  	nl,
  	diff([1,2,3,4,5,6,7,10], [10,7,8,9], Result),
  	write(Result),
  	nl, nl,
  	fail.
  

