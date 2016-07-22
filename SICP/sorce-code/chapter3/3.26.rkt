#lang planet neil/sicp

; Exercise 3.26

; pseudocode

(define (find-value-by-a-key key table)
  (define (find-iter curr-key)
    (if (empty-key? curr-key)
        false
        (let ((comparsion (compare-key (get-key curr-key) key)))
          (cond ((= comparsion 0)
                 (get-value curr-key))
                ((= comparsion 1)
                 (find-iter (right-branch curr-key)))
                ((= comparsion -1)
                 (find-iter (left-branch curr-key)))
                (else
                 (error "get a error in comparsion -- find-value-by-a-key ")))))
    (find-iter (key-list-table table))))

(define (insert-value-in-a-table value key table)
  (define (insert-iter curr-key)
    (let ((comparsion (compare-key (get-key curr-key) key)))
      (cond ((= comparsion 0)
             (set-key-value curr-key value))
            ((= comparsion 1)
             (let ((next-node (right-branch curr-key)))
               (if (empty-key? next-node)
                   (set-right-node key value curr-key)
                   (insert-iter (right-branch curr-key)))))
            ((= comparsion -1)
             (let ((next-node (left-branch curr-key)))
               (if (empty-key? next-node)
                   (set-left-node key value curr-key)
                   (insert-iter (left-branch curr-key)))))
            (else
             (error "get a error in comparsion -- find-value-by-a-key ")))))
  (insert-iter (key-list-table table)))
       