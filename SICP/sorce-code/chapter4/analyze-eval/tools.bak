;#lang planet neil/sicp

; tools

(define (list-of-values exps env)
  (if (no-operands? exps)
      '()
      (cons (evaln (first-operand exps) env)
            (list-of-values (rest-operands exps) env))))

(define (evaln-sequence exps env)
  (cond ((last-exp? exps) (evaln (first-exp exps) env))
        (else (evaln (first-exp exps) env)
              (evaln-sequence (rest-exps exps) env))))

(define (tagged-list? exp tag)
  (if (pair? exp)
      (eq? (car exp) tag)
      false))

; ***************** procedure *********************

(define (make-procedure parameters body env)
  (list 'procedure parameters body env))
(define (compound-procedure? p)
  (tagged-list? p 'procedure))
(define (procedure-parameters p) (cadr p))
(define (procedure-body p) (caddr p))
(define (procedure-environment p) (cadddr p))

(define (last-exp? seq) (null? (cdr seq)))
(define (first-exp seq) (car seq))
(define (rest-exps seq) (cdr seq))

(define (sequence->exp seq)
  (cond ((null? seq) seq)
        ((last-exp? seq) (first-exp seq))
        (else (make-begin seq))))

; ***************** operator *********************

(define (operator exp) (car exp))
(define (operands exp) (cdr exp))
(define (no-operands? ops) (null? ops))
(define (first-operand ops) (car ops))
(define (rest-operands ops) (cdr ops))

(define (true? x)
  (not (eq? x false)))
(define (false? x)
  (eq? x false))