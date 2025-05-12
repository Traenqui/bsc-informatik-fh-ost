# Parallel Programming – Week 1 Summary

## 1. Course Overview

### 1.1 Course Title

Parallel Programming
Institution: OST – Ostschweizer Fachhochschule, Campus Rapperswil
Instructors:

* Prof. Mitra Purandare
* Peter Bühler

### 1.2 Course Focus

* Local parallelization using multi-core CPUs
* Distributed parallelization using GPUs and clusters
* Technologies: Java, C#, C++, CUDA, OpenCL, MPI, .NET TPL
* Programming models: Concurrent, Asynchronous, and Parallel Programming

### 1.3 Weekly Schedule

**Lectures:**

* Thursday 08:10 – 09:50 (St. Gallen)
* Friday 08:10 – 09:50 (Rapperswil)

**Exercises:**

* Monday 13:10 – 14:50 (Rapperswil)
* Thursday 13:10 – 14:50 (St. Gallen)
* Friday 10:10 – 11:50 (Rapperswil)

### 1.4 Moodle Access

All materials including:

* Lecture slides
* Exercises and solutions
* Semester overview and updates
* Exam information (from Week 11)
  Link: [Moodle Course Page](https://moodle.ost.ch/course/section.php?id=94950)

---

## 2. Administrative Details

### 2.1 Exam & Requirements

* You must pass **three mandatory assignments (Testate)** submitted via Moodle to be eligible for the final exam.
* Clearly indicate group work in submissions.
* Deadlines are strict.

### 2.2 Workload (4 ECTS = \~120 hours)

* Weekly:

  * 2 hours lecture
  * 2 hours exercise
  * 1 hour prep/review of lecture
  * 2-4 hours prep/review of exercise
    **Total per week: 7-9 hours**
* Additional:

  * 20 hours exam preparation
  * 2 hours exam

---

## 3. Motivation for Parallel Programming

### 3.1 Software Complexity

Modern applications (like word processors) require multitasking:

* User input handling
* Background spell checking
* Formatting
* Saving and autosaving
  Running all this sequentially would be inefficient.

### 3.2 Moore’s Law and Its Limits

* Originally predicted that the number of transistors on a chip doubles every 2 years.
* Enabled exponential growth in performance for decades.
* However, this trend is nearing physical limits (due to atomic scale constraints).
* Simply increasing clock speed is no longer viable.

### 3.3 Modern Hardware Trends

* Multi-core processors: Instead of scaling vertically (speed), we scale horizontally (more cores).
* Example: Intel Xeon CPUs with up to 128 cores and 4 sockets, totaling 512 cores or 1024 hyperthreads.

### 3.4 Advantages of Parallel Programming

* Better hardware utilization
* More responsive software
* Simplifies design in multitasking scenarios
* Encourages modular task design

---

## 4. Parallelism vs Concurrency

**Parallelism**

* Multiple sub-programs run **simultaneously** on different processors.
* Goal: **Performance** improvement.

**Concurrency**

* Interleaved execution of multiple tasks on one or more processors.
* Tasks may interact or share resources.
* Goal: **Simplification** of program structure.

---

## 5. Operating System Concepts

### 5.1 Process

* An independent executing instance of a program.
* Has its **own address space** (code, heap, stack, registers).
* Expensive to create due to context switching and memory overhead.

### 5.2 Thread

* A lightweight execution unit within a process.
* Shares memory with other threads in the same process.
* Owns a separate stack and register set.
* Cheaper and faster to manage than processes.

**Comparison Table:**

| Aspect        | Process                             | Thread                         |
| ------------- | ----------------------------------- | ------------------------------ |
| Address Space | Separate                            | Shared                         |
| Overhead      | High (expensive creation/switching) | Low (lightweight)              |
| Communication | Complex (via IPC)                   | Simple (via shared memory)     |
| Isolation     | Strong                              | Weak (risk of race conditions) |

---

## 6. Thread Scheduling

### 6.1 Scheduling Types

* **Processor Sharing**: More threads than CPUs; waiting threads release the CPU for others.
* **Processor Multiplexing**: Single CPU simulates parallelism via context switches.

### 6.2 Multitasking Approaches

* **Cooperative**: Thread voluntarily yields control.
* **Preemptive**: Scheduler forcibly interrupts running threads at fixed intervals (Java uses this by default).

---

## 7. Java Multithreading Basics

### 7.1 Java Virtual Machine (JVM)

* JVM is a single process.
* JVM starts the **main thread**, which runs the `main()` method.
* Additional threads can be created by:

  * The programmer
  * Java subsystems (e.g. Garbage Collector, AWT)

### 7.2 JVM Termination

* JVM continues until **all non-daemon threads** are complete.
* **Daemon threads** (e.g., GC) do not block JVM shutdown.

### 7.3 Thread Creation in Java

**Using Thread Class:**

```java
class MyThread extends Thread {
  public void run() {
    // thread behavior
  }
}

var t = new MyThread();
t.start();
```

**Using Runnable Interface:**

```java
class MyRunnable implements Runnable {
  public void run() {
    // thread behavior
  }
}

var t = new Thread(new MyRunnable());
t.start();
```

**Using Lambda Expressions:**

```java
var t = new Thread(() -> {
  // thread behavior
});
t.start();
```

### 7.4 Thread Lifecycle

* **start()**: Starts the thread and invokes `run()`
* **run()**: Actual code executed in the thread
* **end**: Thread ends when `run()` completes or throws an unhandled exception

### 7.5 Output Example

```java
var a = new Thread(() -> multiPrint("A"));
var b = new Thread(() -> multiPrint("B"));
a.start();
b.start();
System.out.println("main finished");
```

This demonstrates non-deterministic output due to parallel execution.

---

## 8. Thread Control Methods

### 8.1 join()

Wait for a thread to finish before proceeding.

```java
a.join();
b.join();
System.out.println("All threads done");
```

### 8.2 sleep()

Suspends thread for a specific time.

```java
Thread.sleep(1000); // 1 second
```

### 8.3 yield()

Gives up CPU voluntarily; thread becomes ready again immediately.

---

## 9. Interruptions and Exceptions

### 9.1 interrupt()

Signal a thread to stop. Not enforced; thread must cooperate.

```java
myThread.interrupt();
```

### 9.2 InterruptedException

Thrown during `sleep()`, `join()`, or `wait()` if interrupted.

```java
try {
  Thread.sleep(1000);
} catch (InterruptedException e) {
  // handle interrupt
}
```

### 9.3 Checking Interrupt Flag

```java
Thread.currentThread().isInterrupted();
Thread.interrupted();
```

---

## 10. Additional Thread Methods

* `Thread.currentThread()` → Returns reference to currently running thread.
* `setDaemon(true)` → Marks a thread as daemon.

---

## 11. Learning Objectives Recap

* Understand OS concepts: process vs thread
* Know how Java implements multithreading
* Understand thread lifecycle and scheduling
* Safely manage shared memory using synchronization
* Use thread control functions: `start()`, `join()`, `sleep()`, `interrupt()`

---

## 12. Suggested Readings

**Java Concurrency**

* Goetz, B. et al. *Java Concurrency in Practice*, Addison-Wesley, 2006
* Herlihy, M. & Shavit, N. *The Art of Multiprocessor Programming*, Morgan Kaufmann, 2012

**GPU & HPC**

* Kirk, D. & Hwu, W. *Programming Massively Parallel Processors*, Morgan Kaufmann, 2016
* Robey, R. & Zamora, Y. *Parallel and High Performance Computing*, Manning, 2021