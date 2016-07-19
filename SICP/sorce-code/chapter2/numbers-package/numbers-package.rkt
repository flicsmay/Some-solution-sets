;#lang planet neil/sicp

;(define numbers-path "c:\\Users\\admin\\scheme\\numbers-package\\")

(define (install-numbers)
  (load (string-append numbers-path "get-put-package.rkt"))
  (load (string-append numbers-path "apply-generic-package.rkt"))
  (load (string-append numbers-path "global-procedure.rkt"))
  (load (string-append numbers-path "rectangular-package.rkt"))
  (load (string-append numbers-path "polar-package.rkt"))
  (load (string-append numbers-path "scheme-number-package.rkt"))
  (load (string-append numbers-path "rational-package.rkt"))
  (load (string-append numbers-path "real-package.rkt"))
  (load (string-append numbers-path "complex-package.rkt"))
  (load (string-append numbers-path "install-numbers-package.rkt"))
  ;(install-numbers-package)
  'done)