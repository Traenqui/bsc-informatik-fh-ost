# Parallel Programming – Week 8 Summary

**Topic:** Cluster Parallelization using MPI
**Instructor:** Prof. Dr. Mitra Purandare
**Institution:** OST – Ostschweizer Fachhochschule
**Date:** 15 May 2024

---

## 1. Learning Goals

* Understand the structure and programming model of **HPC clusters**
* Learn **MPI (Message Passing Interface)** for parallel execution across nodes
* Distinguish between shared and distributed memory architectures

---

## 2. HPC Cluster Overview

### Cluster = Network of Compute Nodes

* Typically located at the same site
* High-speed interconnect (e.g. 100 Gbit/s switch)
* Nodes run Linux and are used in scientific computing (fluids, meteo, traffic, etc.)

### Example: OST Cluster

* 24 nodes × 20 CPU cores = 480 physical cores (960 with hyperthreading)

---

## 3. Motivation

* High acceleration via **distributed parallelism** (factors >100)
* More flexible than GPUs (GPUs are SIMD-heavy)
* Enables **general-purpose** parallel programming on many-core CPUs

---

## 4. Parallelization Levels

| Type            | Example         |
| --------------- | --------------- |
| Hyperthreading  | 2 threads/core  |
| Multi-core      | 2–20 cores      |
| Multi-processor | Dual-socket CPU |
| Cluster         | 100s of CPUs    |

---

## 5. Parallel Programming Models

### SPMD (Single Program Multiple Data)

* All nodes run the **same executable**
* Each process works on **its own data**
* Differentiated by **rank** (unique ID per process)

### MPMD (Multiple Program Multiple Data)

* Each node may run a **different executable**
* Supports mixed-language and hybrid computation

---

## 6. Memory Model: Hybrid Architecture

* **Shared memory** within a node (e.g., among cores)
* **Distributed memory** between nodes (via messaging)
* Common in modern supercomputers

---

## 7. Introduction to MPI

### MPI Features:

* Programming model based on **explicit messaging**
* Standard API for C, C++, Fortran, Java, and .NET
* Implementations: OpenMPI, MPICH, Intel MPI, etc.
* Current standard: **MPI 3.1**; **MPI 4.1** under release

### Key Concepts:

* **Process-based parallelism**
* Each process has private memory
* Communication via explicit **send/receive**

---

## 8. MPI Hello World Program

```c
#include <stdio.h>
#include "mpi.h"

int main(int argc, char* argv[]) {
  MPI_Init(&argc, &argv);

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  printf("MPI process %i\n", rank);

  MPI_Finalize();
  return 0;
}
```

### Key Calls:

* `MPI_Init()`: Initializes MPI environment
* `MPI_Comm_rank()`: Gets current process ID
* `MPI_Finalize()`: Terminates MPI

---

## 9. Processor Identification

```c
char name[MPI_MAX_PROCESSOR_NAME];
int len;
MPI_Get_processor_name(name, &len);
printf("Process %d running on %s\n", rank, name);
```

* Helps track which process runs on which machine

---

## 10. Compilation and Execution

```bash
mpicc HelloCluster.c       # compile
mpiexec -n 24 ./a.out      # run with 24 processes
```

### With Slurm Scheduler:

```bash
sbatch myscript.sub
squeue                    # monitor jobs
```

---

## 11. MPI Process Model

* Each process is a separate instance of the program
* Each has its own **memory space** and **control flow**
* They can synchronize and exchange data via **messages**

---

## 12. Process Identification

```c
MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Rank (0...N-1)
MPI_Comm_size(MPI_COMM_WORLD, &size);  // Total number of processes
```

---

## 13. Direct Message Communication

### Send and Receive

```c
MPI_Send(&value, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
MPI_Recv(&value, 1, MPI_INT, src, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
```

| Parameter  | Description                  |
| ---------- | ---------------------------- |
| `value`    | Pointer to data              |
| `count`    | Number of elements           |
| `datatype` | E.g., `MPI_INT`, `MPI_FLOAT` |
| `dest/src` | Destination/source rank      |
| `tag`      | Message type identifier      |

---

## 14. Example Program (Broadcast-like)

```c
if (rank == 0) {
  int value = rand();
  for (int to = 1; to < size; ++to) {
    MPI_Send(&value, 1, MPI_INT, to, 0, MPI_COMM_WORLD);
  }
} else {
  int value;
  MPI_Recv(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  printf("%i received by %i\n", value, rank);
}
```

* Process 0 broadcasts a random number to all other processes

---

## 15. Collective Communication (Optional)

| Mode      | Description              |
| --------- | ------------------------ |
| Broadcast | One-to-all               |
| Scatter   | One-to-many (split data) |
| Gather    | Many-to-one              |

---

## 16. Synchronization with Barriers

```c
MPI_Barrier(MPI_COMM_WORLD);
```

* Wait until **all processes** reach this point
* Used to synchronize stages of distributed execution

---

## 17. MPI Data Types

| C Type      | MPI Type        |
| ----------- | --------------- |
| `int`       | `MPI_INT`       |
| `float`     | `MPI_FLOAT`     |
| `double`    | `MPI_DOUBLE`    |
| `long long` | `MPI_LONG_LONG` |
| ...         | ...             |

* Custom types via `MPI_Type_contiguous`, etc.

---

## 18. File & Cluster Access

* Access shared files via `\\shpc0003\<username>`
* Upload via file share
* Login via SSH: `shpc0003.ost.ch` (Port 22)

---

## 19. HPC Job Instructions

1. **Upload Program** (e.g. `HelloCluster.c`)
2. **Compile**:

   ```bash
   guix shell --pure gcc-toolchain openmpi -- mpicc HelloCluster.c
   ```
3. **Run Job**:

   ```bash
   sbatch script.sub
   ```
4. **Monitor**:

   ```bash
   squeue
   ```

---

## 20. Summary

* **MPI** enables distributed execution using message passing
* Follows **SPMD model** for efficient parallelism
* Process rank allows differentiation in logic flow
* Manual synchronization and communication provide full control

---

## 21. Further Reading

* MPI Standard: [mpi-forum.org](https://www.mpi-forum.org/)
* MPI 4.1 Specification: [PDF](https://www.mpi-forum.org/docs/mpi-4.1/mpi41-report.pdf)
* OST Cluster Dashboard: [shpc0002.ost.ch](http://shpc0002.ost.ch/dcs/)
* Slurm Job Scheduler: [Wikipedia](https://en.wikipedia.org/wiki/Slurm_Workload_Manager)