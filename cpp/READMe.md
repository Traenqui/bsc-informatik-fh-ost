# Modern and Lucid C++ for Professional Programmers

This repository contains structured lecture summaries (in Markdown) for the course **“Modern and Lucid C++ for Professional Programmers”** (HS20xx, OST – Ostschweizer Fachhochschule).

The goal is that you can **understand and review the course without attending the lecture**, using:

- one Markdown summary per week,
- consistent structure and notation,
- reconstructed diagrams (Mermaid), and
- LaTeX/MathJax for formulas and small schematics.

---

## Course Overview

The course introduces **modern C++** for professional software engineers. It focuses on:

- writing **clear, safe, and idiomatic** C++,
- using the **standard library** effectively,
- understanding **value types, resource management, and generic programming**,
- avoiding common pitfalls of “old” C++.

The summaries currently cover:

1. [Introduction](notes/01-intro.md)  
2. [Values & Streams](notes/02-values-streams.md)
3. [Sequences & Iterators](notes/03-sequences-and-iterators.md)
4. [Functions & Exceptions](notes/04-functions-exceptions.md)
5. [Classes & Operator Overloading](notes/05-classes-operators.md)
6. [Namespaces & Enums](notes/06-namespaces-enums.md)
7. [STL Containers & Iterators](notes/07-stl-containers-iterators.md)
8. [STL Algorithms](notes/08-stl-algorithms.md)
9. [Function Templates](notes/09-function-templates.md)
10. [Class Templates](notes/10-class-templates.md)
11. [Dynamic Heap Memory Management](notes/11-dynamic-heap-memory-management.md)
12. [Dynamic Polymorphism](notes/12-dynamic-polymorphism.md)
13. [Initialization & Aggregates](notes/13-initialization-and-aggregates.md)

Each week’s summary follows the same template:

- Overview & learning goals  
- Key terms and definitions  
- Main content (with subsections)  
- Visualisations (Mermaid / LaTeX)  
- Examples & applications  
- Summary / takeaways  
- Study hints  
- Further topics & references  

---

## Prerequisites

To get the most out of the material, you should already be comfortable with:

- Basic programming concepts (variables, control flow, functions)
- At least one other language (e.g. Java, C#, Python)
- Basic C/C++ syntax (types, pointers/references, headers vs. sources)

No prior experience with **modern C++ (C++11 and later)** is strictly required, but helpful.

---

## Repository Structure

A suggested structure for this repository (the exact filenames may differ slightly):

```text
.
├── notes
│   ├── 01-intro.md
│   ├── 02-values-streams.md
│   ├── 03-sequences-and-iterators.md 
│   ├── 04-functions-exceptions.md    
│   ├── 05-classes-operators.md       
│   ├── 06-namespaces-enums.md        
│   ├── 07-stl-containers-iterators.md
│   ├── 08-stl-algorithms.md
│   ├── 09-function-templates.md      
│   ├── 10-class-templates.md
│   ├── 11-dynamic-heap-memory-management.md
│   ├── 12-dynamic-polymorphism.md
│   └── 13-initialization-and-aggregates.md
└── READMe.md
```

If your actual filenames differ, adjust this list accordingly.

---

## Weekly Content Overview

### Week 1 – Introduction

* Course organisation, tooling, compilation workflow.
* C++ as a **multi-paradigm language** (procedural, OO, generic, RAII).
* First examples: basic types, I/O, build & run.

### Week 2 – Values & Streams

* Value semantics vs. references.
* Input/output via iostreams (`std::cin`, `std::cout`).
* Stream state handling, formatting, and simple file I/O.

### Week 3 – Sequences & Iterators

* Sequences as central abstraction.
* Custom iterator-like patterns.
* Introduction to the idea of **range-based loops** and how iterators enable them.

### Week 4 – Functions & Exceptions

* Parameter passing (by value, reference, const reference).
* Return types and lifetime pitfalls (dangling references).
* Function overloading, default arguments, higher-order functions.
* Lambdas and captures.
* Error handling strategies:

  * ignore, default values, error codes/`std::optional`, side-channel error state, exceptions.
* Throwing, catching, testing with Catch2, `noexcept`, narrow vs. wide contracts.

### Week 5 – Classes & Operator Overloading

* Designing *good* classes: invariants, single responsibility, short members.
* Class layout, access specifiers, `class` vs `struct`.
* Constructors, defaulted/deleted functions, NSDMI, delegating constructors.
* Basics of inheritance and visibility.
* Overloading comparison operators (including `<=>`).
* Stream operators `operator<<` and `operator>>` as free functions.

### Week 6 – Namespaces & Enums

* Namespaces, name lookup, using declarations vs `using namespace`.
* Anonymous namespaces and internal linkage.
* Argument Dependent Lookup (ADL) and its interaction with operators.
* Enumerations: unscoped vs scoped enums, underlying types.
* Customising enum values, bitmask enums.
* Overloading operators for enums (e.g. cyclic increment).
* Simple arithmetic types (e.g. `Ring5`) and conversion pitfalls.

### Week 7 – STL Containers & Iterators

* Container categories:

  * sequence (`vector`, `deque`, `list`, `array`, `forward_list`),
  * associative (`set`, `map`, `multiset`, `multimap`),
  * hashed (`unordered_set`, `unordered_map`, …),
  * adapters (`stack`, `queue`, `priority_queue`).
* Complexity profiles for typical operations.
* Iterator categories:

  * input, output, forward, bidirectional, random-access.
* Helpers: `std::distance`, `std::advance`, `std::next`, `std::prev`.
* `const_iterator` vs `const Iterator`.

### Week 8 – STL Algorithms

* Ranges `[first, last)` and stream iterators.
* Non-modifying algorithms: `find`, `count`, `all_of`, `any_of`, …
* Modifying and mutating algorithms: `transform`, `copy_if`, `remove_if`, `replace`, `rotate`, `reverse`, …
* The erase–remove idiom.
* Numeric algorithms (`std::accumulate`, `inner_product`, `partial_sum`, …).
* Heap algorithms (`make_heap`, `push_heap`, `pop_heap`, `sort_heap`).
* Pitfalls: mismatched iterator pairs, invalidation, missing capacity.
* C++20 `std::ranges` and execution policies.

### Week 9 – Function Templates

* Differences between Java generics and C++ templates (compile-time vs type erasure).
* Basic function templates and template argument deduction.
* Implicit “concepts” (duck typing) in templates.
* Variadic templates and parameter packs (`printAll`, variadic `min`).
* Overloading templates and non-templates (string literals, pointers).
* Lifetime and reference-return pitfalls.

### Week 10 – Class Templates

* Class template syntax (`template <typename T> class Sack;`).
* Dependent names, `typename` and `this->` in template bases.
* Static members in class templates.
* Partial and explicit specialisation (e.g. forbidding `Sack<T*>`, special `Sack<char const*>`).
* Adapting standard containers (`SafeVector<T>`, container-based `Sack<T, Container>`).
* Class template argument deduction (CTAD) and deduction guides.
* Template-template parameters & non-type template parameters.
* Variable templates as lightweight type traits/constants.

### Week 11 – Dynamic Heap Memory Management

* When and why heap memory is needed (large objects, object graphs, polymorphic factories).
* RAII and why **raw `new`/`delete`** should be avoided.
* `std::unique_ptr<T>`:

  * unique ownership, move-only, custom deleters, C-API interop.
* `std::shared_ptr<T>`:

  * shared ownership, reference counting, polymorphic use.
* Ownership cycles and memory leaks.
* `std::weak_ptr<T>` to break cycles and implement observer relationships.
* Recursive structures (trees, graphs, family trees) with smart pointers.
* `std::enable_shared_from_this<T>` and `shared_from_this` / `weak_from_this`.

### Week 12 – Dynamic Polymorphism

* Inheritance and when to use it (mix-ins, adapters, runtime polymorphism).
* Dynamic dispatch through `virtual` functions.
* Shadowing vs overriding; using `override` to enforce correct overriding.
* Object slicing (passing polymorphic objects by value) and why it’s dangerous.
* Member hiding and `using Base::foo` to re-expose base overloads.
* Abstract base classes and pure virtual functions.
* Virtual destructors and interaction with smart pointers.
* Liskov Substitution Principle (LSP) and why many textbook hierarchies violate it.
* Why inheritance can be a bad default; alternatives (composition, templates, `std::variant`).

### Week 13 – Initialization & Aggregates

* Different kinds of initialization:

  * default, value, direct, copy, list, aggregate initialization.
* Syntax forms and how they map to initialization kinds.
* Default initialization and uninitialized locals (UB).
* Value initialization via `{}` and why it’s safer.
* Direct initialization and the “most vexing parse”.
* Copy initialization (`=`) and implicit conversions.
* List initialization with `{}` and interaction with `std::initializer_list`.
* Aggregate types (struct/array-like) and constraints:

  * no user-declared constructors or virtuals,
  * no private/protected data members,
  * rules for base classes.
* Aggregate initialization rules: member order, missing vs extra initializers.

---

## How to Use These Summaries

1. **As primary reference**
   If you missed a lecture, use the weekly Markdown files to catch up:

   * Start with section **“Overview”** and **“Key Terms”**.
   * Work through **“Main Content”** and diagrams.
   * Use **“Examples & Applications”** to connect theory to code.
   * Check **“Summary / Takeaways”** and **“Study Hints”** as a checklist.

2. **During exam preparation**

   * For each week, ensure you can:

     * explain all key terms in your own words,
     * sketch central diagrams from memory,
     * write small code snippets that demonstrate the concepts.
   * Use the **“Further topics”** sections as pointers for deeper study if needed.

3. **Alongside the original slides**

   * Open the official slides and the corresponding Markdown summary side by side.
   * The Markdown aims to make the content **linear, complete, and searchable**.

---

## Conventions in the Summaries

* **Language**: English (to match the lecture material).

* **Code examples**: modern C++ style, using:

  * `auto` with trailing return types where appropriate (`auto f() -> int;`),
  * `std::` prefix for standard library,
  * uniform initialisation `{}`.

* **Diagrams**: Mermaid blocks, for example:

  ```mermaid
  flowchart TD
    A[Input] --> B[Processing]
    B --> C[Output]
  ```

* **Formulas**: LaTeX/MathJax, for example:

$$
    \text{size} = \text{end} - \text{begin}
$$

* **References**: Each file ends with a short list of references in IEEE style.

---

## Suggested Study Path

1. **Weeks 1–3**: Refresh C++ basics and mental model
   Focus on values, references, streams, and the notion of sequences/iterators.

2. **Weeks 4–6**: Structured programming and interfaces
   Functions, error handling, classes, operators, namespaces, enums.

3. **Weeks 7–8**: Standard library power
   Containers, iterators, algorithms; start using them in all your code.

4. **Weeks 9–10**: Generic programming
   Function/class templates, type requirements, deduction, specialisation.

5. **Weeks 11–13**: Resources, polymorphism, and low-level details
   Smart pointers and heap management, dynamic polymorphism, initialization forms, aggregates.

---

## License / Usage

* These notes are intended for **personal study** and as a companion to the official course.
* Always check against the **official slides and standard documentation** (e.g. cppreference) for up-to-date details and exact wording.

---

## Further Reading

* Bjarne Stroustrup – *The C++ Programming Language* (4th ed.)
* Nicolai Josuttis – *The C++ Standard Library: A Tutorial and Reference*
* cppreference.com – up-to-date C++ reference
* ISO C++ standard (for formal definitions)

Happy studying & clean C++ coding! 🙂