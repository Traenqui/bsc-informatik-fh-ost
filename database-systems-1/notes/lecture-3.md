# 📚 **Lecture Notes**

---

## 🗓️ **Course Details**

- **Course Title:** Datenbanksysteme 1
- **Lecture Title:** Logischer Datenbank-Entwurf: Abbildung vom UML-Klassendiagramm zur relationalen Schreibweise
- **Lecturers:** S. Keller & J. Schwab
- **Date:** HS 2024/25
- **Lecture Number:** Week 3, Chapter 3

---

## 📝 **Key Topics Covered**

1. The Database Design Process
2. Transformation from Conceptual to Relational Models
3. Mapping Rules:
   - Classes and Attributes
   - Associations
   - Inheritance and Specializations
4. Relational Notation and Practical Examples
5. Case Study: "Angestellter-Abteilung-Projekt"

---

## 🧠 **Learning Objectives**

- Understand how to transform a UML Class Diagram (conceptual model) into a relational database schema (logical model).
- Learn and apply mapping rules for different scenarios, such as associations, aggregations, and inheritance.
- Understand the relational notation format for describing database schemas.
- Explore normalization as a consistency check for logical models.

---

## 📖 **Detailed Notes**

### **1. Introduction: Database Design Process**

- **Phases:**
  - **Conceptual Design:** UML Class Diagrams or Entity-Relationship Models to capture domain-specific requirements.
  - **Logical Design:** Convert conceptual models into a relational schema.
  - **Physical Design:** Tailor the schema for a specific DBMS, including indexes and storage optimizations.

### **2. Relational Notation**

- **Format:**
  - TableName (AttributeName [DataType] [PK/FK] [Constraints])
  - **Example:**
    ```sql
    Student (
        id INTEGER PK,
        name TEXT NOT NULL,
        dept INT REFERENCES Department(id)
    )
    ```
- **Key Elements:**
  - **Primary Keys:** Underlined.
  - **Foreign Keys:** Italicized or marked with `REFERENCES`.

---

### **3. Mapping Rules**

#### **Rule 1: Mapping Classes**

- Each UML Class maps to a table.
- Attributes map to table columns.
- **Primary Key:** Chosen from existing attributes or introduced as a surrogate key.
- **Example:**
  - UML: `Student { Name, Wohnort }`
  - Relational Schema:
    ```sql
    Student (
        StudId INT PK,
        Name TEXT NOT NULL,
        Wohnort TEXT NOT NULL
    )
    ```

#### **Rule 2: Mapping Associations**

1. **One-to-Many:**

   - Add a foreign key to the "many" side referencing the "one" side.
   - **Example:**
     - UML: `Student 1..* belongsTo 1 Department`
     - Relational Schema:
       ```sql
       Department (
           DeptId INT PK,
           Name TEXT NOT NULL
       )
       Student (
           StudId INT PK,
           Name TEXT NOT NULL,
           DeptId INT REFERENCES Department(DeptId)
       )
       ```

2. **Optional Associations:**

   - Use nullable foreign keys or a separate linking table.
   - **Example with nullable FK:**
     ```sql
     Book (
         BookId INT PK,
         Title TEXT NOT NULL,
         Borrower INT NULL REFERENCES Person(PId)
     )
     ```

3. **Many-to-Many:**
   - Introduce a linking table with composite keys.
   - **Example:**
     ```sql
     Enrollment (
         StudentId INT REFERENCES Student(StudId),
         CourseId INT REFERENCES Course(CourseId),
         PRIMARY KEY (StudentId, CourseId)
     )
     ```

#### **Rule 3: Mapping Inheritance**

1. **Separate Tables for Subclasses and Superclasses:**

   - Each subclass and superclass gets a table.
   - **Example:**
     ```sql
     Vehicle (
         VehicleId INT PK,
         Type TEXT
     )
     Car (
         VehicleId INT PK REFERENCES Vehicle(VehicleId),
         NumSeats INT NOT NULL
     )
     ```

2. **Single Table for All Classes:**
   - Use a discriminator column to differentiate subtypes.
   - **Example:**
     ```sql
     Vehicle (
         VehicleId INT PK,
         Type TEXT NOT NULL,
         NumSeats INT NULL,
         LoadCapacity INT NULL
     )
     ```

---

### **4. Practical Example: "Angestellter-Abteilung-Projekt"**

- **Schema Design:**
  - Tables:
    ```sql
    Employee (
        EmpId INT PK,
        Name TEXT NOT NULL,
        DeptId INT REFERENCES Department(DeptId),
        Salary DECIMAL NOT NULL
    )
    Department (
        DeptId INT PK,
        Name TEXT NOT NULL UNIQUE
    )
    Project (
        ProjId INT PK,
        Title TEXT NOT NULL
    )
    Assignment (
        EmpId INT REFERENCES Employee(EmpId),
        ProjId INT REFERENCES Project(ProjId),
        Hours INT
    )
    ```
- **Key Relations:**
  - One-to-Many: Department and Employee.
  - Many-to-Many: Employee and Project via `Assignment`.

---

## ❓ **Questions Raised**

- How do composite keys affect performance in large-scale systems?
- What is the best strategy for mapping complex inheritance hierarchies in practice?

---

## 🔗 **Further Reading/Resources**

- [Relational Model Overview](https://en.wikipedia.org/wiki/Relational_model)
- [SQL Guide for Beginners](https://www.sqltutorial.org/)

---

## 📌 **Summary**

- **Main Takeaways:**
  - The transition from UML to relational models follows well-defined mapping rules.
  - Associative tables resolve many-to-many relationships elegantly.
  - Choosing the right inheritance mapping strategy depends on the use case.
- **Connection to Previous Content:**
  - Builds on data modeling basics, diving into practical schema transformation.

---

## ✅ **Action Items**

- Practice transforming UML diagrams into SQL schemas.
- Explore tools like PostgreSQL to test relational schema designs.
- Investigate advanced normalization techniques.

---

### **Lecture Review**

- **What I Learned:**
  - Step-by-step mapping from conceptual to relational models.
  - Practical handling of inheritance and associations.
- **What Needs Clarification:**
  - Balancing normalization and performance in real-world systems.
- **My Plan to Review This Material:**
  - Design and implement a database schema for a mock organization.
  - Experiment with different inheritance mapping strategies.
