#lang planet neil/sicp

(define (expmod base exp m)
  (define (square x) (* x x))
  
  (cond ((= exp 0) 1)
        ((even? exp)
         (remainder (square (expmod base (/ exp 2) m))
                    m))
        (else
         (remainder (* base (expmod base (- exp 1) m))
                    m))))

(define (congruent? a n)
  (= (expmod a n n) a))

(define (fermat-test-all n)
  
  (define (inner-loop index)
    (if (< index n)
        (if (congruent? index n)
            (inner-loop (+ 1 index))
            false)
        true))
  
  (inner-loop 2))


           