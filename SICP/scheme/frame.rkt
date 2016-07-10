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


; make-segment : x-point, y-point
; make a segment with two given points
(define (make-segment x y)
  (list (x y)))

; start-segment : segment
; return the start point of segment
(define (start-segment segment)
  (car segment))

; end-segment : segment
; return the end point of a given segment
(define (end-segment segment)
  (cadr segment))

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


(define (transform-painter painter origin corner1 corner2)
  (lambda (frame)
    (let ((m (frame-coord-map frame)))
      (let ((new-origin (m origin)))
        (painter
         (make-frame new-origin
                     (sub-vect (m corner1) new-origin)
                     (sub-vect (m corner2) new-origin)))))))

(define (flip-vert painter)
  (transform-painter painter
                     (make-vect 0.0 1.0)   ; new origin
                     (make-vect 1.0 1.0)   ; new end of edge1
                     (make-vect 0.0 0.0))) ; new end of edge2

(define (shrink-to-upper-right painter)
  (transform-painter painter
                     (make-vect 0.5 0.5)
                     (make-vect 1.0 0.5)
                     (make-vect 0.5 1.0)))

(define (rotate90 painter)
  (transform-painter painter
                     (make-vect 1.0 0.0)
                     (make-vect 1.0 1.0)
                     (make-vect 0.0 0.0)))

(define (squash-inwards painter)
  (transform-painter painter
                     (make-vect 0.0 0.0)
                     (make-vect 0.65 0.35)
                     (make-vect 0.35 0.65)))

(define (beside painter1 painter2)
  (let ((split-point (make-vect 0.5 0.0)))
    (let ((paint-left
           (transform-painter painter1
                              (make-vect 0.0 0.0)
                              split-point
                              (make-vect 0.0 1.0)))
          (paint-right
           (transform-painter painter2
                              split-point
                              (make-vect 1.0 0.0)
                              (make-vect 0.5 1.0))))
      (lambda (frame)
        (paint-left frame)
        (paint-right frame)))))


(define (make-frame origin edge1 edge2)
    (list origin edge1 edge2))

(define (origin-frame f)
    (car f))

(define (edge1-frame f)
    (cadr f))

(define (edge2-frame f)
    (caddr f))