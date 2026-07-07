# Sailed Language Spec

---

## 0. How to read this document
Syntactic constructs will use a regex-like notation, for example:
```
binding ::= (mods: let-modifiers) "let" (denoter: pattern) "=" (denotee: expression)
```
You can read this as saying:
- A `binding` is
   - a `let-modifiers`, called `mods`
   - followed by "`let`"
   - followed by a `pattern`, called `denoter`
   - followed by "`=`"
   - followed by an `expression`, called `denotee`

So, in the example:
- `pub let x = f(y)`
   - `mods` is "`pub`"
   - `denoter` is "`x`"
   - `denotee` is "`f(y)`"

---

## 1. Design principles
1. **Expressive safety.** You can express essentially any interface using the type
   system, and the compiler ensures the interface is used safely. Safety is not
   sacrificed for convenience.
2. **Theory first.** The language is built around theory, not the other way around.
   Complexity lives in the type theory, not in ad-hoc syntax or special cases.
3. **Canonicity.** There is always exactly one best way to do something, and where
   enforceable, that way is the only way.
4. **Uniformity.** Analogous things look similar syntactically.

Expect demanding semantics and a demanding type system to match. 
That is the intended shape, not an accident.

---

## 2. Lexical surface

### 2.1 Reserved keywords
```
let unquote send where with decl impl comptime runtime as super
struct 
```

### 2.2 Contextual keywords
```
complete incomplete exit
```

## 3. Core syntax

```
expression ::=
   scoped-identifier
|  application
|  block
|  share
|  borrow
|  func-cons
|  alg-cons
|  
|  "type"
|  func-type
|  alg-type
|  share-type
|  borrow-type
|  indirect-type

scoped-identifier ::= sep-list(identifier, "::")

statement ::= (
   expression
|  binding
) ";"

binding ::= (mods: let-modifiers) "let" (denoter: expression) "=" (denotee: expression)

application ::= (func: scoped-identifier) "(" (
   args: for (n: nat), sep-list(expression, ",", n)
) ")"

func-type ::= "(" (args: nonempty-sep-list()) ")" "->"


items: nonempty-sep-list(part: symbol, sep: symbol, pn: nat) ::= 
   for i in 0..pn repeat ((items[i]: part) sep)
   (items[pn]: part) sep?

items: nonempty-unambig-sep-list(part: symbol, sep: symbol, pn: nat) ::=
   if pn == 0 then (items[0]: part) sep
|  else nonempty-sep-list(part, sep, pn)

sep-list(part: symbol, sep: symbol, n: nat) ::= 
   if n == 0 then "" 
|  if n == pn + 1 then nonempty-sep-list(part, sep, pn)

unambig-sep-list(part: symbol, sep: symbol, n: nat) ::=
   if n == 0 then "" 
|  if n == pn + 1 then nonempty-unambig-sep-list(part, sep, pn)
```

