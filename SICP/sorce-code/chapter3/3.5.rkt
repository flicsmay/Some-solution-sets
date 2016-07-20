#lang planet neil/sicp

; Exercise 3.5

(define (test) (estimate-integral -1.0 1.0 -1.0 1.0 6))

(define (estimate-integral x1 x2 y1 y2 trials)
  (* 4 (monte-carlo trials (circular-test (random-point-in-range x1 x2 y1 y2)
                                          (/ (- x2 x1) 2)
                                          (make-point (/ (+ x1 x2) 2)
                                                      (/ (+ y1 y2) 2))))))

(define (circular-test point r mid-point)
  (let ((delta-x (- (x-point point)
                    (x-point mid-point)))
        (delta-y (- (y-point point)
                    (y-point mid-point))))
    (define (square x) (* x x))
    (if (< (+ (square delta-x)
              (square delta-y))
           (square r))
        #t
        #f)))

(define (random-in-range low high)
  (let ((range (- high low)))
    (+ low (random range))))

(define (random-point-in-range x1 x2 y1 y2)
  (make-point (random-in-range x1 x2)
              (random-in-range y1 y2)))

(define (monte-carlo trials experiment)
  (define (iter trials-remaining trials-passed)
    (cond ((= trials-remaining 0)
           (/ trials-passed trials))
          ((experiment)
           (iter (- trials-remaining 1) (+ trials-passed 1)))
          (else
           (iter (- trials-remaining 1) trials-passed))))
  (iter trials 0))

(define (make-point x y) (cons x y))
(define (x-point z) (car z))
(define (y-point z) (cdr z))