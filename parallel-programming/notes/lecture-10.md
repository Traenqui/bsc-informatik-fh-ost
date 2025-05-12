# Parallel Programming – Week 10 Summary

**Topic:** OpenMP and Hybrid Parallelization
**Instructor:** Prof. Dr. Mitra Purandare
**Institution:** OST – Ostschweizer Fachhochschule
**Date:** Week 10

---

## 1. Learning Goals

* Learn **OpenMP** for shared-memory parallelization
* Understand hybrid programming using **MPI + OpenMP**
* Avoid race conditions using OpenMP constructs like **mutexes**, **atomics**, and **reductions**

---

## 2. Background Context

### Cluster Architecture

* 24 compute nodes × 20 CPU cores = 480 physical cores (960 with hyperthreading)
* Shared memory within a node, **no shared memory between nodes**
* Nodes communicate via **message passing (MPI)**

---

## 3. Why OpenMP?

### Need for a Thread Framework:

* Shared memory parallelization within a single machine
* Easier than writing thread code manually (e.g., `pthreads`)
* Compiler-based support using **pragmas**

---

## 4. OpenMP Programming Model

* Explicit parallelism through compiler directives (e.g. `#pragma omp parallel`)
* Suitable for **shared-memory** systems (within a node)
* Programmer defines:

  * How threads are created
  * What work is assigned to each thread

---

## 5. OpenMP Execution Model: Fork-Join

```c
#include <omp.h>
int main() {
  #pragma omp parallel
  {
    printf("Hello from thread %d\n", omp_get_thread_num());
  }
}
```

### Steps:

1. Starts with one **master thread**
2. `#pragma omp parallel` forks multiple threads
3. Threads execute in **parallel region**
4. At the end, threads join and control returns to master

---

## 6. Thread Configuration

* **Runtime function**: `omp_set_num_threads(N)`
* **Environment variable**: `OMP_NUM_THREADS`
* Threads are indexed from `0` to `N-1`

---

## 7. Parallel Loops

```c
#pragma omp parallel for
for (int i = 0; i < n; i++) {
  // loop iterations are split among threads
}
```

* Work is automatically **divided** among available threads
* OpenMP handles **oversubscription**

---

## 8. OpenMP Memory Model

### Shared vs Private

```c
#pragma omp parallel for private(A) shared(B)
```

* **Private**: Each thread gets its own copy
* **Shared**: All threads access the same variable
* After parallel region ends, private variables are destroyed

---

## 9. Race Conditions in Parallel Loops

### Problem:

```c
int sum = 0;
#pragma omp parallel for
for (int i = 0; i < n; i++) {
  sum += i;  // Race condition
}
```

---

## 10. Avoiding Race Conditions

### 1. Using `critical` (heavyweight mutex)

```c
#pragma omp critical
{
  sum += i;
}
```

* Correct but **very slow**

---

### 2. Using `atomic` (lightweight mutex)

```c
#pragma omp atomic
sum += i;
```

* More efficient for simple updates

---

### 3. Using `reduction` (most efficient)

```c
#pragma omp parallel for reduction(+:sum)
for (int i = 0; i < n; i++) {
  sum += i;
}
```

---

## 11. Manual Reduction (for understanding)

```c
int final_sum = 0;
#pragma omp parallel {
  int partial_sum = 0;
  #pragma omp for
  for (int i = 0; i < n; i++) {
    partial_sum += i;
  }
  #pragma omp atomic
  final_sum += partial_sum;
}
```

---

## 12. Hybrid Programming: MPI + OpenMP

### Combining MPI across nodes with OpenMP within nodes

```c
MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);

#pragma omp parallel {
  int tid = omp_get_thread_num();
  printf("Thread %d from process %d\n", tid, rank);
}
MPI_Finalize();
```

---

## 13. Application Example: Monte Carlo Simulation of π

### Distributed + Multithreaded Version:

```c
long count_hits(long trials) {
  long hits = 0;
  #pragma omp parallel for reduction(+:hits) private(x, y)
  for (long i = 0; i < trials; i++) {
    double x = random_double();
    double y = random_double();
    if (x * x + y * y <= 1) hits++;
  }
  return hits;
}
```

Used with MPI:

```c
long hits = count_hits(trials_per_process);
MPI_Reduce(&hits, &total, 1, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
```

---

## 14. Summary

| Concept           | Description                                     |
| ----------------- | ----------------------------------------------- |
| OpenMP            | Shared memory threading via compiler directives |
| Fork-Join Model   | Master thread spawns team, threads join later   |
| Critical Section  | Serializes access, prevents data races          |
| Atomics           | Lightweight, for simple shared updates          |
| Reductions        | Efficient built-in aggregation                  |
| Hybrid MPI+OpenMP | MPI across nodes, OpenMP within node            |

---

## 15. Further Reading

* [OpenMP Specification](https://www.openmp.org/specifications/)
* Tim Mattson, *Parallel Programming with OpenMP*
* Blaise Barney, *OpenMP Tutorial*, LLNL
* [Hybrid MPI/OpenMP programming](https://mpitutorial.com/tutorials/using-openmp-with-mpi/)
