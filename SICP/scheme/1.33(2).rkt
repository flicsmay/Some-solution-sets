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


(define (gcd a b)
  (if (= b 0)
      a
      (gcd b (remainder a b))))

(define (relative-prime? a b)
  (= 1 (gcd a b)))

(define (product-relative-prime n)
  (filtered-accumulate *
                       1
                       (lambda (a) (relative-prime? a n))
                       (lambda (x) x)
                       1
                       (lambda (x) (+ 1 x))
                       n))