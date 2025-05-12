# Parallel Programming – Week 3 Summary

**Topic:** Specific Synchronization Primitives
**Instructor:** Mitra Purandare
**Date:** Week 3

---

## 1. Recap: Java Monitors

### Problem Scenario:

```java
public class Turnstile {
  private boolean open = false;

  public synchronized void pass() throws InterruptedException {
    while (!open) { wait(); }
    open = false;
  }

  public synchronized void open() {
    open = true;
    notify(); // or notifyAll() ?
  }
}
```

### Observations:

* `notifyAll()` ensures correctness when multiple conditions or fairness is desired.
* Use `while` loop with `wait()` to handle spurious wakeups and re-check conditions.

---

## 2. Limitations of Monitors

* **notifyAll()** wakes all threads, causing inefficiency when only one needs to proceed.
* **notify()** lacks fairness (not FIFO).
* Monitor has a single waiting queue—inefficient for multiple semantic conditions.
* Lacks shared locks like read-write locks.

---

## 3. Synchronization Alternatives Covered

* Semaphore
* Lock & Condition
* Read-Write Lock
* CountDownLatch
* CyclicBarrier
* Exchanger

---

## 4. Semaphore

### Concept:

* Introduced by E.W. Dijkstra in 1965.
* Manages access to a limited number of resources using a **counter**.

### Methods:

* `acquire()` — Waits if counter is zero or less, then decrements.
* `release()` — Increments counter and notifies waiting threads.

### Example:

```java
Semaphore s = new Semaphore(11);
s.acquire();
s.release();
```

### Binary Semaphore:

```java
Semaphore mutex = new Semaphore(1);
```

### Fairness:

```java
Semaphore fairSem = new Semaphore(N, true); // FIFO-based
```

### Bounded Buffer with Semaphores:

```java
private Semaphore upperLimit = new Semaphore(CAPACITY, true); // for free space
private Semaphore lowerLimit = new Semaphore(0, true);        // for available items

put(T item):
  upperLimit.acquire();
  synchronized(queue) { queue.add(item); }
  lowerLimit.release();

get():
  lowerLimit.acquire();
  synchronized(queue) { item = queue.remove(); }
  upperLimit.release();
```

---

## 5. Lock and Condition (Replaces `synchronized`, `wait()`, and `notify()`)

### Concepts:

* Allows **multiple condition variables** per lock.
* More explicit and targeted than Java Monitor.

### Key Methods:

* `lock()`, `unlock()` — Manage access to critical section.
* `await()` — Waits on a condition.
* `signal()` / `signalAll()` — Notifies waiting threads.

### Example:

```java
private Lock lock = new ReentrantLock(true);
private Condition nonFull = lock.newCondition();
private Condition nonEmpty = lock.newCondition();

put():
  lock.lock();
  try {
    while (queue.size() == CAPACITY) nonFull.await();
    queue.add(item);
    nonEmpty.signal();
  } finally {
    lock.unlock();
  }

get():
  lock.lock();
  try {
    while (queue.isEmpty()) nonEmpty.await();
    item = queue.remove();
    nonFull.signal();
    return item;
  } finally {
    lock.unlock();
  }
```

---

## 6. Read-Write Lock

### Purpose:

* Allow **multiple readers** or **one writer** at a time.
* Readers do not block other readers.

### API:

```java
ReadWriteLock lock = new ReentrantReadWriteLock(true);
lock.readLock().lock(); // shared lock
lock.writeLock().lock(); // exclusive lock
```

### Example:

```java
public Collection<String> find(String pattern) {
  lock.readLock().lock();
  try {
    // Read from shared collection
  } finally {
    lock.readLock().unlock();
  }
}

public void put(String name) {
  lock.writeLock().lock();
  try {
    // Modify shared collection
  } finally {
    lock.writeLock().unlock();
  }
}
```

---

## 7. Temporal Synchronization Primitives

### CountDownLatch

**Concept**: Blocks threads until a specified number of signals are received.

```java
CountDownLatch ready = new CountDownLatch(N);
CountDownLatch start = new CountDownLatch(1);

ready.countDown();   // N times
start.await();       // N threads wait
start.countDown();   // Starts execution
```

* One-time use only

---

### CyclicBarrier

**Concept**: All threads wait at a barrier point until a fixed number have arrived.

```java
CyclicBarrier barrier = new CyclicBarrier(N);

barrier.await();  // Waits until N threads arrive
```

* Reusable
* Useful for repeated rounds in games, simulations, etc.

---

### Exchanger

**Concept**: Two threads exchange data.

```java
Exchanger<Integer> exchanger = new Exchanger<>();
int received = exchanger.exchange(myValue);
```

* Each thread blocks until it exchanges data with another.
* Returns the value provided by the other thread.

---

## 8. Summary of Synchronization Primitives

| Primitive          | Purpose                                        | Fairness | Supports Multiple Conditions |
| ------------------ | ---------------------------------------------- | -------- | ---------------------------- |
| `synchronized`     | Simple locking, monitor-based                  | No       | No                           |
| `Semaphore`        | Manage resource access via counter             | Optional | No                           |
| `Lock & Condition` | Advanced monitor with targeted condition waits | Yes      | Yes                          |
| `ReadWriteLock`    | Allow concurrent reads, exclusive writes       | Yes      | No (but supports lock types) |
| `CountDownLatch`   | Wait until a number of threads reach a point   | No       | One-time use only            |
| `CyclicBarrier`    | Wait until group arrives, reusable barrier     | Yes      | No                           |
| `Exchanger`        | Thread-to-thread data swap                     | No       | No                           |

---

## 9. Key Takeaways

* **Semaphores** are versatile but low-level.
* **Locks and Conditions** are more flexible and clearer for complex interactions.
* **Read-Write Locks** optimize for read-heavy scenarios.
* **CountDownLatch** and **CyclicBarrier** synchronize groups of threads at specific points.
* **Exchanger** enables direct thread-to-thread communication.

---

## 10. Further Reading

* Goetz, B. et al. *Java Concurrency in Practice*, Addison-Wesley, 2006 – Sections 5.5, 14.3, 14.6
* Lea, D. *Concurrent Programming in Java*, 2nd Ed., Addison-Wesley, 2000 – Sections 3.4, 4.4.3
* E. W. Dijkstra’s foundational papers on semaphores (1965–1971)
