# Modern and Lucid C++ for Professional Programmers – Week 12: Dynamic Polymorphism

## Overview

* **Topic of the unit:** Dynamic polymorphism, inheritance pitfalls, virtual functions, slicing, and safe design 
* **Lecturers:** Thomas Corbat, Felix Morgner 
* **Learning goals:**

  * Safely use virtual dispatch and inheritance
  * Understand the difference between shadowing and overriding
  * Recognise and avoid object slicing and member hiding
  * Design abstract base classes (pure virtual interfaces)
  * Use `std::unique_ptr` / `std::shared_ptr` with polymorphic types
  * Apply guidelines like the Liskov Substitution Principle (LSP)


## 1. Introduction / Context

This week ties together:

* **Smart pointers** from Week 11 (unique ownership vs shared ownership) with
* **Dynamic polymorphism** via virtual functions and inheritance.

C++ already provides strong **value semantics** and **compile-time polymorphism** (templates). Dynamic polymorphism is only needed when behaviour must vary at **run-time** (e.g. different GUI elements, strategies, or iostreams backends). 

The lecture emphasises:

* Virtual dispatch only works through **references or pointers**.
* Inheritance introduces **tight coupling** and several pitfalls (slicing, hiding, bad base interfaces).
* Use inheritance sparingly and deliberately.


## 2. Key Terms and Definitions

| Term                                    | Definition                                                                                                                                     |
| --------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------- |
| **Inheritance**                         | Relationship where a derived class extends a base class, inheriting its interface and (optionally) implementation.                             |
| **Dynamic polymorphism**                | Run-time selection of behaviour via **virtual functions** called through base references/pointers.                                             |
| **Shadowing (hiding)**                  | A derived member with the same name as a base member hides all base overloads of that name. Non-virtual, static binding.                       |
| **Virtual function**                    | Member function declared `virtual`; calls are dispatched based on the actual object type at run time when accessed via base reference/pointer. |
| **Override**                            | Redefinition of a virtual function in a derived class with the **same signature**; often marked with `override`.                               |
| **Pure virtual function**               | Virtual function with `= 0` and no implementation; makes the class **abstract** (non-instantiable).                                            |
| **Abstract base class**                 | Class with at least one pure virtual function; defines a common interface.                                                                     |
| **Object slicing**                      | Copying a derived object into a base object by value discards the derived part (extra data + behaviour).                                       |
| **Member hiding**                       | A derived function/variable with the same name hides base members with the same name, even with different signatures.                          |
| **Liskov Substitution Principle (LSP)** | Objects of a derived class must be substitutable wherever base objects are expected without breaking correctness.                              |


## 3. Main Content

### 3.1 Reasons for Using Inheritance

**Good use cases** (slide 9–10):

1. **Mix-in functionality** (often CRTP):

   * Empty base classes that add operators or helper functions.
   * No extra data, only behaviour.

   ```cpp
   struct Date : boost::equality_comparable<Date> {
       // provides == in terms of <, etc.
   };
   ```

2. **Adapting concrete classes**:

   * Small adapter that inherits from another class (no extra state).
   * E.g. `indexableSet` inheriting from `std::set` to add `operator[]`. 

3. **Dynamic binding / design patterns**:

   * Strategy, Template Method, Composite, Decorator …
   * Shared abstract interface `Base` with multiple implementations `Derived1`, `Derived2`, chosen at **run-time**.

The *GUI hierarchy diagram on page 10* shows `GuiElement` with derived `Button`, `TextBox`, `Group`, etc., all offering `display()`. Clients talk to `GuiElement`, concrete types supply behaviour. 

Similarly, the *iostream hierarchy on page 11* illustrates inheritance in the standard library (`istream`, `ostream`, `ifstream`, `ostringstream`, etc.).


### 3.2 Inheritance Syntax and Base Class Initialisation

Recap (slide 12):

```cpp
class Base {};
class DerivedPrivateBase : Base {};        // private inheritance (class)
struct DerivedPublicBase : Base {};        // public inheritance (struct)

struct MixIn {};
struct MultipleBases : public Base, private MixIn {};
```

* **Order in the base list matters** → defines base-class initialisation order. 
* For interface inheritance, bases should be **public**.
* Private inheritance is rarely appropriate except for certain mix-ins.

Base constructors are called in the order of base declaration, **not** the order in the member-initialiser list (slide 13–14):

```cpp
class DerivedWithCtor : public Base1, public Base2 {
    int mvar;
public:
    DerivedWithCtor(int i, int j)
    : mvar{j}, Base2{}, Base1{mvar} {}   // init order: Base1, Base2, mvar
};
```

Even though `Base2{}` appears before `Base1{mvar}`, the actual order is `Base1` then `Base2` then `mvar`. The compiler enforces this rule and may warn about “reordered initialiser list”.


### 3.3 Shadowing vs Virtual Dispatch

#### Shadowing member functions (non-virtual)

Example (slide 16):

```cpp
struct Base {
    auto sayHello() const -> void {
        std::cout << "Hi, I'm Base\n";
    }
};
struct Derived : Base {
    auto sayHello() const -> void {
        std::cout << "Hi, I'm Derived\n";
    }
};

auto greet(Base const& base) -> void {
    base.sayHello();
}

auto main() -> int {
    Derived derived{};
    greet(derived);     // prints "Hi, I'm Base"
}
```

* `Derived::sayHello` **shadows** `Base::sayHello`.
* With a parameter type `Base const&`, the static type is `Base`, so non-virtual call → `Base::sayHello`.

#### Virtual member functions

Same code but `virtual` (slide 17–18):

```cpp
struct Base {
    virtual auto sayHello() const -> void {
        std::cout << "Hi, I'm Base\n";
    }
};
struct Derived : Base {
    auto sayHello() const -> void override {
        std::cout << "Hi, I'm Derived\n";
    }
};
```

Now:

```cpp
Derived d{};
greet(d);    // prints "Hi, I'm Derived"
```

* `virtual` enables **dynamic dispatch** through base references/pointers.
* Mark overrides with `override` so the compiler checks you are actually overriding something (signature must match exactly, including `const`-ness and parameter list). 

#### Signature rules (slide 19)

To override:

* Signature must be identical.
* `const` is part of the signature.
* A different parameter list → **overload**, not override.

```cpp
struct Base {
    virtual auto sayHello() const -> void;
};

struct Bad1 : Base {
    auto sayHello() -> void override;              // error: missing const
};

struct Bad2 : Base {
    auto sayHello(std::string) const -> void override;  // error: different params
};
```


### 3.4 How Virtual Functions Are Actually Called

**Value parameter vs reference parameter** (slide 20–21):

```cpp
auto greet(Base base) -> void {      // by value
    base.sayHello();                // always Base::sayHello
}

auto greet(Base const& base) -> void { // by const reference
    base.sayHello();                // dynamic: depends on actual type
}
```

Through pointers/smart pointers (slide 21):

```cpp
auto greet(std::unique_ptr<Base> base) -> void {
    base->sayHello();               // dynamic
}

auto greet(Base const* base) -> void {
    base->sayHello();               // dynamic
}
```

**Rule of thumb:**

* Dynamic polymorphism requires **base class reference or pointer**; passing objects **by value** leads to slicing and static binding.


### 3.5 Mixed Example: Virtual / Non-virtual, Slicing, Construction

The *animal/bird/hummingbird example on page 22* shows several issues:

```cpp
struct Animal {
    auto makeSound() -> void { cout << "---\n"; }
    virtual auto move() -> void { cout << "---\n"; }
    Animal()  { cout << "animal born\n"; }
    ~Animal() { cout << "animal died\n"; }
};

struct Bird : Animal {
    virtual auto makeSound() -> void { cout << "chirp\n"; }
    auto move() -> void { cout << "fly\n"; }
    Bird()  { cout << "bird hatched\n"; }
    ~Bird() { cout << "bird crashed\n"; }
};

struct Hummingbird : Bird {
    auto makeSound() -> void { cout << "peep\n"; }
    virtual auto move() -> void { cout << "hum\n"; }
    Hummingbird()  { cout << "hummingbird hatched\n"; }
    ~Hummingbird() { cout << "hummingbird died\n"; }
};
```

Main:

```cpp
Hummingbird hummingbird;
Bird bird = hummingbird;          // slicing: only Bird part copied
Animal& animal = hummingbird;

hummingbird.makeSound(); // "peep"
bird.makeSound();        // "chirp" (sliced)
animal.makeSound();      // "peep" or "chirp"? (non-virtual in Animal)
```

Problems:

* `Animal::makeSound` is **non-virtual** but overridden in derived classes → calls depend on static type.
* `Bird bird = hummingbird;` slices away `Hummingbird` part.
* Destructors are non-virtual; if pointer-to-base were used for heap objects, destruction would be wrong.

Takeaway: if you expect overridden behaviour, make functions `virtual` in the base and avoid passing/assigning polymorphic objects by value. 


### 3.6 Abstract Base Classes (Interfaces)

C++ has no `interface` keyword, but **abstract classes** via pure virtual functions (slide 23):

```cpp
struct AbstractBase {
    virtual void doitnow() = 0;  // pure virtual
};
```

* A pure virtual function (`= 0`) has no implementation (or at least none that must be provided).
* Abstract classes **cannot be instantiated**.

The example:

```cpp
AbstractBase create() {
    return AbstractBase{};        // error: abstract type
}
```


### 3.7 Virtual Destructors

If a class has **any virtual member**, its destructor should be virtual (or at least protected) when used polymorphically:

#### Non-virtual destructor (slide 24)

```cpp
struct Fuel {
    virtual auto burn() -> void = 0;
    ~Fuel() { std::cout << "put into trash\n"; }
};

struct Plutonium : Fuel {
    auto burn() -> void { std::cout << "split core\n"; }
    ~Plutonium() { std::cout << "store many years\n"; }
};

auto main() -> int {
    std::unique_ptr<Fuel> surprise = std::make_unique<Plutonium>();
}
```

Output:

```text
put into trash
```

* Only `Fuel`’s destructor runs → resource leak / UB in real code.

#### Virtual destructor (slide 25)

```cpp
struct Fuel {
    virtual auto burn() -> void = 0;
    virtual ~Fuel() { std::cout << "put into trash\n"; }
};
```

Now output:

```text
store many years
put into trash
```

* `Plutonium` destroyed first, then `Fuel`.

#### `std::shared_ptr` case (slide 26)

With `std::shared_ptr<Fuel> surprise = std::make_shared<Plutonium>();` the output is correct even without virtual destructor because `shared_ptr` remembers the **concrete type** in its control block. Still, the guideline stands: if you intend polymorphic deletion via `Base*`/`unique_ptr<Base>`, make the destructor virtual or protected.


### 3.8 Why Inheritance Can Be Bad

Slides 27–31 discuss **software engineering drawbacks**:

1. **Strong coupling**:

   * Base & derived are tightly bound; changing the base is hard.
   * Base API must suit all current and future subclasses → difficult design problem.

2. **Conceptual hierarchies** often misleading:

   * Classic `Animal → Bird → Duck` examples rarely map cleanly to software needs.
   * In practice, behaviour often doesn’t align with a strict tree. 

3. **Object slicing via pass-by-value** (slide 28):

```cpp
struct Base {
    int member{};
    explicit Base(int initial) : member{initial} {}
    virtual ~Base() = default;
    virtual auto modify() -> void { member++; }
    auto print(std::ostream& out) const -> void;
};

struct Derived : Base {
    using Base::Base;
    auto modify() -> void { member += 2; }
};

auto modifyAndPrint(Base base) -> void {  // slicing here
    base.modify();                        // calls Base::modify
    base.print(std::cout);
}

int main() {
    Derived derived{25};
    modifyAndPrint(derived);              // output: 26
}
```

* `derived` is **copied** into `base` parameter; only `Base` subobject survives → behaviour lost.

4. **Member hiding** (slide 29–30):

```cpp
struct Base {
    virtual void modify();
};

struct Derived : Base {
    using Base::Base;
    void modify(int value) { member += value; }  // hides Base::modify()
};
```

`derived.modify();` is ill-formed (no zero-arg overload) unless you bring `Base::modify` into scope:

```cpp
struct Derived : Base {
    using Base::Base;
    using Base::modify;    // re-expose base overloads

    void modify(int value) { member += value; }
};
```

5. **Assignment of polymorphic objects** (slide 31–32):

Copy-assigning a `Book` reference that actually refers to an `EBook` instance destroys the derived invariants:

```cpp
Book& some = designPatterns; // EBook
some = refactoring;          // overwrites only Book part
```

* The `Book` subobject is copied, but derived data (e.g. `currentPageNumber`) is untouched → inconsistent object state.

To prevent this, delete copy operations in the base (slide 33):

```cpp
struct Book {
    Book(Book const&)            = delete;
    auto operator=(Book const&) -> Book& = delete;
};
```

Derived can then define copy operations for **EBook** specifically.


## 4. Relationships and Interpretation

Dynamic polymorphism in C++:

* Requires **virtual member functions**.
* Works only through **references/pointers/smart pointers** to the base.
* Interacts deeply with:

  * **Object lifetime** (virtual destructor, smart pointers),
  * **Value semantics** (slicing),
  * **Overload resolution and name lookup** (member hiding).

Compile-time polymorphism (templates) is often **more efficient and simpler** when dynamic run-time flexibility is not required.

Inheritance should be used only when:

* There is a clear, stable **abstraction** that multiple implementations share.
* Subclasses truly satisfy the **Liskov Substitution Principle** (slide 35):

  * They preserve base invariants.
  * They accept the same argument types (no narrowing).
  * They return results compatible with base expectations (covariant returns are allowed, but semantics must remain consistent). 


## 5. Examples and Applications

* **GUI toolkit**:
  Base `GuiElement` with virtual `display()`; derived `Button`, `TextBox`, `Group`. Container holds `std::unique_ptr<GuiElement>`.

* **Pluggable strategy**:
  `Strategy` base with `execute()`; switch strategies at run time by swapping `std::unique_ptr<Strategy>`.

* **I/O abstraction**:
  `std::ostream` hierarchy; factories returning `std::shared_ptr<std::ostream>` (file vs string stream).

* **Resource types**:
  `Fuel` base with virtual `burn()` and virtual destructor; `Plutonium` and other fuels as derived classes.

In each case, clients hold **pointers/ref to base**, never by-value objects.


## 6. Summary / Takeaways

* C++ already offers **strong value semantics** and **templates**; reach for **dynamic polymorphism only when needed**. 
* Use inheritance for:

  * mix-ins (no data),
  * small adapters,
  * dynamic polymorphism where a stable abstraction exists.
* Distinguish **shadowing** from **overriding**:

  * Use `virtual` + `override`.
  * Make signatures match exactly.
* Virtual dispatch requires **base references or pointers**; passing by value slices.
* Member hiding can break overloads; restore them with `using Base::foo;`.
* Classes with virtual functions should have **virtual (or protected) destructors**, especially with `unique_ptr<Base>`.
* Avoid assignment and copying through base-class interfaces; delete copy operations in polymorphic bases.
* Follow **LSP**: subclasses must be safe drop-in replacements for base types.


## 7. Study Hints

* Rewrite a small class hierarchy with:

  * proper `virtual` functions,
  * `override` annotations,
  * virtual destructor,
  * and test calls via base references/pointers.
* Create examples that:

  * demonstrate **slicing** (pass-by-value) vs correct behaviour (pass-by-ref),
  * show **member hiding** and fix it with `using Base::...`.
* Design a simple **strategy** or **composite** pattern using `std::unique_ptr<Base>` and verify destruction order.
* Take an existing “is-a” hierarchy (e.g. animals, vehicles) and examine whether it really fits LSP; think about where inheritance may be the wrong tool.


## 8. Further / Advanced Concepts

* Interfaces with **pure virtual functions only**, possibly with default implementations in separate helpers.
* Alternatives to inheritance:

  * **Composition** and **delegation**,
  * **std::variant** and **visitors**,
  * Concepts and templates for compile-time polymorphism.
* Performance aspects of virtual calls vs inlining and templates.
* Type erasure (e.g. `std::function`, `std::any`) as another way to achieve runtime polymorphism without explicit inheritance.


## 9. References & Literature (IEEE)

[1] ISO/IEC, *Programming Languages — C++ (ISO/IEC 14882:2020)*, International Organization for Standardization, 2020.

[2] B. Stroustrup, *The C++ Programming Language*, 4th ed., Addison-Wesley, 2013.

[3] N. M. Josuttis, *The C++ Standard Library: A Tutorial and Reference*, 2nd ed., Addison-Wesley, 2012.

[4] T. Corbat, F. Morgner, *Modern and Lucid C++ for Professional Programmers – Week 12 – Dynamic Polymorphism*, OST – Ostschweizer Fachhochschule, HS2025. 
