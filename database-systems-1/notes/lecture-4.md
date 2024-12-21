# 📚 **Lecture Notes**

---

## 🗓️ **Course Details**

- **Course Title:** Datenbanksysteme 1
- **Lecture Title:** Relationale Algebra and Normalisierung
- **Lecturers:** S. Keller & J. Schwab
- **Date:** HS 2024/25
- **Lecture Numbers:** Chapter 3, Week 4

---

## 📝 **Key Topics Covered**

1. Relational Algebra
   - Operations: Projection, Selection, Join, Cartesian Product, Set Operations
2. Relational Model Foundations
3. Functional Dependencies and Normal Forms
   - 1NF, 2NF, 3NF, BCNF
4. Redundancy, Anomalies, and Denormalization
5. Case Studies in Relational Schema Design

---

## 🧠 **Learning Objectives**

- Understand the mathematical foundation of the relational model.
- Master relational algebra operations and their implementation in SQL.
- Recognize and address data redundancy through normalization.
- Learn to detect anomalies and apply advanced normalization forms.
- Explore trade-offs between normalization and denormalization.

---

## 📖 **Detailed Notes**

### **1. Relational Algebra**

#### **Overview**

- **Purpose:** Defines operations that manipulate relations (tables).
- **Key Properties:**
  - **Closure:** Result of any operation is always a relation.
  - **Operations:**
    - Unary: Selection (σ), Projection (π)
    - Binary: Cartesian Product (×), Join (⋈), Set Operations (∪, ∩, −)

#### **Key Operations**

1. **Projection (π):**

   - Selects specific columns from a relation.
   - **Example SQL:**
     ```sql
     SELECT A1, A4 FROM Ausgangstabelle;
     ```

2. **Selection (σ):**

   - Filters rows based on a condition.
   - **Example SQL:**
     ```sql
     SELECT * FROM Tabelle WHERE A1 > 30;
     ```

3. **Cartesian Product (×):**

   - Combines every row of two relations.
   - **Example SQL:**
     ```sql
     SELECT * FROM R1, R2;
     ```

4. **Join Operations (⋈):**

   - Combines relations based on matching attributes.
   - Types: Theta Join, Equi-Join, Natural Join, Outer Join.
   - **Example SQL:**
     ```sql
     SELECT * FROM R NATURAL JOIN S;
     ```

5. **Set Operations:**
   - **Union (∪):**
     Combines rows from two relations.
     ```sql
     SELECT * FROM R1 UNION SELECT * FROM R2;
     ```
   - **Intersection (∩):**
     Returns common rows.
     ```sql
     SELECT * FROM R1 INTERSECT SELECT * FROM R2;
     ```
   - **Difference (−):**
     Returns rows in R1 not in R2.
     ```sql
     SELECT * FROM R1 EXCEPT SELECT * FROM R2;
     ```

---

### **2. Normalization**

#### **Purpose:**

- Ensure data integrity by eliminating redundancy and anomalies.
- Use Normal Forms (NF) to systematically refine database design.

#### **Normal Forms Overview**

1. **1NF:**

   - All attributes must have atomic (indivisible) values.
   - **Violation Example:** Lists or sets as column values.
   - **Solution:** Split multi-valued attributes into separate rows.

2. **2NF:**

   - Satisfies 1NF, and every non-key attribute is fully functionally dependent on the primary key.
   - **Violation Example:** Partial dependency in composite keys.
   - **Solution:** Split tables into smaller ones.

3. **3NF:**

   - Satisfies 2NF, and no transitive dependencies exist.
   - **Violation Example:** Non-key attribute dependent on another non-key attribute.
   - **Solution:** Create separate tables for transitively dependent attributes.

4. **BCNF (Boyce-Codd):**
   - Extends 3NF to address overlapping composite keys.
   - **Violation Example:** Functional dependency where determinant is not a superkey.

---

### **3. Anomalies and Denormalization**

- **Anomalies:**
  - **Insert:** Cannot add data without related existing data.
  - **Delete:** Removing data can unintentionally delete related information.
  - **Update:** Redundant data changes inconsistently.
- **Denormalization:**
  - Introduces redundancy for performance gains.
  - Example: Combining customer and order data in a single table for faster queries.

---

### **4. Case Study: "Projekt-Zuteilung"**

#### **From 1NF to 3NF**

- **Initial Schema (1NF):**

  ```sql
  PERSNR | NAME   | WOHNORT | PROJNR | ProAnteil | PLNr | PLName
  ```

- **2NF:**

  - Split attributes depending on subsets of composite keys:
    ```sql
    PERSNR | NAME   | WOHNORT
    PROJNR | PLNr   | PLName
    PERSNR | PROJNR | ProAnteil
    ```

- **3NF:**
  - Remove transitive dependencies:
    ```sql
    PROJNR | PLNr
    PLNr   | PLName
    ```

---

## ❓ **Questions Raised**

- How to balance normalization for data integrity and denormalization for performance?
- When is BCNF overkill in real-world scenarios?

---

## 🔗 **Further Reading/Resources**

- [Relational Algebra Overview](https://en.wikipedia.org/wiki/Relational_algebra)
- [Database Normalization Basics](https://www.essentialsql.com/what-is-database-normalization/)

---

## 📌 **Summary**

- **Main Takeaways:**
  - Relational algebra operations form the basis of SQL queries.
  - Normalization ensures clean database design but has performance trade-offs.
  - Advanced forms like BCNF are situationally applied in complex databases.
- **Connection to Previous Content:**
  - Builds on UML and relational schema transformation, adding mathematical rigor.

---

## ✅ **Action Items**

- Practice relational algebra queries using SQL.
- Design and normalize a mock database to 3NF.
- Explore denormalization scenarios for performance improvement.

---

### **Lecture Review**

- **What I Learned:**
  - Practical techniques for relational algebra and normalization.
  - Theoretical underpinnings of database anomalies.
- **What Needs Clarification:**
  - Optimization strategies when denormalization is necessary.
- **My Plan to Review This Material:**
  - Develop relational algebra exercises and test on sample databases.
  - Research case studies of denormalized schemas in production.
