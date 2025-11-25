# Modern and Lucid C++ for Professional Programmers – Week 8: STL Algorithms

## Overview

* **Topic of this unit:** STL algorithms (overview, signatures, functors/predicates, numeric algorithms, heaps, pitfalls, ranges) 
* **Lecturers:** Thomas Corbat, Felix Morgner 
* **Learning objectives:**

  * Know why and when to prefer algorithms over hand-written loops
  * Read and understand STL algorithm signatures
  * Use key algorithms from `<algorithm>` and `<numeric>`
  * Understand functors and predicates, including standard function objects
  * Apply algorithms correctly with iterator ranges and inserter iterators
  * Use the erase–remove-idiom, numeric algorithms and heap algorithms
  * Avoid typical pitfalls (iterator mismatches, invalidation, missing capacity)
  * Be aware of C++20 `std::ranges` and execution policies


## 1. Introduction / Context

This week takes the **containers & iterators** from Week 7 and adds the final STL ingredient: **algorithms**.

Algorithms:

* Work on **ranges defined by iterators** (usually `[first, last)`).
* Live in `<algorithm>` and `<numeric>`.
* Encode common patterns: searching, transforming, copying, removing, sorting, numeric accumulation, heaps, etc. 

The central message:

> Prefer **algorithms** to hand-written loops – for correctness, readability, and often performance.


## 2. Key Terms and Definitions

| Term                         | Definition                                                                                                                                                            |
| ---------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Range**                    | A half-open interval of elements defined by two iterators: `[first, last)` – `first` points to the first element, `last` one past the last. Empty if `first == last`. |
| **Unary function**           | Callable taking one argument (`f(x)`), used e.g. in `std::for_each`, `std::transform` (single range).                                                                 |
| **Binary function**          | Callable taking two arguments, e.g. `std::transform` with two input ranges, `std::accumulate` with custom operation.                                                  |
| **Functor**                  | A type (class/struct) that overloads `operator()`, so its objects can be “called like functions”. Lambdas compile down to functors.                                   |
| **Predicate**                | Function/functor/lambda returning `bool` (or convertible), expressing a condition. Unary predicate: 1 arg, binary predicate: 2 args.                                  |
| **Standard function object** | Predefined functor templates in `<functional>` for common operators: `std::plus<>`, `std::less<>`, `std::greater<>`, etc.                                             |
| **Erase–remove idiom**       | Pattern `c.erase(std::remove_if(begin(c), end(c), pred), end(c));` to actually erase removed elements from sequence containers.                                       |
| **Insert iterator**          | Special output iterator (`std::back_inserter`, `std::front_inserter`, `std::inserter`) that calls container member functions to grow the container.                   |
| **Heap**                     | Tree structure implemented on top of a random-access range that guarantees the largest (or smallest) element at the root (`*first`).                                  |
| **Execution policy**         | Parameter controlling parallelism of some algorithms (`std::execution::seq`, `par`, `par_unseq`).                                                                     |
| **`std::ranges`**            | C++20 range library: algorithms in the `std::ranges::` namespace that take ranges (containers/views) directly instead of iterator pairs.                              |


## 3. Main Content

### 3.1 Why Prefer Algorithms Over Loops?

The lecture starts with three perspectives: **correctness, readability, performance.** 

#### Correctness

Buggy manual reverse:

```cpp
auto reverse(std::vector<int>& values) -> void {
    for (int i = 0; i <= values.size(); i++) {      // off by one
        auto otherIndex{values.size() - i};         // wrong indices
        auto tmp = values[0];
        values[i] = values[otherIndex];
        values[otherIndex] = values[i];
    }
}
```

Correct algorithm version:

```cpp
#include <algorithm>

auto reverse(std::vector<int>& values) -> void {
    std::reverse(begin(values), end(values));
}
```

* Less code, fewer places to make mistakes.
* Complex details are hidden inside a well-tested library implementation.

#### Readability

“Find maximum” example: 

Loop version (what does this do at a glance?):

```cpp
auto ???(std::vector<int> values) -> int {
    auto var = std::numeric_limits<int>::min();
    for (auto v : values) {
        if (v > var)
            var = v;
    }
    return var;
}
```

Algorithm version:

```cpp
auto ???(std::vector<int> values) -> int {
    if (values.empty()) {
        return std::numeric_limits<int>::min();
    }
    return *std::max_element(begin(values), end(values));
}
```

Even without a name, `std::max_element` makes intent obvious.

#### Performance

Contains example: 

```cpp
auto contains(std::vector<int> values, int sought) -> bool {
    for (auto it = begin(values); it != end(values); ++it) {
        if (*it == sought) return true;
    }
    return false;
}
```

vs.

```cpp
auto contains(std::vector<int> values, int sought) -> bool {
    return std::find(begin(values), end(values), sought) != end(values);
}
```

A modern compiler will often optimise both similarly, but library algorithms:

* are carefully tuned,
* can be specialised for iterator categories,
* can gain parallelisation via execution policies.


### 3.2 Algorithm Basics: Ranges and Stream Iterators

#### Ranges via iterators

* Algorithms operate on **ranges** `[first, last)` where:

  * `first` points at first element,
  * `last` points one past the last element.
* If `first == last`, the range is empty. 

```cpp
std::vector<int> values{54, 23, 17, 95, 85, 57, 12, 9};
std::xxx(begin(values), end(values), /* more args */);
```

The diagram on *page 14* shows `begin(values)` pointing at `54` and `end(values)` just past `9`.

#### Stream iterators

Streams need a wrapper to work with algorithms: 

```cpp
using in_iter  = std::istream_iterator<char>;
using out_iter = std::ostream_iterator<char>;

auto redirect(std::istream& in, std::ostream& out) -> void {
    std::copy(in_iter{in}, in_iter{}, out_iter{out});
}
```

* Default-constructed `std::istream_iterator<T>{}` acts as end iterator (EOF).


### 3.3 `for_each`, Functors and Predicates

#### `std::for_each`

* Applies a function/lambda/functor to each element in a range.
* Takes two **input iterators** and a callable.
* Returns the callable (useful for stateful functors like accumulators). 

```cpp
auto values = std::vector{3, 0, 1, 4, 0, 2};
auto f = [](auto v) { /* ... */ };

std::for_each(begin(values), end(values), f);
```

#### Reading algorithm signatures

Example from cppreference (slide 17): 

```cpp
template<class InputIt, class UnaryFunction>
UnaryFunction for_each(InputIt first, InputIt last, UnaryFunction f);
```

Key points:

* Template parameters express allowed iterator & callable types.
* Return type and requirements are described in documentation.
* Algorithms specify which **iterator category** they require (input/forward/bidirectional/random-access/output).

#### Functors

A **functor** is any type with `operator()`. Example `Accumulator` (slide 18): 

```cpp
struct Accumulator {
    int count{0};
    int accumulatedValue{0};

    auto operator()(int value) -> void {
        ++count;
        accumulatedValue += value;
    }

    auto average() const -> int;
    auto sum() const -> int;
};
```

Usage:

```cpp
auto average(std::vector<int> values) -> int {
    auto acc = Accumulator{};
    return std::for_each(begin(values), end(values), acc).average();
}
```

* Lambdas compile to anonymous functor types under the hood.

#### Predicates

Predicates are callables returning `bool`. 

```cpp
auto is_odd = [](auto i) -> bool { return i % 2; };              // unary
auto divides = [](auto i, auto j) -> bool { return !(i % j); };  // binary
```

Used in `_if` algorithms such as `std::count_if`, `std::find_if`, `std::remove_if`, …


### 3.4 Standard Function Objects & Custom Comparators

Header `<functional>` provides functor templates for many operators (slide 21): 

* Arithmetic: `std::plus<>`, `std::minus<>`, `std::multiplies<>`, `std::divides<>`, `std::modulus<>`
* Logical: `std::logical_and<>`, `std::logical_or<>`, `std::logical_not<>`
* Comparisons: `std::less<>`, `std::greater<>`, `std::less_equal<>`, `std::greater_equal<>`, `std::equal_to<>`, `std::not_equal_to<>`

Example with `std::transform`: 

```cpp
std::transform(begin(v), end(v), begin(v), std::negate<>{});
std::sort(begin(v), end(v), std::greater<>{});  // sort descending
```

These are often reusable instead of ad-hoc lambdas.

#### Associative containers with custom comparators

`std::set`, `std::map`, etc. take an optional comparator functor type: 

```cpp
std::set<int, std::greater<>> reverse_int_set{};
```

Requirements:

* Comparator must be a **strict weak ordering** (irreflexive, transitive, etc.).
* `std::greater_equal<>` is **not** valid because it is reflexive (fails ordering requirements).

Example **caseless** comparator for a dictionary (`std::multiset<std::string, caseless>`) on *page 23* uses `std::lexicographical_compare` with a character lambda that calls `std::tolower`. 


### 3.5 Core Algorithms: `transform`, `merge`, `remove`, `accumulate`, `_if`, `_n`

#### `transform` – mapping elements

* Maps:

  * one range → one output range, or
  * two ranges → one output range.
* Input and output element types may differ. 

Example combining counts and letters (slide 24):

```cpp
auto counts  = std::vector{3, 0, 1, 4, 0, 2};
auto letters = std::vector{'g', 'a', 'u', 'y', 'f', 'o'};
auto combined = std::vector<std::string>{};

auto times = [](auto i, auto c) { return std::string(i, c); };

std::transform(begin(counts), end(counts),
               begin(letters),
               std::back_inserter(combined),
               times);
```

Result: `{"ggg", "", "u", "yyyy", "", "oo"}`.

#### `merge` – merging sorted ranges

Merges two **sorted** ranges into a destination (also sorted). 

```cpp
std::vector r1{9, 12, 17, 23, 54, 57, 85, 95};
std::vector r2{2, 30, 32, 41, 49, 63, 72, 88};
std::vector d(r1.size() + r2.size());

std::merge(begin(r1), end(r1),
           begin(r2), end(r2),
           begin(d));
```

The diagram on *page 25* shows how values are pulled from both inputs to produce `d: 2 9 12 17 23 30 32 41 49 54 57 63 72 85 88 95`.

The “Right or Wrong” slide 26 confirms:

* Merging two `std::set<int>` is **correct** because sets are sorted.
* A `transform` filling an existing `indices` vector is correct **only if** enough space exists.

#### Erase–remove idiom

`std::remove` and `std::remove_if` do **not** erase from containers; they:

* partition the range so that “kept” elements are at the front,
* return an iterator to the new logical end. 

Typical pattern (slide 27):

```cpp
auto values = std::vector{54, 13, 17, 95, 2, 57, 12, 9};
auto is_prime = [](unsigned u) { /*...*/ };

auto newEnd = std::remove_if(begin(values), end(values), is_prime);
// [begin(values), newEnd) now holds all non-primes

values.erase(newEnd, end(values));  // physically remove trailing garbage
```

#### `accumulate` – numeric and beyond

From `<numeric>`, not `<algorithm>`.

Sums elements, or uses a custom binary operation: 

```cpp
std::vector<std::string> longMonths{
    "Jan", "Mar", "May", "Jul", "Aug", "Oct", "Dec"
};

auto accumulatedString = std::accumulate(
    std::next(begin(longMonths)),  // start at 2nd element
    end(longMonths),
    longMonths.at(0),              // initial value
    [](std::string const& acc, std::string const& element) {
        return acc + ", " + element;
    });
// "Jan, Mar, May, Jul, Aug, Oct, Dec"
```

Many numeric algorithms (like `accumulate`) can be repurposed for non-numeric aggregation.

#### `_if` variants

Algorithms with `_if` suffix expect a predicate instead of a value (slide 29):

* `count_if`, `find_if`, `find_if_not`
* `copy_if`, `remove_if`, `remove_copy_if`
* `replace_if`, `replace_copy_if` 

Example:

```cpp
auto numbers = std::set{1,2,3,4,5,6,7,8,9};
auto isPrime = [](auto u) { /*...*/ };

auto nOfPrimes = std::count_if(begin(numbers), end(numbers), isPrime);
```

#### `_n` variants

Algorithms using a **count** instead of an end iterator (slide 30):

* `copy_n`, `fill_n`, `generate_n`, `for_each_n`, `search_n`.

Example:

```cpp
auto numbers = std::set{1,2,3,4,5,6,7,8,9};
auto top5 = std::vector<int>(5);

std::copy_n(rbegin(numbers), 5, begin(top5));  // copy 5 largest elements
```


### 3.6 Heap Algorithms

Heap algorithms implement a **binary heap** on top of a random-access container (e.g. `std::vector`). 

* `std::make_heap` – turn a range into a heap (`~3N` comparisons).
* `std::push_heap` – incorporate last element into heap (`log N`).
* `std::pop_heap` – move the largest element to the end and restore heap invariant for remaining (`2 log N`).
* `std::sort_heap` – heap sort: repeatedly pop into sorted tail.

Example sequence (slides 32–36):

```cpp
std::vector<int> v{3, 1, 4, 1, 5, 9, 2, 6};

std::make_heap(begin(v), end(v));  // v now satisfies heap invariant
std::pop_heap(begin(v), end(v));   // largest moved to v.back()
v.pop_back();                      // remove largest
v.push_back(8);                    // add new element
std::push_heap(begin(v), end(v));  // restore heap
std::sort_heap(begin(v), end(v));  // fully sort
```

The diagrams show the vector content plus tree representation after each step.


### 3.7 Pitfalls When Using Algorithms

#### Mismatching iterator pairs

Both iterators in a range must come from the **same underlying sequence**, and advancing `first` must eventually reach `last` without leaving the container (slide 38). 

Buggy example:

```cpp
std::vector<unsigned> values1 = create_vector();
std::vector<unsigned> values2 = create_vector();

auto f = [](unsigned u) { /*...*/ };

std::for_each(begin(values1), end(values2), f);  // WRONG
```

* `begin(values1)` and `end(values2)` form a nonsensical range; behaviour is undefined.

#### Not reserving/allocating enough output space

When using algorithms that **write to an output iterator**, you must ensure the output destination is valid.

Bad example (slide 39): 

```cpp
std::set<unsigned> numbers{1,2,3,4,5,6,7,8,9};
std::vector<unsigned> primes{};   // empty, size() == 0

auto isPrime = [](unsigned u) { /*...*/ };

std::copy_if(begin(numbers), end(numbers),
             begin(primes),  // WRONG: no elements to write into
             isPrime);
```

Fix: either pre-size `primes` or use an **insert iterator**.

#### Insert iterators

To grow containers automatically (slide 40): 

```cpp
std::copy_if(begin(numbers), end(numbers),
             std::back_inserter(primes),  // uses push_back
             is_prime);
```

Other variants:

* `std::front_inserter(c)` – uses `push_front`.
* `std::inserter(c, pos)` – uses `insert` at position.

#### Iterator invalidation as side effect

Modifying a container while iterating over it with algorithms may invalidate iterators (slide 41).

Bad example:

```cpp
std::vector<unsigned> values{3, 0, 1, 4, 0, 2};
auto f = [&values](unsigned v) {
    values.push_back(v);  // may reallocate and invalidate iterators
};

std::for_each(begin(values), end(values), f); // UB
```

* `push_back` can reallocate when `size() > capacity()`, invalidating *all* iterators, including those used by `for_each`.

#### Returning a container by value and iterating over different instances

Example on slide 42: function `primes` returns a **vector by value**, but main calls it twice inside `begin()`/`end()`:

```cpp
auto primes(std::vector<unsigned> const& values) {
    std::vector<unsigned> primeValues{};
    copy_if(begin(values), end(values),
            back_inserter(primeValues),
            isPrime);
    return primeValues;   // return by value
}

int main() {
    std::istream_iterator<unsigned> inIter{std::cin};
    std::istream_iterator<unsigned> eof{};
    std::vector<unsigned> const values{inIter, eof};

    std::ostream_iterator<unsigned> out{std::cout};
    copy(begin(primes(values)), end(primes(values)), out);  // WRONG
}
```

* `begin(primes(values))` and `end(primes(values))` refer to **two different temporary vectors**; the range is meaningless → undefined behaviour (maybe nothing prints, maybe more). 

Correct approach: call `primes(values)` once, store the result, then use `begin/end` on that object.


### 3.8 C++20 `std::ranges` and Algorithm Catalog

#### `std::ranges` algorithms

C++20 introduces a unified notion of ranges and range-based algorithms (slide 43–44): 

* Use `std::ranges::begin` / `std::ranges::end`.
* Algorithms take containers/views directly, not just iterator pairs.

Example:

```cpp
std::vector<int> values{3, 1, 4, 1, 5, 9};

std::reverse(begin(values), end(values));      // classic
std::ranges::reverse(values);                  // ranges version
```

Ranges APIs clean up signatures and prevent some misuses (e.g. mismatched iterators).

#### Algorithm headers and categories

From `<algorithm>` (slide 47–49): 

* **Non-modifying sequence operations**

  * `all_of`, `any_of`, `none_of`
  * `find`, `find_if`, `find_if_not`, `find_end`, `find_first_of`, `adjacent_find`
  * `count`, `count_if`
  * `search`, `search_n`
  * `for_each`
  * `mismatch`, `equal`, `is_permutation`
* **Mutating sequence operations**

  * `copy*`, `move*`, `swap_ranges`
  * `transform`
  * `replace*`, `fill*`, `generate*`
  * `remove*`, `unique*`
  * `reverse*`, `rotate*`, `shuffle`
  * `is_partitioned`, `partition*`
* **Sorting and related operations**

  * `sort`, `stable_sort`, `partial_sort*`
  * `is_sorted`, `nth_element`
  * `lower_bound`, `upper_bound`, `equal_range`, `binary_search`
  * `merge`, `inplace_merge`, set algorithms (`set_union`, etc.)
  * Heap algorithms (`make_heap`, `push_heap`, `pop_heap`, `sort_heap`, `is_heap*`)
  * Min/max algorithms (`min`, `max`, `minmax*`)
  * Permutation algorithms (`next_permutation`, `prev_permutation`)

From `<numeric>` (slide 46):

* `accumulate`, `inner_product`, `partial_sum`, `adjacent_difference`, `iota`.

#### Execution policies (C++17/20)

Some algorithms accept an **execution policy** parameter (slide 50):

* `std::execution::seq` – sequential (default).
* `std::execution::par` – parallel (may use multiple threads).
* `std::execution::par_unseq` – parallel and vectorised (even more freedom for the implementation). 

These allow parallel and SIMD implementations without changing the algorithm call sites conceptually.


## 4. Relationships and Interpretation

* Containers + iterators (Weeks 7) become truly powerful only with **algorithms**:

  ```mermaid
  flowchart LR
    C[Container] -- begin/end --> R["Range<br/>(iterators)"]
    R --> A[Algorithm]
    A --> C2[Result container / value]
  ```

* Algorithms:

  * Express **intent** clearly (`find`, `max_element`, `copy_if`, `transform`).
  * Improve **correctness** by hiding common pitfalls (loop bounds, off-by-one).
  * Enable **optimisation** and parallelisation centrally in the library.

* Functors and predicates are the glue that customise algorithm behaviour (e.g. using a caseless comparator with `std::set`, or a lambda with `transform`).

* **Iterator categories** still matter: some algorithms require more capabilities (e.g. `sort` needs random access, heap algorithms likewise).

* `std::ranges` provides a more robust abstraction of ranges and will likely be the preferred way in modern C++ going forward.


## 5. Examples and Applications

* **Reverse a container**: `std::reverse` / `std::ranges::reverse`.
* **Filter values**: `std::copy_if` into a vector using `std::back_inserter`.
* **Find max/min**: `std::max_element`, `std::minmax_element`.
* **Build a “dictionary”**:
  `std::multiset<std::string, caseless>` with custom comparator for case-insensitive ordering.
* **Build a comma-separated string**: `std::accumulate` with string concatenation.
* **Unique / deduplicate**: `std::unique` followed by `erase` on a sorted vector.
* **Top-K elements**: `std::partial_sort` or `std::nth_element` (plus `sort` on the prefix).
* **Priority queues**: use `std::priority_queue`, or explicitly use `make_heap`, `push_heap`, `pop_heap` to implement a heap on a `std::vector`.


## 6. Summary / Takeaways

* Prefer **algorithms** over manual loops for correctness, readability, and performance. 
* Learn to **read algorithm signatures**: iterator types, callable requirements, return types.
* Use **functors**, **lambdas**, and **standard function objects** from `<functional>` to parameterise algorithms.
* Remember the **erase–remove idiom** for sequence containers.
* Use **insert iterators** (`back_inserter`, `front_inserter`, `inserter`) to avoid writing into unallocated memory.
* Be careful with:

  * **Mismatched iterator pairs**
  * **Iterator invalidation** when modifying containers
  * Ranges defined over **different temporary objects**
* Explore `<numeric>` algorithms like `accumulate` for non-numeric tasks.
* Understand heap algorithms and when they underlie higher-level abstractions like `std::priority_queue`.
* Recognise `std::ranges` and **execution policies** as modern extensions for safer, more powerful algorithm usage.


## 7. Study Hints

* Revisit your own code and try to replace manual loops with appropriate algorithms.
* Pick a container (e.g. `std::vector<int>`) and:

  * use `std::fill`, `std::generate`, `std::shuffle`, `std::sort`, `std::unique`, etc., in a small program.
* Implement small text utilities:

  * count word frequencies with `std::map` or `std::unordered_map` and `std::for_each` or `std::accumulate`;
  * filter lines or characters using `std::copy_if` and stream iterators.
* Experiment with the **_if** and **_n** versions to see where they simplify your code.
* For practice with pitfalls:

  * deliberately write code with mismatched iterator pairs or missing capacity, then fix it using inserters and correct ranges.
* Start using `std::ranges` equivalents (`std::ranges::sort`, `::reverse`, `::transform`) in new code to get used to the newer API.


## 8. Extensions / Further Concepts

* Deeper dive into **ranges**: views (`filter_view`, `transform_view`), pipelines (`vec | views::filter(...) | views::transform(...)`).
* Writing your **own algorithms** that follow STL conventions and accept iterator/range input.
* Designing custom **iterator types** and integrating them with algorithms.
* Combining algorithms with **parallel execution policies** to leverage multicore CPUs.
* Boost Iterator library (slide 52) as self-study: pre-built iterators for counting, filtering, transforming.


## 9. References & Literature (IEEE)

[1] ISO/IEC, *Programming Languages — C++ (ISO/IEC 14882:2020)*, International Organization for Standardization, 2020.

[2] N. M. Josuttis, *The C++ Standard Library: A Tutorial and Reference*, 2nd ed., Addison-Wesley, 2012.

[3] cppreference.com, “<algorithm>” and “<numeric>” – online reference for standard algorithms, accessed: [reader’s current date].

[4] T. Corbat, F. Morgner, *Modern and Lucid C++ for Professional Programmers – Week 8 – STL Algorithms*, OST – Ostschweizer Fachhochschule, HS2025. 
