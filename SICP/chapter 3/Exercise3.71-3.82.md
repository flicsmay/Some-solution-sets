##Exercise 3.71-3.82

###3.71
write a stream-filter for twos in stream.
	
	(define (Ramanujan s) 
	  (define (stream-cadr s) (stream-car (stream-cdr s))) 
	  (define (stream-cddr s) (stream-cdr (stream-cdr s)))
	  (let ((scar (stream-car s)) 
	        (scadr (stream-cdr s))) 
	    (if (= (sum-triple scar) (sum-triple scadr))  
	        (cons-stream (list (sum-triple scar) scar scadr) 
	                     (Ramanujan (stream-cddr s))) 
	        (Ramanujan (stream-cdr s))))) 
	(define (triple x) (* x x x)) 
	(define (sum-triple x) (+ (triple (car x)) (triple (cadr x)))) 
	(define Ramanujan-numbers 
	  (Ramanujan (weighted-pairs integers integers sum-triple)))
###3.72
print out all pairs that sorting by sum of their elems square, and find three elems that have the same weight in the output list.

	(define (square x) (* x x)) 
	(define (sum-square x) (+ (square (car x)) (square (cadr x)))) 
	(define (squaresn s) 
	  (define (stream-cadr s) (stream-car (stream-cdr s))) 
	  (define (stream-caddr s) (stream-cadr (stream-cdr s))) 
	  (let ((scar (stream-car s)) 
	        (scadr (stream-cadr s)) 
	        (scaddr (stream-caddr s))) 
	    (if (= (sum-square scar) (sum-square scadr) (sum-square scaddr)) 
	        (cons-stream (list (sum-square scar) scar scadr scaddr) 
	                     (squaresn (stream-cdr (stream-cdr (stream-cdr s))))) 
	        (squaresn (stream-cdr s))))) 
	(define square-numbers  
	  (squaresn (weighted-pairs integers integers sum-square)))  
###3.73
using integral above, have not been tested.

	(define (RC r c dt) 
	  (lambda (i-stream v0) 
	    (add-streams (scale-stream i-stream r) 
	                 (integral (scale-stream i-stream (/ 1 c)) v0 dt))) 
	  proc)
###3.74
there are another ver of stream-map (solve in Exercise 3.50) that take multiple args. We need the second arg a stream as well as the last-value of the evaluating stream. so, we might define liske this.

	(define (zero-crossings sense-data) 
	  (stream-map sign-change-detector sense-data (stream-cdr sense-data)))
###3.75
notice that Louis' mistaken is that he detect the sign change with a avpt and a last value, the simplest way to solve it is to add an avpt arg.

	(define (make-zero-crossings input-stream last-value last-avpt) 
	  (let ((avpt (/ (+ (stream-car input-stream) last-value) 2))) 
	    (cons-stream (sign-change-detetor avpt last-avpt) 
	                 (make-zero-crossings (stream-cdr input-stream) 
	                                      (stream-car input-stream) 
	                                      avpt))))  
###3.76
It remind me the procedure 'euler-transform in section 3.5.3. transform a stream to a smoothed stream.

	(define (smooth s)
	  (let ((s0 (stream-ref s 0))
	        (s1 (stream-ref s 1)))
	    (cons-stream (/ (+ s0 s1) 2)
	                 (smooth (stream-cdr s)))))
###3.77
add a (let ((force..))) and a delay procedures.

	(define (integral delayed-integrand initial-value dt) 
	  (cons-stream initial-value 
	               (let ((integrand (force delayed-integrand))) 
	                 (if (stream-null? integrand) 
	                     the-empty-stream 
	                     (integral (delay (stream-cdr integrand)) 
	                               (+ (* dt (stream-car integrand)) 
	                                  initial-value) 
	                               dt)))))
###3.78
	(define (solve-2nd a b dt y0 dy0) 
	  (define y (integral (delay dy) y0 dt)) 
	  (define dy (integral (delay ddy) dy0 dt)) 
	  (define ddy (add-streams (scale-stream dy a) (scale-stream y b))) 
	  y)
###3.79
	(define(general-solve-2nd f y0 dy0 dt) 
	  (define y (integral (delay dy) y0 dt)) 
	  (define dy (integral (delay ddy) dy0 dt)) 
	  (define ddy (stream-map f dy y)) 
	  y) 
###3.80
skip;
###3.81
skip;
###3.82
skip;
