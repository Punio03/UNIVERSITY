#lang plait

(define-type-alias Value Number)

(define (fifth [xs : (Listof 'a)]) : 'a
  (fourth (rest xs)))

(define (sixth [xs : (Listof 'a)]) : 'a
  (fourth (rest (rest xs))))

; abstract syntax ---------------------------------------------------------

(define-type P
  (defineP [ds : (Listof D)] [e : E]))

(define-type D
  (funD [f : Symbol] [xs : (Listof Symbol)] [e : E]))

(define-type E
  (numE [n : Value])
  (varE [x : Symbol])
  (opE [e1 : E] [⊕ : OP] [e2 : E])
  (ifzE [e0 : E] [e1 : E] [e2 : E])
  (letE [x : Symbol] [e1 : E] [e2 : E])
  (callE [f : Symbol] [es : (Listof E)]))

(define-type OP
  (add) (sub) (mul) (leq))

; parse -------------------------------------------------------------------

(define (parse-P [s : S-Exp]) : P
  (if (s-exp-match? `{define {ANY ...} for ANY} s)
      (let ([ss (s-exp->list s)])
        (defineP (map parse-D (s-exp->list (second ss)))
                 (parse-E (fourth ss))))
      (error 'parse "invalid input")))

(define (parse-D [s : S-Exp]) : D
  (if (s-exp-match? `[fun SYMBOL (SYMBOL ...) = ANY] s)
      (let ([ss (s-exp->list s)])
        (funD (s-exp->symbol (second ss))
              (map s-exp->symbol (s-exp->list (third ss)))
              (parse-E (fifth ss))))
      (error 'parse "invalid input")))

(define (parse-E [s : S-Exp]) : E
  (cond
    [(s-exp-match? `NUMBER s)
     (numE (s-exp->number s))]
    [(s-exp-match? `SYMBOL s)
     (varE (s-exp->symbol s))]
    [(s-exp-match? `{ANY SYMBOL ANY} s)
     (let ([ss (s-exp->list s)])
       (opE (parse-E (first ss))
            (parse-OP (s-exp->symbol (second ss)))
            (parse-E (third ss))))]
    [(s-exp-match? `{ifz ANY then ANY else ANY} s)
     (let ([ss (s-exp->list s)])
       (ifzE (parse-E (second ss))
             (parse-E (fourth ss))
             (parse-E (sixth ss))))]
    [(s-exp-match? `{let SYMBOL be ANY in ANY} s)
     (let ([ss (s-exp->list s)])
       (letE (s-exp->symbol (second ss))
             (parse-E (fourth ss))
             (parse-E (sixth ss))))]
    [(s-exp-match? `{SYMBOL (ANY ...)} s)
     (let ([ss (s-exp->list s)])
       (callE (s-exp->symbol (first ss))
              (map parse-E (s-exp->list (second ss)))))]
    [else (error 'parse "invalid input")]))

(define (parse-OP [⊕ : Symbol]) : OP
  (cond
    [(eq? '+  ⊕) (add)]
    [(eq? '-  ⊕) (sub)]
    [(eq? '*  ⊕) (mul)]
    [(eq? '<= ⊕) (leq)]
    [else (error 'parse "unknown operator")]))

; eval --------------------------------------------------------------------

(define-type Binding
  (bind [name : Symbol]
        [val : Value]))

;; environments

(define-type-alias Env (Listof Binding))

(define mt-env empty)

(define (extend-env [env : Env] [x : Symbol] [v : Value]) : Env
  (cons (bind x v) env))

(define (lookup-env [n : Symbol] [env : Env]) : Value
  (type-case Env env
    [empty (error 'lookup "unbound variable")]
    [(cons b rst-env) (cond
                        [(eq? n (bind-name b)) (bind-val b)]
                        [else (lookup-env n rst-env)])]))

(define-type-alias Defs (Listof D))

(define (lookup-defs [n : Symbol] [defs : Defs]) : D
  (type-case Defs defs
    [empty (error 'lookup "unbound definition")]
    [(cons d rst-defs) (cond
                        [(eq? n (funD-f d)) d]
                        [else (lookup-defs n rst-defs)])]))

; primitive operations

(define (leq->proc) : (Value Value -> Value)
  (λ (v1 v2) (if (<= v1 v2) 0 1)))

(define (op->proc [⊕ : OP]) : (Value Value -> Value)
  (type-case OP ⊕
    [(add) +]
    [(sub) -]
    [(mul) *]
    [(leq) (leq->proc)]))

; evaluation functions

(define (eval-P [p : P]) : Value
  (eval-E (defineP-e p) mt-env (defineP-ds p)))

(define (eval-E [e : E] [env : Env] [defs : Defs]) : Value
  (type-case E e
    [(numE n) n]
    [(varE x) (lookup-env x env)]
    [(opE e1 ⊕ e2)
     ((op->proc ⊕) (eval-E e1 env defs) (eval-E e2 env defs))]
    [(ifzE e0 e1 e2)
     (if (= 0 (eval-E e0 env defs))
         (eval-E e1 env defs)
         (eval-E e2 env defs))]
    [(letE x e1 e2)
     (let ([v1 (eval-E e1 env defs)])
       (eval-E e2 (extend-env env x v1) defs))]
    [(callE f es)
     (let ([d (lookup-defs f defs)])
       (eval-E (funD-e d) (map2 (λ (x y) (bind x (eval-E y env defs))) (funD-xs d) es) defs))]))
     
(define (run [s : S-Exp]) : Value
  (eval-P (parse-P s)))
