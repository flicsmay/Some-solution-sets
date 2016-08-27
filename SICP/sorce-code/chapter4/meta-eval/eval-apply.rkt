;#lang planet neil/sicp

; evaln and applyn

(define (evaln exp env)
  (cond ((self-evalnuating? exp) exp)
        ((variable? exp) (lookup-variable-value exp env))
        ((quoted? exp) (text-of-quotation exp))
        ((assignment? exp) (evaln-assignment exp env))
        ((definition? exp) (evaln-definition exp env))
        ((if? exp) (evaln-if exp env))
        ((lambda? exp)
         (make-procedure (lambda-parameters exp)
                         (lambda-body exp)
                         env))
        ((begin? exp) 
         (evaln-sequence (begin-actions exp) env))
        ((cond? exp) (evaln (cond->if exp) env))
        ((let? exp) (evaln (let->combination exp) env))
        ((application? exp)
         (applyn (evaln (operator exp) env)
                (list-of-values (operands exp) env)))
        (else
         (error "Unknown expression type -- evaln" exp))))

(define (applyn procedure arguments)
  (cond ((primitive-procedure? procedure)
         (applyn-primitive-procedure procedure arguments))
        ((compound-procedure? procedure)
         (evaln-sequence
           (procedure-body procedure)
           (extend-environment
             (procedure-parameters procedure)
             arguments
             (procedure-environment procedure))))
        (else
         (error
          "Unknown procedure type -- applyn" procedure))))
