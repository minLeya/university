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
start :-
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
