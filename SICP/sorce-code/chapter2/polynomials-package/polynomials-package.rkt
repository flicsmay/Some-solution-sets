#lang planet neil/sicp

(define curr-path "")

; polynomianal-package
(define outer-path "..\\")
(define numbers-path
  (string-append curr-path-poly outer-path "numbers-package\\"))

(define (install-polynomianals) ; curr-path "" if this pro is main
  (load (string-append curr-path numbers-path "numbers-package.rkt"))
  (load (string-append curr-path "global-procedure.rkt"))
  (load (string-append curr-path "install-polynomials-package.rkt"))
  'done)

  