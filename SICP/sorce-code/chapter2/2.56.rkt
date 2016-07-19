#lang planet neil/sicp

; deriv : expression, variable
; make the procedure d(expression)/d(variable)
(define (deriv exp var)
  (cond ((number? exp) 0)
        ((variable? exp)
         (if (same-variable? exp var) 1 0))
        ((sum? exp)
         (make-sum (deriv (addend exp) var)
                   (deriv (augend exp) var)))
        ((product? exp)
         (make-sum
           (make-product (multiplier exp)
                         (deriv (multiplicand exp) var))
           (make-product (deriv (multiplier exp) var)
                         (multiplicand exp))))
        ((exponentiation? exp)
         (let ((ex (exponent exp))
               (bs (base exp)))
           (make-product (make-product ex
                                       (make-exponentiation bs (- ex 1)))
                         ; n * u ^(n-1)
                         (deriv bs var))))
                         
        (else
         (error "unknown expression type -- DERIV" exp))))

; exponentiation? : expression
; return TRUE if the given expression IS a exponentiation
(define (exponentiation? exp)
  (and (pair? exp)
       (eq? (car exp) '^)))

; make-exponentiation : base, exponent
; compose an exponentiation with base and exponent
(define (make-exponentiation base exponent)
  (cond ((= exponent 0)
         1)
        ((= exponent 1)
         base)
        (else
         (list '^ base exponent))))

; exponent : expression
; return exponent part of the expression
(define (exponent exp)
  (caddr exp))

; base : expression
; return base part of the expression
(define (base exp)
  (cadr exp))

(define (variable? x) (symbol? x))

(define (same-variable? v1 v2)
  (and (variable? v1) (variable? v2) (eq? v1 v2)))

(define (sum? x)
  (and (pair? x) (eq? (car x) '+)))

(define (addend s) (cadr s))

(define (augend s) (caddr s))

(define (product? x)
  (and (pair? x) (eq? (car x) '*)))

(define (multiplier p) (cadr p))

(define (multiplicand p) (caddr p))

(define (make-sum a1 a2)
  (cond ((=number? a1 0) a2)
        ((=number? a2 0) a1)
        ((and (number? a1) (number? a2)) (+ a1 a2))
        (else (list '+ a1 a2))))

(define (=number? exp num)
  (and (number? exp) (= exp num)))

(define (make-product m1 m2)
  (cond ((or (=number? m1 0) (=number? m2 0)) 0)
        ((=number? m1 1) m2)
        ((=number? m2 1) m1)
        ((and (number? m1) (number? m2)) (* m1 m2))
        (else (list '* m1 m2))))