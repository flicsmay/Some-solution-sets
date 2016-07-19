#lang racket

(define (multi-iter a b)
  (define (double n) (+ n n))
  (define (halve n) (/ n 2))
  (define (even? n) (= (remainder n 2) 0))
  
  (define (inner-loop a b result)
    (cond ((= b 0) result)
          ((even? b) (inner-loop (double a)
                                 (halve b)
                                 result))
          (else (inner-loop a
                            (- b 1)
                            (+ a result)))))
  (inner-loop a b 0))