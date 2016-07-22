#lang planet neil/sicp

; Exercise 3.23

(define (front-ptr deque) (car deque))
(define (rear-ptr deque) (cdr deque))

(define (set-front-ptr! deque item) (set-car! deque item))
(define (set-rear-ptr! deque item) (set-cdr! deque item))

(define (empty-deque? deque) (null? (front-ptr deque)))

(define (front-deque deque)
  (if (empty-deque? deque)
      (error "FRONT called with an empty deque" deque)
      (car (front-ptr deque))))

(define (rear-deque deque)
  (if (empty-deque? deque)
      (error "REAR called with an empty deque" deque)
      (cdr (rear-ptr deque))))


(define (make-new-node item)
  (cons item (cons '() '())))

(define (next-node node)
  (cddr node))

(define (prev-node node)
  (cadr node))

(define (set-prev-node! node prev-node)
  (set-car! (cdr node) prev-node))

(define (set-next-node! node next-node)
  (set-cdr! (cdr node) next-node))

(define (front-insert-deque! deque item)
  (let ((new-pair (make-new-node item)))
    (cond ((empty-deque? deque)
           (set-front-ptr! deque new-pair)
           (set-rear-ptr! deque new-pair)
           deque)
          (else
           (let ((front-node (front-ptr deque)))
             (set-next-node! new-pair front-node)
             (set-prev-node! front-node new-pair)
             (set-front-ptr! deque new-pair)
             deque)))))


(define (rear-insert-deque! deque item)
  (let ((new-pair (make-new-node item)))
    (cond ((empty-deque? deque)
           (set-front-ptr! deque new-pair)
           (set-rear-ptr! deque new-pair)
           deque)
          (else
           (let ((rear-node (rear-ptr deque)))
             (set-prev-node! new-pair rear-node)
             (set-next-node! rear-node new-pair)
             (set-rear-ptr! deque new-pair)
             deque)))))


(define (front-delete-deque! deque)
  (cond ((empty-deque? deque)
         (error "DELETE! called with an empty deque" deque))
        ((eq? (front-ptr deque) (rear-ptr deque))
         (set-rear-ptr! deque '())
         (set-front-ptr! deque '()))
        (else
         (set-front-ptr! deque (next-node (front-ptr deque)))
         (set-prev-node! (rear-ptr deque) '())
         deque)))

(define (rear-delete-deque! deque)
  (cond ((empty-deque? deque)
         (error "DELETE! called with an empty deque" deque))
        ((eq? (front-ptr deque) (rear-ptr deque))
         (set-rear-ptr! deque '())
         (set-front-ptr! deque '()))
        (else
         (set-rear-ptr! deque (prev-node (rear-ptr deque)))
         (set-next-node! (rear-ptr deque) '())
         deque)))

(define (print-deque deque)
  (define (iter rest result)
    (if (null? rest)
        result
        (let ((next (next-node rest)))
          (iter next (append result 
                             (list (car rest)))))))
  (if (empty-deque? deque)
      '()
      (iter (front-ptr deque) '())))


