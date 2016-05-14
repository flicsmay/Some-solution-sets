#lang planet neil/sicp

(define (search f neg-point pos-point)
  (let ((midpoint (average neg-point pos-point)))
    (if (close-enough? neg-point pos-point)
        midpoint
        (let ((test-value (f midpoint)))
          (cond ((positive? test-value)
                 (search f neg-point midpoint))
                ((negative? test-value)
                 (search f midpoint pos-point))
                (else midpoint))))))

(define (average a b) (/ (+ a b)
                         2))

(define (close-enough? x y)
  (< (abs (- x y)) 0.001))

(define (half-interval-method f a b)
  (let ((a-value (f a))
        (b-value (f b)))
    (cond ((and (negative? a-value) (positive? b-value))
           (search f a b))
          ((and (negative? b-value) (positive? a-value))
           (search f b a))
          (else
           (error "Value are not of opposite sign" a b)))))

; finding fixed points of functions

(define tolerance 0.00001)

(define (fixed-point f frist-guess)
  
  (define (close-enough? v1 v2)
    (< (abs (- v1 v2)) tolerance))
  
  (define (try guess count)
    (let ((next (f guess)))
      (display count)(display " -> ")
      (display guess)
      (newline)
      (if (close-enough? guess next)
          next
          (try next (+ 1 count)))))
  
  (try frist-guess 0))

(define (f x) (/ (log 1000) (log x)))
(define (f-d x) (average x
                         (f x)))









