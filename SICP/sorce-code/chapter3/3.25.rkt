#lang planet neil/sicp

; Exercise 3.25
; psuedocode

(define (look-up key . rest-keys)
  (define (iter-find rest-key-list curr-table)
    (let ((curr-key (car rest-key-list))
          (rest-keys (cdr rest-key-list)))
      (let ((key-finded (find-key-in-table curr-key curr-table)))
        (if key-finded
            (if (more-keys rest-keys)
                (let ((next-table (key-value key-finded)))
                  (iter-find rest-keys next-table))
                (key-value key-finded))))))
  (iter-find (cons key rest-keys)
             local-table))
              

(define (insert! value . keys)
  (define (iter-insert rest-keys-list curr-table)
    (let ((curr-key (car rest-key-list))
          (rest-keys (cdr rest-key-list)))
      (let ((key-finded (find-key-in-table curr-key curr-table)))
        (if key-finded
            (if (more-keys rest-keys)
               (let ((next-table (key-value key-finded)))
                  (iter-insert rest-keys next-table))
                (set-key-value key-finded value))
            (let ((new-table (make-new-table curr-key)))
              (add-newtable-to-table new-table curr-table)
              (if (more-keys rest-keys)
                  (iter-insert rest-keys new-table)
                  (set-key-value (car new-table))))))))
  (if (null? keys)
      (error "NO keys input")
      (iter-insert keys local-table)))
              