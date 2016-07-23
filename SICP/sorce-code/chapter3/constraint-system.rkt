#lang planet neil/sicp

; constraint system

(define constraint-system-path "c:\\users\\admin\\scheme\\chapter3\\")

(define (install-constraint-system)
  (load (string-append constraint-system-path "connect.rkt"))
  (load (string-append constraint-system-path "constraint.rkt"))
  'done)