#lang racket

(define (cube-root x)
  
  (define (cube-root-guess guess)
    (if (good-enough? guess)
        guess
        (cube-root-guess (better-guess guess))))
  
  (define (good-enough? guess)
    (> 0.01 (abs (- x (cube guess)))))
  (define (cube x) (* x x x))
  
  (define (better-guess guess)
    (/ (+ (/ x (* guess guess))
          (+ guess guess))
       3))
  
  (cube-root-guess 1.0))