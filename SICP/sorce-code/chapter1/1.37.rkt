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

(define (f x) 1)


(define (cont-frac-recur n f k)

  (define (inner-loop index)
    (if (> index k)
        1
        (/ (n index)
           (+ (n index)
              (inner-loop (+ index 1))))))
  (inner-loop 1))

