##Exercise 4.11 - 4.20

###4.11
change the constructor and selectors.

	(define (make-frame variables values) 
	  (if (= (length variables) (length values)) 
	      (map cons variables values) 
	      (error "length mismatch -- MAKE-FRAME" variables values))) 
	
	(define (frame-variables frame) (map car frame)) 
	(define (frame-values frame) (map cdr frame)) 
###4.12
but i think that the upper exercise's solutions it clear enough.

	(define (lookup-variable-value var env)
	  (if (empty-environment? env)
	      (error "look for a unbound variable -- LOOKUP" var)
	      (let ((binding (lookup-binding-in-frame var 
	                                              (first-frame env))))
	        (if binding
	            (binding-val binding)
	            (lookup-variable-value var (enclosing-environment env))))))
	
	(define (extend-environment vars vals base-env)
	  (if (not (= (length vars) (length vals)))
	      (error "dismatch between vars and vals" vars vals)
	      (adjoin-frame-to-env (make-frame vars vals) base-env)))
	
	(define (define-variable var val env)
	  (if (empty-environment? env)
	      (error "a empty environment input")
	      (add-binding-into-frame (make-binding var val) (first-frame env))))
	
	(define (set-variable-value! var val env)
	  (if (empty-environment? env)
	      (error "look for a unbound variable -- LOOKUP" var)
	      (let ((binding (lookup-binding-in-frame var
	                                              (first-frame env))))
	        (if binding
	            (set-binding-val binding)
	            (set-variable-value! var val (enclosing-environment env))))))
###4.13
I believe that it should just remove the current frame's bound.

	(define (make-unbound! var env)
	  (if (empty-environment? env)
	      (error "a empty environment input")
	      (let ((finded (lookup-binding-in-frame (first-frame env))))
	        (if finded
	            (remove-a-binding-from-frame finded (first-frame env))))))
###4.14
skip;
###4.15
skip;
###4.16
####a
add the clause below into the *look-up-variable-value* procedure.

	(if (eq? (car vals) '*unassigned*) 
	    (error "variable is unassigned" var) 
	    (car vals))

####b


####c
installed in **make-procedure** is better, otherwise *scan-out-defines* would be called when *procedure-body* is called.