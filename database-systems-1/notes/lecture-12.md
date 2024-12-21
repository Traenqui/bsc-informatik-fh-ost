# 📚 **Lecture Notes**

---

## 🗓️ **Course Details**

- **Course Title:** Datenbanksysteme 1
- **Lecture Title:** Transaktionen Teil 3 - Backup and Recovery
- **Lecturers:** S. Keller & J. Schwab
- **Date:** HS 2024/25
- **Lecture Number:** Chapter 6, Week 12

---

## 📝 **Key Topics Covered**

1. Database Architecture and Transaction Management
2. Error Classification in DB Systems
3. Write-Ahead Logs (WAL) and Log File Structure
4. Recovery Mechanisms
5. Transaction Savepoints
6. Database Backup Strategies and Tools

---

## 🧠 **Learning Objectives**

- Classify errors in database systems and their implications.
- Understand Write-Ahead Logs (WAL) and their role in recovery.
- Learn recovery techniques for different error scenarios.
- Explore database backup strategies, including logical and physical backups.
- Apply Transaction Savepoints for partial rollbacks.

---

## 📖 **Detailed Notes**

### **1. Database Architecture**

- **Transaction Manager:**
  - Coordinates transaction execution and communicates with the Scheduler.
- **Scheduler:**
  - Ensures high parallelism without compromising data integrity.
- **Recovery Manager:**
  - Handles failures and restores the database to a consistent state using logs.
- **Buffer Manager:**
  - Manages in-memory database buffers and transfers data between memory and disk.

---

### **2. Error Classification in DB Systems**

#### **Types of Errors:**

1. **Local Transaction Errors:**
   - Caused by application bugs or user actions.
   - **Recovery:** Local undo via rollback; typically completed within milliseconds.
2. **Memory Loss Errors:**
   - Caused by software crashes, power outages, or hardware failure.
   - **Recovery:**
     - **Global Undo:** Roll back active transactions.
     - **Global Redo:** Replay committed transactions.
     - Recovery time: Minutes.
3. **Disk Loss Errors:**
   - Caused by disk crashes or catastrophic events.
   - **Recovery:**
     - Reconstruct data from backups.
     - Use log files to redo committed transactions.

---

### **3. Write-Ahead Logs (WAL)**

#### **Principles:**

- Logs record all modifications before they are applied to the database.
- WAL ensures atomicity and durability.
- **Structure:**
  - `LSN (Log Sequence Number)`
  - `Transaction ID`
  - `Page ID`
  - `Redo` and `Undo` operations.
  - `PrevLSN` (points to the previous log entry of the transaction).

#### **Recovery with WAL:**

1. **REDO:** Replay operations from committed transactions.
2. **UNDO:** Revert changes from incomplete transactions.

---

### **4. Recovery Mechanisms**

#### **Key Processes:**

- **Checkpointing:**
  - Periodically flushes all changes to disk and writes a checkpoint to the log.
- **Crash Recovery Steps:**
  1. **Analysis:** Identify active and committed transactions at the time of the crash.
  2. **Redo:** Reapply committed changes from logs.
  3. **Undo:** Roll back incomplete transactions.

#### **Example:**

```plaintext
T1: Update Account A (-100); Commit.
T2: Update Account B (+100); System crashes before Commit.
- Recovery Process:
  - REDO T1.
  - UNDO T2.
```

---

### **5. Transaction Savepoints**

- Allow partial rollbacks within a transaction.
- **Commands:**
  ```sql
  SAVEPOINT savepoint_name;
  ROLLBACK TO SAVEPOINT savepoint_name;
  RELEASE SAVEPOINT savepoint_name;
  ```

#### **Example:**

```sql
BEGIN;
INSERT INTO FlightReservation VALUES ("LX212", "Alice");
SAVEPOINT FlightOK;
INSERT INTO HotelReservation VALUES ("BudgetHotel", "Alice");
ROLLBACK TO FlightOK;
INSERT INTO HotelReservation VALUES ("LuxuryHotel", "Alice");
COMMIT;
```

---

### **6. Backup Strategies**

#### **Types of Backup:**

1. **Logical Backup:**
   - Exports data in SQL format using tools like `pg_dump`.
   - Suitable for medium-sized datasets and supports cross-version compatibility.
2. **Physical Backup:**
   - Copies the entire database cluster.
   - Faster but only compatible with the same PostgreSQL version.
3. **Incremental Backup:**
   - Stores changes since the last backup, using WAL logs.
4. **Cloud Backup:**
   - Backups provided by cloud service providers, varying in functionality.

#### **Best Practices:**

- Perform regular full and incremental backups.
- Store backups and WAL logs on separate disks.
- Use mirroring and RAID for redundancy.

---

### **7. PostgreSQL-Specific Backup Tools**

1. **`pg_dump`:** Creates logical backups.
   ```bash
   pg_dump dbname > backup.sql
   ```
2. **`pgbackrest` and `pgbarman`:** Advanced tools for physical and incremental backups.
3. **Cloud Solutions:** Offer built-in backup and point-in-time recovery.

---

## ❓ **Questions Raised**

- What are the best strategies to minimize recovery time for large databases?
- How to optimize backup processes in high-availability systems?

---

## 🔗 **Further Reading/Resources**

- [PostgreSQL Documentation on Backup](https://www.postgresql.org/docs/current/backup.html)
- [Database Recovery Techniques](https://www.dataversity.net/)

---

## 📌 **Summary**

- **Main Takeaways:**
  - WAL ensures database durability and simplifies recovery.
  - Error classification helps determine appropriate recovery strategies.
  - PostgreSQL offers robust tools for logical, physical, and cloud backups.
- **Connection to Previous Content:**
  - Builds on transaction management by introducing durability and recovery.

---

## ✅ **Action Items**

- Practice backup and recovery operations using `pg_dump` and WAL logs.
- Implement Transaction Savepoints in a sample database.
- Design a recovery strategy for a high-availability PostgreSQL system.

---

### **Lecture Review**

- **What I Learned:**
  - WAL’s importance in ensuring durability.
  - Backup types and their applications in PostgreSQL.
- **What Needs Clarification:**
  - Performance trade-offs between logical and physical backups.
- **My Plan to Review This Material:**
  - Test backup and recovery scenarios in a PostgreSQL test environment.
