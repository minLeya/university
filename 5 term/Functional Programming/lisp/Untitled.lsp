; Program name: Untitled.lsp
; Author: Лейсан
; Creation date: 22.11.2023
; Description:
(defun UF1 (x)
    (+ (+ (log x 2) (log x 6)) (log x 10)))

(defun UF2 (x)
    (* 2 (sin (/ (* 2 x) 3)) (cos(/ (* 2 x) 3))))

(let ((arg-value 5))

(setq UFR (list (UF1 arg-value)(UF2 arg-value))))
(print UFR)

(setq X1 (reverse UFR))
(print X1)

(setq X2 (length UFR))
(print X2)

(setq X3 (+ (first UFR)(second UFR)))
(print X3)
