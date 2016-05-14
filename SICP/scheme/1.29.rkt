#lang planet neil/sicp

 (define (simpson-rule f a b n)
  
  (let ((h (/ (- b a) n)))
    (define (accrute-enough? x) (>= x n))
    
    (define (even-inner-loop index sum)
      (if (accrute-enough? index)
          sum
          (even-inner-loop (+ 2 index) (+ sum
                                          (* 2 (f (+ a (* index h))))))))
    
    (define (odd-inner-loop index sum)
      (if (accrute-enough? index)
          sum
          (odd-inner-loop (+ 2 index) (+ sum
                                         (* 4 (f (+ a (* index h))))))))
    
    (if (even? n)
        (* (+ (f a)
              (odd-inner-loop 1 0)
              (even-inner-loop 2 0)
              (f (+ a (* n h)))
              )
           (/ h 3))
        (display "n must be even"))))
        

(define (cube x) (* x x x))