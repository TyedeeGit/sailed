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

## 2. Semantics