#lang planet neil/sicp

; Exercise 2.28

; fringe : s_tree
; Convert the whole tree to a list whose elements are 
; the node of the given tree
(define (fringe tree)
  (cond ((null? tree)
         nil)
        ((not (pair? tree))
         tree)
        (else
         (append (car tree)
                 (cdr tree)))))

(define tree (list (list 1 2) (list 3 4)))