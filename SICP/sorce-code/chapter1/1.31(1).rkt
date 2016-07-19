#lang planet neil/sicp

(define (product term a next b)
  (if (> a b)
      1
      (* (term a)
         (product term (next a) next b))))

(define (pi n)
  (define (next n) (+ 2 n))
  
  (define (even-term a) (/ a (- a 1)))
  (define (odd-term a) (/ a (+ a 1)))
  (- (* 4
        (product odd-term 2 next n)
        (product even-term 4 next n))
     0.0000000000001))