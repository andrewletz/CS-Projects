(*  Here's a skeleton file to help you get started on Interpreter 1.
 * Original version by Geoffrey Smith - http://users.cs.fiu.edu/~smithg/
 *)

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
  | RES_FUN of (string * term)
  | RES_CLOSURE of (result * env)
  | RES_TEMP of (term * (string->result));
(*  An environment is a function string -> result.
 *  I've included code for the empty environment
 *  and code that produces the updated environment E[x : t].
 *)

exception UnboundID
exception UnJustifiedEnvironmentMatch
datatype env = Env of (string -> result)
fun emptyenvFun  (x : string) : result = raise UnboundID;
val emptyenv = Env emptyenvFun

(*  update : (string -> result) -> string -> result -> string -> result  *)
fun update (Env e) (x : string) (ty : result) y = if x = y then ty else e y

(*  Here's a partial skeleton of interp : (env * term) -> result.
    I've done the first case for you
*)
fun interp_lazy (env:env, AST_ID i)          = (case env of (Env e)=> (case e(i) of RES_TEMP(ee, enn) => interp_lazy(env, ee) | _=>RES_ERROR "Environment Error"))
  | interp_lazy (env:env, AST_NUM n)         = RES_NUM(n)
  | interp_lazy (env:env, AST_BOOL b)        = RES_BOOL(b)
  | interp_lazy (env:env, AST_FUN (i,e))     = RES_FUN(i, e)
  | interp_lazy (env:env, AST_APP (e1,e2))   = let
		val func = interp_lazy(env, e1)
	in
		case func of RES_SUCC =>
			(case interp_lazy(env, e2) of RES_NUM(n) => RES_NUM(n+1)|_=>RES_ERROR "Argument mismatch, not of type int.")
		| RES_PRED => (case interp_lazy(env, e2) of RES_NUM(n) => if n = 0 then RES_NUM(0) else RES_NUM(n-1)|_=>RES_ERROR "Argument mismatch, not of type int.")
		| RES_ISZERO => (case interp_lazy(env, e2) of RES_NUM(n)=>if n = 0 then RES_BOOL(true) else RES_BOOL(false) |_=>RES_ERROR "Argument mismatch, not of type int.")
		| RES_FUN(i,e) => (let
							val kt = RES_TEMP(e2, case env of Env v => v);
							val edd = update 
											env 
												i 
													kt;
						in
							interp_lazy(Env(edd),e)
						end)
		| _=> RES_ERROR "Argument mismatch, can't apply to non-function"
	end
  | interp_lazy (env:env, AST_SUCC)          = RES_SUCC
  | interp_lazy (env:env, AST_PRED)          = RES_PRED
  | interp_lazy (env:env, AST_ISZERO)        = RES_ISZERO
  | interp_lazy (env:env, AST_IF (e1,e2,e3)) = let
		val hyp = interp_lazy(env, e1)
	in
		case hyp of RES_BOOL(i)=>if i then interp_lazy(env, e2) else interp_lazy(env, e3)
		| _=> RES_ERROR "Argument mismatch, condition not of type bool"
  end;
  

  val test1 = AST_APP(AST_IF(AST_BOOL(true), AST_SUCC, AST_PRED), AST_NUM(3)); 
 
val test2 = AST_APP(AST_FUN("f", AST_APP(AST_FUN("x", AST_APP(AST_ID("f"), AST_ID("x"))), AST_NUM(5))), AST_FUN("z", AST_ID("x")));
 
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
			
val test4 = AST_APP(AST_FUN("y", AST_NUM(0)), 
			AST_APP(AST_FUN("x", AST_APP(AST_ID("x"), AST_ID("x"))),AST_FUN("x", AST_APP(AST_ID("x"), AST_ID("x")))));
			
			
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
						