#lang planet neil/sicp

; Exercise 2.39

; reverse-fr : s_list
; reverse a given list, implememted with fold-right
(define (reverse-fr sequence)
  (fold-right (lambda (x y) (append y (list x)))
              ; convert x to a node then itcan be linked to main chain
              nil
              sequence))

; reverse-fl : s_list
; reverse a given list, implemented with fold-left
(define (reverse-fl sequence)
  (fold-left (lambda (x y) (cons y x))
             nil
             sequence))


; ===================================================

; fold-left : #op, initial, s_list
; combining the given elements from left to right
(define (fold-left op initial sequence)
  (define (iter result rest)
    (if (null? rest)
        result
        (iter (op result (car rest))
              (cdr rest))))
  (iter initial sequence))



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

; fold-right : accumulate
(define fold-right accumulate)