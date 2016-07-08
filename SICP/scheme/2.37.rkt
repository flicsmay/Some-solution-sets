#lang planet neil/sicp

; Exercise 2.37

; dot-product : s_vector, s_vector
; return the sums of v[i]*w[i]
(define (dot-product v w)
  (accumulate + 0 (map * v w)))


; matrix-*-vector : s_matrix, s_vector
; return the vector of r[i] = sumof m[i][j]*v[j]
(define (matric-*-vector m v)
  (map (lambda (col)
         (dot-product col v))
       m))

; transpose : s_matrix
; return the matrix n, where n[i][j] = m[j][i]
(define (transpose mat)
  (accumulate-n cons '() mat))


; matrix-*-matrix : s_matrix, s-matrix
; return the matrix of r[i][j] = sumof m[i][j]*n[j][k]
(define (matrix-*-matrix m n)
  (let ((cols (transpose n)))
    (map (lambda (row) (matric-*-vector cols row)) m)))



; accumulate-n : #operation, initial, sequence[s]
; calculate the accumulate of the given sequence[s] respectively
(define (accumulate-n op init seqs)
  (if (null? (car seqs))
      nil
      (cons (accumulate op init 
                        (map (lambda (x) (car x)) seqs))
            (accumulate-n op init
                          (map (lambda (x) (cdr x)) seqs)))))


; accumulate : #operation, initial, s_list/s_tree
; #oper to every elements in the structure together with an initial value
(define (accumulate op initial sequence)
  (if (null? sequence)
      initial
      (op (car sequence)
          (accumulate op initial (cdr sequence)))))