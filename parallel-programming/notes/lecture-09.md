# Parallel Programming – Week 9 Summary

**Topic:** Cluster Programming with MPI (Collective Communication & Applications)
**Instructor:** Prof. Dr. Mitra Purandare
**Institution:** OST – Ostschweizer Fachhochschule
**Date:** 23 May 2024

---

## 1. Learning Goals

* Master **collective communication** in MPI
* Understand and implement **MPI applications**
* Practice distributed parallelization using **clusters**

---

## 2. Quick Recap of MPI Basics

* `MPI_Init()` and `MPI_Finalize()`: Initialize and terminate MPI environment
* `MPI_COMM_WORLD`: Communicator representing all processes
* `MPI_Comm_rank()`: Get process ID (rank)
* `MPI_Comm_size()`: Get total number of processes
* `MPI_Send()` and `MPI_Recv()`: Send/receive data between processes
* `MPI_Get_processor_name()`: Get host machine name

---

## 3. Collective Communication in MPI

### What is it?

* Operations involving **groups of processes**, not just one-to-one
* Enables efficient **data distribution** and **aggregation**

### Common Types:

* **Broadcast**: One to all
* **Reduce**: All to one
* **AllReduce**: All to all
* **Gather**: Many to one

---

## 4. Broadcast

### Naive Point-to-Point Broadcast:

```c
if (rank == 0) {
  for (to = 1; to < size; to++)
    MPI_Send(&value, 1, MPI_INT, to, 0, MPI_COMM_WORLD);
} else {
  MPI_Recv(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
}
```

### Efficient Version with `MPI_Bcast`:

```c
MPI_Bcast(&value, 1, MPI_INT, 0, MPI_COMM_WORLD);
```

* Reduces complexity and communication overhead

---

## 5. Reduction with `MPI_Reduce`

### Purpose:

* Aggregate data from all processes into one result (e.g., sum, max)

### Example:

```c
MPI_Reduce(&value, &total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
```

* Only **root process** receives the result

### Built-in Reduction Operators:

* `MPI_SUM`, `MPI_MAX`, `MPI_MIN`, `MPI_PROD`
* Bitwise and logical: `MPI_LAND`, `MPI_LOR`, `MPI_BAND`, `MPI_BOR`
* Max/Min with location: `MPI_MAXLOC`, `MPI_MINLOC`

---

## 6. AllReduce: Share Result with All

```c
MPI_Allreduce(&value, &total, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
```

* Every process receives the final result
* Internally: combines **reduce + broadcast**

### Comparison:

| Operation       | Result Receiver | Efficiency         |
| --------------- | --------------- | ------------------ |
| `MPI_Reduce`    | One process     | More efficient     |
| `MPI_Allreduce` | All processes   | More communication |

---

## 7. MPI\_Gather

```c
MPI_Gather(&send_value, 1, MPI_INT, &recv_array, 1, MPI_INT, 0, MPI_COMM_WORLD);
```

* Each process sends its value to **process 0**
* Result is collected into an array at the root

---

## 8. Application Example: Monte Carlo Simulation of π

### Idea:

* Throw random points inside a unit square
* Check how many fall into the inscribed unit circle
* Estimate π using:

  $$
  \pi \approx 4 \cdot \frac{\text{Points in Circle}}{\text{Total Points}}
  $$

### Trigonometry Refresher:

* A point (x, y) lies inside a unit circle if:

  $$
  x^2 + y^2 \leq 1
  $$

---

## 9. Sequential Implementation

```c
long count_hits(long trials) {
  long hits = 0;
  for (int i = 0; i < trials; i++) {
    double x = rand() / (double)RAND_MAX;
    double y = rand() / (double)RAND_MAX;
    if (x * x + y * y <= 1) hits++;
  }
  return hits;
}
```

---

## 10. Parallelized Version with MPI

```c
int rank, size;
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &size);

srand(rank * 4711);  // Seed per process
long hits = count_hits(TRIALS / size);

long total;
MPI_Reduce(&hits, &total, 1, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

if (rank == 0) {
  double pi = 4 * ((double)total / TRIALS);
  printf("Estimated Pi: %f\n", pi);
}
```

* Each process performs a portion of the work
* Results aggregated using `MPI_Reduce`

---

## 11. Performance Observations

| Processes | Time (ms) |
| --------- | --------- |
| 10        | 4963      |
| 20        | 2891      |
| 30        | 1573      |
| 100       | 597       |
| 150       | 398       |
| 180       | 360       |

* **Embarrassingly parallel**: almost linear scalability

---

## 12. Takeaways

* Collective MPI operations improve code efficiency and clarity
* Use `MPI_Reduce` for result aggregation
* Use `MPI_Bcast` and `MPI_Allreduce` for result sharing
* Monte Carlo π is a classic **parallelizable** problem

---

## 13. Further Reading

* [MPI Standard Documentation](https://www.mpi-forum.org/docs/)
* [Why calculate π to 62.8 trillion digits?](https://theconversation.com/why-bother-calculating-pi-to-62-8-trillion-digits-its-both-useless-and-fascinating-166271)
* Wikipedia articles on:

  * [Monte Carlo Method](https://en.wikipedia.org/wiki/Monte_Carlo_method)
  * [Mathematical Constant π](https://en.wikipedia.org/wiki/Pi)
