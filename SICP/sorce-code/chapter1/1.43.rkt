#lang planet neil/sicp

(define (compose f g)
  (lambda (x)
    (f (g x))))

(define (square x) (* x x))

(define (inc x) (+ 1 x))

(define (repeated f n)
  (define (inner-loop index result)
    (if (<= index 1)
        result
        (inner-loop (- index 1)
                    (compose f result))))
  (inner-loop n f))

; repeated function n times