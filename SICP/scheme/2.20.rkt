#lang planet neil/sicp

; parity? : int 
; for Exercise 2.20
; return 0 if the given number is even
(define (parity? n)
  (remainder n 2))

; same-parity : int, int ... int
; return the list that have same even-odd parity as the first arg
(define (same-parity first-arg . remaining-args)
  (let ((first-parity (parity? first-arg)))
    (define (same-parity-iter resultlist worklist)
      (cond ((null? worklist)
             resultlist)
            ((= first-parity (parity? (car worklist)))
             (same-parity-iter (append resultlist (list (car worklist)))
                               (cdr worklist)))
            (else
             (same-parity-iter resultlist (cdr worklist)))))
    (same-parity-iter '() remaining-args)))