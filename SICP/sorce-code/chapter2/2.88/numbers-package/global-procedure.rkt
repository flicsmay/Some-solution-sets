;#lang planet neil/sicp

; global procedure

(define coercion-table (make-table))
(define get-coercion (coercion-table 'lookup-proc))
(define put-coercion (coercion-table 'insert-proc!))

(define (make-real n)
  ((get 'make 'real) n))

(define (make-scheme-number n)
  ((get 'make 'scheme-number) n))

(define (make-rational n d)
  ((get 'make 'rational) n d))

(define (make-complex-from-real-imag x y)
  ((get 'make-from-real-imag 'complex) x y))
(define (make-complex-from-mag-ang r a)
  ((get 'make-from-mag-ang 'complex) r a))


; global procedure

(define (add x y) (apply-generic 'add x y))
(define (sub x y) (apply-generic 'sub x y))
(define (mul x y) (apply-generic 'mul x y))
(define (div x y) (apply-generic 'div x y))
(define (raise x) (apply-generic 'raise x))
(define (=zero? x) (apply-generic '=zero? x))
(define (neg x) (apply-generic 'neg x))

(define (sine x) (apply-generic 'sine x)) 
(define (cosine x) (apply-generic 'cosine x))

(define (project n)
  (apply-generic 'project n))
  
(define (equ? x y)
  (apply-generic 'equ? x y))
  
(define (can-be-dropped? n)
    (if (get 'project (list (type-tag n)))
        (let ((projected (project n)))
          (if (get 'raise (list (type-tag projected)))
              (let ((retrived (raise projected)))
                (equ? retrived n))
              #f))
        #f))
  
(define (drop n)
  (define (drop-iter current)
    (if (can-be-dropped? current)
        (drop-iter (project current))
        current))
  (drop-iter n))