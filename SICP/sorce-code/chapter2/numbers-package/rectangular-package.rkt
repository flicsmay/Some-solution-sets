;#lang planet neil/sicp



(define (install-rectangular-package)
  ;; internal procedures
  (define (real-part z) (car z))
  (define (imag-part z) (cdr z))
  (define (square x) (* x x))
  (define (make-from-real-imag x y) (cons x y))
  (define (magnitude z)
    (sqrt (+ (square (real-part z))
             (square (imag-part z)))))
  (define (angle z)
    (atan (imag-part z) (real-part z)))
  ; atan ......
  (define (make-from-mag-ang r a) 
    (cons (* r (cos a)) (* r (sin a)))) ; TO DO tranfrom cos and sin
  (define (tag x) (attach-tag 'rectangular x))
  
  (put '=zero? '(rectangular)
       (lambda (x) (and (= (real-part x) 0)
                        (= (imag-part x) 0))))
  (put 'real-part '(rectangular) real-part)
  (put 'imag-part '(rectangular) imag-part)
  (put 'magnitude '(rectangular) magnitude)
  (put 'angle '(rectangular) angle)
  (put 'make-from-real-imag 'rectangular 
       (lambda (x y) (tag (make-from-real-imag x y))))
  (put 'make-from-mag-ang 'rectangular 
       (lambda (r a) (tag (make-from-mag-ang r a))))
  'done)