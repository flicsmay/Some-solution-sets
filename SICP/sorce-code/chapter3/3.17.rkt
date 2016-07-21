#lang planet neil/sicp

; Exercise 3.17

(define (append! x y)
  (set-cdr! (last-pair x) y)
  x)

(define (last-pair x)
  (if (null? (cdr x))
      x
      (last-pair (cdr x))))

(define (make-cycle x)
  (set-cdr! (last-pair x) x)
  x)

(define (mystery x)
  (define (loop x y)
    (if (null? x)
        y
        (let ((temp (cdr x)))
          (set-cdr! x y)
          (loop temp x))))
  (loop x '()))

(define three (cons (cons 1 2) (cons 3 4)))
(define w (cons 3 4))
(define x (cons w w))
(define four (cons x 1))
(define y (cons 1 2))
(define z (cons y y))
(define seven (cons z z))

(define a (cons 1 2))
(define b (cons 3 4))
(define c (cons 5 6))
(define (infinite)
  (begin (set-car! a b)
         (set-car! b c)
         (set-car! c a)
         a))
  
(define (count-pairs pairs)
  (define pairs-table (list 'head))
  
  (define (have-been-counted? pair)
    (memq pair pairs-table))
  
  (define (tagged-pairs pair)
    (append! pairs-table (list pair)))
  (define (count-pairs-iter curr)
    (if (or (null? curr) (not (pair? curr)))
        0
        (if (have-been-counted? curr)
            0
            (begin (tagged-pairs curr)
                   (+ (count-pairs-iter (car curr))
                      (count-pairs-iter (cdr curr))
                      1)))))
  (count-pairs-iter pairs))
  

  