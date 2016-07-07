#lang planet neil/sicp

; Exercise 2.23

; for-each-my-v : procedure, s_list
; applies the procedure to each items in the given list
(define (for-each-my-v f items)
  (define (for-each-iter lst)
    (cond ((not (null? lst))
            (f (car lst))
            (for-each-iter (cdr lst)))))
  (for-each-iter items))