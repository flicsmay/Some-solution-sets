#lang planet neil/sicp

(define register-machine-path "C:\\Users\\李烽源\\Desktop\\编程\\scheme\\register-machine\\")

(define (install-register-machine)
  (load (string-append register-machine-path "make-machine.rkt"))
  'done)

;  (install-register-machine)