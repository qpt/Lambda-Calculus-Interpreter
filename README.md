# Lambda-Calculus-Interpreter
Parses pure lambda calculus expressions and reduces them to B-NF (if exists)


# Syntax
  
  variables: ^[a-z][0-9]*$

  λx.x:   Lx.x

# Examples

  (Lx.x)y

  (Lx.xx)(Lx.xx)

  Lf.(Lx.f(xx))(Lx.f(xx))


# References

Loop
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Ω = ((Lx.xx)(Lx.xx))
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Recursion
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Y = (Lf.(Lx.f(xx))(Lx.f(xx)))
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

T/F
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
T = (Lx.(Ly.x))
F = (Lx.(Ly.y))
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


M = S-expressions and Loop


Lists : M^k
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
[]                = (Lx.x)
[t1]              = (Lx.xt1(Lx.x))
[t1, t2]          = (Lx.xt1(Lx.xt2(Lx.x)))
[t1, t2, t3]      = (Lx.xt1(Lx.xt2(Lx.xt3(Lx.x))))
...
[t1, t2, ..., tk] = (Lx.xt1 [t2, t3, ..., tk])

Where t1, t2, ...,tk should be replaced ONLY by S-expressions (Lists, Numbers, Booleans) or Loop, otherwise functions defined below may produce nonsense.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Numbers : M
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
0' = []             = (Lx.x)
1' = [F]            = (Lx.x(Lx.(Ly.y))(Lx.x))
2' = [F, F]         = (Lx.x(Lx.(Ly.y))(Lx.x(Lx.(Ly.y))(Lx.x)))
3' = [F, F, F]      = (Lx.x(Lx.(Ly.y))(Lx.x(Lx.(Ly.y))(Lx.x(Lx.(Ly.y))(Lx.x))))
...
n' = [F, F, ..., F] = (Lx.x(Lx.(Ly.y)) (n-1)' )
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Booleans : M
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
False = 0' = (Lx.x)
True  = 1' = (Lx.x(Lx.(Ly.y))(Lx.x))

These are Boolean S-Expressions. Should not be confused with T/F, which aren't S-Expressions!
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

null : M -> M
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Null = (Lx.(x (Lx.(Ly.(Lz.z)))      T        0'              1'          ))
Null = (Lx.(x (Lx.(Ly.(Lz.z))) (Lx.(Ly.x)) (Lx.x) (Lx.x(Lx.(Ly.y))(Lx.x))))
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

if : M^3 -> M
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
If = (Lx.(Ly.(Lz.((((                              Null                                   x)      T     ) y) z))))
If = (Lx.(Ly.(Lz.(((((Lx.(x (Lx.(Ly.(Lz.z))) (Lx.(Ly.x)) (Lx.x) (Lx.x(Lx.(Ly.y))(Lx.x)))) x) (Lx.(Ly.x))) y) z))))
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

false : M -> M (always returns 0' if halts)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
False = (Lx.((((x (Lx.(Ly.(Lz.   0'   ))))      T     )             1'         )       F    ))
False = (Lx.((((x (Lx.(Ly.(Lz. (Lx.x) )))) (Lx.(Ly.x))) (Lx.x(Lx.(Ly.y))(Lx.x))) (Lx.(Ly.y))))
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

atom : M ->
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Atom  = (Lx.                                                If                                                             (                                     Null                            x)              1'         (                              False                                                    (x       T     )))
Atom  = (Lx. (Lx.(Ly.(Lz.(((((Lx.(x (Lx.(Ly.(Lz.z))) (Lx.(Ly.x)) (Lx.x) (Lx.x(Lx.(Ly.y))(Lx.x)))) x) (Lx.(Ly.x))) y) z)))) ((Lx.(x (Lx.(Ly.(Lz.z))) (Lx.(Ly.x)) (Lx.x) (Lx.x(Lx.(Ly.y))(Lx.x)))) x) (Lx.x(Lx.(Ly.y))(Lx.x)) ((Lx.((((x (Lx.(Ly.(Lz. (Lx.x) )))) (Lx.(Ly.x))) (Lx.x(Lx.(Ly.y))(Lx.x))) (Lx.(Ly.y)))) (x (Lx.(Ly.x)) )))
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~