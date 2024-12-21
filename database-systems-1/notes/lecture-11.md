# 📚 **Lecture Notes**

---

## 🗓️ **Course Details**

- **Course Title:** Datenbanksysteme 1
- **Lecture Title:** Transaktionen Teil 2
- **Lecturers:** S. Keller & J. Schwab
- **Date:** HS 2024/25
- **Lecture Number:** Chapter 6, Week 11

---

## 📝 **Key Topics Covered**

1. Isolation Levels
2. Common Transaction Anomalies
3. Snapshot Isolation (SI) and Serializable Snapshot Isolation (SSI)
4. Implementation in PostgreSQL (MVCC)
5. Optimistic and Pessimistic Concurrency Control
6. Conflict and Deadlock Resolution
7. Exercises and Best Practices

---

## 🧠 **Learning Objectives**

- Understand isolation levels and their trade-offs.
- Identify and analyze common anomalies in database transactions.
- Explore advanced isolation mechanisms like Snapshot Isolation and Serializable Snapshot Isolation.
- Learn PostgreSQL-specific implementations for transaction isolation and concurrency control.
- Apply strategies to resolve transaction conflicts and deadlocks.

---

## 📖 **Detailed Notes**

### **1. Isolation Levels**

- Defined by ANSI SQL-92 Standards:

  1. **READ UNCOMMITTED:**
     - Transactions may read uncommitted data ("dirty reads").
  2. **READ COMMITTED (Default in PostgreSQL):**
     - Only committed data is readable.
  3. **REPEATABLE READ:**
     - Prevents non-repeatable reads; no changes visible during a transaction.
  4. **SERIALIZABLE:**
     - Provides the highest isolation; transactions execute as if serialized.

- **PostgreSQL Configuration:**
  ```sql
  SET TRANSACTION ISOLATION LEVEL SERIALIZABLE;
  BEGIN;
  -- Transaction Statements
  COMMIT;
  ```

---

### **2. Common Transaction Anomalies**

- **Dirty Read:**
  - Reading uncommitted changes from another transaction.
  - **Example:**
    ```sql
    T1: SELECT * FROM Account WHERE Owner = 'Bob'; -- sees uncommitted changes by T2
    T2: UPDATE Account SET Balance = 0 WHERE Owner = 'Bob'; ROLLBACK;
    ```
- **Non-Repeatable Read (Fuzzy Read):**
  - Repeated reads yield different results due to another transaction's updates.
- **Phantom Read:**
  - New rows appear or existing rows disappear during a transaction.
- **Serialization Anomaly:**
  - Results differ from serial execution of transactions.

---

### **3. Snapshot Isolation (SI)**

- **Definition:**
  - Each transaction works with a consistent snapshot of the database at its start time.
  - Write conflicts are resolved at commit time.
- **Advantages:**
  - Readers don’t block writers and vice versa.
- **Drawbacks:**
  - Does not guarantee serializability (e.g., Write Skew Anomalies).

#### **Serializable Snapshot Isolation (SSI):**

- **Implementation:**
  - Detects conflicts dynamically and aborts transactions that violate serializability.
- **PostgreSQL Implementation:**
  - Available for `REPEATABLE READ` and `SERIALIZABLE` isolation levels since PostgreSQL 9.1.

---

### **4. Implementation in PostgreSQL**

- **Multi-Version Concurrency Control (MVCC):**
  - Maintains multiple versions of a tuple.
  - Each transaction sees the latest version valid at its start time.
- **Advantages of MVCC:**
  - Avoids reader-writer blocking.
  - Reduces contention in high-concurrency systems.
- **Conflict Resolution:**
  - Transactions encountering a write conflict are rolled back.

---

### **5. Optimistic and Pessimistic Concurrency Control**

#### **Pessimistic Methods:**

- Locking is used to prevent conflicts.
- **Two-Phase Locking (2PL):**
  - **Growing Phase:** Acquires all locks.
  - **Shrinking Phase:** Releases locks.
- **Advantages:**
  - Ensures serializability.
- **Disadvantages:**
  - May cause deadlocks.

#### **Optimistic Methods:**

- Assumes minimal conflicts and resolves them at commit time.
- **Snapshot Isolation:** Uses versioning to handle conflicts.

---

### **6. Conflict and Deadlock Resolution**

#### **Deadlock Detection:**

- Use a Wait-For Graph to detect cycles.
- Abort one of the transactions in the cycle.

#### **Deadlock Prevention:**

1. **Timeouts:** Transactions waiting too long are aborted.
2. **Lock Ordering:** Enforce a global order for acquiring locks.

#### **Conflict Resolution in PostgreSQL:**

- Rollback transactions violating consistency.

---

### **7. Exercises and Best Practices**

- **Practice:**
  - Experiment with different isolation levels and analyze anomalies.
  - Explore deadlock scenarios and resolution strategies.
- **Best Practices:**
  - Use `SERIALIZABLE` for critical operations requiring consistency.
  - Monitor for long-running transactions to avoid conflicts.

---

## ❓ **Questions Raised**

- How does PostgreSQL implement deadlock detection in large-scale systems?
- What are the trade-offs between using SI and SSI for high-concurrency workloads?

---

## 🔗 **Further Reading/Resources**

- [PostgreSQL Documentation on MVCC](https://www.postgresql.org/docs/current/mvcc.html)
- [Serializable Isolation for Snapshot Databases](https://dl.acm.org/doi/10.1145/1376616.1376673)

---

## 📌 **Summary**

- **Main Takeaways:**
  - Isolation levels define trade-offs between consistency and concurrency.
  - Snapshot Isolation improves concurrency but does not guarantee serializability.
  - PostgreSQL’s MVCC efficiently implements SI and SSI for transactional consistency.
- **Connection to Previous Content:**
  - Builds on the foundational concepts of ACID properties and transaction management.

---

## ✅ **Action Items**

- Test different isolation levels in PostgreSQL for practical understanding.
- Analyze and implement solutions for Write Skew and Phantom Read anomalies.
- Design a high-concurrency system using MVCC principles.

---

### **Lecture Review**

- **What I Learned:**
  - Theoretical and practical nuances of isolation levels.
  - PostgreSQL's approach to handling transactional anomalies.
- **What Needs Clarification:**
  - Performance implications of SSI under heavy write loads.
- **My Plan to Review This Material:**
  - Develop a simulation of transaction conflicts using a test database.
