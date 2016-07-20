#lang planet neil/sicp

; Exercise 3.4

(define (make-account balance password)
  (define incorrect-count 0)
  (define (withdraw amount)
    (if (>= balance amount)
        (begin (set! balance (- balance amount))
               balance)
        "Insufficient funds"))
  (define (deposit amount)
    (set! balance (+ balance amount))
    balance)
  (define (call-the-cops) "calling the cops")
  (define (dispatch pwd m)
    (if (eq? pwd password)
        (begin (set! incorrect-count 0)
               (cond ((eq? m 'withdraw) withdraw)
                     ((eq? m 'deposit) deposit)
                     (else (error "Unknown request -- MAKE-ACCOUNT"
                                  m))))
        (lambda (x) (begin (set! incorrect-count (+ incorrect-count 1))
                           (if (> incorrect-count 6)
                               (call-the-cops)
                               "Incorrect password")))))
  dispatch)