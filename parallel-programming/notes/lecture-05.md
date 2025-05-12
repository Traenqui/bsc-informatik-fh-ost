# Parallel Programming – Week 5 Summary

**Topic:** Thread Pools
**Instructor:** Mitra Purandare
**Institution:** OST – Ostschweizer Fachhochschule

---

## 1. Learning Goals

* Understand the **thread pool** concept
* Use **Java ForkJoinPool** for parallel task execution
* Explore the **.NET Task Parallel Library (TPL)**

---

## 2. Motivation

### Limitations of Low-Level Threading:

* Using raw `Thread` objects:

  * Costly in memory (each thread has a stack)
  * Slows down with too many threads
  * Limited scalability
* Need **high-level abstractions** to support **massive concurrency**.

---

## 3. Thread Pool Concept

### Key Ideas:

* **Task**: Passive object encapsulating parallel work logic
* **Thread Pool**: Limited number of **worker threads** execute queued tasks
* **Run-to-completion**: Each task completes before the thread moves to the next

### Benefits:

* Reuse threads instead of creating/destroying them
* Avoid overhead of excessive thread creation
* Configurable thread count (recommended: processors + pending I/O)
* Clear separation between **task declaration** and **task execution**

---

## 4. Java ForkJoinPool

### Basic Example:

```java
var pool = new ForkJoinPool();
Future<Integer> future = pool.submit(() -> {
    return someComputation();
});
int result = future.get();  // blocks until done
```

### `Future<T>` Interface:

* Represents a result of an async computation
* Methods:

  * `get()` – Waits for result
  * `cancel()` – Attempts to stop execution
  * `isDone()` – Checks if completed

### Recursive Task Example:

```java
class CountTask extends RecursiveTask<Integer> {
  protected Integer compute() {
    if (upper - lower <= THRESHOLD) return countPrimes();
    int mid = (lower + upper) / 2;
    var left = new CountTask(lower, mid);
    var right = new CountTask(mid, upper);
    left.fork(); right.fork();
    return right.join() + left.join();
  }
}
```

### ForkJoinPool Features:

* Tasks submitted go into **global queue**
* Forked tasks are pushed into **local queues**
* **Work stealing**: idle threads steal tasks from others

---

## 5. .NET Task Parallel Library (TPL)

### Features:

* Provides types in `System.Threading` and `System.Threading.Tasks`
* Default **ThreadPool** with load-balancing
* Tasks are lightweight
* Supports:

  * Task-based parallelism
  * Data parallelism
  * Asynchronous programming

### Basic Task Example:

```csharp
Task<int> task = Task.Run(() => {
    return someCalculation();
});
int result = task.Result;  // blocks
```

### Nested Tasks:

```csharp
var task = Task.Run(() => {
    var left = Task.Run(() => Count(leftPart));
    var right = Task.Run(() => Count(rightPart));
    return left.Result + right.Result;
});
```

---

## 6. .NET Parallel Statements & Loops

### `Parallel.Invoke`

Run independent statements in parallel:

```csharp
Parallel.Invoke(
    () => MergeSort(left),
    () => MergeSort(right)
);
```

### `Parallel.ForEach`

Parallelize loop bodies:

```csharp
Parallel.ForEach(files, file => Convert(file));
```

### `Parallel.For`

Parallel iteration over a range:

```csharp
Parallel.For(0, array.Length, i => Process(array[i]));
```

### Partitioning:

* **Range partitioning** for indexable data (e.g. arrays)
* **Chunk partitioning** for general enumerables

---

## 7. PLINQ – Parallel LINQ

### What is PLINQ?

* Parallel version of **LINQ** (Language-Integrated Query)
* Analogous to Java’s Stream API with `.parallelStream()`

### Example:

```csharp
from book in bookCollection.AsParallel()
where book.Title.Contains("Concurrency")
select book.ISBN;
```

* `AsParallel()` activates parallel execution
* Use `AsOrdered()` to maintain order (slower)

---

## 8. Thread Pool Limitations

### Key Caution:

* **Tasks should not wait on each other** unless using explicit subtasks (fork-join)
* Risk of **deadlock** if tasks block while waiting for other queued tasks

---

## 9. Java vs .NET Thread Pools

| Feature             | Java (ForkJoinPool)           | .NET (TPL)                         |
| ------------------- | ----------------------------- | ---------------------------------- |
| Task Model          | RecursiveTask/RecursiveAction | Task, Parallel.For/Invoke/PLINQ    |
| Thread Reuse        | Yes                           | Yes                                |
| Result Handling     | Future<T>                     | Task<T>                            |
| Work Stealing       | Yes                           | Yes                                |
| Nested Tasks        | Fork/Join                     | Tasks can start and wait sub-tasks |
| Deadlock Prevention | Manual                        | Thread injection, hill-climbing    |

---

## 10. Additional Notes

* Java: `ForkJoinPool.commonPool()` may underutilize processors.
* .NET: TPL dynamically injects threads using **Hill Climbing Algorithm** to optimize performance.
* Fire-and-forget tasks can lead to untracked failures (handle exceptions properly).

---

## 11. Learning Recap

* Thread pools provide efficient concurrency
* ForkJoinPool is Java’s tool for recursive parallelism
* TPL is the high-level concurrency API in .NET
* Parallelism can be applied to both tasks and data

---

## 12. Further Reading

* Goetz, B. *Java Concurrency in Practice*, Addison-Wesley – Chapters 6 & 8
* Java Executor Tutorial: [Oracle Documentation](https://docs.oracle.com/javase/tutorial/essential/concurrency/executors.html)
* Albahari, J. *Threading in C#* – [albahari.com/threading](https://www.albahari.com/threading)
* Leijen, D. et al. *The Design of a Task Parallel Library*, OOPSLA '09
* Stephen Cleary, *Concurrency in C# Cookbook*, 2nd ed., O’Reilly