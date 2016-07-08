#lang planet neil/sicp

; Exercise 2.32

; subsets : s_list
; return a list of subsets of the given list
(define (subsets s)
  (if (null? s)
      (list nil)
      (let ((rest (subsets (cdr s))))
        (append rest (map (lambda (x)
                            (cons (car s) x))
                          rest)))))