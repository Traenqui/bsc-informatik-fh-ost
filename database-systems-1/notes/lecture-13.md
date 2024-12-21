# 📚 **Lecture Notes**

---

## 🗓️ **Course Details**

- **Course Title:** Datenbanksysteme 1
- **Lecture Title:** Indexing and Physical Storage Structures
- **Lecturers:** S. Keller & J. Schwab
- **Date:** HS 2024/25
- **Lecture Number:** Chapter 7, Week 13

---

## 📝 **Key Topics Covered**

1. Basics of Indexing in Databases
2. Index Structures: B-Trees, B+-Trees, ISAM, and Hash
3. Advanced Index Variations in PostgreSQL
4. Best Practices for Index Optimization
5. Animation and Demonstration of B-Tree Operations

---

## 🧠 **Learning Objectives**

- Understand the purpose and structure of database indexes.
- Learn how B-Trees and B+-Trees organize and retrieve data efficiently.
- Explore PostgreSQL index types and their use cases.
- Analyze and optimize database queries using indexing techniques.
- Visualize the creation, insertion, and deletion in B-Tree structures.

---

## 📖 **Detailed Notes**

### **1. Basics of Indexing**

- **Definition:**
  - An index is a data structure separate from the table, improving data retrieval.
  - Reduces the complexity of search operations:
    - Without index: O(n) (linear).
    - With index: O(log n) (logarithmic).
- **Trade-offs:**
  - **Advantages:** Faster queries.
  - **Disadvantages:** Slower inserts, updates, and deletes due to index maintenance.
- **SQL Commands:**
  - Create Index:
    ```sql
    CREATE INDEX idx_name ON table(column);
    ```
  - Drop Index:
    ```sql
    DROP INDEX idx_name;
    ```

---

### **2. Index Structures**

#### **B-Trees and B+-Trees**

- **B-Trees:**
  - Balanced multi-way search trees where all leaves are at the same level.
  - Nodes contain keys and pointers to child nodes or data.
  - Operations:
    - **Search:** Logarithmic complexity.
    - **Insert/Delete:** Adjust the tree to maintain balance.
- **B+-Trees:**
  - Only leaf nodes contain data pointers, while internal nodes store keys.
  - Leaf nodes are linked for efficient range queries.
  - Used for clustering and indexing in systems like PostgreSQL.

#### **ISAM (Indexed Sequential Access Method):**

- Sorts data by index key, maintaining a sequential index.
- Fast for static data but inefficient for frequent updates.

#### **Hash Indexes:**

- Uses a hash function to map keys to buckets.
- Effective for equality searches but unsuitable for range queries.

---

### **3. Index Variations in PostgreSQL**

#### **Supported Index Types:**

1. **B-Tree (Default):**

   - General-purpose index for equality, range queries, and pattern matching.
   - Syntax:
     ```sql
     CREATE INDEX idx_name ON table USING btree(column);
     ```

2. **Hash Index:**

   - Optimized for equality searches.
   - Example:
     ```sql
     CREATE INDEX idx_name ON table USING hash(column);
     ```

3. **GiST (Generalized Search Tree):**

   - For geometric, range, and full-text searches.
   - Requires extensions like `btree_gist`.
   - Example:
     ```sql
     CREATE INDEX idx_name ON table USING gist(column);
     ```

4. **GIN (Generalized Inverted Index):**

   - Ideal for full-text and JSONB indexing.
   - Example:
     ```sql
     CREATE INDEX idx_name ON table USING gin(column);
     ```

5. **BRIN (Block Range Index):**
   - Uses block-level indexing for sorted or clustered data.
   - Example:
     ```sql
     CREATE INDEX idx_name ON table USING brin(column);
     ```

#### **Advanced Indexing Options:**

- **Composite Index:**
  - Index across multiple columns.
  - Example:
    ```sql
    CREATE INDEX idx_name ON table(column1, column2);
    ```
- **Partial Index:**
  - Applies only to specific rows defined by a condition.
  - Example:
    ```sql
    CREATE INDEX idx_name ON table(column) WHERE condition;
    ```
- **Functional Index:**
  - Indexes the result of a function.
  - Example:
    ```sql
    CREATE INDEX idx_name ON table(LOWER(column));
    ```

---

### **4. Best Practices for Index Optimization**

- Index frequently queried columns (especially in `WHERE` clauses).
- Avoid indexing:
  - Columns with low cardinality (e.g., boolean values).
  - Frequently updated columns.
- Use partial and functional indexes for specific use cases.
- Regularly analyze and vacuum tables to update statistics.
- Monitor index performance using tools like `EXPLAIN`.

---

### **5. Animation of B-Tree Operations**

#### **Visualization of Insertion:**

- Inserting keys into a B-Tree:
  1. Keys are inserted sequentially into leaf nodes.
  2. If a node exceeds capacity, it splits, and the middle key is promoted to the parent.
  3. The process repeats until the tree is balanced.

#### **Visualization of Deletion:**

- Deleting keys from a B-Tree:
  1. Locate and remove the key.
  2. If a node underflows, borrow keys from siblings or merge nodes.
  3. Adjust parent nodes to maintain balance.

#### **Key Concepts:**

- Tree height remains logarithmic relative to the number of keys.
- B-Trees ensure efficient searches, inserts, and deletes.

---

## ❓ **Questions Raised**

- How do BRIN indexes compare with B-Tree indexes for time-series data?
- What are the practical trade-offs between GIN and GiST for text indexing?

---

## 🔗 **Further Reading/Resources**

- [PostgreSQL Index Types Documentation](https://www.postgresql.org/docs/current/indexes-types.html)
- [Visualization of B-Tree Operations](https://www.cs.usfca.edu/~galles/visualization/BTree.html)

---

## 📌 **Summary**

- **Main Takeaways:**
  - Indexes optimize database performance by reducing query time complexity.
  - B-Trees and B+-Trees are the most widely used structures for indexing.
  - PostgreSQL offers a variety of index types tailored to specific use cases.
- **Connection to Previous Content:**
  - Extends query optimization concepts with advanced indexing strategies.

---

## ✅ **Action Items**

- Implement composite and functional indexes in PostgreSQL.
- Test query performance with and without indexes using `EXPLAIN`.
- Visualize B-Tree operations with animated tools for deeper understanding.

---

### **Lecture Review**

- **What I Learned:**
  - Practical application of indexing in PostgreSQL.
  - Importance of choosing the right index type for specific queries.
- **What Needs Clarification:**
  - Performance benchmarks for GIN vs. GiST indexes.
- **My Plan to Review This Material:**
  - Experiment with index types on a large dataset in PostgreSQL.
