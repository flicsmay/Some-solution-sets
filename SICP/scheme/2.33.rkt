#lang planet neil/sicp

; Exercise 2.33

(define (map p sequence)
  (accumulate (lambda (x y) (cons (p x) y))
              nil
              sequence))

(define (append seq1 seq2)
  (accumulate cons seq2 seq1))

(define (length sequence)
  (accumulate (lambda (x y) (+ 1 y))
              0
              sequence))

; Section 2.2.3


; filter : #procedure, s_list/s_tree
; go through the every elements of the given tree/list with #pro
; eliminates all elements but those whose predication are TRUE
(define (filter predicate sequence)
  (cond ((null? sequence) nil)
        ((predicate (car sequence))
         (cons (car sequence)
               (filter predicate (cdr sequence))))
        (else
         (filter predicate (cdr sequence)))))

; accumulate : #operation, initial, s_list/s_tree
; #oper to every elements in the structure together with an initial value
(define (accumulate op initial sequence)
  (if (null? sequence)
      initial
      (op (car sequence)
          (accumulate op initial (cdr sequence)))))

; enumerate-interval : int_low, int_high
; go through the integer list from low to high
(define (enumerate-interval low high)
  (if (> low high)
      nil
      (cons low (enumerate-interval (+ low 1) high))))

; enumerate-tree : s_tree
; go through a given tree and return a list of tree's elements
(define (enumerate-tree tree)
  (cond ((null? tree) nil)
        ((not (pair? tree)) (list tree))
        (else
         (append (enumerate-tree (car tree))
                 (enumerate-tree (cdr tree))))))