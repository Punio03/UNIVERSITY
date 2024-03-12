#lang racket
(require data/heap)
(provide sim? wire?
         (contract-out
          [make-sim        (-> sim?)]
          [sim-wait!       (-> sim? positive? void?)]
          [sim-time        (-> sim? real?)]
          [sim-add-action! (-> sim? positive? (-> any/c) void?)]
          [make-wire       (-> sim? wire?)]
          [wire-on-change! (-> wire? (-> any/c) void?)]
          [wire-value      (-> wire? boolean?)]
          [wire-set!       (-> wire? boolean? void?)]
          [bus-value (-> (listof wire?) natural?)]
          [bus-set!  (-> (listof wire?) natural? void?)]
          [gate-not  (-> wire? wire? void?)]
          [gate-and  (-> wire? wire? wire? void?)]
          [gate-nand (-> wire? wire? wire? void?)]
          [gate-or   (-> wire? wire? wire? void?)]
          [gate-nor  (-> wire? wire? wire? void?)]
          [gate-xor  (-> wire? wire? wire? void?)]
          [wire-not  (-> wire? wire?)]
          [wire-and  (-> wire? wire? wire?)]
          [wire-nand (-> wire? wire? wire?)]
          [wire-or   (-> wire? wire? wire?)]
          [wire-nor  (-> wire? wire? wire?)]
          [wire-xor  (-> wire? wire? wire?)]
          [flip-flop (-> wire? wire? wire? void?)]))

; sim ------------------------------------------------------

(struct sim
  ([time        #:mutable]
   [event-queue #:mutable]))

(define (make-sim)
  (sim 0 (make-heap (λ (pair1 pair2) (<= (cdr pair1) (cdr pair2))))))

(define (sim-wait! sim duration)
  (let ([event-queue    (sim-event-queue sim)]
        [new-time (+ duration (sim-time sim))])
    (unless (= 0 (heap-count event-queue))
      (let* ([event (heap-min event-queue)]
             [event-time       (cdr event)]
             [event-action     (car event)])
        (unless (< new-time event-time)
          (set-sim-time! sim event-time)
          (event-action)
          (heap-remove! event-queue event)
          (sim-wait! sim (- new-time event-time)))
        (set-sim-time! sim new-time)))
    (set-sim-time! sim new-time)))
      
(define (sim-add-action! sim delay action)
  (let ([event-time (+ (sim-time sim) delay)])
    (heap-add! (sim-event-queue sim) (cons action event-time))))

; wire -----------------------------------------------------

(struct wire
  ([sim              ]
   [value   #:mutable]
   [actions #:mutable]))

(define (make-wire sim)
  (wire sim #f '()))

(define (wire-on-change! wire action)
  (set-wire-actions! wire (cons action (wire-actions wire)))
  (action))

(define (wire-set! wire value)
  (unless (equal? value (wire-value wire))
      (set-wire-value! wire value)
      (for-each (λ (action) (action)) (wire-actions wire))))

; bus ------------------------------------------------------

(define (bus-set! wires value)
  (match wires
    ['() (void)]
    [(cons w wires)
     (begin
       (wire-set! w (= (modulo value 2) 1))
       (bus-set! wires (quotient value 2)))]))

(define (bus-value ws)
  (foldr (λ (w value) (+ (if (wire-value w) 1 0) (* 2 value)))
         0
         ws))

; gate-operator --------------------------------------------

; Próbowałem zrobić szablon funkcji dla bramek z operatorami 2-argumentowymi.
; Niestety limity czasu nas tutaj ograniczają.

(define (gate-not out in)
  (let ([action (λ () (wire-set! out (not (wire-value in))))])
    (wire-on-change! in (λ () (sim-add-action! (wire-sim out) 1 action)))))

(define (gate-and out in1 in2)
  (let ([action (λ () (sim-add-action! (wire-sim out) 1
                                       (λ () (wire-set! out (and (wire-value in1) (wire-value in2))))))])
    (wire-on-change! in1 action)
    (wire-on-change! in2 action)))

(define (gate-nand out in1 in2)
  (let ([action (λ () (sim-add-action! (wire-sim out) 1
                                       (λ () (wire-set! out (nand (wire-value in1) (wire-value in2))))))])
    (wire-on-change! in1 action)
    (wire-on-change! in2 action)))

(define (gate-or out in1 in2)
  (let ([action (λ () (sim-add-action! (wire-sim out) 1
                                       (λ () (wire-set! out (or (wire-value in1) (wire-value in2))))))])
    (wire-on-change! in1 action)
    (wire-on-change! in2 action)))

(define (gate-nor out in1 in2)
  (let ([action (λ () (sim-add-action! (wire-sim out) 1
                                       (λ () (wire-set! out (nor (wire-value in1) (wire-value in2))))))])
    (wire-on-change! in1 action)
    (wire-on-change! in2 action)))

(define (gate-xor out in1 in2)
  (let ([action (λ () (sim-add-action! (wire-sim out) 2
                                       (λ () (wire-set! out (xor (wire-value in1) (wire-value in2))))))])
    (wire-on-change! in1 action)
    (wire-on-change! in2 action)))

; wire-operator --------------------------------------------------

(define (wire-not in)
  (let ([out (make-wire (wire-sim in))])
    (gate-not out in)
    out))

(define (wire-template in1 in2 gate-op)
  (let ([out (make-wire (wire-sim in1))])
    (gate-op out in1 in2)
    out))

(define (wire-and in1 in2)
  (wire-template in1 in2 gate-and))

(define (wire-nand in1 in2)
  (wire-template in1 in2 gate-nand))

(define (wire-or in1 in2)
  (wire-template in1 in2 gate-or))

(define (wire-nor in1 in2)
  (wire-template in1 in2 gate-nor))

(define (wire-xor in1 in2)
  (wire-template in1 in2 gate-xor))

; flip-flop ------------------------------------------------

(define (flip-flop out clk data)
  (define sim (wire-sim data))
  (define w1  (make-wire sim))
  (define w2  (make-wire sim))
  (define w3  (wire-nand (wire-and w1 clk) w2))
  (gate-nand w1 clk (wire-nand w2 w1))
  (gate-nand w2 w3 data)
  (gate-nand out w1 (wire-nand out w3)))