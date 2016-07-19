#lang racket

(define (two-larger-sum a b c)
  (if (> a b)
      (if (> b c)
          (+ a b)
          (+ a c))
      (if (> a c)
          (+ a b)
          (+ b c))))

(define (a-plus-abs-b a b)
  ((if (> b 0) + -) a b))