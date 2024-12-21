# 📚 **Lecture Notes**

---

## 🗓️ **Course Details**

- **Course Title:** Datenbanksysteme 1
- **Lecture Title:** SQL DML – Views and Updatable Views
- **Lecturers:** S. Keller & J. Schwab
- **Date:** HS 2024/25
- **Lecture Number:** Chapter 4, Week 8 (Continuation)

---

## 📝 **Key Topics Covered**

1. Advanced SQL Joins (Including Lateral Joins)
2. Introduction to Views
3. Updatable Views
4. Materialized Views
5. Handling NULL Values in SQL

---

## 🧠 **Learning Objectives**

- Understand the use of Views for encapsulation and simplification.
- Learn about the differences and applications of updatable and materialized views.
- Explore advanced join techniques like Lateral Joins.
- Improve handling and understanding of NULL values in SQL.

---

## 📖 **Detailed Notes**

### **1. Advanced SQL Joins**

#### **Joins Recap:**

1. **Cross Join:** Produces a Cartesian product of two tables.
2. **Inner Join:** Combines rows when a condition is met.
3. **Theta Join:** Allows arbitrary conditions, including inequalities.
4. **Semi Join:** Returns rows from the left table matching rows in the right table.
5. **Anti Join:** Returns rows in the left table that do not have matches in the right table.

#### **Lateral Join:**

- **Definition:** Allows a subquery to reference columns from preceding tables in the `FROM` clause.
- **Use Case:** Essential for correlated subqueries within a `FROM` clause.
- **Example:**
  ```sql
  SELECT department.*,
         (SELECT MAX(salary)
          FROM employee
          WHERE employee.department_id = department.id) AS max_salary
  FROM department;
  ```

---

### **2. Introduction to Views**

- **Definition:** A virtual table defined by a `SELECT` statement.
- **Purpose:**
  - Simplifies complex queries for users.
  - Enhances security by hiding sensitive data.
  - Provides schema independence for applications.
- **Syntax:**
  ```sql
  CREATE VIEW view_name AS
  SELECT columns
  FROM table
  WHERE condition;
  ```

#### **Example:**

- View for Employee Details:
  ```sql
  CREATE VIEW EmployeeDetails AS
  SELECT id, name, department_id
  FROM employee
  WHERE active = TRUE;
  ```
- Query the View:
  ```sql
  SELECT * FROM EmployeeDetails;
  ```

---

### **3. Updatable Views**

- **Conditions for Updatability:**
  - Based on a single table or updatable view.
  - No `DISTINCT`, `GROUP BY`, `HAVING`, `LIMIT`, or set operations.
  - All columns in the `SELECT` list map directly to base table columns.
- **Example of Updatable View:**

  ```sql
  CREATE VIEW ActiveProjects AS
  SELECT id, name
  FROM projects
  WHERE status = 'active';
  ```

- **Non-Updatable Views:**
  - Contain joins, aggregates, or derived columns.

---

### **4. Materialized Views**

- **Definition:** Stores query results persistently for faster access.
- **Difference from Regular Views:** Not updated automatically; requires manual refresh.
- **Syntax:**
  ```sql
  CREATE MATERIALIZED VIEW materialized_view_name AS
  SELECT columns
  FROM table;
  ```
- **Refresh:**
  ```sql
  REFRESH MATERIALIZED VIEW materialized_view_name;
  ```

---

### **5. Handling NULL Values**

#### **NULL Logic:**

- Represents "unknown" or "missing" data.
- **Three-Valued Logic (3VL):**
  - `TRUE`, `FALSE`, `UNKNOWN`.
  - Any comparison with `NULL` results in `UNKNOWN`.
- **Best Practices:**
  - Use `IS NULL` or `IS NOT NULL` for checking.
  - Use `COALESCE` to provide a default value.
    ```sql
    SELECT COALESCE(column, 'default_value') AS column_alias
    FROM table;
    ```

#### **Examples of NULL Surprises:**

- Incorrect Query:
  ```sql
  SELECT * FROM employee WHERE manager_id = NULL;
  ```
- Correct Query:
  ```sql
  SELECT * FROM employee WHERE manager_id IS NULL;
  ```

---

## ❓ **Questions Raised**

- How to optimize queries using materialized views for real-time data needs?
- When are Lateral Joins preferred over traditional joins or subqueries?

---

## 🔗 **Further Reading/Resources**

- [PostgreSQL Documentation on Views](https://www.postgresql.org/docs/current/sql-createview.html)
- [Understanding Lateral Joins](https://blog.jooq.org/a-probably-incomplete-comprehensive-guide-to-the-many-different-ways-to-join-tables-in-sql/)

---

## 📌 **Summary**

- **Main Takeaways:**
  - Views and materialized views are essential tools for simplifying access and improving performance.
  - Lateral Joins address the limitations of traditional joins with correlated subqueries.
  - Handling NULL values effectively is crucial for SQL query accuracy.
- **Connection to Previous Content:**
  - Builds upon SQL DML concepts, introducing advanced techniques for data manipulation and encapsulation.

---

## ✅ **Action Items**

- Implement views and materialized views for a sample database.
- Explore Lateral Joins with correlated subqueries for complex queries.
- Practice handling NULL values in aggregate functions and conditional queries.

---

### **Lecture Review**

- **What I Learned:**
  - Practical applications of views for query encapsulation.
  - How Lateral Joins enable advanced subquery capabilities.
- **What Needs Clarification:**
  - Trade-offs between materialized and regular views in high-load environments.
- **My Plan to Review This Material:**
  - Design a schema with updatable views and test scenarios for NULL handling.
