;#lang planet neil/sicp

; conjoin and disjoin

(define (conjoin conjuncts frame-stream)
   (if (empty-conjunction? conjuncts)
       frame-stream
       (conjoin (rest-conjuncts conjuncts)
                (qeval (first-conjunct conjuncts)
                       frame-stream))))

(define (disjoin disjuncts frame-stream)
   (if (empty-disjunction? disjuncts)
       the-empty-stream
       (interleave-delayed
        (qeval (first-disjunct disjuncts) frame-stream)
        (delay (disjoin (rest-disjuncts disjuncts)
                        frame-stream)))))