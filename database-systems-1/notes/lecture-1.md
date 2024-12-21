# 📚 **Lecture Notes**

---

## 🗓️ **Course Details**

- **Course Title:** Datenbanksysteme 1
- **Lecture Title:** Einführung and UML-Klassendiagramme
- **Lecturers:** S. Keller & J. Schwab
- **Date:** HS 2024/25
- **Lecture Number:** Week 1, Chapter 1

---

## 📝 **Key Topics Covered**

1. Introduction to Databases and Database Systems
2. UML Class Diagrams
3. Database Models and Paradigms
4. Functions and Architectures of DBMS
5. Examples and Practical Applications of Databases

---

## 🧠 **Learning Objectives**

- Understand foundational database concepts and terminology.
- Explore different database models and their use cases.
- Learn the basic notation and purpose of UML Class Diagrams.
- Recognize the role and functions of a Database Management System (DBMS).
- Familiarize yourself with database user categories and system architectures.

---

## 📖 **Detailed Notes**

### **1. Introduction to Databases**

- **Key Points:**
  - Databases are integral to applications, enabling data storage, management, and retrieval.
  - Importance of databases in organizing the information deluge in modern contexts (Data Science, Digitalization).
  - Examples include contact lists, banking systems, and ticket bookings.
- **Core Concepts:**
  - **Information:** Data interpreted by users (e.g., strategic business data).
  - **Data:** Machine-readable but non-interpretive without context; includes formatted (e.g., tables) and unformatted (e.g., text).

---

### **2. Database Models and Paradigms**

- **Key Models:**
  1. **Hierarchical:** Organizes data in a tree-like structure; limited by inflexible schema.
  2. **Network:** Allows multiple parent-child relationships; foundational for graph databases.
  3. **Relational:** Stores data in tables; high flexibility and market dominance.
  4. **Object-relational:** Extends relational models with OO features like inheritance.
  5. **NoSQL/NewSQL:** Handles diverse formats like JSON or key-value pairs.
- **Practical Example:** JSON and XML for hierarchical data, Graph databases for network models.

---

### **3. UML Class Diagrams**

- **Purpose:** Visual representation of system structure, focusing on class attributes and their relationships.
- **Key Elements:**
  - **Classes:** Represent entities with attributes (e.g., `Angestellter` with `Name`).
  - **Associations:** Define relationships between classes (e.g., `Angestellter` works on `Projekt`).
  - **Multiplicity:** Indicates the cardinality of relationships (e.g., `1..*` for one-to-many).
  - **Special Cases:**
    - **Composition:** Strong dependency (e.g., `Gebäude` and `Raum`).
    - **Inheritance:** `is-a` relationships (e.g., `Angestellter` is a `Person`).

---

### **4. Functions of a DBMS**

- **Core Responsibilities:**
  - **Data Persistence:** Centralized data storage independent of applications.
  - **Data Consistency:** Enforced through data types and constraints.
  - **Transactions:** All-or-nothing operations ensure reliability.
  - **Multi-user Access:** Simultaneous, synchronized data access.
  - **Security:** Role-based access control and backup mechanisms.
- **Architectural Models:**
  - Client-server systems with middleware facilitating access.

---

### **5. Examples of Database Use**

- **Real-world Applications:**
  - Healthcare systems (e.g., patient records).
  - E-commerce (e.g., product inventories, order management).
  - Social media platforms (e.g., user profiles, messaging).

---

## ❓ **Questions Raised**

- How does UML adapt to more complex relationships in real-world applications?
- What considerations are necessary when selecting between NoSQL and relational databases for a project?

---

## 🔗 **Further Reading/Resources**

- [UML Class Diagram Tutorials](https://uml-diagrams.org/)
- [Relational Database Design Principles](https://en.wikipedia.org/wiki/Relational_model)

---

## 📌 **Summary**

- **Main Takeaways:**
  - Databases are foundational for managing large, structured datasets.
  - UML Class Diagrams help model system structures for both software and domain concepts.
  - Understanding database models ensures appropriate system design choices.
- **Connection to Previous Content:** Builds foundational understanding for advanced database design techniques and query optimizations.

---

## ✅ **Action Items**

- Review UML Class Diagram notations and practice modeling simple systems.
- Compare different database paradigms for suitability in specific applications.
- Explore DBMS tools such as MySQL, Oracle, and MongoDB for practical insights.

---

### **Lecture Review**

- **What I Learned:**
  - The versatility and limitations of various database models.
  - How UML diagrams facilitate communication among stakeholders.
- **What Needs Clarification:**
  - Handling dynamic schema changes in NoSQL systems.
- **My Plan to Review This Material:**
  - Implement a sample UML diagram for a mock employee-project system.
  - Research practical case studies for each database model.
