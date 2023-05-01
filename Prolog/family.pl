%дети Алексея и Натальи (Natalya) Нарышкиной - Наталья (Natasha) и Петр
parent(alexey, natasha).
parent(alexey, petr).
parent(natalya, natasha).
parent(natalya, petr).

%ребенок Доротеи и Самуила - Екатерина
parent(samuel, ekaterina).
parent(dorothy, ekaterina).

%дети Петра 1 и Екатерины 1 - Анна, Елизавета
parent(petr, anna).
parent(petr, elizaveta).
parent(ekaterina, anna).
parent(ekaterina, elizaveta).

% задание простого одноместного предиката (фактов) "мужчина"
male(petr).
male(alexey).
male(samuel).

% задание простого одноместного предиката (фактов) "женщина"
female(anna).
female(elizaveta).
female(ekaterina).
female(natasha). %дочь Натальи
female(natalya). %мама Натальи(Наташи) и Петра
female(dorothy).

%последние титулы (т.е. будучи кем они умерли).
titul(alexey, king).
titul(natalya, queen).
titul(samuel, unknown).
titul(dorothy, unknown).
titul(natasha, princess).
titul(petr, emperor).
titul(ekaterina, empress).
titul(anna, duchess).
titul(elizaveta, empress).

%правители России (Русь, Российская империя)
pravlenie(alexey, yes).
pravlenie(natalya, yes).
pravlenie(samuel, no).
pravlenie(dorothy, no).
pravlenie(natasha, no).
pravlenie(petr, yes).
pravlenie(ekaterina, yes).
pravlenie(elizaveta, yes).
pravlenie(anna, no).

%дата рождения
born(alexey, 29, 3, 1629).
born(natalya, 1, 9, 1651).
born(samuel, unknown, unknown, unknown).
born(dorothy, unknown, unknown, unknown).
born(natasha, 22, 8, 1673).
born(petr, 9, 6, 1672).
born(ekaterina, 15, 4, 1684).
born(anna, 27, 1, 1708).
born(elizaveta, 29, 12, 1709).

% задание сложного предиката (правила) "отец"
father(X, Y) :- parent(X, Y), male(X).

% задание сложного предиката (правила) "мама"
mother(X, Y) :- parent(X, Y), female(X).

% задание сложного предиката (правила) "сестра" - X является сестрой для
% Y
sister(X, Y):- parent(Z, X), parent(Z, Y), female(X), not(X=Y).

% брат - X яв-ся братом для Y
brother(X, Y):- parent(Z, X), parent(Z,Y), male(X), not(X=Y).

% задание сложного предиката (правила) "сын" - X яв-ся сыном для Y
son(X, Y) :- parent(Y, X), male(X).

%grandmother(X, Y) := parent(X, Z), parent(Z, Y), female(X).

%цель1: является ли Анна дочерью Екатерины? - true
goal1 :- parent(ekaterina, anna), female(anna).

%цель2: является ли Х матерью
goal2(X) :- mother(X, _).

%цель3: кто является бабушкой Анны - Доротея и Наталья
goal3 :- (writeln("Anna's grandmothers are:");parent(X, anna), mother(Y, X), writeln(Y)), fail.

%цель4: Наташа - мама или тетя Елизаветы?
goal4 :- mother(natasha, elizaveta), write("Natasha is Elizaveta's mother."), nl; sister(natasha, X), parent(X, elizaveta), write("Natasha is Elizaveta's aunt."), nl.

%кто правил страной
goal5:-pravlenie(X, yes), writef("%t ruled the country.\n", [X]), fail.

%родились ли X и Y в один день
goal6(X, Y):- born(X, T, _, _), born(Y, T, _, _), write("they were born on the same day"), nl;  born(X, _, _, _), born(Y, _, _, _), write("they weren't born on the same day"), nl.
