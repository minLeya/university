%первое задание
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

% задание сложного предиката (правила) "мама"
mother(X, Y) :- parent(X, Y), female(X).

% задание сложного предиката (правила) "сестра" - X является сестрой для
% Y
sister(X, Y):- parent(Z, X), parent(Z, Y), female(X), not(X=Y).

%grandmother(X, Y) := parent(X, Z), parent(Z, Y), female(X).

%цель1: является ли Анна дочерью Екатерины? - true
goal1 :- parent(ekaterina, anna), female(anna), write("Анна является дочерью Екатерины"), nl; write("Анна не является дочерью Екатерины"), nl.

%цель2: кто является бабушкой Анны - Доротея и Наталья
goal2 :- (writeln("Бабушки Анны:");parent(X, anna), mother(Y, X), writeln(Y)), fail.

%цель3: Наташа - мама или тетя Елизаветы?
goal3 :- mother(natasha, elizaveta), write("Наташа - мама Елизаветы."), nl; sister(natasha, X), parent(X, elizaveta), write("Наташа - тётя Елизаветы."), nl.

%кто правил страной
goal4:-pravlenie(X, yes), writef("%t правил страной.\n", [X]), fail.

%родились ли X и Y в один день
goal5(X, Y):- born(X, T, _, _), born(Y, T, _, _), write("Они родились в один день."), nl;  born(X, _, _, _), born(Y, _, _, _), write("Они не родились в один день."), nl.



%второе задание
%Функция для получения ln(1+X) с точностью N
compute_without_accuracy(X, N, Answer):-
    N =:= 0, Answer is 0;
    N =:= 1, Answer is X;
%В остальных случаях получаем рекурсией результат функции
%для N-1 и добавляем к полученному результату слагаемое,
%полученное по формуле
    N_1 is N - 1,
    compute_without_accuracy(X, N_1, PrevAnswer),
    Answer is (PrevAnswer + ((-1)**(N+1))*(X**N/N)).

%Функция, возвращающая точный ответ
compute(X, Answer):-
    Answer is log(1+X).

%Функция, реализовывающая диалог с пользователем и вывод ответа
start_computings :-
    write("X = "),
    read(X),
    -1 < X,
    X =< 1,
    write("N = "),
    read(N),
    N > 0,
    compute(X, Result),
    compute_without_accuracy(X, N, UnaccuracyResult),
    write("Точный ответ:"), nl,
    format('~6f', Result), nl,
    write("Приближенный ответ:"), nl,
    format('~6f', UnaccuracyResult), nl,
    Error is abs(UnaccuracyResult - Result),
    write("Ошибка вычислений составила:"), nl,
    format('~6f', Error), nl;
    write("Ошибка: введены некорректные значения!").


start :-
    writeln("Выберите необходимое действие: "),
    writeln("1 - Перейти в меню вычислений."),
    writeln("2 - Перейти в меню работы с семьей."),
    writeln("3 - Завершить работу программы."),
    read(Answer),
   (
        (Answer =:= 1, start_computings);
        (Answer =:= 2, family);
        (Answer =:= 3, halt(0));
        writeln("Вы, вероятно, ошиблись.")
   ),
   %После выполнения всех действий для того, чтобы программа начала новый цикл,
   %рекурсивно вызываем главное меню еще раз
   start.

family :-
    writeln("Выберите необходимое действие: "),
    writeln("1 - Выяснить, является ли Анна дочерью Екатерины."),
    writeln("2 - Выяснить, кто является бабушкой Анны."),
    writeln("3 - Выяснить, кем является Наташа по отношению к Елизавете: мамой или тётей. "),
    writeln("4 - Выяснить, кто правил страной."),
    writeln("5 - Выяснить, родились ли X и Y в один день."),
    writeln("6 - Покинуть меню семьи."),
    read(Answer),
    %Если был выбран пункт, отличный от 5го, то в конце мы рекурсивно вызываем меню семьи для продолжения работы с ним
    %В противном случае работа с меню семьи завершается, и мы возвращаемся в главное
    (
        (
            Answer =:= 1,
            goal1,
            family
         );

        (
            Answer =:= 2,
            goal2,
            family
        );

        (
            Answer =:= 3,
            goal3,
            family
        );

        (
            Answer =:= 4,
            goal4,
            family
        );

        (
            Answer =:= 5,
            writeln("Введите имя первого человека: "),
            read(X),
            writeln("Введе имя второго человека: "),
            read(Y),
            goal5(X, Y),
            family
        );

        (
            Answer =:= 6
        );

        (
            writeln("Вероятно, вы ошиблись."),
            family
        )
    ).
