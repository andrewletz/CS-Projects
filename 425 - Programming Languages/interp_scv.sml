(*  Here's a skeleton file to help you get started on Interpreter 1.
 * Original version by Geoffrey Smith - http://users.cs.fiu.edu/~smithg/
 *)
Control.Print.printDepth := 100;

datatype term
  = AST_ID of string
  | AST_NUM of int
  | AST_BOOL of bool
  | AST_FUN of (string * term)
  | AST_APP of (term * term)
  | AST_SUCC
  | AST_PRED
  | AST_ISZERO
  | AST_IF of (term * term * term);

datatype env = Env of (string -> result)
  and result
  = RES_ERROR of string
  | RES_NUM   of int
  | RES_BOOL  of bool
  | RES_SUCC
  | RES_PRED
  | RES_ISZERO
  | RES_CLOSURE   of (env * string * term);

(*  An environment is a function string -> result.
 *  I've included code for the empty environment
 *  and code that produces the updated environment E[x : t].
 *)

exception UnboundID

fun emptyenvFun  (x : string) : result = raise UnboundID;
val emptyenv = Env emptyenvFun

(*  update : (string -> result) -> string -> result -> string -> result  *)
fun update (Env e) (x : string) (ty : result) y = if x = y then ty else e y

(*  Here's a partial skeleton of interp : (env * term) -> result.
    I've done the first case for you
*)
fun interp (env, AST_NUM n)         = RES_NUM(n)
  | interp (env, AST_BOOL b)        = RES_BOOL(b)
  | interp (env, AST_FUN (i,e))     = RES_CLOSURE(env, i, e)
  | interp (env, AST_APP (e1,e2))   = let val v1 = interp(env, e1)
                                          val v2 = interp(env, e2)
                                      in
                                        case (v1, v2) of 
                                          (RES_SUCC, RES_NUM n) => RES_NUM(n + 1)
                                          | (RES_PRED, RES_NUM n) => if n = 0 then RES_NUM(0) else RES_NUM(n - 1)
                                          | (RES_ISZERO, RES_NUM n) => if n = 0 then RES_BOOL(true) else RES_BOOL(false)
                                          | (RES_CLOSURE(env2, name, body), applicant) => let val env2 = Env(update env2 name applicant) in interp(env2, body) end
                                          | (_, _) => RES_ERROR("Invalid function application")
                                      end
  | interp (env, AST_SUCC)          = RES_SUCC
  | interp (env, AST_PRED)          = RES_PRED
  | interp (env, AST_ISZERO)        = RES_ISZERO
  | interp (env, AST_IF (e1,e2,e3)) = let val v1 = interp(env, e1)
                                      in
                                        case v1 of
                                          RES_BOOL(i) => if i then interp(env, e2) else interp(env, e3)
                                          | _ => RES_ERROR "If condition not of type bool"
                                      end
  | interp (env, AST_ID i)          = case env of Env(f) => f(i);

val test1 = AST_APP(AST_IF(AST_BOOL(true), AST_SUCC, AST_PRED), AST_NUM(3)); 

 (*
 If dynamic scope: 5
 If static scope: Error
 *) 
val test2 = AST_APP(AST_FUN("f", AST_APP(AST_FUN("x", AST_APP(AST_ID("f"), AST_ID("x"))), AST_NUM(5))), AST_FUN("z", AST_ID("x")));

(*
  If dynamic scope: 1
  If static scope: 0

*) 
val test3 = AST_APP(
        AST_FUN("x", 
          AST_APP(
            AST_FUN("f", 
              AST_APP(
                AST_FUN("x", 
                  AST_APP(AST_ID("f"), AST_NUM(3))
                )
              , AST_NUM(1)
              )
            )
          ,AST_FUN("y", AST_ID("x"))
          )
        ), 
      AST_NUM(0));   

(*
  If lazy: Returns 0
  If eager: Loops to infinity
*) 
val test4 = AST_APP(AST_FUN("y", AST_NUM(0)), 
      AST_APP(AST_FUN("x", AST_APP(AST_ID("x"), AST_ID("x"))),AST_FUN("x", AST_APP(AST_ID("x"), AST_ID("x")))));    

(*
  If static: 42
  If dynamic: 1
*)
val test5 = AST_APP(AST_FUN("z", 
        AST_APP(AST_FUN("x",
            AST_APP(AST_FUN("f",
              AST_APP(AST_FUN("x",
                AST_APP(AST_FUN("z",
                  AST_APP(AST_ID("f"), AST_NUM(3))
                ), AST_NUM(0))
              ),AST_NUM(1))
            ),AST_FUN("y", AST_ID("x")))),
          AST_APP(AST_SUCC, AST_ID("z"))
        )),AST_NUM(41));      


val tst1 = interp(emptyenv, test1);
(*val tst2 = interp(emptyenv, test2);*)
val tst3 = interp(emptyenv, test3);
(*val tst4 = interp(emptyenv, test4);*)
val tst5 = interp(emptyenv, test5);

(*should give true*)
val tst6 = interp(emptyenv, AST_APP(AST_FUN("x", AST_APP(AST_ISZERO, AST_ID("x"))), AST_NUM(0)));