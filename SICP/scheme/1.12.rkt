#lang racket

(define (Pascal-triangle row col)
  (cond ((> col row) 0)
        ((= row col) 1)
        ((= col 0) 1)
        (else (+ (Pascal-triangle (- row 1)
                                  col)
                 (Pascal-triangle (- row 1)
                                  (- col 1))))))