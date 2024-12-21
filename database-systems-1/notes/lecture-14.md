# 📚 **Lecture Notes**

---

## 🗓️ **Course Details**

- **Course Title:** Datenbanksysteme 1
- **Lecture Title:** Wiederholungsvorlesung (Review Lecture)
- **Lecturers:** Joël Schwab & Stefan Keller
- **Date:** HS 2024/25
- **Lecture Number:** Week 14

---

## 📝 **Key Topics Covered**

1. Database Design Process
2. UML Class Diagrams and Inheritance
3. Normal Forms and Functional Dependencies
4. Data Definition Language (DDL)
5. Data Manipulation Language (DML)
6. Transactions and ACID Properties
7. Indexing and Optimization
8. Data Control Language (DCL)

---

## 🧠 **Learning Objectives**

- Recap and strengthen foundational database concepts.
- Explore advanced concepts, such as transaction management and indexing.
- Revisit SQL syntax for DDL, DML, and DCL operations.
- Understand practical use cases and scenarios for database design.

---

## 📖 **Detailed Notes**

### **1. Database Design Process**

- **Steps:**
  1. **Requirements Analysis:** Define information and data processing needs.
  2. **Conceptual Design:** Create conceptual models like UML or ER diagrams.
  3. **Logical Design:** Map conceptual models to logical database structures.
  4. **Physical Design:** Optimize schemas for the DBMS and hardware.

---

### **2. UML Class Diagrams**

- **Key Elements:**
  - Attributes (e.g., `Name`, `Age`, `Race`).
  - Inheritance types:
    - **Disjoint ({disjoint}):** An object belongs to only one subclass.
    - **Overlapping ({overlapping}):** An object can belong to multiple subclasses.
    - **Complete ({complete}):** All superclass objects must be instances of a subclass.
    - **Incomplete ({incomplete}):** Some superclass objects may not belong to any subclass.

---

### **3. Normal Forms**

#### **2nd Normal Form (2NF):**

- **Requirement:**
  - Remove partial dependencies.
  - Ensure full functional dependency on the primary key.

#### **3rd Normal Form (3NF):**

- **Requirement:**
  - Eliminate transitive dependencies.
  - Example:
    ```plaintext
    trait_id -> trait_name
    trait_id -> description
    race_id, trait_id -> specification
    ```

#### **Normalization Practice:**

- Decompose tables into multiple normalized forms to achieve 3NF.

---

### **4. Data Definition Language (DDL)**

#### **Schema Design:**

1. **Inheritance (Regel 3.a, 3.b, 3.c):**

   - **3.a:** Separate tables for superclass and subclasses with references.
   - **3.b:** Only subclass tables, each with unique attributes.
   - **3.c:** One table for all, using nullable attributes and a `type` column.

2. **One-to-Many Relationships:**

   - Foreign key resides on the "many" side.
   - Example:
     ```sql
     CREATE TABLE item (
       id INTEGER PRIMARY KEY,
       name TEXT NOT NULL,
       person INTEGER REFERENCES person(id)
     );
     ```

3. **Many-to-Many Relationships:**
   - Use a join table:
     ```sql
     CREATE TABLE skill_person (
       skill_id INTEGER REFERENCES skill(id),
       person_id INTEGER REFERENCES person(id),
       PRIMARY KEY(skill_id, person_id)
     );
     ```

---

### **5. Data Manipulation Language (DML)**

- **Key Queries:**
  1. Insert data:
     ```sql
     INSERT INTO race(id, name) VALUES (1, 'Human'), (2, 'Elf');
     ```
  2. Aggregations:
     ```sql
     SELECT item_typ, AVG(value) FROM item GROUP BY item_typ;
     ```
  3. Joins:
     ```sql
     SELECT p.name, c.name AS city
     FROM person p
     JOIN city c ON p.city = c.id;
     ```
  4. Subqueries:
     ```sql
     SELECT name FROM item WHERE value > (SELECT MIN(value) FROM item WHERE item_typ = 1);
     ```

---

### **6. Transactions and ACID Properties**

- **ACID Breakdown:**

  1. **Atomicity:** All operations succeed or none do.
  2. **Consistency:** Transactions move the database from one consistent state to another.
  3. **Isolation:** Transactions are executed as if they were serial.
  4. **Durability:** Committed changes are permanent.

- **Example:**

  ```sql
  BEGIN TRANSACTION;
  UPDATE item SET person = 2 WHERE person = 1 AND name = 'Sword';
  COMMIT;
  ```

- **Concurrency Control:**
  - **Two-Phase Locking (2PL):** Ensures serializability but may lead to deadlocks.
  - **Snapshot Isolation (SI):** Avoids conflicts by working with snapshots.

---

### **7. Indexing**

- **Index Types in PostgreSQL:**

  - **B-Tree:** General-purpose, supports equality and range queries.
  - **GIN:** Ideal for JSON and full-text search.
  - **BRIN:** Lightweight, effective for large datasets.

- **Example:**
  ```sql
  CREATE INDEX idx_item_name ON item(name);
  ```

---

### **8. Data Control Language (DCL)**

- **Commands:**
  1. Create user:
     ```sql
     CREATE USER sc_admin WITH PASSWORD '1234';
     ```
  2. Grant privileges:
     ```sql
     GRANT SELECT ON sword_coast_residents TO sc_admin;
     ```
  3. Create roles:
     ```sql
     CREATE ROLE group_name WITH LOGIN;
     ```

---

## ❓ **Questions Raised**

- How to balance indexing and transaction speed in large datasets?
- What are the practical limitations of 2PL in real-world applications?

---

## 🔗 **Further Reading/Resources**

- [PostgreSQL Documentation on Normalization](https://www.postgresql.org/docs/)
- [Database Design Patterns](https://www.databasedesignpatterns.com/)

---

## 📌 **Summary**

- **Main Takeaways:**
  - Effective database design is essential for performance and scalability.
  - Transactions maintain consistency and integrity in multi-user systems.
  - Indexing accelerates queries but requires careful planning.
- **Connection to Previous Content:**
  - Builds on UML and SQL basics, extending into advanced queries and transaction management.

---

## ✅ **Action Items**

- Design a normalized database schema for a real-world scenario.
- Test transactions with various isolation levels in PostgreSQL.
- Benchmark query performance with different index types.

---

### **Lecture Review**

- **What I Learned:**
  - Recap of normalization, transactions, and indexing.
  - Practical SQL queries for real-world applications.
- **What Needs Clarification:**
  - Best practices for combining indexing and normalization.
- **My Plan to Review This Material:**
  - Implement test cases for each SQL concept in a PostgreSQL sandbox environment.
