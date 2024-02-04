; Program name: lab3.lsp
; Author: Лейсан
; Creation date: 1.12.2023
; Description:

;Нерекурсивная функция - подсчет суммы ряда целых чисел от n до 2n
(defun UF1 (n)
    (cond ((<= n 0) (format T "Значение n должно быть >0. Функция вернет NIL.~%~%"))
          ((> n 0) (let ((double_n (* 2 n)) (sum 0))
                        (loop (cond ((< double_n n) (RETURN sum)))
                            (setq sum (+ sum double_n))
                            (prin1 'value=) (print double_n)
                            (prin1 'sum=) (print sum)
                            (setq double_n (- double_n 2)))))))

;Функция вычисления среднего арифметического
(defun average (mass)
     (setq iter (get 'mass 'Length))
     (do ((count 0) (sum 0))
        ((= count iter) (/ sum count))
            (setq sum (+ sum (get 'mass count)))
            (setq count (+ count 1))))

;Заполнение массива значениями
(defun subaverage (mass)
    (setq count (get 'mass 'Length))
    (do ((iter 0))
        ((= iter count))
            (format T "Введите числовое значение свойства символа ~A: "  iter)
            (setq property_value (read))
            (setf (get 'mass iter) property_value)
            (setq iter (+ iter 1))))

;Вспомогательная функция для main
(defun submain ()
     ;Приглашение для ввода параметра для рекурсивной функции UF1
     (format T "Введите целое число n для вычисления суммы ряда целых~%четных чисел от n до 2n: ")
     ;Запись в символ n введенных данных
     (setq n (read))
     (format T "~%~%")
     ;Вызов вычислительной функции с записью результатов в символ UF1_res
     (setq UF1_res (UF1 n))
     ;Сохранение полученного результата в файл
     (cond ((not UF1_res))
           ((setq my_output_stream (open "outdata.txt" :direction :output))
            (print n my_output_stream)
            (print UF1_res my_output_stream)
            (terpri my_output_stream)
            (close my_output_stream)
            ; Возвращение функцией submain в качестве своего результата результат вызова вычисления,
            ;а также вывод информирующих сообщений.
            (format T "Результат выполнения функции: ~A.~%" UF1_res)
            (format T "Результат выполнения нерекурсивной функции UF1 записан в файл outdata.txt~%~%~%")))

     ;Задание количества элементов "массива" (свойств символа) и введение их в него
     (format T "Введите количество элементов 'массива': ")
     (setq count (read))
     (cond ((<= count 0) (format T "Длина 'массива' должна быть >0. Функция вернет NIL.~%~%"))
           ((setf (get 'mass 'Length) count)
           ;заполнение
            (subaverage 'mass)
            ;Вычисление среднего арифметического
            (setq res (average 'mass))
            ;Вывод конечных результатов
            (print (symbol-plist 'mass))
            (format T "Среднее арифметическое равно: ~A~%" res))))

;Главная функция программы - точка входа
(defun main ()
    (loop
        (format T "Вы хотите начать программу(1) или выйти из нее(0)? ")
        (let ((choice (read)))
            (cond
                ((= choice 1) (submain))
                ((= choice 0) (RETURN))))))

(main)

