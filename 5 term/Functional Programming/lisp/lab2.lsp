; Program name: lab2.lsp
; Author: ������
; Creation date: 22.11.2023
; Description:

(trace UFunc)
(defun UFunc (n double_n sum)
    (cond ((<= n 0) (format T "n ������ ���� ������ 0.~%~%"))
          ((> n 0) (cond ((< double_n n) sum)
                          ((>= double_n n) (setq sum (+ sum double_n)) (UFunc n (- double_n 2) sum))))))
(untrace UFunc)

(defun submain ()
    ;����������� �� ����
     (format T "������� ����� ����� n: ")
    ;������ ���������� n
     (setq n (read))
     (format T "~%~%")
     ;����� ������� � ������ � res
     (setq res (UFunc n (* 2 n) 0))
     (format T "~%~%")
     ;���������� ���� � ����
     (cond (( not res))    (
     (setq my_output (open "output.txt" :direction :output))
     (print n my_output)
     (print res my_output)
     (close my_output)

     (format T "���������: ~A.~%" res)
     (format T "��������� ������� � output.txt~%"))))

(defun main ()
    (loop
        (format T "1 - ������, 2 - �����.")
        (let ((choice (read)))
            (cond
                ((= choice 1) (submain))
                ((= choice 2) (return))))))

(main)
