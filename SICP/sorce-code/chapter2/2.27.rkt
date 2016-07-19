#lang planet neil/sicp


; deep-reverse : s_tree
; reverse sub-trees of each node in the given tree
(define (deep-reverse tree)
  (cond ((null? tree)
         nil)
        ((not (pair? tree))
         tree)
        (else
         (reverse (list (deep-reverse (car tree))
                        (deep-reverse (cadr tree)))))))

(define tree (list (list 1 2) (list 3 4)))