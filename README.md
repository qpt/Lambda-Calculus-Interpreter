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
0' = (Lx.x)
1' = (Lx.x(Lx.(Ly.y))(Lx.x))

These are Boolean S-Expressions. Should not be confused with T/F, which aren't S-Expressions!
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

null : M -> M
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Null = (Lx.(x (Lx.(Ly.(Lz.z)))T0'1'))
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

if : M^3 -> M
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
If = (Lx.(Ly.(Lz.(Null x)Tyz)))
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

false : M -> M (always returns `0'` if halts)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
False = (Lx.x (Lx.(Ly.(Lz.0')))T1'F)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

atom : M -> M
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Atom  = (Lx.If(Null x)1'(False(xT)))
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

not : M -> M (same as null)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Not = (Lx.(x (Lx.(Ly.(Lz.z)))T0'1'))
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

and : M^2 -> M
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
And = (Lx.(Ly.If(Null x) x y))
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

or : M^2 -> M
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Or = (Lx.(Ly.If(Null x) y x))
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

car : M -> M
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Car = (Lx.If(Atom x) Omega (xT))
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

cdr : M -> M
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Cdr = (Lx.If(Atom x) Omega (xF))
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

cons : M^2 -> M
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Cons = (Lx.(Ly. (If(And(Atom y)(Null(Null y)))Omega(If x (Lz.zxy) (Lz.zxy)))))
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~