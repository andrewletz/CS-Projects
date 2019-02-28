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
      [(list '+ x y) `(* ,(TR x) ,(TR y))]
      [(list '* x y) `(+ ,(TR x) ,(TR y))]
      [x (if (number? x) x (error "Error: invalid E"))]
      )))