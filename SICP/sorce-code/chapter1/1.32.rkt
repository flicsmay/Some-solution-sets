#lang planet neil/sicp

(define (accumulate combiner null-value term a next b)
  (define (inner-loop index result)
    (if (> index b)
        result
        (inner-loop (next index) (combiner (term index)
                                           result))))
  (inner-loop a null-value))

(define (sum term a next b)
  (accumulate + 0 term a next b))

(define (product term a next b)
  (accumulate * 1 term a next b))