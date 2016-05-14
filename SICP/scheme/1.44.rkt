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

(define dx 0.0001)

(define (smooth f)
  (lambda (x) (/ (+ (f (- x dx))
                    (f x)
                    (f (+ x dx)))
                 3)))

(define (smooth-n-times f n)
  ((repeated smooth n) f))