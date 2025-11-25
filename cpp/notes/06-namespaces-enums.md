# Modern and Lucid C++ for Professional Programmers – Week 6: Namespaces and Enums

## Overview

* **Topic of this unit:** Namespaces, Argument Dependent Lookup (ADL), enumerations, custom arithmetic types (Ring5) 
* **Lecturers:** Thomas Corbat, Felix Morgner 
* **Learning objectives:**

  * Group and structure names using namespaces
  * Understand and exploit Argument Dependent Lookup (ADL)
  * Define and use enumerations (scoped and unscoped)
  * Specify enumerator values and underlying types
  * Overload operators for enums (e.g. `++`, `<<`)
  * Implement a simple arithmetic type (Ring5) and understand conversion ambiguities
  * Glimpse advanced topics: `constexpr` and user-defined literals


## 1. Introduction / Context

This week continues the design of **types and interfaces**:

* Namespaces solve **name clashes** and help structure code.
* ADL ties functions/operators to the **namespace of their argument types**, enabling natural calls without over-qualification.
* Enumerations (`enum`, `enum class`) provide **small, typed sets of values** instead of magic integers.
* A simple arithmetic type **Ring5** is used to show how to:

  * enforce invariants (`0..4`),
  * overload arithmetic operators,
  * handle **mixed arithmetic** and conversions.
* The final slides give a preview of **compile-time evaluation** (`constexpr`) and **user-defined literals** for improving syntax. 


## 2. Key Terms and Definitions

| Term                                | Definition                                                                                                                                 |
| ----------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------ |
| **Namespace**                       | A named scope that groups related declarations and avoids name clashes, e.g. `std`, `calendar`.                                            |
| **Global namespace**                | The outermost namespace; referenced by a leading `::` (e.g. `::std::cout`).                                                                |
| **Using declaration**               | `using std::string;` – brings a single name into the current scope.                                                                        |
| **Using directive**                 | `using namespace std;` – brings **all** names from a namespace into scope; can pollute scope.                                              |
| **Anonymous namespace**             | `namespace { ... }` – a unique unnamed namespace per translation unit; gives **internal linkage** to its contents.                         |
| **Argument Dependent Lookup (ADL)** | Name lookup rule: for an unqualified function/operator call, the compiler also searches the namespaces associated with the argument types. |
| **Enumeration (`enum`)**            | A type with a finite set of named integral values (enumerators).                                                                           |
| **Unscoped enum**                   | `enum Day {Mon,...};` – enumerators leak into surrounding scope; implicitly convertible to `int`.                                          |
| **Scoped enum**                     | `enum class Day {Mon,...};` – enumerators are qualified (`Day::Mon`), no implicit conversion to `int`.                                     |
| **Underlying type**                 | The integral type used to represent an enum’s values (e.g. `enum class State : unsigned short`).                                           |
| **Enumerator**                      | A named constant inside an enum, like `Mon`, `Tue`, `Sun`.                                                                                 |
| **Arithmetic type (Ring5)**         | User-defined numeric type with operations behaving like mathematical arithmetic (here: modulo 5).                                          |
| **User-defined literal (UDL)**      | Custom suffix for literals (e.g. `4_r5`) invoking an `operator"" _r5`.                                                                     |


## 3. Main Content

### 3.1 Namespaces and Scoping

**Purpose of namespaces** (slide 8):

* Group related names; prevent collisions.
* Allow the same name in different scopes: e.g. three different `Spring` types in `seasons`, `waters`, `machinery` on page 19. 
* Global namespace: referenced as `::`. `::std::cout` and `std::cout` are usually equivalent.

**Defining and using namespaces** (slide 9):

```cpp
namespace demo {
auto foo() -> void;           // declaration #1

namespace subdemo {
auto foo() -> void { /* #2 */ }
} // namespace subdemo
} // namespace demo

namespace demo {
auto bar() -> void {
    foo();          // calls #1 (demo::foo)
    subdemo::foo(); // calls #2 (demo::subdemo::foo)
}
}

auto demo::foo() -> void { /* #1 */ }

auto main() -> int {
    using demo::subdemo::foo;
    foo();       // #2, found via using declaration
    demo::foo(); // #1
    demo::bar();
}
```

Key points:

* Namespaces can be **opened multiple times** across files to collect declarations/definitions.
* Qualified names: `demo::subdemo::foo()`.
* A leading `::` indicates a **fully-qualified** name from the global namespace (e.g. `::std::cout`). 

#### Using declarations and directives (slide 10)

* **Using declaration** – imports one name:

```cpp
using std::string;
string s{"no std:: prefix"};
```

* **Type alias** (shorter name):

```cpp
using input = std::istream_iterator<int>;
input eof{};
```

* **Using directive** – imports all names:

```cpp
auto main() -> int {
    using namespace std;
    cout << "Hello John";   // OK, but namespace std now “pollutes” this scope
}
```

> Recommendation:
>
> * Prefer **using declarations** and **aliases**.
> * Use `using namespace` only in **local scopes** (e.g. inside a function), never in headers. 

#### Anonymous namespaces (slide 11)

```cpp
namespace { // anonymous
auto doit() -> void {
    std::cout << "doit called\n";
}
} // anonymous namespace

auto print() -> void {
    doit(); // OK: same translation unit
    std::cout << "print called\n";
}
```

* Contents have **internal linkage** – not visible in other translation units.
* Great for hiding helper functions/constants inside `.cpp` files.
* In another file:

```cpp
auto caller() -> void {
    void print();
    print();      // OK, declared & linked

    void doit();  // declaration only – no matching external symbol
    doit();       // link error
}
```


### 3.2 Namespaces for Types and ADL

**Placing `Date` in a namespace** (slides 12–13):

```cpp
// Date.hpp
namespace calendar {
class Date {
    auto tomorrow() const -> Date;
};
}

// Date.cpp
auto calendar::Date::tomorrow() const -> Date { /* ... */ }
```

Usage:

```cpp
calendar::Date d{};
```

Member definitions are qualified with both namespace and class: `auto calendar::Date::tomorrow() -> Date`. 

#### Argument Dependent Lookup (ADL) (slides 14–16)

Idea:

* For **unqualified** function/operator calls (no `::` prefix), the compiler:

  * searches the current scope,
  * **plus** the namespaces associated with the argument types.

Example from page 14:

```cpp
namespace calendar {
class Date { /* ... */ };
auto isHoliday(Date const&) -> bool;
}

[](calendar::Date const& d) {
    if (isHoliday(d)) {      // ADL: finds calendar::isHoliday
        // ...
    }
};
```

Because `d` is of type `calendar::Date`, ADL searches namespace `calendar` and finds `isHoliday`.

Similarly, `std::for_each` can be found via ADL when passed iterators from `std::vector` (in namespace `std`), even without qualifying with `std::`. 

#### ADL and operators (slide 15)

* You cannot write `std::cout calendar::<< birthday;` – operator syntax doesn’t allow qualifying on the left.
* For `std::cout << birthday;`, ADL looks into:

  * `std` (for `std::ostream`), and
  * `calendar` (for `calendar::Date`).

Place your `operator<<` in `calendar` so ADL can find it.

```cpp
namespace calendar {
class Date {
    auto operator<(Date const& rhs) const -> bool;
};

inline auto operator>(Date const& lhs, Date const& rhs) -> bool {
    return rhs < lhs;
}
}
```

Then:

```cpp
calendar::Date lower{1981, 1, 1};
calendar::Date upper{1996, 12, 31};
return birthday > lower && birthday < upper; // operators found via ADL
```

#### ADL examples and pitfalls (slides 16–18)

Example (simplified):

```cpp
namespace one {
struct type_one{};
auto f(type_one) -> bool;
}

namespace two {
struct type_two{};
auto f(type_two) -> void;
auto g(one::type_one) -> void;
auto h(one::type_one) -> void;
}

auto g(two::type_two) -> void; // global
```

* `f(t1)` where `t1` is `one::type_one` → ADL finds `one::f`.
* `f(t2)` where `t2` is `two::type_two` → ADL finds `two::f`.
* `g(t1)` (unqualified) → candidates:

  * `two::g(one::type_one)` via ADL (namespace of argument’s type),
  * plus global `g(two::type_two)` if considered, but argument type mismatch.

> The **code snippet on page 16** lists which calls compile and which fail due to argument type mismatch and ADL. 

**ADL “intuition fail” with `std`** (slide 17):

* A generic algorithm with `std::ostream_iterator<std::vector<int>>` may **not** find a global `operator<<` for `std::vector<int>`, because:

  * both arguments (`std::ostream`, `std::vector<int>`) are from **namespace std**,
  * ADL only searches `std`, not the global namespace.
* The “tempting” workaround – putting your operator in `namespace std` – is **undefined behavior** (not allowed to add user-defined overloads to `std` except some very specific cases).

Workaround on page 18:

* Wrap `std::vector<int>` in your own type:

```cpp
namespace X {
struct vec : std::vector<int> {
    using std::vector<int>::vector;  // inherit constructors
};

auto operator<<(std::ostream& os, vec const& v) -> std::ostream& {
    std::copy(begin(v), end(v), std::ostream_iterator<int>{os, ","});
    return os;
}
}
```

* ADL now sees `X::vec` in namespace `X`, where your `operator<<` lives.


### 3.3 Enumerations

#### Basic syntax and semantics (slide 21)

```cpp
enum DayOfWeek {
    Mon, Tue, Wed, Thu, Fri, Sat, Sun
};

enum class DayOfWeek2 {
    Mon, Tue, Wed, Thu, Fri, Sat, Sun
};
```

* Enums are useful when a type can only take **a few named values**.
* Enumerators start at `0` and increment by `1` unless you override them.
* Conversion:

  * Unscoped enums: implicit conversion **to** `int` allowed.
  * Scoped enums: no implicit conversion to `int` – must use `static_cast`. 

Example (slide 22):

```cpp
enum DayOfWeek { Mon, Tue, Wed, Thu, Fri, Sat, Sun };
int day = Sun;  // OK, implicit

DayOfWeek tuesday = static_cast<DayOfWeek>(1);

enum class DayOfWeek2 { Mon, Tue, Wed, Thu, Fri, Sat, Sun };
int day2 = static_cast<int>(DayOfWeek2::Sun);  // requires cast
```

#### Scope of enumerators (slide 23)

* **Unscoped enum**:

```cpp
namespace calendar {
enum DayOfWeek { Mon, Tue, Wed, Thu, Fri, Sat, Sun };
}

auto isWeekend(calendar::DayOfWeek day) -> bool {
    return day == calendar::Sat || day == calendar::Sun;
}
```

Enumerators (`Mon`, ` Tue`, …) “leak” into `calendar`’s scope.

* **Scoped enum**:

```cpp
namespace calendar {
enum class DayOfWeek { Mon, Tue, Wed, Thu, Fri, Sat, Sun };
}

auto isWeekend(calendar::DayOfWeek day) -> bool {
    return day == calendar::DayOfWeek::Sat
        || day == calendar::DayOfWeek::Sun;
}
```

Enumerators are qualified (`calendar::DayOfWeek::Sat`).

> The **Right or Wrong?** example on page 29 shows that with a scoped enum you **must** write `Glass::Empty`, not `Empty`. 

#### Operators for enums (slide 24)

You can overload operators for enums. Example: incrementing `DayOfWeek` cyclically:

```cpp
enum DayOfWeek { Mon, Tue, Wed, Thu, Fri, Sat, Sun };

auto operator++(DayOfWeek& aday) -> DayOfWeek {
    int day = (aday + 1) % (Sun + 1);
    aday = static_cast<DayOfWeek>(day);
    return aday;      // prefix ++
}

auto operator++(DayOfWeek& aday, int) -> DayOfWeek {
    DayOfWeek ret{aday};
    if (aday == Sun) {
        aday = Mon;
    } else {
        aday = static_cast<DayOfWeek>(aday + 1);
    }
    return ret;       // postfix ++
}
```

#### Specifying enumerator values (slide 25)

```cpp
enum Month {
    jan = 1, feb, mar, apr, may,
    jun, jul, aug, sep, oct, nov, dec,
    january = jan, february, march,
    april, june = jun, july, august,
    september, october, november,
    december
};
```

* Explicit values with `=`.
* Subsequent enumerators auto-increment from the last specified value.
* Multiple enumerators may share the same value.

**Bitmask enums**:

```cpp
enum FilePermissions {
    readable  = 1, // 0b001
    writeable = 2, // 0b010
    executable = 4 // 0b100
};
```

Values are powers of 2 to allow bitwise combination. 

#### Output operator for enums (slide 26)

Names don’t automatically map back from enum value to string, but you can build a lookup:

```cpp
auto operator<<(std::ostream& out, Month m) -> std::ostream& {
    static std::array<std::string, 12> const monthNames{
        "Jan","Feb","Mar","Apr","May","Jun",
        "Jul","Aug","Sep","Oct","Nov","Dec"
    };
    out << monthNames[m - 1];  // since jan = 1
    return out;
}
```

#### Underlying types and forward-declared enums (slides 27–28)

You can specify the **underlying type**:

```cpp
enum class State : unsigned short;
```

Useful for forward-declarations and controlling size/layout.

State machine example (slide 28):

```cpp
struct Statemachine {
    Statemachine();
    auto processInput(char c) -> void;
    auto isDone() const -> bool;
private:
    enum class State : unsigned short;
    State theState;
};

// In .cpp:
enum class Statemachine::State : unsigned short { begin, middle, end };

Statemachine::Statemachine()
: theState{State::begin} {}

auto Statemachine::processInput(char c) -> void {
    switch (theState) {
    case State::begin:
        if (!isspace(c)) theState = State::middle;
        break;
    case State::middle:
        if (isspace(c)) theState = State::end;
        break;
    case State::end:
        break;
    }
}

auto Statemachine::isDone() const -> bool {
    return theState == State::end;
}
```

This hides the concrete enum values from users of the class while still allowing an efficient internal representation. 


### 3.4 Arithmetic Types: `Ring5`

Goal: implement a simple arithmetic type representing integers **modulo 5** (slides 31–37).

#### Basic definition and invariant

```cpp
struct Ring5 {
    explicit Ring5(unsigned x = 0u)
    : val{x % 5} {}

    auto value() const -> unsigned { return val; }

private:
    unsigned val;  // invariant: 0..4
};
```

* Invariant: `val` always in `0..4`.
* Constructor enforces it using `% 5`. 

#### Equality comparison (slide 32)

```cpp
struct Ring5 {
    auto operator==(Ring5 const& r) const -> bool = default;
    // ...
};
```

Test:

```cpp
TEST_CASE("testValueCtorWithLargeInput") {
    Ring5 four{19};
    REQUIRE(four == Ring5{4});  // 19 % 5 == 4
}
```

#### Output operator (slide 33)

```cpp
auto operator<<(std::ostream& out, Ring5 const& r) -> std::ostream& {
    out << "Ring5{" << r.value() << '}';
    return out;
}
```

Used by tests and debugging:

```cpp
TEST_CASE("testOutputOperator") {
    std::ostringstream out{};
    out << Ring5{4};
    REQUIRE(out.str() == "Ring5{4}");
}
```

#### Addition (slide 34)

```cpp
struct Ring5 /* : boost::addable<Ring5> */ {
    auto operator+=(Ring5 const& r) -> Ring5& {
        val = (val + r.val) % 5;
        return *this;
    }
    // ...
};
```

`operator+` can be derived automatically via `boost::addable<Ring5>` or written manually:

```cpp
inline auto operator+(Ring5 l, Ring5 const& r) -> Ring5 {
    l += r;
    return l;
}
```

Test:

```cpp
TEST_CASE("testAdditionWrap") {
    Ring5 four{4};
    Ring5 three = four + four;      // (4 + 4) % 5 == 3
    REQUIRE(three == Ring5{3});
}
```

#### Multiplication (slide 35)

```cpp
struct Ring5 {
    auto operator*=(Ring5 const& r) -> Ring5& {
        val = (val * r.val) % 5;
        return *this;
    }
    // ...
};

inline auto operator*(Ring5 l, Ring5 const& r) -> Ring5 {
    l *= r;
    return l;
}
```

Modulo is applied in `*=` to avoid duplication.

#### Mixed arithmetic & conversion pitfalls (slides 36–37)

Goal: allow `Ring5` + `unsigned`.

Option 1 – **explicit overloads**:

```cpp
inline auto operator+(Ring5 const& l, unsigned r) -> Ring5 {
    return Ring5{l.value() + r};
}

inline auto operator+(unsigned l, Ring5 const& r) -> Ring5 {
    return Ring5{l + r.value()};
}
```

Two tests (page 36):

```cpp
TEST_CASE("testAdditionWithIntValueIsFour") {
    Ring5 two{2};
    auto four = two + 2u;
    REQUIRE(four == Ring5{4});
}

TEST_CASE("testAdditionWithIntTypeIsRing5") {
    Ring5 two{2};
    auto four = two + 2u;
    REQUIRE(typeid(decltype(four)).name() == typeid(Ring5).name());
}
```

Option 2 – **implicit conversion constructor + conversion operator**:

```cpp
struct Ring5 {
    Ring5(unsigned x) : val{x % 5} {}
    operator unsigned() const { return val; }
    // ...
};
```

* Non-`explicit` ctor allows conversion `unsigned -> Ring5`.
* Conversion operator allows `Ring5 -> unsigned`.

> Danger: **ambiguity and surprising conversions** – compiler might choose the “wrong direction,” especially in overload sets or templates. That’s why the slides emphasise being careful with implicit conversion operators (page 37). 


## 4. Relationships and Interpretation

* **Namespaces** provide structure and avoid clashes; ADL then uses those namespaces to find functions/operators “near” the types they operate on.
* **Enums** give expressive, type-safe alternatives to “magic numbers” and integrate well with namespaces (e.g. `calendar::DayOfWeek`).
* **Scoped enums** are safer: no implicit integer conversions, no enumerator leakage.
* **Arithmetic types** like `Ring5` combine:

  * a clear **invariant**,
  * operator overloading,
  * careful decisions about **implicit vs. explicit** conversions.
* ADL issues with `std` highlight why you should design your own types (wrappers) instead of injecting stuff into `std`.


## 5. Examples and Applications

* **Namespaces:**

  * Organise a date/time library under `namespace calendar { ... }`.
  * Put your geometry types into `namespace geo { ... }` and use ADL to locate `intersects`, `distance`, etc.
* **Enums:**

  * Represent traffic light states, protocol states, or file permissions with enums instead of raw ints.
  * Use scoped enums (`enum class`) for compile-time safety and better scoping.
* **Ring5:**

  * Model modular arithmetic for toy cryptography or test frameworks.
  * Experiment with other rings, e.g. `Ring7` or `Clock12`.
* **State machine example (Statemachine):**

  * Translate parsing logic or UI states into an internal `enum class State` with a `processInput` function.


## 6. Summary / Takeaways

* Namespaces group related declarations and allow the “same name in different worlds.”
* ADL lets unqualified function/operator calls find implementations in the namespaces of their argument types.
* Enums model small sets of discrete values; **scoped** enums avoid implicit conversions and name clashes.
* You can assign explicit values, implement bitmask enums, and customise printing for enums.
* Arithmetic types like `Ring5` must enforce invariants and supply natural operators; be very cautious with implicit conversions (`explicit` is usually safer).
* Advanced tools (`constexpr`, user-defined literals) can make such types efficient and syntactically pleasant.


## 7. Study Tips

* **Namespace practice:**

  * Move existing classes into a `namespace` and fix call sites using ADL where possible.
  * Add an anonymous namespace to a `.cpp` file and hide helper functions in it.
* **Enum drills:**

  * Convert several `int`-based flags into enums (scoped and unscoped).
  * Implement `operator<<` for your enums using a lookup table.
* **Ring5 exercises:**

  * Add subtraction and division (where valid in modulo 5).
  * Experiment with making the constructor `explicit` vs. non-`explicit` and observe where compilation breaks or becomes ambiguous.
* **ADL inspection:**

  * For a small type of your own, move its free functions into the same namespace and see when you can drop namespace qualifications at call sites.


## 8. Extensions / Further Concepts

The last slides give a teaser of:

* **Compile-time evaluation with `constexpr`**:

  * Mark `Ring5` constructors and operators as `constexpr` to enable compile-time computations and `static_assert` checks. 
* **User-defined literals (UDLs)**:

  * Define `4_r5` as shorthand for `Ring5{4}` via:

    ```cpp
    namespace R5 {
    constexpr auto operator"" _r5(unsigned long long v) -> Ring5 {
        return Ring5{static_cast<unsigned>(v % 5)};
    }
    }
    using namespace R5;
    static_assert(Ring5{2} == 7_r5);
    ```

These topics are handled in more detail in the Advanced C++ part of the course.


## 9. References & Literature (IEEE)

[1] ISO/IEC, *Programming Languages — C++ (ISO/IEC 14882:2020)*, International Organization for Standardization, 2020.

[2] B. Stroustrup, *The C++ Programming Language*, 4th ed., Addison-Wesley, 2013.

[3] N. M. Josuttis, *The C++ Standard Library: A Tutorial and Reference*, 2nd ed., Addison-Wesley, 2012.

[4] Lecture slides “Modern and Lucid C++ for Professional Programmers – Week 6 – Namespaces and Enums”, OST – Ostschweizer Fachhochschule, HS2025. 
