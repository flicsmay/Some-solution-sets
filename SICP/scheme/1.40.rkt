#lang planet neil/sicp

(define (fixed-point f frist-guess)
  
  (define tolerance 0.00001)
  
  (define (close-enough? v1 v2)
    (< (abs (- v1 v2)) tolerance))
  
  (define (try guess)
    (let ((next (f guess)))
      (if (close-enough? guess next)
          next
          (try next))))
  (try frist-guess))

; fixed point func

(define (average x y) (/ (+ x y) 2))

(define (average-damp f)
  (lambda (x) (average x (f x))))

(define (deriv g)
  
  (define dx 0.00001)
  
  (lambda (x)
    (/ (- (g (+ x dx)) (g x))
       dx)))

(define (newton-transform g)
  (lambda (x)
    (- x (/ (g x) ((deriv g) x)))))

(define (newton-method g guess)
  (fixed-point (newton-transform g) guess))

; newton method

(define (cubic a b c)
  (lambda (x) (+ (* x x x)
                 (* a (* x x))
                 (* b x)
                 c)))