#lang racket

(provide (struct-out column-info)
         (struct-out table)
         (struct-out and-f)
         (struct-out or-f)
         (struct-out not-f)
         (struct-out eq-f)
         (struct-out eq2-f)
         (struct-out lt-f)
         table-insert
         table-project
         table-sort
         table-select
         table-rename
         table-cross-join
         table-natural-join)

(define-struct column-info (name type) #:transparent)

(define-struct table (schema rows) #:transparent)

(define cities
  (table
   (list (column-info 'city    'string)
         (column-info 'country 'string)
         (column-info 'area    'number)
         (column-info 'capital 'boolean))
   (list (list "Wrocław" "Poland"  293 #f)
         (list "Warsaw"  "Poland"  517 #t)
         (list "Poznań"  "Poland"  262 #f)
         (list "Berlin"  "Germany" 892 #t)
         (list "Munich"  "Germany" 310 #f)
         (list "Paris"   "France"  105 #t)
         (list "Rennes"  "France"   50 #f))))

(define countries
  (table
   (list (column-info 'country 'string)
         (column-info 'population 'number))
   (list (list "Poland" 38)
         (list "Germany" 83)
         (list "France" 67)
         (list "Spain" 47))))

(define (empty-table columns) (table columns '()))

; Wstawianie
(define (table-insert row tab)
  (define (p? x) ;tworzenie predykatu
    (eval (string->symbol (string-append (symbol->string x) "?"))))
  (define (valid? row schema) ;sprawdzenie poprawnosci wiersza
    (cond [(and (null? row) (null? schema)) #t]
          [(or (null? row) (null? schema))  (error "Niewlasciwa liczba kolumn!")]
          [((p? (column-info-type (car schema))) (car row))
           (valid? (cdr row) (cdr schema))]
          [else (error "Niewlasciwy typ elementu!")]))
  (let ([check (valid? row (table-schema tab))])
         (table (table-schema tab) (cons row (table-rows tab)))))

; Projekcja
(define (table-project cols tab)
  (define (new-schema columns schema copy) ;schema z wybranymi kolumnami
    (cond [(null? columns) '()]
          [(null? schema) (error "Brak podanej kolumny")]
          [(equal? (car columns) (column-info-name (car schema)))
           (cons (car schema) (new-schema (cdr columns) copy copy))]
          [else (new-schema columns (cdr schema) copy)]))
  (define (indexes columns schema copy acc) ;indeksy wybranych kolumn
    (cond [(null? columns) '()]
          [(equal? (car columns) (column-info-name (car schema)))
           (cons acc (indexes (cdr columns) copy copy 0))]
          [else (indexes columns (cdr schema) copy (+ 1 acc))]))
  (define (new-row indexes row copy acc) ;nowy wiersza
    (cond [(null? indexes) '()]
          [(= acc (car indexes))
           (cons (car row) (new-row (cdr indexes) copy copy 0))]
          [else (new-row indexes (cdr row) copy (+ 1 acc))]))
  (let* ([schema (table-schema tab)][newschema (new-schema cols schema schema)][indx (indexes cols schema schema 0)])
    (table newschema (map (lambda (x) (new-row indx x x 0)) (table-rows tab)))))

; Sortowanie
(define (table-sort cols tab)
  (define (compare columns row1 copy1 row2 copy2 schema copy3) ;porownanie dwoch wierszy
    (cond [(null? schema) (error "Brak podanej kolumny")]
          [(null? columns) #t]
          [(equal? (car columns) (column-info-name (car schema)))
           (if (equal? (car row1) (car row2))
               (compare (cdr columns) copy1 copy1 copy2 copy2 copy3 copy3)
               (let ([type (column-info-type (car schema))])
                 (cond [(equal? type 'string) (string<? (car row1) (car row2))]
                       [(equal? type 'boolean) (and (not (car row1)) (car row2))]
                       [(equal? type 'number) (< (car row1) (car row2))]
                       [else (string<? (symbol->string (car row1)) (symbol->string (car row2)))])))]
          [else (compare columns (cdr row1) copy1 (cdr row2) copy2 (cdr schema) copy3)]))
  (define (insert columns row xs schema) ;wstawienie wiersza
    (cond [(null? xs) (cons row xs)]
          [(compare columns row row (car xs) (car xs) schema schema) (cons row xs)]
          [else (cons (car xs) (insert columns row (cdr xs) schema))]))
  (define (insertion-sort columns xs ys schema) ;sortowanie
    (if (null? xs)
        ys
        (insertion-sort columns (cdr xs) (insert columns (car xs) ys schema) schema)))
  (let ([schema (table-schema tab)])
    (table schema (insertion-sort cols (table-rows tab) null schema))))

; Selekcja
(define-struct and-f (l r))
(define-struct or-f (l r))
(define-struct not-f (e))
(define-struct eq-f (name val))
(define-struct eq2-f (name name2))
(define-struct lt-f (name val))

(define (table-select form tab)
  (define (eq-check formula row schema) ;sprawdzenie eq
    (cond [(null? schema) (error "Bledne wejscie")]
          [(equal? (eq-f-name formula) (column-info-name (car schema)))
           (equal? (car row) (eq-f-val formula))]
          [else (eq-check formula (cdr row) (cdr schema))]))
  (define (find row schema name) ;pomocnicza do eq2
    (cond [(null? schema) (error "Bledne wejscie")]
          [(equal? name (column-info-name (car schema))) (car row)]
          [else (find (cdr row) (cdr schema) name)]))
  (define (lt-check formula row schema) ;sprawdzenie lt
    (cond [(null? schema) (error "Bledne wejscie")]
          [(equal? (lt-f-name formula) (column-info-name (car schema)))
           (let ([type (column-info-type (car schema))])
             (cond [(equal? type 'string) (string<? (car row) (lt-f-val formula))]
                   [(equal? type 'boolean) (and (not (car row)) (lt-f-val formula))]
                   [(equal? type 'number) (< (car row) (lt-f-val formula))]
                   [else (string<? (symbol->string (car row)) (symbol->string (lt-f-val formula)))]))]
          [else (lt-check formula (cdr row) (cdr schema))]))
  (define (check-formula formula schema row) ;sprawdzenie formuly
    (cond [(and-f? formula) (and (check-formula (and-f-l formula) schema row)
                                 (check-formula (and-f-r formula) schema row))]
          [(or-f? formula) (or (check-formula (or-f-l formula) schema row)
                                 (check-formula (or-f-r formula) schema row))]
          [(not-f? formula) (not (check-formula (not-f-e formula) schema row))]
          [(eq-f? formula) (eq-check formula row schema)]
          [(eq2-f? formula) (equal? (find row schema (eq2-f-name formula))
                                    (find row schema (eq2-f-name2 formula)))]
          [(lt-f? formula) (lt-check formula row schema)]))
  (let ([schema (table-schema tab)])
    (table schema (filter (lambda (x) (check-formula form schema x)) (table-rows tab)))))

; Zmiana nazwy
(define (change c nc s) ;zamiana nazwy kolumny
    (cond [(null? s) (error "Brak kolumny do zmiany")]
          [(equal? c (column-info-name (car s))) (cons (column-info nc (column-info-type (car s))) (cdr s))]
          [else (cons (car s) (change c nc (cdr s)))]))

(define (table-rename col ncol tab)
  (table (change col ncol (table-schema tab)) (table-rows tab)))

; Złączenie kartezjańskie
(define (table-cross-join tab1 tab2) ;zlaczenie wierszy
  (define (join r1 r2 copy)
    (cond [(null? r1) '()]
          [(null? r2) (join (cdr r1) copy copy)]
          [else (cons (append (car r1) (car r2)) (join r1 (cdr r2) copy))]))
  (table (append (table-schema tab1) (table-schema tab2)) (join (table-rows tab1) (table-rows tab2) (table-rows tab2))))

; Złączenie
(define (table-natural-join tab1 tab2)
  (define (symbol-append name) ;dodanie 2 do symbolu
    (string->symbol (string-append (symbol->string name) "2")))
  (define (the-same schema1 schema2 copy) ;zamiana nazwy powtarzajacych sie kolumn
    (cond [(null? schema1) copy]
          [(null? schema2) (the-same (cdr schema1) copy copy)]
          [(equal? (column-info-name (car schema1)) (column-info-name (car schema2)))
           (let* ([name (column-info-name (car schema2))][new (change name (symbol-append name) copy)])
                                                   (the-same (cdr schema1) new new))]
          [else (the-same schema1 (cdr schema2) copy)]))
  (define (have-two name schema) ;sprawdzenie czy sa powtarzajace sie kolumny
    (cond [(null? schema) #f]
          [(equal? name (column-info-name (car schema))) #t]
          [else (have-two name (cdr schema))]))
  (define (selection tab schema) ;selekcja tych ktore maja takie same wartosci w powtarzajacy sie kolumnach
    (cond [(null? schema) tab]
          [(have-two (symbol-append (column-info-name (car schema))) (cdr schema))
           (selection (table-select (eq2-f (column-info-name (car schema)) (symbol-append (column-info-name (car schema)))) tab) (cdr schema))]
          [else (selection tab (cdr schema))]))
  (define (without-2 schema) ;lista bez powtorzen nazw kolumn
    (cond [(null? schema) '()]
          [(equal? #\2 (let ([s (symbol->string (column-info-name (car schema)))])
                         (string-ref s (- (string-length s) 1)))) (without-2 (cdr schema))]
          [else (cons (column-info-name (car schema)) (without-2 (cdr schema)))]))
  (let* ([new (the-same (table-schema tab1) (table-schema tab2) (table-schema tab2))]
         [tab (table-cross-join tab1 (table new (table-rows tab2)))]
         [new_tab (selection tab (table-schema tab))])
    (table-project (without-2 (table-schema new_tab)) new_tab)))
