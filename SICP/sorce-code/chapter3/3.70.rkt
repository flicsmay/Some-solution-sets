#lang planet neil/sicp

(define (stream-car stream) (car stream))

(define (stream-cdr stream) (force (cdr stream)))

(define (stream-ref s n)
  (if (= n 0)
      (stream-car s)
      (stream-ref (stream-cdr s) (- n 1))))

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

(define (stream-for-each proc s)
  (if (stream-null? s)
      'done
      (begin (proc (stream-car s))
             (stream-for-each proc (stream-cdr s)))))

(define (display-stream s)
  (stream-for-each display-line s))

(define (display-line x)
  (newline)
  (display x))

(define (stream-enumerate-interval low high)
  (if (> low high)
      the-empty-stream
      (cons-stream
       low
       (stream-enumerate-interval (+ low 1) high))))

(define (stream-filter pred stream)
  (cond ((stream-null? stream) the-empty-stream)
        ((pred (stream-car stream))
         (cons-stream (stream-car stream)
                      (stream-filter pred
                                     (stream-cdr stream))))
        (else (stream-filter pred (stream-cdr stream)))))

(define (memo-proc proc)
  (let ((already-run? false) (result false))
    (lambda ()
      (if (not already-run?)
          (begin (set! result (proc))
                 (set! already-run? true)
                 result)
          result))))
      
(define (sieve stream)
  (cons-stream
   (stream-car stream)
   (sieve (stream-filter
           (lambda (x)
             (not (divisible? x (stream-car stream))))
           (stream-cdr stream)))))
(define (divisible? x y) (= (remainder x y) 0))
(define (add-streams s1 s2)
  (stream-map + s1 s2))

(define (integers-starting-from n)
  (cons-stream n (integers-starting-from (+ n 1))))

(define (scale-stream stream factor)
  (stream-map (lambda (x) (* x factor)) stream))

(define (partial-sums stream)
  (cons-stream (stream-car stream)
               (add-streams (stream-cdr stream)
                            (partial-sums stream))))

(define (euler-transform s)
  (let ((s0 (stream-ref s 0))           ; Sn-1
        (s1 (stream-ref s 1))           ; Sn
        (s2 (stream-ref s 2)))          ; Sn+1
    (cons-stream (- s2 (/ (square (- s2 s1))
                          (+ s0 (* -2 s1) s2)))
                 (euler-transform (stream-cdr s)))))

(define (square x) (* x x))

(define (sqrt-improve guess x)
  (average guess (/ x guess)))

(define (sqrt-stream x)
  (define guesses
    (cons-stream 1.0
                 (stream-map (lambda (guess)
                               (sqrt-improve guess x))
                             guesses)))
  guesses)

(define (average x y) (/ (+ x y) 2))

(define (one)
  (define guess
    (cons-stream 1.0 guess))
  guess)

(define (interleave s1 s2)
  (if (stream-null? s1)
      s2
      (cons-stream (stream-car s1)
                   (interleave s2 (stream-cdr s1)))))

(define (pairs s t weighting-fun)
  (cons-stream
   (list (stream-car s) (stream-car t))
   (merge-weighted
    (stream-map (lambda (x) (list (stream-car s) x))
                (stream-cdr t))
    (pairs (stream-cdr s) (stream-cdr t))
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
