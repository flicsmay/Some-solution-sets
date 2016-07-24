##Exercise 3.51-3.60

###3.51
	> (define x (stream-map show (stream-enumerate-interval 0 10)))
	
	0
	> (stream-ref x 5)
	
	1   
	2   
	3   
	4   
	55   
	> (stream-ref x 7)
	
	6   
	77
###3.52
	> (stream-ref y 7)
	136
	> (display-stream z)
	
	10
	15
	45
	55
	105
	120
	190
	210'done

if there are not memo-proc the sum would be added twice and the output would be 420.
###3.53
	s[0]	s[1]	s[2]	...
			1		2
	1		+		+		...
			1		2
###3.54
	(define (mul-streams s1 s2)
    	(stream-map * s1 s2))

	(define factorial
	    (cons-stream 1 
	                 (mul-streams factorial
	                              (stream-cdr integers))))
###3.55
	(define (partial-sum stream)
	  (cons-stream (stream-car stream)
	               (add-streams (stream-cdr stream)
	                            (partial-sum stream))))
###3.56
	(define s (cons-stream 1 
	                       (merge (scale-stream s 2)
	                              (merge (scale-stream s 3)
	                                     (scale-stream s 5)))))
###3.57
n times, apparently
###3.58
1 4 2 8 5 7 1 4 2 8 5 7    
3 7 5 0 0 0 0 0 0 0 0 0
###3.59
####a
	(define (integrate-series a)
	    (mul-streams a   
	                 (div-streams ones integers)))
####b
>     (define sine-series (cons-stream 0 (integrate-series cosine-series)))
>     (define cosine-series (cons-stream 1 (integrate-series (scale-stream sine-series -1))))
###3.60
skip;