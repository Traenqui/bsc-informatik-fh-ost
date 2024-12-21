# 📚 **Lecture Notes**

---

## 🗓️ **Course Details**

- **Course Title:** Datenbanksysteme 1
- **Lecture Title:** Einführung in Transaktionen
- **Lecturers:** S. Keller & J. Schwab
- **Date:** HS 2024/25
- **Lecture Number:** Chapter 6, Week 10

---

## 📝 **Key Topics Covered**

1. Introduction to Transactions
2. ACID Properties
3. SQL Transactions: Commit, Rollback, and Savepoints
4. Isolation and Serializability
5. Conflict Management and Deadlocks
6. Two-Phase Locking Protocols

---

## 🧠 **Learning Objectives**

- Understand the concept of transactions in databases.
- Explain the ACID properties for transaction management.
- Learn the SQL syntax for transaction management (BEGIN, COMMIT, ROLLBACK).
- Understand isolation levels and serializability in concurrent executions.
- Analyze locking mechanisms, deadlocks, and their resolutions.

---

## 📖 **Detailed Notes**

### **1. Why Transactions?**

- **Purpose:**
  - Ensure atomic operations: All or nothing.
  - Maintain isolation in multi-user environments.
  - Guarantee data consistency and durability.
- **Example Use Case:**
  - Bank Transfer: $100 from Bob to Alice should either complete both debit and credit or none.

---

### **2. ACID Properties**

1. **Atomicity:**
   - Ensures a transaction is executed fully or not at all.
   - **Example:** Rollback when an error occurs.
2. **Consistency:**
   - Maintains database rules and constraints after a transaction.
   - **Example:** Sum of balances remains constant after a transfer.
3. **Isolation:**
   - Prevents transactions from interfering with each other.
   - **Implementation:** Locking or versioning mechanisms.
4. **Durability:**
   - Guarantees changes are saved permanently after a commit.
   - **Example:** Write-Ahead Logging (WAL) ensures persistence.

---

### **3. Transactions in SQL**

- **Basic Commands:**
  - Start a transaction:
    ```sql
    BEGIN TRANSACTION;
    ```
  - Commit changes:
    ```sql
    COMMIT;
    ```
  - Rollback changes:
    ```sql
    ROLLBACK;
    ```
- **Savepoints for Partial Rollbacks:**
  ```sql
  SAVEPOINT savepoint_name;
  ROLLBACK TO SAVEPOINT savepoint_name;
  RELEASE SAVEPOINT savepoint_name;
  ```

---

### **4. Isolation and Serializability**

- **Definitions:**
  - **Serializability:** A schedule is serializable if its effect is equivalent to some serial execution.
  - **Conflict Serializable:** No cycles in the conflict graph.
- **Schedules:**
  - **Serial Schedule:** Transactions execute sequentially.
  - **Interleaved Schedule:** Transactions execute concurrently but mimic serial execution.
- **Example Conflict Operations:**
  - **Read-Write Conflict:** Concurrent reads and writes to the same object.
  - **Write-Write Conflict:** Overwriting another transaction's writes.

---

### **5. Locking Mechanisms**

- **Granularity:**
  - Locks can be applied at different levels: table, row, or item.
- **Lock Modes:**
  - **Shared Lock (S):** For read operations; allows multiple transactions.
  - **Exclusive Lock (X):** For write operations; allows only one transaction.
- **Two-Phase Locking (2PL):**
  - **Growing Phase:** Transaction acquires all locks.
  - **Shrinking Phase:** Transaction releases locks.
  - Ensures serializability but can lead to **deadlocks**.

---

### **6. Deadlocks and Conflict Resolution**

- **Deadlock:**
  - Circular wait where two or more transactions wait indefinitely for each other’s locks.
- **Resolution Strategies:**
  1. **Timeouts:** Abort transactions waiting too long.
  2. **Deadlock Detection:**
     - Use a **Wait-For Graph** to identify cycles.
     - Abort one transaction in the cycle.
  3. **Deadlock Prevention:**
     - **Preclaiming Locks:** Acquire all locks upfront.
     - Ensure no cycles form.

---

### **7. Practical Examples**

- **Atomic Bank Transfer:**
  ```sql
  BEGIN TRANSACTION;
  UPDATE Account SET Balance = Balance - 100 WHERE Owner = 'Bob';
  UPDATE Account SET Balance = Balance + 100 WHERE Owner = 'Alice';
  COMMIT;
  ```
- **Handling Errors:**
  ```sql
  BEGIN;
  UPDATE Account SET Balance = Balance - 100 WHERE Owner = 'Bob';
  IF balance < 0 THEN ROLLBACK;
  ELSE COMMIT;
  END IF;
  ```

---

## ❓ **Questions Raised**

- How does snapshot isolation differ from locking mechanisms?
- What are the trade-offs between pessimistic and optimistic concurrency control?

---

## 🔗 **Further Reading/Resources**

- [Interactive Serializability Tutorial](https://www.sachsen.schule/~lava/datenbanken/serialisierbarkeit_am_beispiel.html)
- Bernstein, Hadzilacos, and Goodman, "Concurrency Control and Recovery in Database Systems."

---

## 📌 **Summary**

- **Main Takeaways:**
  - Transactions ensure database reliability through the ACID properties.
  - Serializability guarantees consistent results in concurrent transactions.
  - Locking protocols like 2PL are essential but can lead to deadlocks.
- **Connection to Previous Content:**
  - Builds on database design, focusing on runtime behavior and integrity.

---

## ✅ **Action Items**

- Practice creating conflict-free schedules and analyzing serializability.
- Simulate deadlocks and apply resolution strategies in PostgreSQL.
- Explore Two-Phase Locking variations (Strict 2PL, Preclaiming 2PL).

---

### **Lecture Review**

- **What I Learned:**
  - The importance of ACID properties in transaction management.
  - How serializability ensures correctness in concurrent environments.
- **What Needs Clarification:**
  - Implementation of conflict graphs in real-world DBMS.
- **My Plan to Review This Material:**
  - Test locking mechanisms in PostgreSQL using test datasets.
  - Analyze serializability using example schedules.
