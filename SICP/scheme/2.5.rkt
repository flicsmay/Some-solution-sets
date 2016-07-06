#lang planet neil/sicp

(define (cons a b)
  (let ((left (fast-expt 2 a))
        (right (fast-expt 3 b))
        )
    (lambda (m) (m left right))))

; constructor

(define (car z)
  (z (lambda (p q) p)))

(define (cdr z)
  (z (lambda (p q) q)))

; selector

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