;#lang planet neil/sicp

; apply-generic

(define (apply-generic op . args)
    (let ((type-tags (map type-tag args)))
        (let ((proc (get op type-tags)))
            (if proc
                (if (or (= 1 (length args)) (eq? op 'equ?))
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

(define (attach-tag type-tag contents)
  (if (eq? type-tag 'scheme-number)
      contents
      (cons type-tag contents)))

(define (type-tag datum)
  (cond ((pair? datum)
         (car datum))
        ((number? datum)
         'scheme-number)
        (else
         (error "Bad tagged datum -- TYPE-TAG" datum))))

(define (contents datum)
  (cond ((pair? datum)
         (cdr datum))
        ((number? datum)
         datum)
        (else
         (error "Bad tagged datum -- CONTENT" datum))))