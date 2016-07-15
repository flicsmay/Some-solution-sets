#lang planet neil/sicp

; Exercise 2.75


(define (make-from-mag-ang mag ang)
  (define (dispatch op)
    (cond ((eq? op 'real-part)
           (* mag (cos ang)))
          ((eq? op 'imag-part)
           (* mag (sin ang)))
          ((eq? op 'magnitued) mag)
          ((eq? op 'angle) ang)
          (else
           (error "Unknown op -- MAKE-FROMK-MAG-ANG" op))))
  dispatch)