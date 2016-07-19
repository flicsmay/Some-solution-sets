#lang planet neil/sicp

; Exercise 2.41

; triples-sets : int_n
; generate a list of unique sets with three elements 
; all the elements include must be less than n
(define (triples-sets n)
  (flatmap (lambda (i)
             (map (lambda (j)
                    (cons i j))
                  (unique-pairs (- i 1))))
           (enumerate-interval 1 n)))

; sum-of-triples : s_set
; return the sum of the given set
(define (sum-of-triples triple)
  (+ (car triple) (cadr triple) (caddr triple)))

; triples-sum : int_n, int_s
; given an integer n and an integer s return all ordered sequences (i,j,k)
; that less than n and sums equal to s
(define (triples-sum n s)
  (filter (lambda (pairs) (= s
                             (sum-of-triples pairs)))
          (triples-sets n)))

; unique-pairs : int_n
; generates the sequence of pair (i, j) with 1 <= j < i <= n
(define (unique-pairs n)
  (flatmap (lambda (i)
             (map (lambda (j) (list i j))
                  (enumerate-interval 1 (- i 1))))
           (enumerate-interval 1 n)))


; flatmap : #proc, s_list
; append results which are the map of seq together
(define (flatmap proc seq)
  (accumulate append nil (map proc seq)))

; permutatoins : s_set(list)
; generate all the permutations of the given set
(define (permutations s)
  (if (null? s)
      (list nil)
      (flatmap (lambda (x)
                 (map (lambda (p) (cons x p))
                      (permutations (remove x s))))
               s)))

; remove : item, s_list
; remove the specfic item from the given list
(define (remove item sequence)
  (filter (lambda (x) (not (= x item)))
          sequence))


; =================================================================

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

