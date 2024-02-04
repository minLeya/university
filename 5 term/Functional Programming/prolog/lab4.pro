
include "lab4.inc"

domains
	Trecording = STRING
	Tdisk = STRING
	Tartist = STRING
	Tsong = STRING
facts
	item(Trecording, Tdisk, Tartist, Tsong)

predicates

	switch(INTEGER)
	repeat

clauses

  	repeat.
  	repeat:-repeat.
  	
  	switch(Case) :- Case = '0', write("The end!"), nl.
  	switch(Case) :- Case = '1',
  	write('\10', "add"),
  	write('\10', "recording: "), readln(Trecording),
  	write('\10', "disk: "), readln(Tdisk),
  	write('\10', "author: "), readln(Tauthor),
  	write('\10', "song: "), readln(Tsong),
  	assert(item(Trecording, Tdisk, Tauthor, Tsong)), fail.
  switch(Case) :- Case = '2',
  	write('\10', "delete"),
  	write('\10', "recording: "), readln(Trecording),
  	write('\10', "disk: "), readln(Tdisk),
  	write('\10', "author: "), readln(Tauthor),
  	write('\10', "song: "), readln(Tsong),
  	retract(item(Trecording, Tdisk, Tauthor, Tsong)), fail.
  switch(Case) :- Case = '3',
  	write('\10', "edit"),
  	write('\10', "replace: "),
  	write('\10', "recording: "), readln(Trecording),
  	write('\10', "disk: "), readln(Tdisk),
  	write('\10', "author: "), readln(Tauthor),
  	write('\10', "song: "), readln(Tsong),
  	retract(item(Trecording, Tdisk, Tauthor, Tsong)),
  	write('\10', "recording: "), readln(TRecording1),
  	write('\10', "disk: "), readln(TDisk1),
  	write('\10', "author: "), readln(TAuthor1),
  	write('\10', "song: "), readln(TSong1),
  	assert(item(TRecording1, TDisk1, TAuthor1, TSong1)), fail.
 switch(Case) :- Case = '4',
  	write('\10', "save"),
  	save("C:\\lab\\folder\\db.txt"),
  	write('\10', "saved in db.txt "), nl, fail.
  switch(Case) :- Case = '5',
  	write('\10', "load"),
  	retractall(item(_,_,_,_)),
  	consult("C:\\lab\\folder\\db.txt"),
  	write('\10', "loaded from db.txt "), nl, fail.
  switch(Case) :- Case = '6',
  	write('\10', "print"),
  	item(Trecording, Tdisk, Tauthor, Tsong),
  	write('\10', "recording: ", Trecording),
	write('\10', "disk: ", Tdisk),
	write('\10', "author: ", Tauthor),
	write('\10', "song: ", Tsong), fail.

goal

  repeat,
	write('\10',"menu"),
        write('\10',"1. add"),
        write('\10',"2. delete"),
        write('\10',"3. edit"),
        write('\10',"4. save"),
        write('\10',"5. load"),
        write('\10',"6. print"),
        write('\10',"0. exit"),
        readchar(Case), nl, switch(Case),!.