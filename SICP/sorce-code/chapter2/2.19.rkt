#lang planet neil/sicp

; Exercise 2.19
; change-counting problem 

(define us-coins (list 50 25 10 5 1))
(define uk-coins (list 100 50 20 10 5 2 1 0.5))


; cc : int, s_list
; how many different coins can be changed with the amount of money
; coins-values : store the values of different coins 
(define (cc amount coin-values)
  (cond ((= amount 0) 1)
        ((or (< amount 0) (no-more? coin-values)) 0)
        (else
         (+ (cc amount (except-first-denomination coin-values))
            (cc (- amount (frist-denomination coin-values))
                coin-values)))))

; first-denomination : s_list
; return the first values in the list : s_list
; also can be implemented with the procedure : list-ref (value 0)
(define (frist-denomination currency)
  (car currency))

; except-first-denomination : s_list
; return the given list without the first node
(define (except-first-denomination currency)
  (cdr currency))

; no-more? : s_list
; return TRUE if there are NO values in the list
(define (no-more? givenlist)
  (null? givenlist))