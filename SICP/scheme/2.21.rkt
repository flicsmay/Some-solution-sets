#lang planet neil/sicp

; Exercise 2.21

(define (square x) (* x x))

; square-list1 : s_list
; squares every items in the given list
(define (square-list1 items)
  (if (null? items)
      nil
      (cons (square (car items))
            (square-list1 (cdr items)))))

; square-list2 : s_list
; squares every items in the given list
(define (square-list2 items)
  (map square items))