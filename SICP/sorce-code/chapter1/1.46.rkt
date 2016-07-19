#lang planet neil/sicp

(define (iterative-improve good-enough? improve-guess)
  (lambda (guess)
    
    (define (inner-loop guess)
      (if (good-enough? guess)
          guess
          (inner-loop (improve-guess guess))))
    
    (inner-loop guess)))

; iterative improve

(define (sqrt-iter guess x)
  
  (define (good-enough? guess)
    (< (abs (- (* guess guess) x)) 0.001))
  
  (define (improve guess)
    (/ (+ guess
          (/ x guess))
       2))
  
  ((iterative-improve good-enough? improve) guess))

(define (sqrt x)
  (sqrt-iter 1.0 x))

; sqrt

(define (fixed-point f first-guess)
  
  (define tolerance 0.00001)
  
  (define (close-enough? guess)
    (let ((compares (f guess)))
      (< (abs (- guess compares)) tolerance)))
  
  (define (try guess)
    (f guess))
  
  ((iterative-improve close-enough? try) first-guess))