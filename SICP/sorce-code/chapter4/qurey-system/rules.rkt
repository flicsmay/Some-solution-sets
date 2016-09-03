;#lang planet neil/sicp

; rules

(define (apply-rules pattern frame)
   (stream-flatmap (lambda (rule)
                     (apply-a-rule rule pattern frame))
                   (fetch-rules pattern frame)))

(define (apply-a-rule rule query-pattern query-frame)
   (let ((clean-rule (rename-variables-in rule)))
     (let ((unify-result
            (unify-match query-pattern
                         (conclusion clean-rule)
                         query-frame)))
       (if (eq? unify-result 'failed)
           the-empty-stream
           (qeval (rule-body clean-rule)
                  (singleton-stream unify-result))))))


(define THE-RULES the-empty-stream)
(define (fetch-rules pattern frame)
   (if (use-index? pattern)
       (get-indexed-rules pattern)
       (get-all-rules)))
 (define (get-all-rules) THE-RULES)
 (define (get-indexed-rules pattern)
   (stream-append
    (get-stream (index-key-of pattern) 'rule-stream)
    (get-stream '? 'rule-stream)))

(define (add-rule-or-assertion! assertion)
   (if (rule? assertion)
       (add-rule! assertion)
       (add-assertion! assertion)))

(define (add-rule! rule)
   (store-rule-in-index rule)
   (let ((old-rules THE-RULES))
     (set! THE-RULES (cons-stream rule old-rules))
     'ok))

(define (store-rule-in-index rule)
   (let ((pattern (conclusion rule)))
     (if (indexable? pattern)
         (let ((key (index-key-of pattern)))
           (let ((current-rule-stream
                  (get-stream key 'rule-stream)))
             (put key
                  'rule-stream
                  (cons-stream rule
                               current-rule-stream)))))))