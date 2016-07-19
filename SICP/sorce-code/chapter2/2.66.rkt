#lang planet neil/sicp

; Exercise 2.66

; lookup : given-key, binary-tree
; given a key and search for the value in a binary tree
(define (lookup given-key btree)
  (cond ((null? btree)
         #f)
        ((= given-key (key (car btree)))
         (entry btree))
        ((> given-key (key (car btree)))
         (lookup given-key (right-branch btree)))
        (else
         (lookup given-key (left-branch btree)))))