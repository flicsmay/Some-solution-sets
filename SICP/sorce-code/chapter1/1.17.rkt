#lang racket

(define (multipy a b)
  (define (double n) (* 2 n))
  (define (halve n) (/ n 2))
  (define (even? n) (= (remainder n 2) 0))
  
  (cond ((= b 1) a)
        ((even? b) (multipy (double a) (halve b)))
        (else (+ a
                 (multipy a (- b 1))))))