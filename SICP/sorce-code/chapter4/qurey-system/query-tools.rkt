;#lang planet neil/sicp

; tools for many operations seletor and operator included

(define (tagged-list? exp tag)
  (if (pair? exp)
      (eq? (car exp) tag)
      false))

(define (always-true ignore frame-stream) frame-stream)

(define (indexable? pat)
  (or (constant-symbol? (car pat))
      (var? (car pat))))

(define (index-key-of pat)
  (let ((key (car pat)))
    (if (var? key) '? key)))

(define (use-index? pat)
  (constant-symbol? (car pat)))

(define (type exp)
   (if (pair? exp)
       (car exp)
       (error "Unknown expression TYPE" exp)))

 (define (contents exp)
   (if (pair? exp)
       (cdr exp)
       (error "Unknown expression CONTENTS" exp)))

(define (assertion-to-be-added? exp)
   (eq? (type exp) 'assert!))

 (define (add-assertion-body exp)
   (car (contents exp)))

(define (empty-conjunction? exps) (null? exps))
(define (first-conjunct exps) (car exps))
(define (rest-conjuncts exps) (cdr exps))
(define (empty-disjunction? exps) (null? exps))
(define (first-disjunct exps) (car exps))
(define (rest-disjuncts exps) (cdr exps))
(define (negated-query exps) (car exps))
(define (predicate exps) (car exps))
(define (args exps) (cdr exps))

(define (rule? statement)
  (tagged-list? statement 'rule))
(define (conclusion rule) (cadr rule))
(define (rule-body rule)
  (if (null? (cddr rule))
      '(always-true)
      (caddr rule)))

(define (var? exp)
  (tagged-list? exp '?))
(define (constant-symbol? exp) (symbol? exp))


; rule counter

(define rule-counter 0)
(define (new-rule-application-id)
  (set! rule-counter (+ 1 rule-counter))
  rule-counter)
(define (make-new-variable var rule-application-id)
  (cons '? (cons rule-application-id (cdr var))))

; binding

(define (make-binding variable value)
  (cons variable value))
 (define (binding-variable binding)
   (car binding))
(define (binding-value binding)
  (cdr binding))
(define (binding-in-frame variable frame)
  (assoc variable frame))
(define (extend variable value frame)
  (cons (make-binding variable value) frame))