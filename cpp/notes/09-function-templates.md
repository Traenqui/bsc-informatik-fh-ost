# Modern and Lucid C++ for Professional Programmers – Week 9: Function Templates

## Overview

* **Topic of this unit:** Function templates, template argument deduction, variadic templates, concepts, and common pitfalls 
* **Lecturers:** Thomas Corbat, Felix Morgner 
* **Learning objectives:**

  * Explain the difference between Java generics and C++ templates
  * Implement simple and variadic function templates
  * Understand type requirements (“concepts”) of template parameters
  * Reason about and debug template argument deduction and overload resolution


## 1. Introduction / Context

Week 9 introduces **compile-time polymorphism** via **function templates**:

* Instead of writing many overloads (`min(int,int)`, `min(double,double)`, …), you write **one template** that works for all suitable types. 
* Templates are instantiated by the **compiler** for concrete types – unlike Java generics (which use type erasure at runtime).
* With templates, you can:

  * express **generic algorithms** once,
  * ensure type correctness at compile time,
  * avoid code duplication and keep interfaces consistent.

The slides use `min` and `printAll` as running examples, and end with a set of **“gotchas”** that show how easy it is to misuse templates if you ignore details like string literals, overload resolution and lifetimes. 


## 2. Key Terms and Definitions

| Term                                     | Definition                                                                                                                                                                   |
| ---------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Function template**                    | A function pattern with one or more template parameters. The compiler generates (“instantiates”) concrete functions when the template is used.                               |
| **Template parameter**                   | Placeholder in the template declaration (e.g. `typename T`, `typename... Types`). Can be a type parameter, non-type parameter, or template template parameter.               |
| **Template argument**                    | Concrete type or value used to instantiate a template (e.g. `T = int` in `min<int>`).                                                                                        |
| **Template instantiation**               | The process where the compiler creates an actual function (or class) from a template for a specific set of arguments.                                                        |
| **Concept (informal)**                   | The set of requirements a type must satisfy in order to be valid for a template parameter (e.g. “has `operator<` with itself”, “copy-constructible”).                        |
| **Concept (C++20)**                      | Explicit language feature to write and check such requirements in code, leading to clearer constraints and error messages.                                                   |
| **Template argument deduction**          | Compiler mechanism that infers template arguments from a function call’s parameter types instead of requiring explicit `min<int>(1, 2)`.                                     |
| **Variadic template**                    | Template that takes a variable number of template parameters or function arguments via **parameter packs** (`typename... Types`).                                            |
| **Parameter pack**                       | A template parameter that represents zero or more arguments. Appears in template parameter lists (`typename... Types`) or function parameter lists (`Types const&... rest`). |
| **Pack expansion**                       | Syntax `pattern...` that expands a parameter pack into a comma-separated list of pattern instances (e.g. `printAll(rest...)`).                                               |
| **Duck typing (templates)**              | A type can be used as a template argument if it supports all operations used in the template body – no explicit “implements interface” needed.                               |
| **Overload resolution (with templates)** | Process that selects the best matching function (template or non-template) when multiple candidates share the same name.                                                     |


## 3. Main Content

### 3.1 Motivation and Basic Template Syntax

Naive approach: implement `min` for each fundamental type: 

```cpp
auto min(int left, int right) -> int {
    return left < right ? left : right;
}
```

* You would need versions for `double`, `long`, `std::string`, and every user-defined type.
* This is not maintainable and leads to code duplication.

**Function template** (slide 11):

```cpp
template <typename T>
auto min(T left, T right) -> T {
    return left < right ? left : right;
}
```

* `template <typename T>` introduces a **type template parameter** `T`.
* `T` can be used as a type inside the function (parameters, return, local variables).
* `typename` and `class` are interchangeable here.

**Usage example** (slide 12): 

```cpp
#include "Min.hpp"
#include <iostream>

auto main() -> int {
    int first;
    int second;
    if (std::cin >> first >> second) {
        auto const smaller = min(first, second);   // T deduced as int
        std::cout << "Smaller of " << first
                  << " and " << second
                  << " is: " << smaller << '\n';
    }
}
```

The compiler:

1. Sees a call `min(first, second)`.
2. Deduces `T = int` from parameter types.
3. Instantiates `auto min(int, int) -> int`.
4. Type-checks that `operator<` and copying work for `int`. 

**Template definition placement** (slide 14):

* Typically placed in **header files**, because the compiler must see the full definition wherever instantiation is needed.
* Function templates are implicitly **`inline`**.
* If defined only in a `.cpp`, they can only be instantiated in that translation unit.

Two-phase checking:

* On definition: only syntax and names independent of `T` are checked.
* On instantiation: all uses of `T` are checked (e.g. whether `operator<` exists). 


### 3.2 Templates vs Java Generics and Concepts

Slide 15 compares **Java generics** to **C++ templates**: 

```java
public static <T extends Comparable<? super T>> T min(T first, T second) {
    return first.compareTo(second) < 0 ? first : second;
}
```

Java generics:

* Require **bounds** (`T extends Comparable<...>`).
* Use **type erasure** – runtime type is erased, actual type only accessible via reflection.

C++ templates:

```cpp
template <typename T>
auto min(T left, T right) -> T {
    return left < right ? left : right;
}
```

* Use **duck typing**: any `T` is allowed as long as `T` supports the operations used in the body (`<`, copy/move).
* The concrete type is known at compile time and can be used directly (e.g. to construct `T` objects, call `T`-specific APIs).

**Concepts (informal)** (slide 16):

For `min` to compile, `T` must:

* be **LessThanComparable with itself** – `bool operator<(T, T)`,
* be **copy/move constructible**, so returning `T` by value is possible. 

In C++20, you can express such requirements explicitly using **concepts**, leading to clearer diagnostics if instantiation fails.

**Example concept reasoning: `inner_product`** (slide 17):

```cpp
template<class InputIt1, class InputIt2, class T>
auto inner_product(InputIt1 first1, InputIt1 last1,
                   InputIt2 first2, T init) -> T {
    while (first1 != last1) {
        init = init + *first1 * *first2;
        ++first1;
        ++first2;
    }
    return init;
}
```

From this implementation, you can infer:

* `InputIt1`/`InputIt2`:

  * must be **dereferenceable** (`*first1`, `*first2`),
  * must support **prefix increment** (`++first1`, `++first2`),
  * `InputIt1` must be **comparable to `last1`** via `!=` and convertible to `bool`. 
* `T`:

  * must be usable in `init + *first1 * *first2`,
  * must be assignable from that expression result,
  * must be copy/move constructible.

These *implicit* concepts are part of the template’s contract, even if not written explicitly.


### 3.3 Template Argument Deduction and Ambiguities

**Template argument deduction** (slide 18):

```cpp
template <typename T>
auto min(T left, T right) -> T;

template <typename T>
T min(std::vector<T> const& values);

std::vector<double> values{1.0, 2.0};
min(values);   // T deduced as double
min(1, 2);     // T deduced as int
```

The compiler uses **pattern matching** on the parameter types to deduce `T`.

**Ambiguity example** (slide 19):

```cpp
template <typename T>
auto min(T left, T right) -> T;

auto min(int left, int right) -> int;
auto min(double left, double right) -> double;

min(1, 1.0);   // ?
```

* Could convert `1.0` to `int` to call `min(int,int)`.
* Could convert `1` to `double` to call `min(double,double)`.
* Could deduce `T` as `double` or `int` for the template with conversions.
* This is ambiguous and results in a compile error.

**Takeaway:** Avoid designing templates and overloads that force the compiler to choose between equally good candidate conversions.


### 3.4 Variadic Templates and Pack Expansion

Sometimes the number of arguments is not fixed – you need a function that can take **any number of arguments**.

Syntax uses **`...`** (ellipsis) in several places (slide 20):

* in template parameter lists: `typename... Types` (template parameter pack),
* in function parameter lists: `Types const&... rest` (function parameter pack),
* in `sizeof...(Types)` to count arguments,
* in expressions like `printAll(rest...)` for **pack expansion**.

**Example: `printAll`** (slides 20–23):

Declaration:

```cpp
template<typename First, typename... Types>
auto printAll(First const& first, Types const&... rest) -> void {
    std::cout << first;
    if (sizeof...(Types)) {
        std::cout << ", ";
    }
    printAll(rest...);
}
```

Instantiation for:

```cpp
int i{42};
double d{1.25};
std::string book{"Lucid C++"};

printAll(i, d, book);
```

* First instance (conceptually) is:

```cpp
void printAll(int const& first,
              double const& __rest0,
              std::string const& __rest1) {
    std::cout << first;
    if (2) {                // sizeof...(Types) == 2
        std::cout << ", ";
    }
    printAll(__rest0, __rest1);  // pack expansion of rest...
}
```

* Next level:

```cpp
auto printAll(double const& first, std::string const& __rest0) -> void {
    std::cout << first;
    if (1) {  // one remaining type in Types...
        std::cout << ", ";
    }
    printAll(__rest0);
}

auto printAll(std::string const& first) -> void {
    std::cout << first;
    if (0) {  // no Types...
        std::cout << ", ";
    }
    printAll();   // base case needed
}
```

**Base case** (slide 24):

The recursion needs a **non-variadic** overload:

```cpp
auto printAll() -> void { }

template<typename First, typename... Types>
auto printAll(First const& first, Types const&... rest) -> void {
    std::cout << first;
    if (sizeof...(Types)) {
        std::cout << ", ";
        printAll(rest...);
    }
}
```

* `printAll()` is called when there are no arguments left.
* Without this overload, `printAll()` would be ill-formed.


### 3.5 Variadic `min` and the “Unused Base Case” Trick

Right-or-wrong example (slide 25):

```cpp
template <typename F, typename... T>
auto min(F const& first, T const&... rest) -> F {
    auto const& restMin = min(rest...);
    return first < restMin ? first : restMin;
}

int main() {
    std::cout << min(3, 1, 4, 1, 5);
}
```

At first glance this seems broken: eventually the recursion calls `min()` with **no arguments**, which has no matching overload.

* **Incorrect interpretation:** “It must fail, there’s no base case `min()`”.
* **Correct interpretation (as per slides):**

  * Template code that is never instantiated is **not checked**.
  * In the recursion, there is always at least one argument; an actual call to `min()` with zero arguments is never formed.
  * So lack of `min()` is fine **as long as** you never actually call it.

Safer pattern:

```cpp
template <typename F>
auto min(F const& first) -> F {
    return first;
}

template <typename F, typename... T>
auto min(F const& first, T const&... rest) -> F {
    auto const& restMin = min(rest...);
    return first < restMin ? first : restMin;
}
```

Now there is a real base case, and the recursive logic is explicit and easy to reason about.


### 3.6 Overloading Templates and Non-Templates (Strings, Pointers)

#### String literals and `min`

String literals have type `char const[N]`, which decays to `char const*` in most expressions.

Simple template:

```cpp
template <typename T>
auto min(T left, T right) -> T {
    return left < right ? left : right;
}
```

Call:

```cpp
std::cout << min("Gregor Clegane", "Tyrion Lannister");
```

* `T` deduces to `char const*`.
* Comparison uses `<` on pointers → compares **addresses**, not lexicographical order. 

Overload attempt (slide 26):

```cpp
char const* min(char const* left, char const* right) {
    return left < right ? left : right;
}
```

Still wrong: pointer comparison.

Better approach (slide 29):

```cpp
template <typename T>
auto min(T left, T right) -> T {
    return left < right ? left : right;
}

template <typename T>
auto* min(T* left, T* right) -> T* {
    return *left < *right ? left : right;
}

auto min(char const* left, char const* right) -> char const* {
    return std::string{left} < std::string{right} ? left : right;
}
```

Now:

* Generic template handles value types.
* Pointer template compares pointed-to values.
* Non-template overload for `char const*` converts to `std::string` to achieve lexicographical string comparison.

**Rule:** Non-template overloads are often used to handle special cases like string literals.


### 3.7 Templates Inside Generic Lambdas and Operators

The slides show how a **generic lambda** is implemented internally (slide 30):

```cpp
auto const printer = [&out](auto const& e) {
    out << "Element: " << e;
};
```

Compiled roughly as:

```cpp
struct __PrinterLambda {
    template <typename T>
    auto operator()(T const& e) const -> void {
        __out << "Element: " << e;
    }
    std::ostream& __out;
};
```

* The closure type has a templated `operator()(T const&)`.
* Same pattern can be used manually for functors with template call operators.

**Warning:** making `operator()` (or other operators) a **template too eagerly** can:

* cause unexpected overload resolutions (the template matches better than you intended),
* interfere with other overloads.

Design operator templates sparingly and with clear constraints.


### 3.8 Gotchas: Literals, Overload Resolution, Lifetimes

#### String literals and reference templates (slide 31)

```cpp
template <typename T>
auto min(T const& left, T const& right) -> T const& {
    return left < right ? left : right;
}

std::cout << min("C++", "Java");  // error
```

Here:

* `"C++"` has type `char const[4]`, `"Java"` has type `char const[5]`.
* No single `T` can match both array types → deduction fails.

Fix: use `std::string` literals:

```cpp
using namespace std::string_literals;
std::cout << min("C++"s, "Java"s);
```

Now both arguments are `std::string`, and `T` deduces cleanly. 

#### Template chosen instead of specialised overload (slide 32)

```cpp
template <typename T>
auto min(T& left, T& right) -> T {
    return left < right ? left : right;
}

auto min(std::string const& left, std::string const& right) -> std::string {
    return std::ranges::lexicographical_compare(
        left, right,
        [](char l, char r) { return tolower(l) < tolower(r); }
    ) ? left : right;
}

std::string small{"aa"};
std::string capital{"ZZ"};
std::cout << min(small, capital) << '\n';  // outputs "ZZ"
```

Reason:

* For `min(small, capital)` the **template** taking non-const references is a better match than the overload taking `const&`.
* Thus the template (simple lexicographical `<`) is chosen, not the case-insensitive overload.

**Lesson:** Overloads must be designed so that the “more specific” overload is a strictly better match than the template, or you have to adjust constness/parameters to avoid surprises.

#### Lifetimes of temporaries (slide 33)

```cpp
template <typename T>
auto min(T const& left, T const& right) -> T const& {
    return left < right ? left : right;
}

std::string const& smaller = min("a"s, "b"s);
std::cout << "smaller is: " << smaller;
```

* `"a"s` and `"b"s` are temporary `std::string` objects.
* Lifetime rules:

  * A `const&` **can extend** the lifetime of a temporary, but only the one it is **directly bound to** as the result of the full expression.
* In this example, the return value of `min` is a `const&` to one of the temporaries. The reference `smaller` then binds to that reference.
* The temporary’s lifetime is extended such that `smaller` remains valid.

However, small changes can break lifetime extension, so be cautious when returning references to temporaries from templates.

#### Right or Wrong? (slide 34)

1. **Case 1:**

```cpp
template <typename T>
auto min(T const& left, T const& right) -> T const&;

auto main() -> int {
    std::cout << min("Java", "Rust");
}
```

* Both arguments are `char const[5]`, so `T` deduces as `char const[5]`.
* The function compiles.
* But comparison still happens on **addresses**, not lexicographically.
* **Semantics are wrong**, even though code is technically correct.

2. **Case 2:**

```cpp
template <typename T>
auto min(T const& left, T const& right) -> T const&;

auto main() -> int {
    std::string java{"Java"};
    std::string const rust{"Rust"};
    std::cout << min(java, rust);
}
```

* `java` is non-const `std::string`, `rust` is const `std::string`.
* Both can bind to `T const&`, so `T = std::string`.
* The call is well-formed and uses `std::string`’s `operator<` as expected.


## 4. Relationships and Interpretation

* **Function templates** give **compile-time polymorphism**:

  * The same algorithm (`min`, `inner_product`, `printAll`) works for many types.
  * The compiler enforces constraints based on how the template is written.
* **Duck typing + concepts**:

  * Implicit concepts come from operations used in the template body.
  * C++20 concepts allow these to be made explicit and checked earlier.
* **Variadic templates** generalise functions to arbitrary argument counts, using:

  * parameter packs (`typename... Types`),
  * pack expansions (`rest...`),
  * recursion plus a base case overload.
* **Overload resolution** with templates is subtle:

  * Non-template overloads and more specialised overloads can overshadow or be overshadowed by templates.
  * Literals and qualifiers (`const`, arrays vs pointers) significantly influence which overload is chosen.
* **Lifetime rules** are crucial when templates return references; templates don’t magically protect you from dangling references.


## 5. Examples and Applications

* Generic `min` / `max` / `clamp` functions for user-defined types that implement `operator<`.

* Variadic logging functions:

  ```cpp
  template<typename... Args>
  auto log(std::ostream& out, Args const&... args) -> void {
      ((out << args << ' '), ...);  // fold expression variant
  }
  ```

* Generic `printAll` or `join` utilities to print arbitrary sets of arguments or containers.

* Type-agnostic math helper functions (`dotProduct`, `lerp`) where the concept is “addable and multipliable”.

* Generic comparator functors or lambdas used with `std::sort`, `std::set`, etc.


## 6. Summary / Takeaways

* Function templates let you write **one generic function** instead of many overloads. 
* The compiler **deduces template arguments**, instantiates the template, and checks types at compile time.
* C++ templates differ from Java generics:

  * No type erasure, full compile-time knowledge, duck typing vs. explicit bounds.
* **Concepts** (even informally) describe the required operations for template parameters.
* Variadic templates plus parameter packs support **arbitrary numbers of arguments**.
* Overloading templates, especially with non-template overloads, must be designed carefully to avoid surprises (string literals, pointer comparisons, const vs non-const).
* Be aware of **lifetime** when returning references (e.g. `min` returning `T const&`).
* Template code that’s never instantiated is never checked (and never generated) – both a blessing and a potential source of hidden bugs.


## 7. Study Hints

* Rewrite simple functions (`min`, `max`, `clamp`, `sum`) as templates and test them with:

  * `int`, `double`, `std::string`, and a small custom type with `operator<`.
* For each template you write, **list its informal concept**:

  * What operations are required (comparison, addition, copying)?
* Implement your own `printAll`:

  * first as a fixed-parameter function,
  * then as a variadic template with a base case, and call it with different argument counts.
* Explore **overload resolution**:

  * Create a base template `min(T const&, T const&)`,
  * add overloads for `std::string`, `char const*`,
  * see which overload is chosen in different call scenarios.
* Experiment with string literals vs `std::string`:

  * Call `min("a", "b")` vs `min("a"s, "b"s)`.
* Try to break your templates deliberately:

  * Use types that don’t support the required operations,
  * Observe compiler errors and see how you could express requirements as concepts.


## 8. Extensions / Further Concepts

* **Class templates** and template member functions.
* **Non-type template parameters** (e.g. array size, compile-time constants).
* Explicit **C++20 concepts** and `requires` clauses to formalise type requirements.
* **Fold expressions** as a modern alternative to recursive variadic templates.
* Template **specialisation** (full and partial) for special-case behaviour.
* Templates and **metaprogramming** (e.g. `std::integral_constant`, `std::conditional`).


## 9. References & Literature (IEEE)

[1] ISO/IEC, *Programming Languages — C++ (ISO/IEC 14882:2020)*, International Organization for Standardization, 2020.

[2] B. Stroustrup, *The C++ Programming Language*, 4th ed., Addison-Wesley, 2013.

[3] N. M. Josuttis, *The C++ Standard Library: A Tutorial and Reference*, 2nd ed., Addison-Wesley, 2012.

[4] T. Corbat, F. Morgner, *Modern and Lucid C++ for Professional Programmers – Week 9 – Function Templates*, OST - Ostschweizer Fachhochschule, HS2025. 
