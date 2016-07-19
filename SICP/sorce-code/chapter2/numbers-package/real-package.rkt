;#lang planet neil/sicp

; real-numbers-package
(define (install-real-package)
  (define (tag x)
    (attach-tag 'real x))
  
  ; raise real numbers to complex
  
  (define (raise-to-complex real-num)
    (make-complex-from-real-imag real-num 0))
  
  (define (project-to-rational real)
    (define accuracy 0.000001)
    (define (whole-number? n)
      (= (round n) n))
    (define (iter numer denom)
      (let ((numer-appro (round numer)))
        (let ((appro (/ numer-appro denom)))
          (if  (< (abs (- appro real))
                  accuracy)
               (make-rational numer-appro denom)
               (iter (* numer 10) (* denom 10))))))
    (if (number? real)
        (iter real 1)
        #f))
  
  (put 'project '(real) project-to-rational)
  
  (put 'equ? '(real real)
       (lambda (x y) (= x y)))
  
  (put 'raise '(real) raise-to-complex)
  (put '=zero? '(real)
       (lambda (x) (= 0 x)))
  (put 'add '(real real)
       (lambda (x y) (tag (+ x y))))
  (put 'sub '(real real)
       (lambda (x y) (tag (- x y))))
  (put 'mul '(real real)
       (lambda (x y) (tag (* x y))))
  (put 'div '(real real)
       (lambda (x y) (tag (/ x y))))
  (put 'make 'real
       (lambda (x) (tag x)))
  'done)