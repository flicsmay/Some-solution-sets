#lang planet neil/sicp

(define (product term a next b)
  (define (inner-loop index result)
    (if (> index b)
        result
        (inner-loop (next index) (* (term index)
                                    result))))
  (inner-loop a 1))

(define (pi n)
  (define (next n) (+ 2 n))
  
  (define (even-term a) (/ a (- a 1)))
  (define (odd-term a) (/ a (+ a 1)))
  (- (* 4
        (product odd-term 2 next n)
        (product even-term 4 next n))
     0.1
     -0.1))