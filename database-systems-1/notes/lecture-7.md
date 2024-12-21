# 📚 **Lecture Notes**

---

## 🗓️ **Course Details**

- **Course Title:** Datenbanksysteme 1
- **Lecture Title:** SQL DML - Advanced Topics
- **Lecturers:** S. Keller & J. Schwab
- **Date:** HS 2024/25
- **Lecture Number:** Chapter 4, Week 8

---

## 📝 **Key Topics Covered**

1. Advanced SQL DML Operations
2. Window Functions
3. Common Table Expressions (CTEs)
4. SQL Query Execution Order
5. Examples and Exercises for Analysis

---

## 🧠 **Learning Objectives**

- Understand advanced features of SQL DML, including Window Functions and CTEs.
- Apply these features for complex queries and data analysis.
- Learn the syntactic and logical order of SQL query execution.
- Practice advanced SQL concepts through exercises.

---

## 📖 **Detailed Notes**

### **1. Advanced SQL DML**

- **CRUD Operations:**
  - Insert, Select, Update, Delete.
  - Example for bulk insertion using `COPY`:
    ```sql
    COPY department FROM '/path/to/file.csv' WITH CSV;
    ```
- **Casting and Formatting:**
  - Cast data types using `CAST` or `::`.
    ```sql
    SELECT '2024-01-01'::DATE;
    ```
  - Format date/time:
    ```sql
    SELECT TO_CHAR(NOW(), 'YYYY-MM-DD');
    ```

---

### **2. Window Functions**

- **Definition:**
  - Operate over a "window" of rows, maintaining row granularity.
  - Syntax:
    ```sql
    SELECT column,
           window_function() OVER (PARTITION BY column ORDER BY column) AS alias
    FROM table;
    ```
- **Examples:**
  1. **Maximum Salary by Department:**
     ```sql
     SELECT department_id,
            employee_id,
            MAX(salary) OVER (PARTITION BY department_id) AS max_salary
     FROM employee;
     ```
  2. **Ranking Employees by Salary:**
     ```sql
     SELECT department_id,
            employee_id,
            salary,
            RANK() OVER (PARTITION BY department_id ORDER BY salary DESC) AS rank
     FROM employee;
     ```
  3. **Difference Between Salaries:**
     ```sql
     SELECT employee_id,
            salary,
            LAG(salary) OVER (ORDER BY salary) AS prev_salary,
            salary - LAG(salary) OVER (ORDER BY salary) AS salary_diff
     FROM employee;
     ```

---

### **3. Common Table Expressions (CTEs)**

- **Definition:**
  - Temporary result sets for use in complex queries.
  - Syntax:
    ```sql
    WITH cte_name AS (
      SELECT ...
    )
    SELECT ...
    FROM cte_name;
    ```
- **Recursive CTE:**
  - Example: Sum numbers from 1 to 5.
    ```sql
    WITH RECURSIVE numbers(n) AS (
      SELECT 1
      UNION ALL
      SELECT n + 1 FROM numbers WHERE n < 5
    )
    SELECT SUM(n) FROM numbers;
    ```
- **Use Cases:**
  - Simplify subqueries.
  - Enable recursive queries.
  - Organize complex queries logically.

---

### **4. SQL Query Execution Order**

#### **Logical vs. Syntactic Order:**

- **Syntactic Order:**
  ```sql
  SELECT ...
  FROM ...
  JOIN ...
  WHERE ...
  GROUP BY ...
  HAVING ...
  ORDER BY ...
  ```
- **Logical Order:**
  - `FROM`, `JOIN`, `WHERE`, `GROUP BY`, `HAVING`, `SELECT`, `DISTINCT`, `ORDER BY`.

---

## ❓ **Questions Raised**

- When to use Window Functions vs. GROUP BY?
- How do recursive CTEs impact performance on large datasets?

---

## 🔗 **Further Reading/Resources**

- [PostgreSQL Window Functions Documentation](https://www.postgresql.org/docs/current/functions-window.html)
- [CTE Basics](https://www.postgresql.org/docs/current/queries-with.html)

---

## 📌 **Summary**

- **Main Takeaways:**
  - Window Functions extend the capability of GROUP BY by retaining granularity.
  - CTEs simplify complex SQL queries and enable recursion.
  - Understanding SQL query execution order aids optimization.
- **Connection to Previous Content:**
  - Builds upon basic DML, introducing tools for advanced data analysis.

---

## ✅ **Action Items**

- Implement a database project using Window Functions for analysis.
- Practice recursive queries using CTEs.
- Experiment with query optimization using logical execution order.

---

### **Lecture Review**

- **What I Learned:**
  - The versatility of SQL Window Functions for detailed analysis.
  - How CTEs improve readability and maintainability of complex queries.
- **What Needs Clarification:**
  - Best practices for balancing CTE complexity and performance.
- **My Plan to Review This Material:**
  - Design queries to test recursive CTEs and compare execution plans.
