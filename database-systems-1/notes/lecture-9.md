# 📚 **Lecture Notes**

---

## 🗓️ **Course Details**

- **Course Title:** Datenbanksysteme 1
- **Lecture Title:** Database Security with SQL DCL (PostgreSQL)
- **Lecturers:** S. Keller & J. Schwab
- **Date:** HS 2024/25
- **Lecture Number:** Chapter 5, Week 9

---

## 📝 **Key Topics Covered**

1. Overview of Database Security
2. User Management in PostgreSQL
3. SQL Data Control Language (DCL)
4. Object Privileges and System Privileges
5. SQL Injection and Security Measures
6. Advanced Security Concepts: Row-Level Security

---

## 🧠 **Learning Objectives**

- Understand the role of SQL DCL in database management.
- Learn to manage users, roles, and privileges in PostgreSQL.
- Explore security vulnerabilities like SQL Injection and implement countermeasures.
- Apply advanced security measures, including Row-Level Security.

---

## 📖 **Detailed Notes**

### **1. Introduction to Database Security**

#### **Key Concepts:**

- **Authentication:** Verifying the identity of users (e.g., username and password).
- **Authorization:** Determining what operations a user is allowed to perform.
- **Access Control:** Restricting unauthorized data access.
- **Auditing:** Monitoring and recording user activities.

#### **Types of Security:**

- **System Security:** Focuses on the DBMS as a whole.
- **Data Security:** Ensures the integrity, confidentiality, and availability of data.

---

### **2. SQL Data Control Language (DCL)**

#### **Purpose:**

- Manages database access permissions.
- Commands: `GRANT`, `REVOKE`.

#### **Examples:**

- Granting privileges:
  ```sql
  GRANT SELECT, INSERT ON employee TO john;
  ```
- Revoking privileges:
  ```sql
  REVOKE SELECT ON employee FROM john;
  ```

---

### **3. User Management in PostgreSQL**

#### **Creating Users and Roles:**

- **Syntax:**
  ```sql
  CREATE ROLE username WITH LOGIN PASSWORD 'password';
  ```
- **Role Types:**
  - **Login Role:** Can log into the database.
  - **Group Role:** Cannot log in but manages privileges.

#### **Privileges:**

- Assigning privileges:
  ```sql
  GRANT INSERT ON employee TO group_name;
  ```
- Removing privileges:
  ```sql
  DROP ROLE username;
  ```

---

### **4. Object and System Privileges**

#### **System Privileges:**

- Control operations like database creation.
- PostgreSQL commands:
  ```sql
  CREATE ROLE admin CREATEDB CREATEROLE;
  ```

#### **Object Privileges:**

- Control access to tables, views, and sequences.
- Examples:
  - **Grant SELECT:** Allows reading data.
    ```sql
    GRANT SELECT ON table_name TO user;
    ```
  - **Grant ALL Privileges:**
    ```sql
    GRANT ALL ON table_name TO user;
    ```
  - **Revoke Privileges:**
    ```sql
    REVOKE ALL ON table_name FROM user;
    ```

---

### **5. SQL Injection and Security Measures**

#### **What is SQL Injection?**

- A vulnerability where attackers inject malicious SQL to manipulate or access unauthorized data.

#### **Examples:**

1. Malicious input:
   ```sql
   SELECT * FROM users WHERE username = '' OR 1=1 --' AND password = '';
   ```
2. Exploit through dynamic queries:
   ```sql
   $query = "SELECT * FROM users WHERE id = " . $_GET['id'];
   ```

#### **Countermeasures:**

- Use parameterized queries:
  ```sql
  PREPARE stmt FROM 'SELECT * FROM users WHERE id = ?';
  EXECUTE stmt USING id_value;
  ```
- Validate user inputs (e.g., numeric checks).
- Limit privileges for database users.

---

### **6. Advanced Security Concepts**

#### **Row-Level Security (RLS):**

- Restricts access to individual rows in a table based on policies.
- **Example:**
  ```sql
  ALTER TABLE employee ENABLE ROW LEVEL SECURITY;
  CREATE POLICY employee_policy ON employee
  USING (department_id = current_user_id());
  ```

#### **Materialized Views:**

- Cached query results for faster access.
- Not updated automatically; requires manual refresh.
  ```sql
  CREATE MATERIALIZED VIEW summary AS SELECT ...;
  REFRESH MATERIALIZED VIEW summary;
  ```

---

## ❓ **Questions Raised**

- How can RLS policies impact database performance for large datasets?
- What are best practices for securing dynamic queries in web applications?

---

## 🔗 **Further Reading/Resources**

- [PostgreSQL Documentation on Roles and Privileges](https://www.postgresql.org/docs/current/user-manag.html)
- [OWASP SQL Injection Guide](https://owasp.org/www-community/attacks/SQL_Injection)

---

## 📌 **Summary**

- **Main Takeaways:**
  - SQL DCL is essential for database security management.
  - PostgreSQL offers flexible tools for user, role, and privilege management.
  - Advanced security measures like RLS ensure fine-grained access control.
- **Connection to Previous Content:**
  - Builds upon database design and manipulation by introducing access control mechanisms.

---

## ✅ **Action Items**

- Implement RLS on a sample database and test policies.
- Practice using GRANT and REVOKE commands for role management.
- Review SQL Injection examples and apply countermeasures.

---

### **Lecture Review**

- **What I Learned:**
  - Techniques for managing user roles and privileges securely.
  - Importance of SQL DCL in database operations and security.
- **What Needs Clarification:**
  - Trade-offs between using Views and RLS for access control.
- **My Plan to Review This Material:**
  - Develop a secure database schema with advanced access controls.
