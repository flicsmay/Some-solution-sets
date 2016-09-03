;#lang planet neil/sicp

; stream operations

(define (stream-car stream) (car stream))

(define (stream-cdr stream) (force (cdr stream)))


(define (stream-car stream) (car stream))

(define (stream-cdr stream) (force (cdr stream)))

(define (stream-append s1 s2)
   (if (stream-null? s1)
       s2
       (cons-stream (stream-car s1)
                    (stream-append (stream-cdr s1) s2))))

(define (display-line x)
   (newline)
   (display x))

(define (stream-append-delayed s1 delayed-s2)
   (if (stream-null? s1)
       (force delayed-s2)
       (cons-stream
        (stream-car s1)
        (stream-append-delayed (stream-cdr s1) delayed-s2))))

(define (interleave-delayed s1 delayed-s2)
   (if (stream-null? s1)
       (force delayed-s2)
       (cons-stream
        (stream-car s1)
        (interleave-delayed (force delayed-s2)
                            (delay (stream-cdr s1))))))

(define (stream-flatmap proc s)
   (flatten-stream (stream-map proc s)))

(define (flatten-stream stream)
   (if (stream-null? stream)
       the-empty-stream
       (interleave-delayed
        (stream-car stream)
        (delay (flatten-stream (stream-cdr stream))))))

(define (singleton-stream x)
   (cons-stream x the-empty-stream))

(define (get-stream key1 key2)
   (let ((s (get key1 key2)))
     (if s s the-empty-stream)))

(define (display-stream s)
   (stream-for-each display-line s))

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