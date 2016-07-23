#lang planet neil/sicp

(define wire-path "c:\\users\\admin\\scheme\\chapter3\\")


(define (install-wire-ops)
  (load (string-append wire-path "queue-ops.rkt"))
  (load (string-append wire-path "make-agenda.rkt"))
  (load (string-append wire-path "make-wire.rkt"))
  (load (string-append wire-path "half-full-adder.rkt"))
  'done)