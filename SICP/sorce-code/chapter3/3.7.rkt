#lang planet neil/sicp

; Exercise 3.3

(define (make-account balance password)
  (define (withdraw amount)
    (if (>= balance amount)
        (begin (set! balance (- balance amount))
               balance)
        "Insufficient funds"))
  (define (deposit amount)
    (set! balance (+ balance amount))
    balance)
  (define (make-joint pwd)
    (set! password (append (if (pair? password)
                               password
                               (list password))
                           (list pwd))))
  (define (right-pwd? pwd rest)
    (cond ((null? rest)
           #f)
          ((not (pair? rest))
           (eq? rest pwd))
          ((eq? (car rest) pwd)
           #t)
          (else
           (right-pwd? pwd (cdr rest)))))
          
  (define (dispatch pwd m)
    (if (right-pwd? pwd password)
        (cond ((eq? m 'withdraw) withdraw)
              ((eq? m 'deposit) deposit)
              ((eq? m 'make-joint) make-joint)
              (else (error "Unknown request -- MAKE-ACCOUNT"
                           m)))
        (lambda (x) "Incorrect password")))
  dispatch)


(define (make-joint acc password new-pwd)
  (begin ((acc password 'make-joint) new-pwd)
         acc))