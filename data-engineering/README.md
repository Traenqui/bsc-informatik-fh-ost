# Data Engineering – Course Repository

This repository contains structured summaries and notes for the **Data Engineering** course taught at **OST – Ostschweizer Fachhochschule**, Campus Rapperswil by **Prof. Dr. Stefan Keller** and **Joël Schwab** during the **FS25** semester.

---

## Course Overview

This course covers foundational and advanced database engineering concepts with a strong focus on modern relational databases, distributed data systems, SQL/JSON, indexing, NoSQL models, and data modeling practices.

The emphasis lies on both **relational DBMS features** (e.g., optimization, indexing, stored procedures) and **NoSQL architectures** (e.g., key-value, document, graph, column stores), supplemented by practical use cases and technologies like PostgreSQL, MongoDB, Neo4j, and Cassandra.

---

## Weekly Topics

| Week | Topic                                                    | Summary Link               |
|------|----------------------------------------------------------|----------------------------|
| 01   | Einführung in O/R-Mapping                                | [`Week 01`](./notes/lecture-01.md) |
| 02   | O/R-Mapping: Vererbung, JPQL, Transaktionen              | [`Week 02`](./notes/lecture-02.md) |
| 03   | Stored Procedures, PL/pgSQL & Cursors                    | [`Week 03`](./notes/lecture-03.md) |
| 04   | Stored Procedures & PL/pgSQL (Fortsetzung)               | [`Week 04`](./notes/lecture-04.md) |
| 05   | Triggers, Views, Materialized Views, RLS                 | [`Week 05`](./notes/lecture-05.md) |
| 06   | Arrays, Dictionaries, Graphs, Trees, SQL/JSON            | [`Week 06`](./notes/lecture-06.md) |
| 07   | Optimierung & Indexe (Einführung)                        | [`Week 07`](./notes/lecture-07.md) |
| 08   | Optimierung & Indexe (Fortsetzung)                       | [`Week 08`](./notes/lecture-08.md) |
| 09   | Verteilte Datenbanksysteme & 2-Phase-Commit              | [`Week 09`](./notes/lecture-09.md) |
| 10   | NoSQL I – Key/Value & Document Stores (MongoDB)          | [`Week 10`](./notes/lecture-10.md) |
| 11   | NoSQL II – Graph & Column Family Stores (Neo4j, Cassandra) | [`Week 11`](./notes/lecture-11.md) |

---

## Technologies Covered

- **PostgreSQL** (core RDBMS, PL/pgSQL, triggers, indexing)
- **MongoDB** (Document Store with flexible schema)
- **Neo4j & Cypher** (Graph DBMS and query language)
- **Cassandra** (Column Family Store with CQL)
- **SQL/JSON**, **Arrays**, **hstore**, **Materialized Views**
- **Distributed Transactions**, **2PC**, **Predicate Pushdown**

---

## References & Reading Material

* Elmasri & Navathe – *Fundamentals of Database Systems*
* Kemper & Eickler – *Datenbanksysteme*
* Martin Fowler & Sadalage – *NoSQL Distilled*
* [PostgreSQL Docs](https://www.postgresql.org/docs/current/index.html)
* [MongoDB Manual](https://www.mongodb.com/docs/manual/)
* [Neo4j Cypher Reference](https://neo4j.com/docs/cypher-refcard/current/)
* [Apache Cassandra Docs](https://cassandra.apache.org/doc/)

## 📌 How to Use

- Browse individual weekly summaries for structured lecture content.
- Each `.md` file is self-contained and suitable for review or exam prep.
- Code examples are embedded or referenced for clarity and replication.

---

## 📬 Contributions

This repo reflects **my personal learning journey** through the course. Suggestions and feedback are welcome — feel free to fork or submit pull requests to improve or extend the material.

---

## 📄 License

This work is shared under the **MIT License**. You are free to use, adapt, and share with proper attribution.