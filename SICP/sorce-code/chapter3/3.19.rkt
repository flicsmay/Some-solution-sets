#lang planet neil/sicp

; Exercise 3.18-3.19

(define (append! x y)
  (set-cdr! (last-pair x) y)
  x)

(define (last-pair x)
  (if (null? (cdr x))
      x
      (last-pair (cdr x))))

(define (is-infinite-loop-v1 lst)
  
  (define node-table (list 'head))
  (define (have-visited? pair)
    (memq pair node-table))
  (define (add-in-table pair)
    (append! node-table (list pair)))
  
  (define (iter pair)
    (if (or (null? pair) (not (pair? pair)))
        #f
        (if (have-visited? pair)
            #t
            (begin (add-in-table pair)
                   (iter (cdr pair))))))
  (iter lst))
                    

(define (is-infinite-loop-v2 lst)
  (define (go-forward step num)
    (if (or (null? step) (= num 0))
        step 
        (go-forward (cdr step)
                    (- num 1))))
  
  (define (iter step1 step2)
    (if (or (null? step1) (null? step2))
           #f
        (let ((curr1 (go-forward step1 1))
              (curr2 (go-forward step2 2)))
          (if (eq? curr1 curr2)
              #t
              (iter curr1 curr2)))))
  (iter lst lst))
           

                    
(define (make-cycle x)
  (set-cdr! (last-pair x) x)
  x)

(define z (make-cycle (list 'a 'b 'c)))
                    
                    
                    