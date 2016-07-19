#lang planet neil/sicp

; Exercise 2.42

; queens : int_boardsize
; return solution to the n-queens puzzle
(define (queens board-size)
  (define (queen-cols k)
    (if (= k 0)
        (list empty-board)
        (filter
         (lambda (positions) (safe? k positions))
         (flatmap
          (lambda (rest-of-queens)
            (map (lambda (new-row)
                   (adjoin-position new-row k rest-of-queens))
                 (enumerate-interval 1 board-size)))
          (queen-cols (- k 1))))))
  (queen-cols board-size))

; empty-board 
(define empty-board '())

; safe? : int_k, s_list
; return TRUE if the kth queens is safe in the position list
(define (safe? k position)
  (define (get-kth-pos n rest)
    (if (= n 1)
        (car rest)
        (get-kth-pos (- n 1) (cdr rest))))
  (let ((k-th-pos (get-kth-pos k position)))
    (define (safe-iter n rest)
      (if (= n 0)
          #t
          (and (safe-iter (- n 1) (cdr rest))
               (not (or (= (car rest) (- k-th-pos n))
                        (= (car rest) (+ k-th-pos n))
                        (= (car rest) k-th-pos))))))
    (safe-iter (- k 1) position)))

; adjoin-position : int_pos, int_k, list_rest
; add a position in to the row
(define (adjoin-position new-row k rest)
  (append rest (list new-row)))
; =================================================================

; flatmap : #proc, s_list
; append results which are the map of seq together
; but it actually just remove a lay of list from it
(define (flatmap proc seq)
  (accumulate append nil (map proc seq)))


; filter : #procedure, s_list/s_tree
; go through the every elements of the given tree/list with #pro
; eliminates all elements but those whose predication are TRUE
(define (filter predicate sequence)
  (cond ((null? sequence) nil)
        ((predicate (car sequence))
         (cons (car sequence)
               (filter predicate (cdr sequence))))
        (else
         (filter predicate (cdr sequence)))))

; accumulate : #operation, initial, s_list/s_tree
; #oper to every elements in the structure together with an initial value
(define (accumulate op initial sequence)
  (if (null? sequence)
      initial
      (op (car sequence)
          (accumulate op initial (cdr sequence)))))

; enumerate-interval : int_low, int_high
; go through the integer list from low to high
(define (enumerate-interval low high)
  (if (> low high)
      nil
      (cons low (enumerate-interval (+ low 1) high))))