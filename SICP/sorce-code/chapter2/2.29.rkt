#lang planet neil/sicp

; Exercise 2.29

; make-mobile : s_list, s_list (rec)
(define (make-mobile left right)
  (cons left right));list

; make-branch : int, s_list
(define (make-branch length structure)
  (cons length structure));list

; left-branch : s_tree(list)
; Selector
(define (left-branch branch)
  (car branch))

; right-branch : s_tree(list)
; Selector
(define (right-branch branch)
  (cdr branch)); list cadr

; branch-length : s_list
; return the length of given branch
(define (branch-length branch)
  (car branch))

; branch-structure : s_list
; return the structure of given branch
(define (branch-structure branch)
  (cdr branch)); list cadr

; branch-weigth : s_list
; returun the 

; total-weigth : s_tree
; return the total weigth of a given branch
(define (total-weigth branch)
  (let ((left-is-branch? (is-a-branch? (left-branch branch)))
        (right-is-branch? (is-a-branch? (right-branch branch))))
    (cond (left-is-branch? ; if left is a branch then right must be a branch
           (+ (total-weigth (left-branch branch))
              (total-weigth (right-branch branch))))
          (right-is-branch?
           (total-weigth (right-branch branch)))
          (else
           (branch-structure branch)))))

; is-a-branch : s_list
; return TRUE if the given list is a branch
(define (is-a-branch? branch)
  (pair? branch))

; torque-branch : s_list
; return the torque of a given branch
(define (torque-branch branch)
  (* (branch-length branch)
     (total-weigth branch)))

; balanced? : s_tree
; return TRUE if the given branch IS balanced
(define (balanced? branch)
   (let ((left (left-branch branch))
         (right (right-branch branch))
         (left-is-branch? (is-a-branch? (left-branch branch)))
         (right-is-branch? (is-a-branch? (right-branch branch))))
     (cond (left-is-branch?
            ; if left is a branch then right must be a branch
            (and (balanced? left)
                 (balanced? right)
                 (= (torque-branch left)
                    (torque-branch right))))
           (right-is-branch?
            (balanced? right))
           (else; if branch is a single branch
            #t))))
