#lang planet neil/sicp

(define (smallest-divisor n)
  (define (next-odd n)
  (if (= n 2)
      3
      (+ n 2)))
  
  (define (find-divisor n test-divisor)
    (cond ((> (square test-divisor) n) n)
          ((divides? test-divisor n) test-divisor)
          (else (find-divisor n (next-odd test-divisor)))))
  (define (square n) (* n n))
  (define (divides? a b)
    (= (remainder b a) 0))
  
  (find-divisor n))

(define (prime? n)
  (= n (smallest-divisor n)))


(define (find-continue-primes n count)
  (cond ((= count 0) (display "are primes.\n"))
        ((prime? n) (display n)
                    (newline)
                    (find-continue-primes (+ n 1) (- count 1)))
        (else (find-continue-primes (+ n 1) count))))

(define (counting-run-time n count)
  (let ((start-time (runtime)))
    (find-continue-primes n count)
    (newline)
    (display (- (runtime) start-time))))