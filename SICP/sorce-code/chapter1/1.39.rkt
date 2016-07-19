#lang planet neil/sicp

(define (cont-frac f-d f-n n)
  
  (define (inner-loop index result)
    (if (< index 1)
        result
        (inner-loop (- index 1) (/ (f-n index)
                                   (+ (f-d index)
                                      result)))))
  (+ (inner-loop n 0)
     0.1
     -0.1))

(define (tan-cf x k)
  (define (n index)
    (if (= index 1)
        x
        (* x x)))
  
  (define (d index)
    (- (* index 2) 1))
  
  (cont-frac d n k))