#lang planet neil/sicp

; Exercise 3.8

(define (f x)
  (define count 0)
  (let ((original count))
    (begin (set! count (+ count x))
           original)))