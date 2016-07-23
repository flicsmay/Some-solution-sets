##Exercise 3.41-3.50

###3.41
when you get balance while withdraw or deposit, you will get different results.
###3.42
I'm not really sure, but I think it is safe.
###3.43
skip;
###3.44
Louis is wrong, the two operations in transfer proce are protected.
###3.45
The inner procedure 'withdraw and 'deposit have been block after the proce 'serialized-exchange have been called. So it would block there forever.
###3.46
obviously enough ...
###3.47
The point is you have to set counter to remember how many procedures have entered, the add-1 sub-porcedure must be mutexed to each others. Just like P() and V().

	(define (make-semaphore n)
	  (let ((lock (make-mutex)))
	    
	    (define (acquire)
	      (if (> n 0)
	          (begin (lock 'acquire)
	                 (set! n (- n 1))
	                 (lock 'release)
	                 'ok)
	          (acquire)))
	    
	    (define (release)
	        (set! n (+ n 1))
	        'ok)
	
	    (define (dispatch mode)
	        (cond ((eq? mode 'acquire)
	                (acquire))
	              ((eq? mode 'release)
	                (release))
	              (else
	                (error "Unknown mode MAKE-SEMAPHORE" mode))))
	
	    dispatch))
###3.48
because both 'serialized-exchange procedures try to lock the smaller-number account, so only one of them can gets the authority and others are blocked. so it can avoid deadlock.
###3.49
just like described in the textbook.
###3.50
	(define (stream-map proc . argstream)
	    (if (null? (car argstream))
	        '()
	        (cons-stream
	            (apply proc 
	                   (map (lambda (s)
	                            (stream-car s))
	                        argstream))
	            (apply stream-map 
	                   (cons proc (map (lambda (s)
	                                       (stream-cdr s))
	                                   argstream))))))