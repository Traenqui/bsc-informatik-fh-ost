# 📚 **Lecture Notes**

---

## 🗓️ **Course Details**

- **Course Title:** Datenbanksysteme 1
- **Lecture Title:** PostgreSQL Overview and SQL DDL
- **Lecturers:** S. Keller & J. Schwab
- **Date:** HS 2024/25
- **Lecture Numbers:** Chapter 4, Weeks 5-6

---

## 📝 **Key Topics Covered**

1. PostgreSQL Features and Architecture
2. SQL Standards and Data Types
3. SQL DDL Basics
4. Constraints and Referential Integrity
5. Practical Examples: Schema, Tables, and Constraints

---

## 🧠 **Learning Objectives**

- Understand the history and key features of PostgreSQL as an advanced relational database.
- Learn SQL DDL operations, including creating schemas, tables, and constraints.
- Understand referential integrity and how to enforce it using constraints.
- Explore PostgreSQL-specific data types and functionalities.

---

## 📖 **Detailed Notes**

### **1. PostgreSQL Overview**

- **Key Features:**

  - Open-source and extensible, with extensions like `PostGIS`, `hstore`, and `pgAdmin`.
  - Compliance with modern SQL standards.
  - Supports advanced features such as JSON, arrays, and recursive queries.

- **History:**

  - Evolved from the POSTGRES project by Michael Stonebraker (1985).
  - Current version: PostgreSQL 15 (yearly major releases).

- **Architecture:**
  - **3-tier structure:** Client, Middleware (DBMS), and Storage.
  - Database objects organized into schemas, enabling namespace partitioning.

---

### **2. SQL Standards**

- **Historical Evolution:**
  - SQL-92 to SQL:2023, with increasing support for non-relational features.
- **Modern SQL Features:**
  - JSON and JSONPath querying.
  - Common Table Expressions (CTEs) and recursive queries.
  - Window functions for analytics.

---

### **3. SQL DDL**

#### **Key Commands:**

1. **CREATE SCHEMA:**

   - Groups database objects like tables, views, and constraints.
   - **Example:**
     ```sql
     CREATE SCHEMA myschema;
     ```

2. **CREATE TABLE:**

   - Defines table structure and constraints.
   - **Example:**
     ```sql
     CREATE TABLE project (
         proj_id SERIAL PRIMARY KEY,
         name VARCHAR(50) NOT NULL,
         start_date DATE DEFAULT CURRENT_DATE
     );
     ```

3. **ALTER TABLE:**

   - Modifies table structure, such as adding or dropping constraints.
   - **Example:**
     ```sql
     ALTER TABLE project ADD COLUMN duration INT CHECK (duration > 0);
     ```

4. **DROP TABLE:**
   - Deletes tables and their constraints.
   - **Example:**
     ```sql
     DROP TABLE project CASCADE;
     ```

#### **Constraints:**

- **Column-Level:**

  - `NOT NULL`: Ensures no NULL values.
  - `CHECK`: Validates conditions on column values.
  - **Example:**
    ```sql
    duration INT CHECK (duration BETWEEN 1 AND 100);
    ```

- **Table-Level:**
  - `PRIMARY KEY`: Combines NOT NULL and UNIQUE for one or more columns.
  - `FOREIGN KEY`: Ensures referential integrity with cascading options (`ON DELETE`, `ON UPDATE`).
  - **Example:**
    ```sql
    CONSTRAINT fk_project FOREIGN KEY (proj_id) REFERENCES projects(id);
    ```

---

### **4. Referential Integrity**

#### **Cascading Options:**

1. **ON DELETE CASCADE:**

   - Deletes dependent rows when the referenced row is deleted.
   - **Example:**
     ```sql
     FOREIGN KEY (dept_id) REFERENCES department(id) ON DELETE CASCADE;
     ```

2. **ON DELETE SET NULL:**

   - Sets the foreign key column to NULL.
   - **Example:**
     ```sql
     FOREIGN KEY (dept_id) REFERENCES department(id) ON DELETE SET NULL;
     ```

3. **ON UPDATE CASCADE:**
   - Updates foreign key values when the referenced primary key changes.
   - **Example:**
     ```sql
     FOREIGN KEY (dept_id) REFERENCES department(id) ON UPDATE CASCADE;
     ```

---

### **5. Practical PostgreSQL Tips**

- **Indexing:**

  - Create indexes to speed up queries.
  - **Example:**
    ```sql
    CREATE INDEX idx_project_name ON project(name);
    ```

- **Table Management:**

  - Use scripts for table creation and separate scripts for constraints.
  - Avoid creating tables in the `postgres` system database.

- **Testing and Learning:**
  - Experiment with tools like pgAdmin, DBeaver, and db-fiddle.
  - Leverage online resources and tutorials, such as [Modern SQL](https://modern-sql.com).

---

## ❓ **Questions Raised**

- What are the practical use cases for advanced constraints like `ON DELETE SET DEFAULT`?
- How does PostgreSQL handle differences in NULL values for JSON data?

---

## 🔗 **Further Reading/Resources**

- [PostgreSQL Documentation](https://www.postgresql.org/docs/)
- [Modern SQL Features](https://modern-sql.com)
- [PostgreSQL Cheat Sheets](https://www.postgresqltutorial.com/)

---

## 📌 **Summary**

- **Main Takeaways:**
  - PostgreSQL is a feature-rich, standards-compliant RDBMS.
  - SQL DDL allows creating and managing database structures effectively.
  - Constraints ensure data integrity, with various cascading options for referential integrity.
- **Connection to Previous Content:**
  - Builds on relational modeling, introducing practical database schema implementation.

---

## ✅ **Action Items**

- Create and test schemas with multiple tables and constraints in PostgreSQL.
- Practice SQL queries involving complex joins and cascading operations.
- Explore PostgreSQL-specific features like `JSON` and `CTE`.

---

### **Lecture Review**

- **What I Learned:**
  - Practical insights into SQL DDL and PostgreSQL's architecture.
  - Importance of constraints in ensuring database consistency.
- **What Needs Clarification:**
  - Performance implications of various cascading strategies.
- **My Plan to Review This Material:**
  - Implement a small-scale project with PostgreSQL, using advanced constraints and indexing.
