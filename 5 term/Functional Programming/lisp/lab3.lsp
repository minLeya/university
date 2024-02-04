; Program name: lab3.lsp
; Author: ������
; Creation date: 1.12.2023
; Description:

;������������� ������� - ������� ����� ���� ����� ����� �� n �� 2n
(defun UF1 (n)
    (cond ((<= n 0) (format T "�������� n ������ ���� >0. ������� ������ NIL.~%~%"))
          ((> n 0) (let ((double_n (* 2 n)) (sum 0))
                        (loop (cond ((< double_n n) (RETURN sum)))
                            (setq sum (+ sum double_n))
                            (prin1 'value=) (print double_n)
                            (prin1 'sum=) (print sum)
                            (setq double_n (- double_n 2)))))))

;������� ���������� �������� ���������������
(defun average (mass)
     (setq iter (get 'mass 'Length))
     (do ((count 0) (sum 0))
        ((= count iter) (/ sum count))
            (setq sum (+ sum (get 'mass count)))
            (setq count (+ count 1))))

;���������� ������� ����������
(defun subaverage (mass)
    (setq count (get 'mass 'Length))
    (do ((iter 0))
        ((= iter count))
            (format T "������� �������� �������� �������� ������� ~A: "  iter)
            (setq property_value (read))
            (setf (get 'mass iter) property_value)
            (setq iter (+ iter 1))))

;��������������� ������� ��� main
(defun submain ()
     ;����������� ��� ����� ��������� ��� ����������� ������� UF1
     (format T "������� ����� ����� n ��� ���������� ����� ���� �����~%������ ����� �� n �� 2n: ")
     ;������ � ������ n ��������� ������
     (setq n (read))
     (format T "~%~%")
     ;����� �������������� ������� � ������� ����������� � ������ UF1_res
     (setq UF1_res (UF1 n))
     ;���������� ����������� ���������� � ����
     (cond ((not UF1_res))
           ((setq my_output_stream (open "outdata.txt" :direction :output))
            (print n my_output_stream)
            (print UF1_res my_output_stream)
            (terpri my_output_stream)
            (close my_output_stream)
            ; ����������� �������� submain � �������� ������ ���������� ��������� ������ ����������,
            ;� ����� ����� ������������� ���������.
            (format T "��������� ���������� �������: ~A.~%" UF1_res)
            (format T "��������� ���������� ������������� ������� UF1 ������� � ���� outdata.txt~%~%~%")))

     ;������� ���������� ��������� "�������" (������� �������) � �������� �� � ����
     (format T "������� ���������� ��������� '�������': ")
     (setq count (read))
     (cond ((<= count 0) (format T "����� '�������' ������ ���� >0. ������� ������ NIL.~%~%"))
           ((setf (get 'mass 'Length) count)
           ;����������
            (subaverage 'mass)
            ;���������� �������� ���������������
            (setq res (average 'mass))
            ;����� �������� �����������
            (print (symbol-plist 'mass))
            (format T "������� �������������� �����: ~A~%" res))))

;������� ������� ��������� - ����� �����
(defun main ()
    (loop
        (format T "�� ������ ������ ���������(1) ��� ����� �� ���(0)? ")
        (let ((choice (read)))
            (cond
                ((= choice 1) (submain))
                ((= choice 0) (RETURN))))))

(main)

