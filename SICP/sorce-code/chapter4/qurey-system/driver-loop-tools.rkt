;#lang planet neil/sicp

; input & output  handler

(define (query-syntax-process exp)
   (map-over-symbols expand-question-mark exp))
(define (map-over-symbols proc exp)
   (cond ((pair? exp)
          (cons (map-over-symbols proc (car exp))
                (map-over-symbols proc (cdr exp))))
         ((symbol? exp) (proc exp))
         (else exp)))
 (define (expand-question-mark symbol)
   (let ((chars (symbol->string symbol)))
     (if (string=? (substring chars 0 1) "?")
         (list '?
               (string->symbol
                (substring chars 1 (string-length chars))))
         symbol)))

(define (contract-question-mark variable)
   (string->symbol
    (string-append "?" 
      (if (number? (cadr variable))
          (string-append (symbol->string (caddr variable))
                         "-"
                         (number->string (cadr variable)))
          (symbol->string (cadr variable))))))