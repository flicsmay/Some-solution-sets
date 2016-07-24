##Exercise 3.61-3.70

###3.61
skip
###3.62
skip
###3.63
The local variable *guess* is used to reserve the previous result. but if make it recursive it would not use to previous result.
###3.64
	(define (stream-limit stream tolerance)
	        (if (< (abs (- (stream-ref stream 1) (stream-ref stream 0))) tolerance)
	                (stream-ref stream 1)
	                (stream-limit (stream-cdr stream) tolerance)))
###3.65
just input and get results.
###3.66
there are one more pair (s0,t0) in front of list as well as interleave calculate (s0,t1) first, so there are 100 + 100 - 2 = 198 pairs and 197 in front of the last one.   
(s100,t100) is on the diagonal, when you get one in (sn,tn) you got 2 in (sn-1,tn-1) and 2^2 in (sn-2,tn-2) ... so, you would get 1 + 2 + 4 + ... + 2^100 pairs in front of the last one.(I'm not really sure)
###3.67
I actually don't really know whether it wants me produce *all* numbers pairs or only the pairs whose *i greater than j*

	(define (all-pairs s t)
	        (cons-stream 
	                (list (stream-car s) (stream-car t))
	                (interleave
	                        (interleave
	                                (stream-map (lambda (x) (list (stream-car s) x))
	                                                        (stream-cdr t))
	                                (all-pairs (stream-cdr s) (stream-cdr t)))
	                        (stream-map (lambda (x) (list x (stream-car t)))
	                                                (stream-cdr s)))))
###3.68
It would fall into an infinitely loop, because there is no delay in `(pairs (stream-cdr s) (stream-cdr t)`
###3.69
A bit modification in proc-pairs (pairs t u) to provide pairs whose t <= u

	(define (triples s t u)
	  (cons-stream (list (stream-car s)
	                     (stream-car t) 
	                     (stream-car u))
	               (interleave
	                (stream-map (lambda (x) (cons (stream-car s) x))
	                            (stream-cdr (pairs t u)))
	                (triples (stream-cdr s)
	                         (stream-cdr t)
	                         (stream-cdr u)))))
	(define (phythagorean-numbers)
	  (define (square x) (* x x))
	  (define numbers (triples integers integers integers))
	  (stream-filter (lambda (x) 
	                   (= (square (caddr x)) 
	                      (+ (square (car x)) (square (cadr x)))))
	                 numbers))
###3.70
	(define (pairs s t weighting-fun)
	  (cons-stream
	   (list (stream-car s) (stream-car t))
	   (merge-weighted
	    (stream-map (lambda (x) (list (stream-car s) x))
	                (stream-cdr t))
	    (pairs (stream-cdr s) (stream-cdr t) weighting-fun)
	    weighting-fun)))
	
	(define (merge-weighted s1 s2 weight)
	  (cond ((stream-null? s1) s2)
	        ((stream-null? s2) s1)
	        (else
	         (let ((cars1 (stream-car s1))
	               (cars2 (stream-car s2)))
	           (cond ((< (weight cars1) 
	                     (weight cars2))
	                  (cons-stream cars1 
	                               (merge-weighted (stream-cdr s1) 
	                                               s2 
	                                               weight)))
	                 ((= (weight cars1) 
	                     (weight cars2)) 
	                  (cons-stream cars1 
	                               (merge-weighted (stream-cdr s1) 
	                                               s2 
	                                               weight)))
	                 (else (cons-stream cars2
	                                    (merge-weighted s1
	                                                    (stream-cdr s2)
	                                                    weight))))))))
	
	(define (sum-weighted x)
	  (+ (car x) (cadr x)))

then the (b) just write a weighting function and add a filter outside.