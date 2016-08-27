#lang planet neil/sicp

(define (make-unbound! var env)
  (if (empty-environment? env)
      (error "a empty environment input")
      (let ((finded (lookup-binding-in-frame (first-frame env))))
        (if finded
            (remove-a-binding-from-frame finded (first-frame env))))))