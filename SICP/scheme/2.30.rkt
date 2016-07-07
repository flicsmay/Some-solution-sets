#lang planet neil/sicp

; Exercise 2.30

; square : int
(define (square x) (* x x))

; square-tree : s_tree
; return a tree whose nodes' value are squares of given tree
(define (square-tree tree)
  (cond ((null? tree)
         nil)
        ((not (pair? tree))
         (square tree))
        (else
         (cons (square-tree (car tree))
              (square-tree (cdr tree))))))