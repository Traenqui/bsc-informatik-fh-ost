# Parallel Programming – OST Course Repository

This repository contains structured summaries and notes from the **Parallel Programming** course offered at **OST – Ostschweizer Fachhochschule, Campus Rapperswil**, taught by **Prof. Dr. Mitra Purandare**.

The course focuses on various models and technologies for parallel and concurrent programming on multicore CPUs, GPUs, and clusters. Topics range from multithreading and synchronization to high-performance computing using MPI and OpenMP.

---

## 📚 Course Overview

- **Lecturer:** Prof. Dr. Mitra Purandare
- **Semester:** FS 2025
- **Institution:** OST Rapperswil
- **Focus Areas:**
  - Thread-based parallelism (Java, C#)
  - Distributed computing with MPI
  - Shared-memory parallelism with OpenMP
  - Asynchronous programming
  - Lock-free programming and memory models
  - Cluster and hybrid architectures

---

## 🧭 Repository Structure

Each folder or file corresponds to a week in the course. Summaries are provided in clean Markdown format for readability and reuse.

| Week | Topic                                     | Summary Link              |
|------|-------------------------------------------|---------------------------|
| 01   | Introduction & Multithreading Basics       | [`Week 01`](./notes/week01.md)  |
| 02   | Monitor Synchronization in Java            | [`Week 02`](./notes/week02.md)  |
| 03   | Synchronization Primitives (Semaphores, Locks) | [`Week 03`](./notes/week03.md)  |
| 04   | Dangers of Concurrency                     | [`Week 04`](./notes/week04.md)  |
| 05   | Thread Pools and Task Parallelism          | [`Week 05`](./notes/week05.md)  |
| 06   | Asynchronous Programming                   | [`Week 06`](./notes/week06.md)  |
| 07   | Memory Models (Java and .NET)              | [`Week 07`](./notes/week07.md)  |
| 08   | MPI and Cluster Parallelization (Intro)    | [`Week 08`](./notes/week08.md)  |
| 09   | MPI Collective Communication & Pi Example  | [`Week 09`](./notes/week09.md)  |
| 10   | OpenMP and Hybrid MPI+OpenMP               | [`Week 10`](./notes/week10.md)  |

---

## 🔧 Technologies Covered

- **Languages:** Java, C, C#, OpenMP pragmas
- **Parallel APIs:** Java `Thread`, ForkJoinPool, C# TPL, OpenMP, MPI
- **Models:** SPMD, MPMD, shared/distributed memory
- **Tools:** GCC, OpenMPI, Slurm, PuTTY, SSH

---

## 🧠 Learning Objectives

- Understand and implement parallel programming models
- Write thread-safe code with proper synchronization
- Utilize cluster resources using MPI
- Combine MPI and OpenMP for hybrid parallelism
- Apply parallelism to real problems like Monte Carlo simulations

---

## 📌 How to Use

- Browse individual weekly summaries for structured lecture content.
- Each `.md` file is self-contained and suitable for review or exam prep.
- Code examples are embedded or referenced for clarity and replication.

---

## 📬 Contributions

This repo reflects **my personal learning journey** through the course. Suggestions and feedback are welcome — feel free to fork or submit pull requests to improve or extend the material.

---

## 📄 License

This work is shared under the **MIT License**. You are free to use, adapt, and share with proper attribution.