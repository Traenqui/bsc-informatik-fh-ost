# Parallel Programming – Week 2 Summary

**Topic:** Monitor Synchronization
**Instructor:** Mitra Purandare
**Date:** 26.02.2025

---

## 1. Recap of Week 1

* Understanding of processes vs. threads
* Java thread creation and life cycle
* Concept of daemon threads
* Thread joining (`join()`)
* Thread interruption and `InterruptedException`

---

## 2. Java Thread Lifecycle

### Thread States:

* **New**: Thread created but not yet started.
* **Alive**:

  * **Ready**: Waiting for CPU
  * **Running**: Currently executing
  * **Waiting**: Waiting for a condition or timeout
* **Terminated**: After `run()` ends or an exception occurs

### Notes:

* Methods `suspend()`, `resume()`, `stop()` are deprecated.
* Threads cannot be restarted once terminated.

---

## 3. Thread Synchronization

### Motivation:

* **Non-determinism**: Threads may execute in unpredictable order.
* **Shared Resources**: Concurrent access to shared data (e.g., bank account) can lead to inconsistent results (race conditions).

### Example: Race Condition

```java
class BankAccount {
  private int balance = 0;
  public void deposit(int amount) {
    balance += amount;
  }
}
```

Two threads calling `deposit()` simultaneously may both read the same initial balance, causing one deposit to be lost.

---

## 4. Critical Section and Mutual Exclusion

* **Critical Section**: Code segment that must be executed by only one thread at a time.
* **Mutual Exclusion**: Prevents multiple threads from entering the critical section simultaneously.

### Incorrect Example:

```java
while (locked) { }  // busy waiting
locked = true;
balance += amount;
locked = false;
```

* This naive approach fails due to non-atomic read/write of the `locked` flag.

---

## 5. Java’s Synchronized Mechanism

### Synchronized Method:

```java
public synchronized void deposit(int amount) {
  balance += amount;
}
```

### Synchronized Block:

```java
public void deposit(int amount) {
  synchronized (this) {
    balance += amount;
  }
}
```

### Guarantees:

* Only one thread can hold the object’s monitor (lock).
* Provides mutual exclusion and memory consistency (ensures visibility of changes).
* Every Java object has an intrinsic monitor lock.

---

## 6. Monitor Concept

### Defined by:

* C. A. R. Hoare & Per Brinch Hansen (1974)

### Features:

* Built-in **mutual exclusion**
* **Wait/Notify mechanism** for condition-based synchronization

---

## 7. Wait & Notify in Java

### Naive Approach (Incorrect):

```java
while (amount > balance) {
  Thread.sleep(1);  // doesn't release the lock
}
```

* Problem: `sleep()` holds the monitor, blocking others.

### Correct Monitor Use:

```java
public synchronized void withdraw(int amount) throws InterruptedException {
  while (amount > balance) {
    wait();  // releases lock
  }
  balance -= amount;
}

public synchronized void deposit(int amount) {
  balance += amount;
  notifyAll();  // wake waiting threads
}
```

### Notes:

* `wait()` releases the monitor and suspends the thread.
* `notify()` or `notifyAll()` wakes one or all waiting threads.
* `wait()`/`notify()` must be used inside a synchronized block.
* Use **`while`** loop to re-check condition (due to possible spurious wakeups).

---

## 8. Monitor Behavior in Java

### Monitor Internals:

* **Entry Set**: Threads waiting for the lock
* **Wait Set**: Threads that called `wait()`

### Wake-up Mechanisms:

* **notify()**: Wakes one thread arbitrarily.
* **notifyAll()**: Wakes all threads waiting on that object's monitor.

---

## 9. Monitor Traps and Best Practices

### Trap 1: `wait()` inside `if` instead of `while`

* Condition might no longer hold when awakened.
* Another thread might "overtake" and consume the resource.
* Always use:

```java
while (!condition) {
  wait();
}
```

### Trap 2: Using `notify()` when multiple conditions exist

* If threads are waiting on different conditions (e.g., "not full" vs. "not empty"), `notify()` may wake the wrong thread.
* Solution: use `notifyAll()` to wake all and let them re-check conditions.

### Final Correct Implementation:

```java
class BoundedBuffer<T> {
  private Queue<T> queue = new LinkedList<>();
  private int capacity = ...;

  public synchronized void put(T x) throws InterruptedException {
    while (queue.size() == capacity) {
      wait();  // wait until not full
    }
    queue.add(x);
    notifyAll();  // signal not empty
  }

  public synchronized T get() throws InterruptedException {
    while (queue.size() == 0) {
      wait();  // wait until not empty
    }
    T x = queue.remove();
    notifyAll();  // signal not full
    return x;
  }
}
```

---

## 10. Monitor Behavior Summary

* Only one thread can be active in the monitor.
* Wait releases the lock and puts the thread in a wait set.
* notify/notifyAll moves threads from wait set to entry set.
* Threads must fight for lock upon re-entry.
* Spurious wakeups can happen, so always validate conditions after waking up.

---

## 11. Learning Goals Achieved

* Identify when synchronization is needed
* Understand Java Monitor concept and usage
* Properly synchronize threads using `synchronized`, `wait()`, `notifyAll()`

---

## 12. Further Reading

* Goetz, B. et al. *Java Concurrency In Practice*, Addison-Wesley, 2006 – Ch. 2
* Lea, D. *Concurrent Programming in Java*, Addison-Wesley, 2003 – Ch. 3.2.2
* Hoare, C.A.R. *Monitors: An Operating System Structuring Concept*, CACM, 1974
