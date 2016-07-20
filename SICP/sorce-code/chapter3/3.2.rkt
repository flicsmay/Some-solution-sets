#lang planet neil/sicp

; Exercise 3.2

(define (make-monitored func)
  (define count 0)
  (define (how-many-calls?)
    count)
  (define (reset-count)
    (set! count 0))
  (define (dispatch x)
    (cond ((eq? x 'how-many-calls?)
           (how-many-calls?))
          ((eq? x 'reset-count)
           (reset-count))
          (else
           (begin (set! count (+ 1 count))
                  (func x)))))
  dispatch)
           