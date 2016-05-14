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