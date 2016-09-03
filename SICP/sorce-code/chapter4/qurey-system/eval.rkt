;#lang racket

; query eval

(define (qeval query frame-stream)
   (let ((qproc (get (type query) 'qeval)))
     (if qproc
         (qproc (contents query) frame-stream)
         (simple-query query frame-stream))))

(define (instantiate exp frame unbound-var-handler)
   (define (copy exp)
     (cond ((var? exp)
            (let ((binding (binding-in-frame exp frame)))
              (if binding
                  (copy (binding-value binding))
                  (unbound-var-handler exp frame))))
           ((pair? exp)
            (cons (copy (car exp)) (copy (cdr exp))))
           (else exp)))
   (copy exp))

(define (execute exp)
   (apply (eval (predicate exp) user-initial-environment)
          (args exp)))

(define (simple-query query-pattern frame-stream)
   (stream-flatmap
    (lambda (frame)
      (stream-append-delayed
       (find-assertions query-pattern frame)
       (delay (apply-rules query-pattern frame))))
    frame-stream))

(define (pattern-match pat dat frame)
   (cond ((eq? frame 'failed) 'failed)
         ((equal? pat dat) frame)
         ((var? pat) (extend-if-consistent pat dat frame))
         ((and (pair? pat) (pair? dat))
          (pattern-match (cdr pat)
                         (cdr dat)
                         (pattern-match (car pat)
                                        (car dat)
                                        frame)))
         (else 'failed)))