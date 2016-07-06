#lang planet neil/sicp

; list-ref : s_list int
; print out the (n-1)th value of a list s_list
(define (list-ref items n)
  (if (= n 0)
      (car items)
      (list-ref (cdr items) (- n 1))))


; length : s_list
; return the length of the s_list
(define (length items)
  (define (length-iter a count)
    (if (null? a)
        count
        (length-iter (cdr a) (+ 1 count))))
  (length-iter items 0))


; last-pair : s_list
; return the last item in the given list s_list
(define (last-pair item)
  (define (last-pair-iter cur-node)
    (if (null? (cdr cur-node))
        (car cur-node)
        (last-pair-iter (cdr cur-node))))
  (last-pair-iter item))



; reverse : s_list
; reverse a given list : s_list
(define (reverse itemlist)
  (define (reverse-iter cur-node result-list)
    (if (null? cur-node)
        result-list
        (reverse-iter (cdr cur-node)
                      (append (cons (car cur-node) nil) ; bulid a list node
                              result-list))))
  (reverse-iter itemlist nil))




      
      