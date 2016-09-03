;#lang planet neil/sicp

; frame-ops

(define (unify-match p1 p2 frame)
   (cond ((eq? frame 'failed) 'failed)
         ((equal? p1 p2) frame)
         ((var? p1) (extend-if-possible p1 p2 frame))
         ((var? p2) (extend-if-possible p2 p1 frame))  ; ***
         ((and (pair? p1) (pair? p2))
          (unify-match (cdr p1)
                       (cdr p2)
                       (unify-match (car p1)
                                    (car p2)
                                    frame)))
         (else 'failed)))

(define (rename-variables-in rule)
   (let ((rule-application-id (new-rule-application-id)))
     (define (tree-walk exp)
       (cond ((var? exp)
              (make-new-variable exp rule-application-id))
             ((pair? exp)
              (cons (tree-walk (car exp))
                    (tree-walk (cdr exp))))
             (else exp)))
     (tree-walk rule)))

(define (extend-if-consistent var dat frame)
   (let ((binding (binding-in-frame var frame)))
     (if binding
         (pattern-match (binding-value binding) dat frame)
         (extend var dat frame))))

(define (extend-if-possible var val frame)
   (let ((binding (binding-in-frame var frame)))
     (cond (binding
            (unify-match
             (binding-value binding) val frame))
           ((var? val)                      ; ***
            (let ((binding (binding-in-frame val frame)))
              (if binding
                  (unify-match
                   var (binding-value binding) frame)
                  (extend var val frame))))
           ((depends-on? val var frame)     ; ***
            'failed)
           (else (extend var val frame)))))

(define (depends-on? exp var frame)
   (define (tree-walk e)
     (cond ((var? e)
            (if (equal? var e)
                true
                (let ((b (binding-in-frame e frame)))
                  (if b
                      (tree-walk (binding-value b))
                      false))))
           ((pair? e)
            (or (tree-walk (car e))
                (tree-walk (cdr e))))
           (else false)))
   (tree-walk exp))