#lang planet neil/sicp

; Exercise 2.40

; unique-pairs : int_n
; generates the sequence of pair (i, j) with 1 <= j < i <= n
(define (unique-pairs n)
  (flatmap (lambda (i)
             (map (lambda (j) (list i j))
                  (enumerate-interval 1 (- i 1))))
           (enumerate-interval 1 n)))

; prime-sum-pairs-modify : int_n
; return a list of pairs whose sum are prime
(define (prime-sum-pairs n)
  (map make-pair-sum
       (filter prime-sum? (unique-pairs n))))

; flatmap : #proc, s_list
; append results which are the map of seq together
(define (flatmap proc seq)
  (accumulate append nil (map proc seq)))

; prime-sum? : s_pair
; return TRUE if the sum of the given pair is prime
(define (prime-sum? pair)
  (prime? (+ (car pair) (cadr pair))))

; make-pair-sum : pair
; make (pair, sum-of-pair)
(define (make-pair-sum pair)
  (list (car pair) (cadr pair) (+ (car pair) (cadr pair))))

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

(define (smallest-divisor n)
  (define (find-divisor n test-divisor)
    (cond ((> (square test-divisor) n) n)
          ((divides? test-divisor n) test-divisor)
          (else (find-divisor n (+ test-divisor 1)))))
  (define (square n) (* n n))
  (define (divides? a b)
    (= (remainder b a) 0))
  
  (find-divisor n 2))

(define (prime? n)
  (= n (smallest-divisor n)))
