datatype 'a Seq = Nil | Cons of 'a * (unit -> 'a Seq);

fun intList(n) = Cons( (n, fn(x) => x + 1), fn()=>intList(n+1) );

fun head (Cons (x, _)) = x;
fun tail (Cons (_, xs)) = xs();

fun get(n,s) = if n=0 then head(s) else get(n-1,tail(s));

fun takeN 0 (Cons(x, y)) = []
  | takeN n (Cons(x, y)) =  x::(takeN (n-1) (y()));

val z = get(10, intList(10));

val p = takeN 4 (intList(10));