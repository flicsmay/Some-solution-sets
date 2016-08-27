#lang planet neil/sicp

(define (lookup-variable-value var env)
  (if (empty-environment? env)
      (error "look for a unbound variable -- LOOKUP" var)
      (let ((binding (lookup-binding-in-frame var 
                                              (first-frame env))))
        (if binding
            (binding-val binding)
            (lookup-variable-value var (enclosing-environment env))))))

(define (extend-environment vars vals base-env)
  (if (not (= (length vars) (length vals)))
      (error "dismatch between vars and vals" vars vals)
      (adjoin-frame-to-env (make-frame vars vals) base-env)))

(define (define-variable var val env)
  (if (empty-environment? env)
      (error "a empty environment input")
      (add-binding-into-frame (make-binding var val) (first-frame env))))

(define (set-variable-value! var val env)
  (if (empty-environment? env)
      (error "look for a unbound variable -- LOOKUP" var)
      (let ((binding (lookup-binding-in-frame var
                                              (first-frame env))))
        (if binding
            (set-binding-val binding)
            (set-variable-value! var val (enclosing-environment env))))))