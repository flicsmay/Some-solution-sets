#lang planet neil/sicp

(define (fast-expt b n)
  (define (square x) (* x x))
  
  (define (inner-loop base index result)
    (cond ((= index 0) result)
          ((even? index) (inner-loop (square base)
                                     (/ index 2)
                                     result))
          (else (inner-loop base
                            (- index 1)
                            (* result base)))))
  
  (define (even? n)
    (= (remainder n 2) 0))
  
  (if (< n 1)
      1
      (inner-loop b n 1)))
   
; fast-expt iteration

(define (average x y) (/ (+ x y) 2))

(define (average-damp f)
  (lambda (x) (average x (f x))))

; average damp

(define (fixed-point f frist-guess)
  
  (define tolerance 0.00001)
  
  (define (close-enough? v1 v2)
    (< (abs (- v1 v2)) tolerance))
  
  (define (try guess)
    (let ((next (f guess)))
      (if (close-enough? guess next)
          next
          (try next))))
  (try frist-guess))

; fixed point func

(define (compose f g)
  (lambda (x)
    (f (g x))))

(define (repeated f n)
  (define (inner-loop index result)
    (if (<= index 1)
        result
        (inner-loop (- index 1)
                    (compose f result))))
  (inner-loop n f))

; repeated function

(define (n-roots-f x n)
  (lambda (y) (/ x (fast-expt y (- n 1)))))

; n roots

(define (n-times-deboost n)
  (repeated average-damp n))

; n times deboost

(define (xs-n-roots-with-k-damp x n k)
  (fixed-point ((n-times-deboost k) (lambda (y) (/ x (fast-expt y (- n 1)))))
               1.0))

; x's n roots using k deboots

(define (lg n)
  (/ (log n) (log 2)))

; lg n

(define (x-n-roots x n)
  (xs-n-roots-with-k-damp x n (lg n)))