predicates

  parent(STRING, STRING).
  woman(STRING).
  man(STRING).
  married_couple(STRING, STRING).
  
  son(STRING, STRING).
  nephew(STRING, STRING).
  %n-þðîäíûé áðàò
  n_cousin_brother(STRING, STRING, INTEGER).
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
  
  /*A is n-cousin-brother for B*/
  n_cousin_brother(Ancestor_1, Ancestor_2, 0):-
  	Ancestor_1 = Ancestor_2.
  n_cousin_brother(A, B, N):-
  	N>0,
  	parent(C, A),
  	parent(D, B),
  	M = N - 1,
  	n_cousin_brother(C, D, M).
  
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
%1)Íàõîäèòñÿ ëè ñóáúåêò a â îòíîøåíèè R ñ ñóáúåêòîì b?[òèï: R(a, b)]
	write("ßâëÿåòñÿ ëè Ìèõàèë ñûíîì Þëèè"), nl,
	son("Mihail", "Julia"),
	write("Ìèõàèë - ñûí Þëèè"),
	nl, nl,
	fail;
	
	write("ßâëÿåòñÿ ëè Ïàâåë ïëåìÿííèêîì Êèðèëëà"), nl,
	nephew("Pavel", "Kirill"),
	write("Ïàâåë - ïëåìÿííèê Êèðèëëà."),
	nl, nl,
	fail;

	write("ßâëÿåòñÿ ëè Äàíèë òðîþðîäíûì áðàòîì Ìèõàèëà?"), nl,
	n_cousin_brother("Danil", "Mihail", 3),
	write("Äàíèë - òðîþðîäíûé áðàò Ìèõàèëà."),
	nl, nl,
	fail;
	
	write("ßâëÿåòñÿ ëè Âëàä òðîþðîäíûì ïëåìÿííèêîì Êñåíèè?"), nl,
	second_cousin_nephew("Vlad", "Ksenia"),
	write("Âëàä - òðîþðîäíûé ïëåìÿííèê Êñåíèè."),
	nl, nl,
	fail;
	
	write("ßâëÿåòñÿ ëè Ðàäà îòïðûñêîì Àíàñòàñèè?"), nl,
	shoot("Rada", "Anastasia", 4),
	write("Ðàäà - îòïðûñê Àíàñòàñèè."),
	nl, nl,
	fail;

	write("ßâëÿåòñÿ ëè Ìàðê çÿòåì Íåëëè?"), nl,
	daughters_husband("Mark", "Nelly"),
	write("Ìàðê - çÿòü Íåëëè."),
	nl, nl,
	fail;
	
%2)Êòî íàõîäèòñÿ â îòíîøåíèè R ñ ñóáúåêòîì a?[òèï: R(a, Y), R(X, b)]
	write("Êòî ÿâëÿåòñÿ ðîäèòåëÿìè Êñåíèè?"), nl,
	parent(Parent, "Ksenia"),
	write(Parent), 
	nl,
	fail;

	nl,
	write("Êòî ÿâëÿåòñÿ çÿòåì Àëåêñåÿ?"), nl,
	daughters_husband("Alexey", Daughters_parent),
	write(Daughters_parent),
	nl,
	fail;

	nl,
	write("Êòî ÿâëÿåòñÿ ñûíîì Àëèñû?"), nl,
	son(Son, "Alice"),
	write(Son),
	nl,
	fail;
	
%3)Íàéòè âñå ïàðû ñóáúåêòîâ, íàõîäÿùèõñÿ â îòíîøåíèè R. [òèï: R(X,Y)]".
	nl,
	write("Ñïèñîê âñåõ æåíàòûõ ïàð:"), nl,
	married_couple(Woman, Man),
	write(Woman, " è ",Man),
	nl,
	fail;
	
	nl,
	write ("Ñïèñîê âñåõ ïëåìÿííèêîâ:"), nl,
	nephew(Nephew, Uncle),
	write(Nephew, " äëÿ ",Uncle),
	nl,
	fail;
	
	nl,
	write ("Ñïèñîê âñåõ òðîþðîäíûõ ïëåìÿííèêîâ:"), nl,
	second_cousin_nephew(Second_cousin_nephew, Second_cousin_uncle),
	write(Second_cousin_nephew, " äëÿ ",Second_cousin_uncle),
	nl,
	fail.
goal
	run().
  
