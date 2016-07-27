##Exercise 4.1 - 4.10

###4.1
using let to eval the 'left or 'right value before the 'cons operation.

	; from left to right
	(define (list-of-values exps env)
	    (if (not-operands? exps)
	        '()
	        (let ((first-value (eval (first-operand exps) env)))
	            (cons first-value
	                  (list-of-values (rest-operands exps) env)))))
	; from right to left
	(define (list-of-values exps env)
	    (if (no-operands? exps)
	        '()
	        (let ((rest-values (list-of-values (rest-operands exps) env)))
	            (cons (eval (first-operand exps) env)
	                  rest-values))))
###4.2
The 'define will be regraded as a 'application, and it would always fail to define anything.   
modify procedure below.

	(define (application? exp) (tagged-list? exp 'call)) 
	(define (operator exp) (cadr exp)) 
	(define (operands exp) (cddr exp)) 
###4.3
	(define (eval exp env) 
	  (cond ((self-evaluating? exp) exp) 
	        ((variable? exp) 
	         (lookup-variable-value exp env)) 
	        ((get 'op (car exp)) 
	         (apply (get 'op (car exp) exp env))) 
	        ((application? exp) (apply (eval (operator exp) env)
	                                    (list-of-values (operands exp) env))) 
	        (else  
	         (error "Unkown expression type -- EVAL" exp)))) 
	(put 'op 'quote text-of-quotation) 
	(put 'op 'set! eval-assignment) 
	(put 'op 'define eval-definition) 
	(put 'op 'if eval-if) 
	(put 'op 'lambda 
	     (lambda (x y) (make-procedure (lambda-parameters x) (lambda-body x) y))) 
	(put 'op 'begin 
	     (lambda (x y) (eval-sequence (begin-sequence x) y))) 
	(put 'op 'cond 
	     (lambda (x y) (eval (cond->if x) y)))
###4.4
####a.
	; added in 'eval
	((and? expr) (eval-and (and-clauses expr) env)) 
	((or? expr) (eval-or (or-clauses expr) env))
	
	; and? and or?
	(define (and? expr) (tagged-list? expr 'and)) 
	(define (or? expr) (tagged-list? expr 'or))
	
	(define (and-clauses expr) (cdr expr))
	(define (or-clauses expr) (cdr expr))
	
	(define (eval-and exps env)
	    (cond ((null? exps)
	            #t)
	          ((last-exp? (first-exp exps))
	            (eval (first-exp exps)))
	          ((true? (eval (first-exp exps) env))
	            (eval-and (rest-exp exps) env))
	          (else
	            #f)))

	(define (eval-or exps env)
	    (cond ((null? exps)
	            #f)
	          ((true? (eval (first-exp exps) env))
	            #t)
	          (else
	            #f)))
####b.
you can convert and-exp and or-exp to if-else clauses.
###4.5
modify the selcter of the 'cond make cond-actions can handle the special-cond.

	(define (special-cond? clause) 
	  (eq? (cadr clause) '=>)) 
	  
	(define (cond-actions clause) 
	  (if (special-cond? clause) 
	      (cons (caddr clause) (cond-predicate clause)) 
	      (cdr clause)))
###4.6
	; eval
	((let? expr) (evaln (let->combination expr) env)) 
	
	; selector
	(define (let? expr) (tagged-list? expr 'let)) 
	(define (let-vars expr) (map car (cadr expr))) 
	(define (let-inits expr) (map cadr (cadr expr))) 
	(define (let-body expr) (cddr expr)) 
	
	(define (let->combination expr) 
	  (list (make-lambda (let-vars expr) (let-body expr)) 
	        (let-inits expr))) 
###4.7
convert let* to recursive make-let to constraining the variable.

	(define (let*? expr) (tagged-list? expr 'let*)) 
	(define (let*-body expr) (caddr expr)) 
	(define (let*-inits expr) (cadr expr)) 
	
	(define (let*->nested-lets expr) 
	  (let ((inits (let*-inits expr)) 
	        (body (let*-body expr))) 
	    (define (make-let-rec clauses) 
	      (if (null? clauses) 
	          body 
	          (list 'let (list (car clauses)) (make-let-rec (cdr clauses))))) 
	    (make-let-rec inits)))
###4.8
skip;
###4.9
skip;
###4.10
skip;