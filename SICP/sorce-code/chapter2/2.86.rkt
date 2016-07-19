#lang planet neil/sicp

; Exercise 2.84

; apply-generic

(define (apply-generic op . args)
    (let ((type-tags (map type-tag args)))
        (let ((proc (get op type-tags)))
            (if proc
                (if (or (= 1 (length args)) (eq? op 'equ?)) 
                    ; unary op and equ? shouldn't drop
                    (apply proc (map contents args))
                    (drop (apply proc (map contents args))))
                (if (= (length args) 2)
                    (let ((type1 (car type-tags))
                          (type2 (cadr type-tags))
                          (a1 (car args))
                          (a2 (cadr args)))
                        (let ((comparison (which-is-higher type1 type2)))
                          (cond ((= 0 comparison)
                                 (error "No method for these types" (list op type-tags)))
                                ((= 1 comparison)
                                 (let ((a1 (raise-to-type type2 a1)))
                                   (apply-generic op a1 a2)))
                                ((= -1 comparison)
                                 (let ((a2 (raise-to-type type1 a2)))
                                   (apply-generic op a1 a2)))
                                (else
                                 (error "Unkonwn mistaken..")))))
                                
                    (error "No method for these types"
                            (list op type-tags)))))))

(define (get-level type)
  (cond ((eq? 'scheme-number type)
         0)
        ((eq? 'rational type)
         1)
        ((eq? 'real type)
         2)
        ((eq? 'complex type)
         3)
        (else
         (error "Unkonwn-type -- GET-LEVEL" (list type)))))

(define (which-is-higher type1 type2)
  (let ((lv1 (get-level type1))
        (lv2 (get-level type2)))
    (cond ((= lv1 lv2)
           0)
          ((< lv1 lv2)
           1)
          ((> lv1 lv2)
           -1)
          (else
           (error "Unkonwn mistaken -- WHICH-IS-HIGER" (list type1 type2))))))

(define (raise-to-type type val)
  (let ((level (get-level type)))
    (define (iter result)
      (let ((curr-level (get-level (type-tag result))))
        (if (= curr-level level)
            result
            (iter (raise result)))))
    (iter val)))

; tag operation
; ***********************************************************

(define (attach-tag type-tag contents)
    (cons type-tag contents))

(define (type-tag datum)
    (if (pair? datum)
        (car datum)
         (error "Bad tagged datum -- TYPE-TAG" datum)))

(define (contents datum)
    (if (pair? datum)
        (cdr datum)
        (error "Bad tagged datum -- CONTENT" datum)))

; ***********************************************************

; the implement of 'get and 'put
; in p186 of textbook (chs ver)

(define (make-table)
  (let ((local-table (list '*table*)))
    (define (lookup key-1 key-2)
      (let ((subtable (assoc key-1 (cdr local-table))))
        (if subtable
            (let ((record (assoc key-2 (cdr subtable))))
              (if record
                  (cdr record)
                  false))
            false)))
    (define (insert! key-1 key-2 value)
      (let ((subtable (assoc key-1 (cdr local-table))))
        (if subtable
            (let ((record (assoc key-2 (cdr subtable))))
              (if record
                  (set-cdr! record value)
                  (set-cdr! subtable
                            (cons (cons key-2 value)
                                  (cdr subtable)))))
            (set-cdr! local-table
                      (cons (list key-1
                                  (cons key-2 value))
                            (cdr local-table)))))
      'ok)    
    (define (dispatch m)
      (cond ((eq? m 'lookup-proc) lookup)
            ((eq? m 'insert-proc!) insert!)
            (else (error "Unknown operation -- TABLE" m))))
    dispatch))

; get put & get-coercion put-coercion
(define operation-table (make-table))
(define get (operation-table 'lookup-proc))
(define put (operation-table 'insert-proc!))
(define coercion-table (make-table))
(define get-coercion (coercion-table 'lookup-proc))
(define put-coercion (coercion-table 'insert-proc!))


; ***********************************************************

; package for bulid-in numbers

(define (install-scheme-number-package)
  (define (tag x)
    (attach-tag 'scheme-number x)) 
  (define (raise-to-rational scheme-num)
    (make-rational scheme-num 1))
  
  (put 'raise '(scheme-number) raise-to-rational)
  (put 'equ? '(scheme-number scheme-number)
       (lambda (x y) (= x y)))
  (put 'sine 'scheme-number 
      (lambda (x) (tag (sin x)))) 
  (put 'cosine 'scheme-number 
      (lambda (x) (tag (cos x))))
  
  (put 'add '(scheme-number scheme-number)
       (lambda (x y) (tag (+ x y))))
  (put 'sub '(scheme-number scheme-number)
       (lambda (x y) (tag (- x y))))
  (put 'mul '(scheme-number scheme-number)
       (lambda (x y) (tag (* x y))))
  (put 'div '(scheme-number scheme-number)
       (lambda (x y) (tag (/ x y))))
  (put 'make 'scheme-number
       (lambda (x) (tag x)))
  'done)

; ***********************************************************

; package for rational numbers

(define (numer x) (car x))
(define (denom x) (cdr x))

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

; ***********************************************************
  
; real-numbers-package
(define (install-real-package)
  (define (tag x)
    (attach-tag 'real x))
  
  (define (raise-to-complex real-num)
    (make-complex-from-real-imag real-num (make-scheme-number 0)))
  
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
    (iter real 1))
  
  (put 'project '(real) project-to-rational)
  
  (put 'equ? '(real real)
       (lambda (x y) (= x y)))
  
  (put 'raise '(real) raise-to-complex)
  
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


; ***********************************************************

; package for complex numbers

(define (square x) (* x x))

(define (install-rectangular-package)
  ;; internal procedures
  (define (real-part z) (car z))
  (define (imag-part z) (cdr z))
  (define (make-from-real-imag x y) (cons x y))
  (define (magnitude z)
    (sqrt (+ (square (real-part z))
             (square (imag-part z)))))
  (define (angle z)
    (atan (imag-part z) (real-part z)))
  (define (make-from-mag-ang r a) 
    (cons (* r (cos a)) (* r (sin a))))
  (define (tag x) (attach-tag 'rectangular x))
  (put 'real-part '(rectangular) real-part)
  (put 'imag-part '(rectangular) imag-part)
  (put 'magnitude '(rectangular) magnitude)
  (put 'angle '(rectangular) angle)
  (put 'make-from-real-imag 'rectangular 
       (lambda (x y) (tag (make-from-real-imag x y))))
  (put 'make-from-mag-ang 'rectangular 
       (lambda (r a) (tag (make-from-mag-ang r a))))
  'done)

; ***********************************************************  
  
(define (install-polar-package)
  ;; internal procedures
  (define (magnitude z) (car z))
  (define (angle z) (cdr z))
  (define (make-from-mag-ang r a) (cons r a))
  (define (real-part z)
    (* (magnitude z) (cos (angle z))))
  (define (imag-part z)
    (* (magnitude z) (sin (angle z))))
  (define (make-from-real-imag x y) 
    (cons (sqrt (+ (square x) (square y)))
          (atan y x)))
  ;; interface to the rest of the system
  (define (tag x) (attach-tag 'polar x))
  (put 'real-part '(polar) real-part)
  (put 'imag-part '(polar) imag-part)
  (put 'magnitude '(polar) magnitude)
  (put 'angle '(polar) angle)
  (put 'make-from-real-imag 'polar
       (lambda (x y) (tag (make-from-real-imag x y))))
  (put 'make-from-mag-ang 'polar 
       (lambda (r a) (tag (make-from-mag-ang r a))))
  'done)

(define (real-part z) (apply-generic 'real-part z))
(define (imag-part z) (apply-generic 'imag-part z))
(define (magnitude z) (apply-generic 'magnitude z))
(define (angle z) (apply-generic 'angle z))

; ***********************************************************

(define (install-complex-package)
  ;; imported procedures from rectangular and polar packages
  (define (make-from-real-imag x y)
    ((get 'make-from-real-imag 'rectangular) x y))
  (define (make-from-mag-ang r a)
    ((get 'make-from-mag-ang 'polar) r a))
  ;; internal procedures
  (define (add-complex z1 z2)
    (make-from-real-imag (add (real-part z1) (real-part z2))
                         (add (imag-part z1) (imag-part z2))))
  (define (sub-complex z1 z2)
    (make-from-real-imag (sub (real-part z1) (real-part z2))
                         (sub (imag-part z1) (imag-part z2))))
  (define (mul-complex z1 z2)
    (make-from-mag-ang (mul (magnitude z1) (magnitude z2))
                       (add (angle z1) (angle z2))))
  (define (div-complex z1 z2)
    (make-from-mag-ang (div (magnitude z1) (magnitude z2))
                       (sub (angle z1) (angle z2))))
  (define (project-to-real complex-num)
    (make-real (real-part complex-num)))
 
  (put 'project '(complex) project-to-real)
  
  (put 'equ? '(complex complex)
        (lambda (x y)
            (and (equ? (real-part x) (real-part y))
                 (equ? (imag-part x) (imag-part y)))))
  (define (tag z) (attach-tag 'complex z))
  (put 'add '(complex complex)
       (lambda (z1 z2) (tag (add-complex z1 z2))))
  (put 'sub '(complex complex)
       (lambda (z1 z2) (tag (sub-complex z1 z2))))
  (put 'mul '(complex complex)
       (lambda (z1 z2) (tag (mul-complex z1 z2))))
  (put 'div '(complex complex)
       (lambda (z1 z2) (tag (div-complex z1 z2))))
  (put 'make-from-real-imag 'complex
       (lambda (x y) (tag (make-from-real-imag x y))))
  (put 'make-from-mag-ang 'complex
       (lambda (r a) (tag (make-from-mag-ang r a))))
  (put 'real-part '(complex) real-part)
  (put 'imag-part '(complex) imag-part)
  (put 'magnitude '(complex) magnitude)
  (put 'angle '(complex) angle)
  'done)

; ***********************************************************  
  
(define (install-all)
  (install-scheme-number-package)
  (install-rational-package)
  (install-real-package)
  (install-complex-package)
  (install-rectangular-package)
  (install-polar-package)
  'done)

; make numbers

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

