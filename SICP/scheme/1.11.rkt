#lang racket

(define (f n)
  (define (f-iter i f1 f2 f3)
    (if (> i n)
        f3
        (f-iter (+ i 1)
                f2
                f3
                (+ f3
                   (* 2 f2)
                   (* 3 f1)))))
  (if (< n 3)
      n
      (f-iter 3 0 1 2)))