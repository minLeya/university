; Program name: lab2.lsp
; Author: Лейсан
; Creation date: 22.11.2023
; Description:

(trace UFunc)
(defun UFunc (n double_n sum)
    (cond ((<= n 0) (format T "n должно быть больше 0.~%~%"))
          ((> n 0) (cond ((< double_n n) sum)
                          ((>= double_n n) (setq sum (+ sum double_n)) (UFunc n (- double_n 2) sum))))))
(untrace UFunc)

(defun submain ()
    ;приглашение на ввод
     (format T "Введите целое число n: ")
    ;запись введенного n
     (setq n (read))
     (format T "~%~%")
     ;вызов функции и запись в res
     (setq res (UFunc n (* 2 n) 0))
     (format T "~%~%")
     ;сохранение реза в файл
     (cond (( not res))    (
     (setq my_output (open "output.txt" :direction :output))
     (print n my_output)
     (print res my_output)
     (close my_output)

     (format T "Результат: ~A.~%" res)
     (format T "Результат записан в output.txt~%"))))

(defun main ()
    (loop
        (format T "1 - начать, 2 - выйти.")
        (let ((choice (read)))
            (cond
                ((= choice 1) (submain))
                ((= choice 2) (return))))))

(main)
