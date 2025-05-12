# Parallel Programming – Week 7 Summary

**Topic:** Memory Models
**Instructor:** Mitra Purandare
**Institution:** OST – Ostschweizer Fachhochschule
**Date:** April 3, 2025

---

## 1. Learning Goals

* Understand the **Java and .NET memory models**
* Use **atomic instructions** and **volatile variables**
* Grasp the design of **lock-free data structures**

---

## 2. Motivation for Lock-Free Programming

* Synchronize concurrent operations **without using locks**
* Use **memory model guarantees** for correctness
* Goal: **efficient and scalable** concurrency control

---

## 3. The Problem: Instruction Reordering

### Code Example

```java
x = y = 0;

Thread 1:
x = 1;
j = y;

Thread 2:
y = 1;
i = x;
```

* Due to **reordering**, both `i` and `j` could be `0`, even though logically that seems impossible.
* Caused by **compiler/runtime/CPU optimizations**.

---

## 4. Java Memory Model (JMM)

### Guarantees:

| Concept    | Description                                                              |
| ---------- | ------------------------------------------------------------------------ |
| Atomicity  | 32-bit primitives and object references are atomic by default            |
| Visibility | One thread’s writes become visible to others under specific conditions   |
| Ordering   | Memory operations may be reordered unless synchronization enforces order |

---

## 5. Atomicity in Java

* **Guaranteed Atomic Types**: All 32-bit primitive types and object references
* **Not Guaranteed**: `long` and `double` without `volatile`
* **Atomic does NOT mean visible**: Another thread may not see the updated value

---

## 6. Visibility in Java

### Guaranteed By:

* **Lock release/acquire**
* **Volatile write → volatile read**
* **Thread start/join**
* **Final fields after constructor**

### Example (broken):

```java
while (doRun) {
  // infinite loop possible
}
```

### Fix:

```java
private volatile boolean doRun = true;
```

---

## 7. Ordering in Java

* Partial order: Writes before a volatile write are visible after a volatile read
* Total order: No reordering of:

  * `synchronized` blocks
  * Volatile accesses
  * Thread start/join

### Example: Rendez-Vous

```java
Thread 1: a = true; while (!b) {}
Thread 2: b = true; while (!a) {}
```

* Works if `a` and `b` are `volatile`

---

## 8. Spin Lock: Incorrect Implementation

### Problem:

```java
while (locked) {}
locked = true;
```

* Not atomic. Multiple threads may pass the check before setting `locked = true`.

### Correct Version (with atomic operation):

```java
AtomicBoolean locked = new AtomicBoolean(false);
while (locked.getAndSet(true)) {}
```

---

## 9. Atomic Operations in Java

* Provided via classes in `java.util.concurrent.atomic`:

  * `AtomicBoolean`, `AtomicInteger`, `AtomicLong`, `AtomicReference`
* Support:

  * `getAndSet()`
  * `compareAndSet()`
  * `updateAndGet()`, etc.

---

## 10. Optimistic Synchronization Pattern

```java
do {
  oldValue = atomicVar.get();
  newValue = modify(oldValue);
} while (!atomicVar.compareAndSet(oldValue, newValue));
```

* Retry until the update succeeds
* Enables **lock-free concurrent updates**

---

## 11. Lock-Free Data Structures

### Example: Treiber Stack

```java
AtomicReference<Node<T>> top;

void push(T value) {
  Node<T> newNode = new Node<>(value);
  do {
    Node<T> current = top.get();
    newNode.next = current;
  } while (!top.compareAndSet(current, newNode));
}
```

### Java Library Support:

* `ConcurrentLinkedQueue`
* `ConcurrentHashMap`

---

## 12. .NET Memory Model

### Key Differences from Java:

* No atomic guarantee for `long`/`double` without `lock`
* No precise visibility rules like volatile-read/write pairs

---

## 13. .NET Memory Barriers

### Volatile Semantics (Half Fence):

* **Volatile Write**: Acts as a release
* **Volatile Read**: Acts as an acquire

### Full Fence:

```csharp
Thread.MemoryBarrier();
```

* Prevents reordering in both directions

---

## 14. Rendez-Vous in .NET

### Incorrect Without Barrier:

```csharp
a = true;
while (!b) {}

b = true;
while (!a) {}
```

### Correct With Barrier:

```csharp
a = true;
Thread.MemoryBarrier();
while (!b) {}

b = true;
Thread.MemoryBarrier();
while (!a) {}
```

---

## 15. Summary

### Java Memory Model:

* Guarantees **atomicity**, **visibility**, and **ordering** under specific constructs

### .NET Memory Model:

* Uses **memory fences** and `volatile` for partial ordering
* Requires `Thread.MemoryBarrier()` for strong ordering

### Lock-Free Programming:

* Atomic operations enable safe data structures without locks
* Optimistic synchronization patterns (CAS loops) are essential

---

## 16. Key Concepts Recap

| Topic                 | Java                                     | .NET                                     |
| --------------------- | ---------------------------------------- | ---------------------------------------- |
| Atomic Variables      | Yes (`Atomic*` classes)                  | Yes (`Interlocked` class)                |
| Volatile Semantics    | Volatile write/read visibility rules     | Half fences (release/acquire)            |
| Full Memory Barrier   | Implicit with `synchronized`, `volatile` | Explicit: `Thread.MemoryBarrier()`       |
| Lock-Free Collections | Yes (`Concurrent*` classes)              | Yes (in `System.Collections.Concurrent`) |

---

## 17. Further Reading

* **Java Language Specification**, SE 18 (2022), Section 17.4
* **.NET Memory Model**: ECMA 335 CLI Spec v6, Section I.12.6
* Manson, J., Pugh, W., Adve, S.V., *The Java Memory Model*, POPL, 2005
* Pugh, B., *Double-Checked Locking is Broken*: [cs.umd.edu link](https://www.cs.umd.edu/~pugh/java/memoryModel/DoubleCheckedLocking.html)
* Goetz, B. *Java Concurrency in Practice*, Chapters 15–16
* Treiber, R.K., *Coping with Parallelism*, IBM, 1986
* Michael, M. & Scott, M.L., *Simple, fast, and practical non-blocking concurrent queue algorithms*, PODC 1996
