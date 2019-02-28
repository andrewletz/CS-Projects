Control.Print.printDepth := 100;

datatype typ = VAR of string | INT | BOOL | ARROW of typ * typ

(*  Convert a typ to a string, using as few parentheses as possible.  *)

fun typ2str (VAR a)		= "'" ^ a
|   typ2str INT			= "int"
|   typ2str BOOL		= "bool"
|   typ2str (ARROW(t1 as ARROW(_, _), t2)) =	(*  the tricky bit  *)
      "(" ^ typ2str t1 ^ ") -> " ^ typ2str t2
|   typ2str (ARROW(t1, t2))	= typ2str t1 ^ " -> " ^ typ2str t2


(*  An environment is a function string -> typ.
 *  I've included code for the empty environment
 *  and code that produces the updated environment E[x : t].
 *)

exception UnboundID

type env = (string -> typ)

fun emptyenv (x : string) : typ = raise UnboundID

(*  update : (string -> typ) -> string -> typ -> string -> typ  *)

fun update E (x : string) (ty : typ) y = if x = y then ty else E y 

(* A term datatype with typed function arguments to allow type checking *)
datatype term
  = AST_ID of string
  | AST_NUM of int
  | AST_BOOL of bool
  | AST_FUN of (string * typ * term)
  | AST_APP of (term * term)
  | AST_SUCC
  | AST_PRED
  | AST_ISZERO
  | AST_IF of (term * term * term)

exception Unimplemented
exception TypeError

(*
 *  I have included the code for AST_NUM and AST_IF; you must complete
 *  the other cases!
 *)

(* typeOf : env -> term -> typ *)
fun typeOf env (AST_ID s) = env(s)
  | typeOf env (AST_NUM n) = INT
  | typeOf env (AST_BOOL b) = BOOL
  | typeOf env (AST_FUN (i,t,e)) = 
    let val env = update env i t
        val t1 = typeOf env e
    in
        ARROW(t, t1)
    end
  | typeOf env (AST_APP (e1,e2)) =
    let val t1 = typeOf env e1
        val t2 = typeOf env e2
    in
        case t1 of
            ARROW(t_1, t_2) => if t_1 = t2 then t_2 else raise TypeError
            | _ => raise TypeError
    end
  | typeOf env AST_SUCC = ARROW(INT, INT)
  | typeOf env AST_PRED = ARROW(INT, INT)
  | typeOf env AST_ISZERO = ARROW(INT, BOOL)
  | typeOf env (AST_IF (e1,e2,e3)) =
    let val t1 = typeOf env e1
        val t2 = typeOf env e2
        val t3 = typeOf env e3
    in
        case (t1 = BOOL) andalso (t2 = t3) of
            true => t3
          | false => raise TypeError
    end

(*
Some sample functions translated into abstract syntax for you to test
your typechecker on:
*)

(* fn (f : a -> a) => fn (x : a) => f (f x) *)
val test1 = AST_FUN("f", ARROW(VAR "a", VAR "a"),
                AST_FUN("x", VAR "a",
                    AST_APP(AST_ID "f",
                        AST_APP(AST_ID "f", AST_ID "x"))));

(* fn (f : 'b -> 'c) => fn (g : 'a -> 'b) => fn (x : 'a) => f (g x) '*)
val test2 = AST_FUN("f", ARROW(VAR "b", VAR "c"),
                AST_FUN("g", ARROW(VAR "a", VAR "b"),
                    AST_FUN("x", VAR "a",
                        AST_APP(AST_ID "f",
                            AST_APP(AST_ID "g", AST_ID "x")))));

(* (* fn (b : bool) => if b then 1 else 0 *) *)
val test3 = AST_FUN("b", BOOL,
                AST_IF(AST_ID "b", AST_NUM 1, AST_NUM 0));


(* feel free to write your own test expressions! *)
val tst1 = typeOf emptyenv test1;

val tst2 = typeOf emptyenv test2;

val tst3 = typeOf emptyenv test3;