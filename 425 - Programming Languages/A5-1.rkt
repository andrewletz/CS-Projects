#lang racket
(require racket/match)
(define interp
  (lambda (e)
    (match e
      [(list '+ x y) (+ (interp x) (interp y))]
      [(list '* x y) (* (interp x) (interp y))]
      [x (if (number? x) x (error "Error: invalid E"))]
      )))

(define TR
  (lambda (e)
    (match e
      [(list '+ x y) (quasiquote (* (unquote (TR x)) (unquote (TR y))))]
      [(list '* x y) (quasiquote (+ (unquote (TR x)) (unquote (TR y))))]
      [x (if (number? x) (quasiquote (unquote x)) (error "Error: invalid E"))]
      )))