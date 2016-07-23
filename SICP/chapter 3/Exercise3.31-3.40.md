##Exercise 3.31-3.40

###3.31
if the 'accept-action-pro' doesn't run the proc immediately, this proc won't be added to time-table until this wire's value have been changed. when the propagate proc be called without the change of initial value, the output is wrong.

###3.32
It may affect the next input in the todo-list, so it may affect the final outcome.

###3.33
	(define (averager a b c)
	    (let ((sum (make-connector))
	          (d (make-connector)))
	        (adder a b sum)
	        (multiplier sum d c)
	        (constant (/ 1 2) d)
	        'ok))
###3.34
It will not give you an answer when you set value-b.
because multiplier will not sets two inputs when there are only a output signal.
###3.35
	(define (squarer a b)
	    (define (process-new-value)
	        (if (has-value? b)
	            (if (< (get-value b) 0)
	                (error "square less than 0 -- SQUARER" (get-value b))
	                (set-value! a
	                            (sqrt (get-value b))
	                            me))
	            (if (has-value? a)
	                (set-value! b
	                            (square (get-value a))
	                            me)
	                (error "Neither a nor b has value"))))
	    (define (process-forget-value)
	        (forget-value! a me)
	        (forget-value! b me))
	    (define (me request)
	        (cond
	            ((eq? request 'I-have-a-value)
	                (process-new-value))
	            ((eq? request 'I-lost-my-value)
	                (process-forget-value))
	            (else
	                (error "Unknown request -- MULTIPLIER" request))))
	    (connect a me)
	    (connect b me)
	    me)
###3.36
skip;
###3.37
	(define (c+ x y)
	    (let ((sum (make-connector)))
	        (adder x y sum)
	        sum))
	
	(define (c-sub x y)
	    (let ((diff (make-connector)))
	        (adder y diff x)
	        diff))
	
	(define (c* x y)
	    (let ((product (make-connector)))
	        (multiplier x y product)
	        product))
	
	(define (c/ p q)
	    (let ((r (make-connector)))
	        (multiplier q r p)
	        r))
###3.38
110，90，80，60，55，50，45，40，35，30 
###3.39
121,101
###3.40
100，1,000，10,000，100,000，1,000,000