#lang planet neil/sicp

; Exercise 2.68

; encode : message, tree
; encode a given message with a Huffman tree
(define (encode message tree)
  (if (null? message)
      '()
      (append (encode-symbol (car message) tree)
              (encode (cdr message) tree))))

; encode-symbol : char, Huffman-tree
; return the binary list of the char in Huffman-tree
(define (encode-symbol char tree)
  (define (encode-iter result curr-branch)
    (cond ((leaf? curr-branch)
           result)
          ((pair? (memq char (symbols (left-branch curr-branch))))
           (encode-iter (append result (list 0))
                        (left-branch curr-branch)))
          (else
           (encode-iter (append result (list 1))
                        (right-branch curr-branch)))))
  (if (not (pair? (memq char (symbols tree))))
      (error "not that char -- encode-symbol" char)
      (encode-iter '() tree)))

; ****************************************************

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

(define sample-tree
    (make-code-tree (make-leaf 'A 4)
                    (make-code-tree
                        (make-leaf 'B 2)
                        (make-code-tree (make-leaf 'D 1)
                                        (make-leaf 'C 1)))))