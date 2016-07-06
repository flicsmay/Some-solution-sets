#lang planet neil/sicp

(define (make-interval a b)
  (cons a b))

; constructor

(define (lower-bound z)
  (car z))

(define (upper-bound z)
  (cdr z))

; selector

; add-interval book version

(define (add-interval x y)
  (make-interval (+ (lower-bound x) (lower-bound y))
                 (+ (upper-bound x) (upper-bound y))))

; mul-interval
; in book version
(define (mul-interval x y)
  (let ((p1 (* (lower-bound x) (lower-bound y)))
        (p2 (* (lower-bound x) (upper-bound y)))
        (p3 (* (upper-bound x) (lower-bound y)))
        (p4 (* (upper-bound x) (upper-bound y))))
    (make-interval (min p1 p2 p3 p4)
                   (max p1 p2 p3 p4))))

; interval division
; forbid the division that try to divide an interval spans zero
(define (div-interval x y)
  (if (and (> (upper-bound y) 0) (< (lower-bound y) 0))
      (display "divide an interval that spans zero is forbidden")
      (mul-interval x
                (make-interval (/ 1.0 (upper-bound y))
                               (/ 1.0 (lower-bound y))))))

; subtract two intervals
; problem 2.8
(define (sub-interval x y)
  (add-interval x
                (make-interval (- (lower-bound y))
                               (- (upper-bound y)))))


; make-center-percent
; make an interval by a center point and a tolerance
(define (make-center-percent center tolerance)
  (let ((lower (- center (* center tolerance)))
        (upper (+ center (* center tolerance))))
    (make-interval lower upper)))


; get-tolerances
; get a tolerances of an interval
(define (get-tolerance z)
  (let ((upper (upper-bound z))
        (lower (lower-bound z)))
    (/ (- upper lower)
       (+ upper lower))))