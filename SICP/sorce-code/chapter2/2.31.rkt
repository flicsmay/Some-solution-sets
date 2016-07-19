#lang planet neil/sicp

; Exercise 2.31

; tree-map : #procedure, s_tree
; applies #proc to every nodes in the given tree
(define (tree-map f tree)
  (cond ((null? tree)
         nil)
        ((not (pair? tree))
         (f tree))
        (else
         (cons (tree-map f (car tree))
               (tree-map f (cdr tree))))))

; square-tree : s_tree
(define (square-tree tree) (tree-map square tree))


; square : int
(define (square x) (* x x))