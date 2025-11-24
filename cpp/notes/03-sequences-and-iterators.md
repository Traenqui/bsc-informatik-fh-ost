# Modern and Lucid C++ for Professional Programmers – Week 3: Sequences and Iterators

## Overview

* **Topic of this unit:** Basic sequence containers, iteration, algorithms, and stream iterators 
* **Lecturers:** Thomas Corbat, Felix Morgner 
* **Date:** Week 3
* **Learning objectives:**

  * Use `std::array` and `std::vector` instead of C-style arrays
  * Obtain and use iterators for standard containers
  * Access and modify container contents using standard algorithms
  * Understand and apply C++20 ranges (`std::ranges`)
  * Connect containers and streams to algorithms using iterators
  * Read from and write to streams using (stream) iterators

---

## 1. Introduction / Context

This week moves from **single values** (Week 2) to **sequences of values** and how to work with them efficiently and safely:

* Represent sequences with `std::array` (fixed size) and `std::vector` (dynamic size).
* Traverse sequences with range-based for loops and iterators.
* Use **standard algorithms** instead of hand-written loops wherever possible.
* Understand how **iterators** connect:

  * containers ↔ algorithms and
  * streams ↔ algorithms.

The diagrams on pages 24 and 32 of the slides visualize iterators as the “glue” between containers/streams and algorithms. 

---

## 2. Key Terms and Definitions

| Term                                 | Definition                                                                                                                           |
| ------------------------------------ | ------------------------------------------------------------------------------------------------------------------------------------ |
| **Container**                        | Object that owns a collection of elements (e.g. `std::array`, `std::vector`).                                                        |
| **`std::array<T, N>`**               | Fixed-size sequence container of `N` elements of type `T`. Size is compile-time constant and part of the type.                       |
| **`std::vector<T>`**                 | Dynamic sequence container of elements of type `T`; can grow and shrink at runtime.                                                  |
| **Element access**                   | Accessing elements via `operator[]` (no bounds check, UB on invalid index) or `.at()` (throws `std::out_of_range` on invalid index). |
| **Iterator**                         | “Pointer-like” object used to traverse elements in a container or stream; supports `*it` for access and `++it` to move forward.      |
| **Range `[begin, end)`**             | Half-open interval of elements starting at `begin` and stopping *before* `end`; defined by two iterators.                            |
| **Range-based for**                  | `for (auto& x : container)` syntax that iterates over all elements without explicit indices.                                         |
| **Algorithm**                        | Generic function (e.g. `std::count`, `std::accumulate`, `std::ranges::for_each`) that operates on ranges via iterators.              |
| **C++20 ranges (`std::ranges`)**     | New algorithm interfaces that often take a **whole range** (container/view) instead of separate iterators.                           |
| **Back inserter**                    | Iterator adapter that turns `push_back` into an output iterator, e.g. `std::back_inserter(v)`.                                       |
| **Stream iterator**                  | `std::istream_iterator<T>` / `std::ostream_iterator<T>` that read/write values from/to streams using `>>` / `<<`.                    |
| **`std::istreambuf_iterator<char>`** | Stream iterator that reads raw characters via `get()`, including whitespace.                                                         |

---

## 3. Main Content

### 3.1 Basic Sequence Containers: `std::array` and `std::vector`

#### `std::array<T, N>`

* Fixed-size container; size known at compile time. 

```cpp
#include <array>

std::array<int, 5> numbers{1, 2, 3, 4, 5};
std::array<int, 5> empty{};  // 5 default-constructed ints (0)
```

* Template parameters:

  * `T` – element type
  * `N` – number of elements (non-type template parameter)
* `.size()` returns `N`.
* Prefer `std::array` over C-style arrays (`int arr[]{...};`).

Element access:

```cpp
int x = numbers[0];       // no bounds check, UB if index invalid
int y = numbers.at(1);    // throws std::out_of_range if index invalid
```

The diagram on page 9 shows the array elements laid out in order with indices and iterator entry points (`begin`, `end`, `rbegin`, `rend`, `front`, `back`). 

#### `std::vector<T>`

* Dynamic container; elements stored *inside* the vector (no extra `new` required). 

```cpp
#include <vector>

std::vector<int> v{1, 2, 3, 4, 5};
std::vector<double> vd{};              // empty
std::vector<std::string> words(6);     // 6 default-constructed strings
```

* Type can be deduced from the initializer:

```cpp
std::vector v{1, 2, 3, 4, 5};  // C++17 CTAD
std::vector v{};               // empty vector<int>
```

* Size and capacity are independent; vector can grow:

  * `v.push_back(value);` – append
  * `v.insert(v.begin() + 3, value);` – insert at position

The diagram on page 11 shows how `std::vector` can grow and where iterators (`begin`, `end`, `rbegin`, `rend`) and modifiers (`push_back`, `insert`) operate. 

#### Comparison to Java’s `ArrayList<E>`

* `ArrayList<E>`: collection storing **references** to heap-allocated `E` objects.
* `std::vector<T>`: container storing **T objects directly**.
* Code example in slides (page 12) contrasts a Java `ArrayList<Ship>` with a C++ `std::vector<Ship>`; in C++ the ships are actual objects in the container, not references. 

---

### 3.2 Iterating over Containers

#### Index-based iteration (often bad style)

```cpp
for (std::size_t i = 0; i < v.size(); ++i) {
    std::cout << "v[" << i << "] = " << v[i] << '\n';
}
```

* Works, but has pitfalls:

  * No bounds check with `[]` → undefined behavior if `i` out of range.
  * Off-by-one mistakes are easy, especially when doing things like `size() - 1`.
    The `printButLast` example on page 15 becomes UB for an empty vector because `size() - 1` underflows an unsigned type. 
* Use index-based loops **only** if you truly need the index.

#### Range-based for (preferred)

```cpp
for (auto& ref : v) {        // modify elements
    ref *= 2;
}

for (auto copy : v) {        // work on copies
    copy *= 2;
    std::cout << copy << '\n';
}

for (auto const& cref : v) { // read-only access
    std::cout << cref << '\n';
}
```

* No index → no index errors.
* Works with all containers and even initializer lists (`{1, 2, 3}`).
* Choose between `&` (reference) vs. copy, and `const` vs. non-const depending on whether you modify the elements. 

#### Manual iterator loops

```cpp
for (auto it = std::cbegin(v); it != std::cend(v); ++it) {
    std::cout << *it << ", ";
}

for (auto it = std::begin(v); it != std::end(v); ++it) {
    std::cout << (*it)++ << ", ";
}
```

* `std::begin(v)` / `std::end(v)` – normal iterators, can modify elements.
* `std::cbegin(v)` / `std::cend(v)` – constant iterators, read-only.
* Most useful when you need the iterator itself (e.g. for `insert`, `erase`, or range splitting). 

---

### 3.3 Algorithms and Lambdas

#### Algorithms in `<algorithm>`, `<numeric>`, `<iterator>`

**Counting blanks:**

```cpp
#include <algorithm>

auto count_blanks(std::string s) -> std::size_t {
    return std::count(s.cbegin(), s.cend(), ' ');
}
```

* `std::count(first, last, value)` counts how often `value` appears in `[first, last)`.

**Summing elements:**

```cpp
#include <numeric>
#include <vector>

std::vector<int> v{5, 4, 3, 2, 1};
auto sum = std::accumulate(std::cbegin(v), std::cend(v), 0);
```

* `std::accumulate` applies `+` from an initial value.

**Distance between iterators:**

```cpp
#include <iterator>
#include <string>

auto printDistanceAndLength(std::string s) -> void {
    std::cout << "distance: " << std::distance(s.begin(), s.end()) << '\n';
    std::cout << "in a string of length: " << s.size() << '\n';
}
```

The diagram on page 24 shows algorithms consuming iterator pairs, with iterators obtained from containers via `begin`/`end`. 

#### `for_each` and lambdas

```cpp
#include <algorithm>

auto printAll(std::vector<int> v, std::ostream& out) -> void {
    std::for_each(std::cbegin(v), std::cend(v),
                  [&out](auto x) {
                      out << "print: " << x << '\n';
                  });
}
```

* Lambda structure:

```cpp
[capture](parameters) -> return_type {
    // body
}
```

* `[&out]` captures `out` by reference, so the lambda can print to any given `std::ostream`.
* `auto x` lets the compiler deduce the parameter type.

#### C++20 ranges

```cpp
auto printAll(std::vector<int> v, std::ostream& out) -> void {
    std::ranges::for_each(v,
                          [&out](auto x) {
                              out << "print: " << x << '\n';
                          });
}
```

* `std::ranges::for_each` takes the container directly instead of `begin`/`end`.
* Many classic algorithms have `std::ranges::` equivalents with simpler parameter lists. 

---

### 3.4 Modifying and Filling Vectors

#### Copying into a vector – use inserter adapters

**Wrong (UB):**

```cpp
std::vector<int> source{1, 2, 3}, target{};
std::copy(source.cbegin(), source.cend(), target.end());  // UB
```

* `target.end()` is a valid iterator but does **not** point to existing space; `std::copy` expects a range of valid output positions. 

**Correct with `std::back_inserter`:**

```cpp
#include <iterator>

std::vector<int> source{1, 2, 3}, target{};
std::copy(source.cbegin(), source.cend(), std::back_inserter(target));
std::ranges::copy(source, std::back_inserter(target));
```

* `std::back_inserter(target)` turns `target.push_back(x)` into an output iterator.

#### Filling with a single value

```cpp
#include <algorithm>
#include <vector>

std::vector<int> v{};
v.resize(10);
std::fill(std::begin(v), std::end(v), 2);
std::ranges::fill(v, 2);
```

Or combine in one step:

```cpp
std::vector<int> v(10);   // 10 default-initialised ints
std::ranges::fill(v, 2);  // all become 2

std::vector v(10, 2);     // directly 10 elements with value 2
```

#### Filling with generated values

```cpp
#include <algorithm>
#include <numeric>
#include <vector>

std::vector<double> powersOfTwo{};
double x{1.0};
std::generate_n(std::back_inserter(powersOfTwo), 5,
                [&x] { return x *= 2.0; });
// → 2,4,8,16,32

std::vector<int> v(100);
std::iota(std::begin(v), std::end(v), 1);
// → 1,2,3,...,100
```

* `std::generate` / `std::generate_n` call a generator function for each element.
* `std::iota` fills with consecutive values. 

#### Finding and counting

```cpp
auto zero_it = std::ranges::find(v, 0);
if (zero_it == std::end(v)) {
    std::cout << "no zero found\n";
}

auto isEven = [](int x) { return !(x % 2); };
std::cout << std::ranges::count(v, 42) << " times 42\n";
std::cout << std::ranges::count_if(v, isEven) << " even numbers\n";
```

#### Prefer algorithms over manual loops

```cpp
bool find_with_loop(std::vector<int> const& values, int v) {
    auto const end = std::end(values);
    for (auto it = std::begin(values); it != end; ++it) {
        if (*it == v) {
            return true;
        }
    }
    return false;
}

bool find_with_algorithm(std::vector<int> const& values, int v) {
    auto const pos = std::ranges::find(values, v);
    return pos != std::end(values);
}
```

Algorithms express your *intent* directly and are more likely to be correct, readable, and optimised. 

---

### 3.5 Iterators for I/O

Streams cannot be used with algorithms directly; **stream iterators** bridge this gap.

#### `std::ostream_iterator<T>`

```cpp
#include <iterator>

std::vector<int> v{1, 2, 3};
std::ranges::copy(v, std::ostream_iterator<int>{std::cout, ", "});
```

* Writes each element to `std::cout` followed by `", "`.
* No special `end` iterator – output stops when input range ends. 

#### `std::istream_iterator<T>` and `std::ranges::istream_view<T>`

```cpp
#include <iterator>
#include <string>

std::istream_iterator<std::string> in{std::cin};
std::istream_iterator<std::string> eof{};
std::ostream_iterator<std::string> out{std::cout, " "};

std::copy(in, eof, out);
```

* Reads space-separated strings from `std::cin` using `>>` until the stream becomes bad or EOF is reached.
* C++20 ranges version:

```cpp
std::ranges::istream_view<std::string> in{std::cin};
std::ostream_iterator<std::string> out{std::cout, " "};
std::ranges::copy(in, out);
```

The diagram on page 32 shows algorithms using `istream_iterator`/`ostream_iterator` to process streams. 

#### Type aliases for shorter names

```cpp
using input  = std::istream_iterator<std::string>;
using output = std::ostream_iterator<std::string>;

input eof{};
input in{std::cin};
output out{std::cout, " "};

std::copy(in, eof, out);
```

* `using alias = type;` reduces repetition of long template names. 

#### “Unformatted” character input

`std::istream_iterator<T>` uses `>>` and thus skips whitespace. To copy *exactly* all characters, including spaces and newlines, use `std::istreambuf_iterator<char>`:

```cpp
#include <iterator>

using input = std::istreambuf_iterator<char>;

input eof{};
input in{std::cin};
std::ostream_iterator<char> out{std::cout};

std::copy(in, eof, out);
```

#### Filling a vector from input

```cpp
// Using back_inserter and istream_view<int> (ranges)
using input = std::ranges::istream_view<int>;
std::vector<int> v{};
std::ranges::copy(input{std::cin}, std::back_inserter(v));

// Using istream_iterator constructor
using input_it = std::istream_iterator<int>;
input_it eof{};
std::vector<int> const v{input_it{std::cin}, eof};
```

---

## 4. Relationships and Interpretation

* **Containers** (`std::array`, `std::vector`) hold sequences of values.
* **Iterators** describe **where** in those sequences you operate.
* **Algorithms** express **what** you want to do with ranges (count, find, copy, transform, ...).
* **Ranges (`std::ranges`)** simplify algorithm usage by letting you pass whole containers/views.
* **Stream iterators** generalise this idea to **input and output streams**, so streams can be processed with the same algorithms used for containers.

In short:

$$
\text{Container/Stream} \xrightarrow{\text{Iterators}} \text{Algorithm (Ranges)}
$$

---

## 5. Examples and Applications

* Printing elements of a vector in different orders using

  * range-based for,
  * iterator loops,
  * `std::ranges::for_each`.
* Counting blanks in a string with `std::count` instead of a manual loop.
* Computing sums and sequences:

  * total of a vector with `std::accumulate`,
  * sequence of powers of two with `std::generate_n`,
  * sequence `1..100` with `std::iota`.
* Filling vectors from standard input using `istream_iterator` or `istream_view` and `std::ranges::copy`.
* Building simple Unix-style filters using `istreambuf_iterator<char>` to copy and transform raw character streams.

---

## 6. Summary / Takeaways

* Prefer **`std::array` / `std::vector`** over plain C-arrays.
* **Range-based for** is the default way to iterate unless you need indices or iterators.
* Use **iterators** to define ranges `[begin, end)`; avoid hand-crafted loops when an algorithm exists.
* `std::ranges` versions of algorithms often give clearer code and reduce boilerplate.
* Use **inserter adapters** (`std::back_inserter`) when algorithms need to grow a container.
* Use **stream iterators** to connect algorithms with input and output streams.
* Overall motto: express *what* you want using algorithms; let the standard library handle the *how*.

---

## 7. Study Hints

* Rewrite existing loop-based code using algorithms (`std::ranges::find`, `count`, `copy`, `for_each`, `fill`, `generate`).
* Practice with `std::vector<int>` and `std::vector<std::string>`:

  * build, modify, search, count, copy.
* Implement small utilities:

  * reverse print a vector,
  * read all integers from stdin into a vector,
  * copy stdin to stdout with and without whitespace (using `istream_iterator` vs. `istreambuf_iterator`).
* When you write a loop, ask: “Is there a standard algorithm that expresses this more clearly?”
* Get comfortable reading and writing lambdas with captures – they are essential with algorithms.

---

## 8. Extensions / Further Concepts

Later topics will build on this:

* Associative containers (`std::set`, `std::map`) and their iterators.
* More advanced range utilities and views (filter, transform, take/drop).
* Custom iterators and iterator categories.
* Combining containers, iterators, and algorithms with templates and generic code.
* Using algorithms and ranges with user-defined container-like types.

A solid grasp of Week 3 is required for understanding these higher-level abstractions.

---

## 9. References & Literature (IEEE)

- [1] ISO/IEC, *Programming Languages — C++ (ISO/IEC 14882:2020)*, International Organization for Standardization, 2020.
- [2] N. M. Josuttis, *The C++ Standard Library: A Tutorial and Reference*, 2nd ed., Addison-Wesley, 2012.
- [3] cppreference.com, “Containers library” and “Iterators library,” online reference for C++ containers and iterators, accessed: [reader’s current date].
- [4] Lecture slides “Modern and Lucid C++ for Professional Programmers – Week 3 – Sequences and Iterators”, OST – Ostschweizer Fachhochschule, HS2025. 
