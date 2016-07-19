#lang planet neil/sicp

(define (filtered-accumulate combiner null-value filter
                             term a next b)
  (define (inner-loop index result)
    (if (> index b)
        result
        (inner-loop (next index) (if (filter index)
                                     (combiner (term index)
                                               result)
                                     result))))
  (inner-loop a null-value))

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

(define (square-sum a b) (+ (* a a) b))

(define (primes-square-sum a b)
  (filtered-accumulate square-sum
                       0
                       prime?
                       (lambda (x) x)
                       a
                       (lambda (x) (+ x 1))
                       b))