#lang planet neil/sicp

; Exercise 3.1

(define (make-accumulator total)
  (lambda (num)
    (begin (set! total (+ total num))
           total)))