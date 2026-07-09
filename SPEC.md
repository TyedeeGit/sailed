# Sailed Language Spec

---

## 0. How to read this document

### 0.1. Syntax
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

### 0.2. Type Ascriptions
A type ascription looks like
```
theValue: TheType
```

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

## 2. Universes
Every value has a type, but types are also values. 
So what is the type of a type?
```
3: NatSize
``` 
`NatSize` is an example of a *small* type, the most common type.
The type of small types is `universe(0)`, or more commonly known as `type`:
```
NatSize: type
```
But what is `type`'s type? It is `universe(1)`, or also known as `kind`:
```
type: kind
```
Of course, `kind`'s type based on this pattern is `universe(2)`, and so on:
```
universe(n): universe(n + 1)
```

---

## 3. Type connectives
A type connective is a way of combining simpler types into more complex types.
For example, `struct`s:
```
struct {
   x: Int32,
   y: Int32
}
```

### 3.0. Types with fields
Most of these connectives will have field descriptions like
```
{
   a: A,
   b: B,
   ...
}
```
If you have an instance of the type `x`, you should be able to access the fields:
```
x.a
```
However, field access will be limited by the semantics of the type.
Similarly, you can construct instances with:
```
.{
   a = ...,
   b = ...,
   ...
}
```
And again, valid constructions are constrained by the semantics of the type.

Implicit fields are denoted with `#` prefixes:
```
#a: A
```
These fields need not be assigned, unless the compiler can't determine a suitable 
value for that field automatically, or a default is provided. You can provide a default:
```
#a: A = ...
```
You can manually assign these fields(if you want to override the provided default or automatically
determined value, or there isn't a provided default and the value couldn't be determined 
automatically), as follows:
```
#a = ...
```

### 3.1. Structs
A value of a `struct` type is a composite of independent values, available and 
provided simultaneously.
You can create a `struct` type by using the `struct` keyword and listing the fields in a `{...}` 
block:
```
struct {
   // fields
}
```
Now, `struct`s are special in that you can have dependent field types. For example:
```
struct {
   i: NatSize,
   iBelowN: i < n
}
```
Notice how the second field's type refers to the value of the first field. We say that this is
a *dependent `struct` type*.

To make an instance, you must assign to each required field with independent values available 
simultaneously:
```
.{
   x = 3,
   y = -4
}
```
You can then access the fields simultaneously:
```
let distSq = square(point.x) + square(point.y);
```

`struct`s are dual to `couple`s.

### 3.2. Variants
A value of a `variant` type is chosen from the various fields. Similarly to `struct`s, you
use the `variant` keyword and list the fields to make a `variant` type:
```
variant {
   numberMsg: Int32,
   writtenMsg: &'Str
}
```
To make an instance, simply assign to one field:
```
.{
   numberMsg = 5
}
```
If the field is implicit, just put the field name:
```
.{
   #implicitField
}
```
You can then access the fields, but you must handle each in choosable branches:
```
match
| let n = msg.numberMsg => io.println("Recieved number: " + n.toString())
| let s = msg.writtenMsg => io.println("Recieved text: " + s)
```

`variant`s are dual to `choice`s.

### 3.3. Choices
A value of a `choice` type is an offering between the various fields.
```
choice {
   fst: () -> () moves,
   snd: () -> () moves
}
```
To make an instance, assign to each field. Unlike `struct`s, you can move the same value twice:
```
.{
   fst = () => {
      val.foo(); // moves `val`
      io.println("Picked first option!");
   },
   snd = () => {
      val.bar(); // also moves `val`
      io.println("Picked second option!");
   }
}
```
You can then access one field, but the other fields become inaccessible upon doing so:
```
choices.fst();
// CAN'T DO:
// choices.snd();
```

`choice`s are dual to `variant`s.

### 3.4. Couples
A value of a `couple` is a composite of interacting fields available simultaneously.
```
couple {
   consumer: T -> Consumed,
   producer: T
}
```
To make an instance, assign to each field. Unlike `struct`s, data is sent between fields:
```
.{
   consumer = (t) => {
      to .producer send t;
      end
   },
   producer = from .consumer recv
}
```
You can access the fields, but the way in which you access them must be independent:
```
foo(pair.consumer);
bar(pair.producer);
// CAN'T DO
// baz(pair.consumer, pair.producer)
```

`couple`s are dual to `struct`s.
