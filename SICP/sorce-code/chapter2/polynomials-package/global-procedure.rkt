;#lang planet neil/sicp

; global procedure

(define (make-polynomial var terms)
  ((get 'make 'polynomial) var terms))