#lang planet neil/sicp

; frame-coord-map : s_frame
; used to shift and scale images to fit the frame
(define (frame-coord-map frame)
  (lambda (v)
    (add-vect
     (origin-frame frame)
     (add-vect (scale-vect (xcor-vect v)
                           (edge1-frame frame))
               (scale-vect (ycor-vect v)
                           (edge2-frame frame))))))

; Exercise 2.46

; make-vect : x-point, y-point
; make a vector with two given points
(define (make-vect x y)
  (cons x y))

; xcor-vect : vector
; return the x point of given vector
(define (xcor-vect v)
    (car v))

; ycor-vect : vector
; return the x point of given vector
(define (ycor-vect v)
    (cadr v))

; add-vect : vect1, vect2
; return a vector which is the sum of two given vectors
(define (add-vect v1 v2)
  (make-vect (+ (xcor-vect v1) (xcor-vect v2))
             (+ (ycor-vect v1) (ycor-vect v2))))

; sub-vect : vect1, vect2
; return the subtraction of two given vectors
(define (sub-vect v1 v2)
  (make-vect (- (xcor-vect v1) (xcor-vect v2))
             (- (ycor-vect v1) (ycor-vect v2))))

; scale-vect : factor, vector
; scale the given vector with a given factor
(define (scale-vect factor vect)
    (make-vect (* factor (xcor-vect vect))
               (* factor (ycor-vect vect))))