#lang planet neil/sicp

; Exercise 2.60
; duplicate represent allowed

; element-of-set : elem, set
; return TRUE if the given element is a member of a set
(define (element-of-set? x set)
  (cond ((null? set) false)
        ((equal? x (car set)) true)
        (else (element-of-set? x (cdr set)))))

; adjoin-set : elem, set
; return the set that contains the original elems with adjoined elem
(define (adjoin-set x set)
  (cons x set))

; union-set : set1, set2
; return a set which contains all the elements from two given sets
(define (union-set set1 set2)
  (append set1 set2))

; intersection-set : set1, set2
; return the set which is the inersection of two sets
(define (intersection-set set1 set2)
  (define (inter-set-iter result rest)
    (cond ((null? rest) result)
          ((and (element-of-set? (car rest) set2)
                (not (element-of-set? (car rest) result)))
           (inter-set-iter (adjoin-set (car rest) result)
                           (cdr rest)))
          (else
           (inter-set-iter result (cdr rest)))))
  (inter-set-iter '() set1))
   
   
   
   
   
   
   
   
   
   
   