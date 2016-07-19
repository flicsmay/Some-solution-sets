#lang planet neil/sicp

; Exercise 2.69

; generate-huffman-tree : pairs-table
; return a Huffman tree with a pairs table
(define (generate-huffman-tree pairs)
  (successive-merge (make-leaf-set pairs)))

; successive-merge : sorted-set
; merge a weight-set into a huffman tree
(define (successive-merge set)
  (define (successive-merge-iter curr)
    (if (= 1 (length curr))
        curr
        (let ((new-node (make-code-tree (car curr)
                                        (cadr curr))))
          (successive-merge-iter (adjoin-set new-node
                                             (cddr curr))))))
  (if (null? set)
      '()
      (successive-merge-iter set)))

; make-leaf-set : pair-table
; transform the pairs table to a set
(define (make-leaf-set pairs)
  (if (null? pairs)
      '()
      (let ((pair (car pairs)))
        (adjoin-set (make-leaf (car pair)    ; symbol
                               (cadr pair))  ; frequency
                    (make-leaf-set (cdr pairs))))))

; adjoin-set : elem, set
; adjoin a elem in to a given set
(define (adjoin-set x set)
  (cond ((null? set) (list x))
        ((< (weight x) (weight (car set))) (cons x set))
        (else (cons (car set)
                    (adjoin-set x (cdr set))))))

(define (make-leaf symbol weight)
  (list 'leaf symbol weight))
(define (leaf? object)
  (eq? (car object) 'leaf))
(define (symbol-leaf x) (cadr x))
(define (weight-leaf x) (caddr x))

 
(define (make-code-tree left right)
  (list left
        right
        (append (symbols left) (symbols right))
        (+ (weight left) (weight right))))
  
(define (left-branch tree) (car tree))

(define (right-branch tree) (cadr tree))
(define (symbols tree)
  (if (leaf? tree)
      (list (symbol-leaf tree))
      (caddr tree)))
(define (weight tree)
  (if (leaf? tree)
      (weight-leaf tree)
      (cadddr tree)))