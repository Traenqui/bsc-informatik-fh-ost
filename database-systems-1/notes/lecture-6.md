Here are the detailed lecture notes on **SQL Data Manipulation Language (DML)** from the uploaded PDF.

---

# 📚 **Lecture Notes**

---

## 🗓️ **Course Details**

- **Course Title:** Datenbanksysteme 1
- **Lecture Title:** SQL DML with PostgreSQL
- **Lecturers:** S. Keller & J. Schwab
- **Date:** HS 2024/25
- **Lecture Number:** Chapter 4, Week 6

---

## 📝 **Key Topics Covered**

1. SQL DML Commands (INSERT, UPDATE, DELETE, SELECT)
2. SELECT-FROM-WHERE Clauses
3. Aggregation and Grouping (GROUP BY, HAVING)
4. Joins and Subqueries
5. Set Operations (UNION, INTERSECT, MINUS)
6. NULL Handling in SQL

---

## 🧠 **Learning Objectives**

- Learn to manipulate data using SQL DML commands.
- Understand the structure and execution of SQL SELECT queries.
- Apply grouping and aggregation functions effectively.
- Use Joins, Subqueries, and Set Operations to solve complex queries.
- Handle NULL values in data manipulation and queries.

---

## 📖 **Detailed Notes**

### **1. SQL DML Overview**

- **Commands:**
  - `INSERT`: Adds rows to a table.
  - `UPDATE`: Modifies existing rows.
  - `DELETE`: Removes rows from a table.
  - `SELECT`: Retrieves data from one or more tables.
- **Examples:**
  ```sql
  INSERT INTO employee (id, name, salary) VALUES (101, 'John Doe', 5000);
  UPDATE employee SET salary = salary * 1.1 WHERE id = 101;
  DELETE FROM employee WHERE id = 101;
  SELECT * FROM employee;
  ```

---

### **2. SELECT-FROM-WHERE Clause**

- **Basic Syntax:**
  ```sql
  SELECT columns
  FROM tables
  WHERE conditions
  ORDER BY columns;
  ```
- **Examples:**
  ```sql
  SELECT name, salary
  FROM employee
  WHERE salary > 3000
  ORDER BY salary DESC;
  ```
- **Key Features:**
  - Projection: Specify columns to retrieve.
  - Selection: Filter rows using `WHERE`.
  - Sorting: Use `ORDER BY ASC/DESC`.

---

### **3. Aggregation and Grouping**

#### **Aggregation Functions:**

- **Common Functions:**
  - `SUM`, `AVG`, `MAX`, `MIN`, `COUNT`.
  ```sql
  SELECT AVG(salary), MAX(salary) FROM employee;
  ```

#### **GROUP BY and HAVING:**

- **Grouping:**
  ```sql
  SELECT department, AVG(salary) AS avg_salary
  FROM employee
  GROUP BY department;
  ```
- **Filtering Groups:**
  ```sql
  SELECT department, COUNT(*) AS num_employees
  FROM employee
  GROUP BY department
  HAVING COUNT(*) > 5;
  ```

---

### **4. Joins**

#### **Types:**

1. **Inner Join:**

   - Retrieves matching rows from both tables.

   ```sql
   SELECT e.name, d.name AS department
   FROM employee e
   INNER JOIN department d ON e.department_id = d.id;
   ```

2. **Left Outer Join:**

   - Includes all rows from the left table and matching rows from the right table.

   ```sql
   SELECT e.name, p.project_name
   FROM employee e
   LEFT OUTER JOIN project p ON e.id = p.employee_id;
   ```

3. **Right Outer Join:**
   - Includes all rows from the right table and matching rows from the left table.
   ```sql
   SELECT d.name, e.name
   FROM department d
   RIGHT OUTER JOIN employee e ON e.department_id = d.id;
   ```

---

### **5. Subqueries**

- **Types:**
  - **Scalar Subquery:** Returns a single value.
    ```sql
    SELECT name FROM employee WHERE salary = (SELECT MAX(salary) FROM employee);
    ```
  - **IN Subquery:** Checks membership in a set.
    ```sql
    SELECT name FROM employee WHERE department_id IN (SELECT id FROM department WHERE name = 'Sales');
    ```
  - **EXISTS Subquery:** Tests for existence.
    ```sql
    SELECT name FROM employee WHERE EXISTS (SELECT * FROM project WHERE employee_id = employee.id);
    ```

---

### **6. Set Operations**

- **UNION:** Combines two queries, removing duplicates.
  ```sql
  SELECT name FROM employee WHERE department = 'HR'
  UNION
  SELECT name FROM contractor WHERE department = 'HR';
  ```
- **INTERSECT:** Returns common rows between two queries.
  ```sql
  SELECT name FROM employee
  INTERSECT
  SELECT name FROM contractor;
  ```
- **MINUS/EXCEPT:** Returns rows in the first query not in the second.
  ```sql
  SELECT name FROM employee
  EXCEPT
  SELECT name FROM contractor;
  ```

---

### **7. NULL Handling**

- **Concepts:**
  - `NULL` represents missing or unknown data.
  - Arithmetic operations with `NULL` result in `NULL`.
- **Handling Examples:**
  ```sql
  SELECT name FROM employee WHERE salary IS NULL;
  SELECT name, COALESCE(salary, 0) AS effective_salary FROM employee;
  ```

---

## ❓ **Questions Raised**

- How does the performance of different join types compare in large databases?
- What are best practices for optimizing complex subqueries?

---

## 🔗 **Further Reading/Resources**

- [PostgreSQL Documentation on DML](https://www.postgresql.org/docs/current/sql.html)
- [SQL Tutorial](https://www.w3schools.com/sql/)
- [SQL Island Practice Tool](http://sql-island.informatik.uni-kl.de/)

---

## 📌 **Summary**

- **Main Takeaways:**
  - SQL DML is foundational for data manipulation in relational databases.
  - SELECT queries can range from simple to highly complex using joins, subqueries, and set operations.
  - Proper handling of NULL values is critical in data integrity and query results.
- **Connection to Previous Content:**
  - Builds upon schema design (DDL), focusing on data interaction and analysis.

---

## ✅ **Action Items**

- Practice SELECT queries with different joins and subqueries.
- Explore SQL optimization techniques for DML operations.
- Implement a small database project to apply these concepts.

---

### **Lecture Review**

- **What I Learned:**
  - How to structure complex SQL queries using DML commands.
  - Advanced usage of joins and subqueries.
- **What Needs Clarification:**
  - Practical scenarios where UNION vs. JOIN is more effective.
- **My Plan to Review This Material:**
  - Use a dataset to practice aggregation, joins, and subqueries in PostgreSQL.
