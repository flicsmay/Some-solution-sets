;#lang planet neil/sicp

; delay & force

(define (delay exp)
  (lambda () exp))

(define (force delayed-object)
   (delayed-object))

(define (cons-stream a b)
  (cons a (delay b)))

(define (stream-car stream) (car stream))

(define (stream-cdr stream) (force (cdr stream)))
