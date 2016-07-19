;#lang planet neil/sicp

; package for rational numbers

(define (install-rational-package)
  ;; internal procedures
  (define (numer x) (car x))
  (define (denom x) (cdr x))
  (define (make-rat n d)
    (let ((g (gcd n d)))
      (cons (/ n g) (/ d g))))
  (define (add-rat x y)
    (make-rat (+ (* (numer x) (denom y))
                   (* (numer y) (denom x)))
              (* (denom x) (denom y))))
  (define (sub-rat x y)
    (make-rat (- (* (numer x) (denom y))
                   (* (numer y) (denom x)))
              (* (denom x) (denom y))))
  (define (mul-rat x y)
    (make-rat (* (numer x) (numer y))
              (* (denom x) (denom y))))
  (define (div-rat x y)
    (make-rat (* (numer x) (denom y))
              (* (denom x) (numer y))))
  ;; interface to rest of the system
  
  ; add tag
  (define (tag x) (attach-tag 'rational x))
  
  (define (raise-to-real rational-num)
    (make-real (/ (numer rational-num)
                  (denom rational-num))))
  
  (define (project-to-integer rational)
    (make-scheme-number (round (/ (numer rational)
                                  (denom rational)))))
  
  (put 'project '(rational) project-to-integer)
  
  (put 'equ? '(rational rational)
       (lambda (x y)
         (and (= (numer x) (numer y))
              (= (denom x) (denom y)))))
  
  (put '=zero? '(rational)
       (lambda (x) (= (numer x) 0)))
  
  (put 'raise '(rational) raise-to-real)
  
  (put 'sine 'rational 
       (lambda (x) (tag (sin x)))) 
  (put 'cosine 'rational 
       (lambda (x) (tag (cos x))))
  
  (put 'add '(rational rational)
       (lambda (x y) (tag (add-rat x y))))
  (put 'sub '(rational rational)
       (lambda (x y) (tag (sub-rat x y))))
  (put 'mul '(rational rational)
       (lambda (x y) (tag (mul-rat x y))))
  (put 'div '(rational rational)
       (lambda (x y) (tag (div-rat x y))))

  (put 'make 'rational
       (lambda (n d) (tag (make-rat n d))))
  'done)
