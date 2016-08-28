#lang planet neil/sicp

; analyze-eval 

(define analyze-eval-path
  "your-path")

(define (install-analyze-eval)
  (load (string-append analyze-eval-path "tools.rkt"))
  (load (string-append analyze-eval-path "cases-tools.rkt"))
  (load (string-append analyze-eval-path "environment-pro.rkt"))
  (load (string-append analyze-eval-path "primitive-procedure.rkt"))
  (load (string-append analyze-eval-path "cases.rkt"))
  (load (string-append analyze-eval-path "eval-analyze.rkt"))
  'done)

;(install-analyze-eval)(define the-global-environment (setup-environment))(driver-loop)
