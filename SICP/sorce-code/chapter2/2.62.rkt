#lang planet neil/sicp

; Exercise 2.62

; union-set : set1, set2
; return the set which is the union of two given sets
(define (union-set set1 set2)
  (define (union-set-iter result rest1 rest2)
    (if (or (null? rest1) (null? rest2))
        (append result rest1 rest2)
        (let ((curr1 (car rest1))
              (curr2 (car rest2)))
          (cond ((= curr1 curr2)
                 (union-set-iter (append result (list curr1))
                                 (cdr rest1)
                                 (cdr rest2)))
                ((< curr1 curr2)
                 (union-set-iter (append result (list curr1))
                                 (cdr rest1)
                                 rest2))
                (else
                 (union-set-iter (append result (list curr2))
                                 rest1
                                 (cdr rest2)))))))
  (union-set-iter '() set1 set2))