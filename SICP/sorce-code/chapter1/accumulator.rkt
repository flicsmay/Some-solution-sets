#lang planet neil/sicp

; Exercise 2.36

; accumulate-n : #operation, initial, sequence[s]
; calculate the accumulate of the given sequence[s] respectively
(define (accumulate-n op init seqs)
  (if (null? (car seqs))
      nil
      (cons (accumulate op init 
                        (map (lambda (x) (car x)) seqs))
            (accumulate-n op init
                          (map (lambda (x) (cdr x)) seqs)))))
                                                                             

; accumulate : #operation, initial, s_list/s_tree
; #oper to every elements in the structure together with an initial value
(define (accumulate op initial sequence)
  (if (null? sequence)
      initial
      (op (car sequence)
          (accumulate op initial (cdr sequence)))))
