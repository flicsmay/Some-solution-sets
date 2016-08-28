#lang planet neil/sicp

; amb-eval 

(define amb-eval-path "C:\\Users\\李烽源\\Desktop\\编程\\scheme\\amb-eval\\")

(define (install-amb-eval)
  (load (string-append amb-eval-path "tools.rkt"))
  (load (string-append amb-eval-path "cases-tools.rkt"))
  (load (string-append amb-eval-path "environment-pro.rkt"))
  (load (string-append amb-eval-path "primitive-procedure.rkt"))
  (load (string-append amb-eval-path "cases.rkt"))
  (load (string-append amb-eval-path "eval-analyze.rkt"))
  (load (string-append amb-eval-path "driver-loop.rkt"))
  'done)

;(install-amb-eval)(define the-global-environment (setup-environment))(driver-loop)
