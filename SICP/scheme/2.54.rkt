#lang planet neil/sicp

; equal? : symbols_a, symbols_b
; return TRUE if a and b are completely equal, FALSE otherwise
(define (equal? a b)
  (cond ((and (null? a) (null? b))
         #t)
        ((or (null? a) (null? b))
         #f)
        ((not (eq? (car a) (car b)))
         #f)
        (else
         (equal? (cdr a) (cdr b)))))