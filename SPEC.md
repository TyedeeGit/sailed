# Sailed Language Spec

---

## 1. Design Principles
1. **Expressive safety.** You can express essentially any interface using the type
   system, and the compiler ensures the interface is used safely. Safety is not
   sacrificed for convenience.
2. **Theory first.** The language is built around theory, not the other way around.
   Complexity lives in the type theory, not in ad-hoc syntax or special cases.
3. **Canonicity.** There is always exactly one best way to do something, and where
   enforceable, that way is the only way.
4. **Uniformity.** Analogous things look similar syntactically.

A consequence of *theory first* worth internalizing: the language deliberately moves
complexity from syntax into semantics. Expect a small keyword set and a demanding type
system. That is the intended shape, not an accident.

---

## 2. Lexical surface

### 2.1 Reserved keywords
```
let unquote send where with decl impl comptime runtime as super root
```

### 2.2 Contextual keywords
```
complete incomplete exit
```