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

(define (d i)
  (if (= 0 (remainder (+ i 1) 3))
      (* 2 (/ (+ i 1) 3))
      1))

(define (n i) 1)

(define (e k)
  (+ (cont-frac d n k)
     2))