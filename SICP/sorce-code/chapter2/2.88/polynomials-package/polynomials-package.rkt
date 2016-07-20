#lang planet neil/sicp

; polynomial-package
(define polynomials-path "c:\\users\\admin\\scheme\\polynomials-package\\")
(define numbers-path "c:\\Users\\admin\\scheme\\numbers-package\\")

(define (install-polynomials) ; curr-path "" if this pro is main
  (load (string-append numbers-path "numbers-package.rkt"))
  (load (string-append polynomials-path "global-procedure.rkt"))
  (load (string-append polynomials-path "install-polynomials-package.rkt"))
  'done)

  