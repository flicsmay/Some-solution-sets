#lang planet neil/sicp

; Exercise 2.61

; adjoin-set : elem, set
; return a set which contains the given set elems as well as the elem
(define (adjoin-set elem set)
  (define (adjoin-set-iter result rest)
    (if (null? rest)
        (append set (list elem))
        (let ((curr (car rest))
              (next (cdr rest)))
          (cond ((= elem curr)
                 set)
                ((> elem curr)
                 (adjoin-set-iter (append result (list curr))
                                  next))
                (else
                 (append result (list elem) rest))))))
  (adjoin-set-iter '() set))