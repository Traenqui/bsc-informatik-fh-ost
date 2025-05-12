# Parallel Programming – Week 4 Summary

**Topic:** Dangers of Concurrency
**Instructor:** Mitra Purandare
**Institution:** OST – Ostschweizer Fachhochschule
**Date:** Week 4

---

## 1. Recap of Synchronization Tools

### Monitor (`synchronized`)

* Simple and efficient for basic mutual exclusion.
* Only one condition queue (uses `wait()`/`notify()`/`notifyAll()`).

### `Lock` & `Condition`

* More control with multiple conditions and fairness via `ReentrantLock(true)`.
* Methods: `lock()`, `unlock()`, `await()`, `signal()`, `signalAll()`.

### Semaphore

* Based on permits.
* Suitable for managing multiple instances of a resource.
* Supports fairness with optional FIFO queue.

### CountDownLatch and CyclicBarrier

* Latch: Wait for N events to occur.
* Barrier: Wait for N threads to meet before continuing; reusable.

---

## 2. Dangers of Concurrency

Concurrency introduces **unique risks** not present in single-threaded programs.

### Common Hazards:

* **Race Conditions**
* **Data Races**
* **Deadlocks**
* **Starvation**

These errors are often hard to detect due to non-deterministic behavior.

---

## 3. Race Conditions and Data Races

### Race Condition

* Occurs when program behavior depends on thread timing/interleaving.
* Non-deterministic and may result in inconsistent outcomes.

### Data Race

* Two threads access the same variable concurrently, and at least one is a write.
* No exclusive lock used.

**Example:**

```java
balance += 100; // Thread 1
balance += 50;  // Thread 2
```

### Synchronization Eliminates Data Race but Not Race Condition

```java
synchronized int getBalance() { ... }
synchronized void setBalance(int x) { ... }
// Still vulnerable to lost updates
```

### Summary Table:

|                       | Data Race | No Data Race   |
| --------------------- | --------- | -------------- |
| **Race Condition**    | Incorrect | Still possible |
| **No Race Condition** | Illegal   | Correct        |

---

## 4. Synchronization is Not Always Needed

### Safe Cases:

* **Immutability**: Objects never change state after creation.
* **Read-Only Sharing**: Multiple threads read without writing.
* **Thread Confinement**: Object is only accessed by a single thread.
* **Object Confinement**: Object access is wrapped inside synchronized methods.

---

## 5. Thread Safety

### Definition:

* Correct behavior under concurrent access without external synchronization.
* Data types must be consistent with expected behavior regardless of thread execution order.

### Examples:

* `StringBuilder` is **not** thread-safe.
* Java collections:

  * Legacy (`Vector`, `Hashtable`): thread-safe
  * Modern (`ArrayList`, `HashMap`): not thread-safe
  * Concurrent (`ConcurrentHashMap`, etc.): thread-safe and scalable

---

## 6. Deadlocks

### What is a Deadlock?

* Two or more threads are waiting on each other’s resources.
* Each holds one lock and waits for the other.

**Example:**

```java
Thread 1: synchronized(listA) { synchronized(listB) { ... } }
Thread 2: synchronized(listB) { synchronized(listA) { ... } }
```

### Detection:

* Modeled using **resource graphs** (cycle = deadlock)

### Prevention Techniques:

* **Lock Ordering**: Always lock resources in a fixed order.
* **Coarse-Grained Locks**: Lock larger units to avoid interlocking.
* **Timeouts** or **tryLock()** (when supported)

---

## 7. Starvation

### What is Starvation?

* A thread is indefinitely denied access to a resource.
* Can happen even when resources are available if scheduling is unfair.

**Example:**

```java
while (!success) {
    success = account.withdraw(100);
}
```

### Causes:

* Thread priorities
* Unfair locks or monitors (Java’s default `synchronized`)

### Prevention:

* Use **fair locks** (e.g., `ReentrantLock(true)`, `Semaphore(true)`).
* Avoid priority inversion.

---

## 8. Correctness in Concurrency

### Safety Conditions:

* No **Race Conditions**
* No **Data Races**
* No **Deadlocks**

### Liveness Conditions:

* No **Starvation**
* All threads should make progress over time.

---

## 9. .NET Concurrency Overview (Optional Topic)

### Threads in .NET:

```csharp
Thread t = new Thread(() => {
    Console.WriteLine("Running thread...");
});
t.Start();
t.Join();
```

* Use `IsBackground = true` for daemon-like behavior.

### Monitor in .NET:

```csharp
lock(syncObject) {
    while (amount > balance) Monitor.Wait(syncObject);
    balance -= amount;
}
```

* `Monitor.Wait()` + `Monitor.PulseAll()` behave like `wait()` + `notifyAll()`.

### Differences:

* .NET lacks fairness flags.
* `ReadWriteLockSlim` is more efficient for readers.
* Use `System.Collections.Concurrent` for thread-safe collections.

---

## 10. Parallel Checker (C# Tool)

* Tool to **detect concurrency bugs** in C#
* Detects data races and deadlocks at coding time
* Available via:

  * Visual Studio Extensions
  * NuGet: `ConcurrencyChecker.ParallelChecker`

**Website:** [https://parallel-checker.com](https://parallel-checker.com)

---

## 11. Learning Outcomes (Week 4)

* Understand concurrency hazards: race conditions, deadlocks, starvation
* Apply safe and fair synchronization techniques
* Compare Java and .NET concurrency mechanisms
* Use tools like Parallel Checker for debugging

---

## 12. Suggested Readings

* Goetz, B. et al. *Java Concurrency in Practice* – Ch. 2, 5, 10
* Dijkstra, E. W. *Hierarchical Ordering of Sequential Processes*, Acta Informatica, 1971
* Stephen Cleary. *Concurrency in C# Cookbook*, O'Reilly, 2019
* Jon Albahari. *Threading in C#*: [albahari.com/threading](http://www.albahari.com/threading)
