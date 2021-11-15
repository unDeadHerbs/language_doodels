(use-modules (system base pmatch))
(define empty-env '())
(define remember_as_in
  (lambda (var val env)
    `((,var . ,val) . ,env)))
(define lookup
  (lambda (x env)
    (pmatch env
            [() (error 'lookup
                       (format #t "unbound variable ~s" x))]
            [((,V . ,v) . ,env^) (guard (eq? V x)) v]
            [(,b . ,env^) (lookup x env^)])))
(define rep*
  (lambda (old new tree)
    (pmatch tree
            [,s (guard (not (pair? s)))
                (if (eq? s old) new s)]
            [() '()]
            [(,a . ,d)
             `(,(rep* old new a) . ,(rep* old new d))])))
(define elmr ; expr -> bindings -> (expr bindings)
  (lambda (expr bindings)
    (let ([old_scope (lambda (v) (cons v bindings))]
          [INTERMEDIATE (cons expr bindings)])
      (pmatch expr
              ;; numbers
              [,n (guard (number? n)) INTERMEDIATE]
              [(P ,n)
               (let ([num (car (elmr n bindings))])
                 (old_scope (- num 1)))]
              [(* ,a ,b)
               (old_scope
                (* (car (elmr a bindings))
                   (car (elmr b bindings))))]
              [(zero? ,n)
               (old_scope
                (zero? (car (elmr n bindings))))]
              ;; Temporary Primitives
              [(if ,c ,t ,f)
               (if (car (elmr c bindings))
                   (elmr t bindings)
                   (elmr f bindings))]
              ;; Quote
              [(q ,x) (old_scope x)]
              ;; variable lookup <- Major Un-Lazy-ing Calculation Point
              [,x (guard (symbol? x))
                  (elmr (lookup x bindings) bindings)]
              ;; lazy macro expansion
              [(m ,p ,b) INTERMEDIATE]
              [((m ,p ,b) ,a)
               (let* ([param (car (elmr p bindings))]
                      [extended_bindings (remember_as_in param a bindings)])
                 (elmr b extended_bindings))]
              ;; lazy lambda expansion
              ;; Alpha rename to a gensym, then be a macro.
              [(l ,p ,b)
               (let* ([s (gensym)]
                      [p^ (car (elmr p bindings))]
                      [b^ (rep* p^ s b)])
                 (old_scope `(m (q ,s) ,b^)))]
              ;; left left recursion
              [(,s ,a) (guard (symbol? s))
               (let* ([S (elmr s bindings)]
                      [f (car S)]
                      [bind (cdr S)])
                 (elmr `(,f ,a) bind))]
              [(,e ,a) (let* ([t (gensym)]
                              [extended_bindings (remember_as_in t e bindings)])
                         (elmr `(,t ,a) extended_bindings))]
              ;; Error case, just show the state
              [else `(HALT ,expr ,bindings)]))))
(define elm ;eval-lazy-lambda-macro
  (lambda (expr)
    (let ([V (elmr expr empty-env)])
      (if (eq? 'HALT (car V))
          V
          (car V)))))
