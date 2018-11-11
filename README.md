# Lambda-Calculus-Interpreter
Parses pure lambda calculus expressions and reduces them to B-NF (if exists)


# Syntax
  
  variables: [a-z]
  λx.x:   Lx.x

# Examples

  (Lx.x)y
  (Lx.xx)(Lx.xx)
  Lf.(Lx.f(xx))(Lx.f(xx))