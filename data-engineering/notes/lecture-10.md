# Data Engineering – NoSQL: Key/Value & Document Stores

**Dozenten:** Prof. Stefan Keller & Joël Schwab
**Semester:** FS25
**Ort:** OST Campus Rapperswil

---

## Lernziele

* Einführung in NoSQL und die Motivation dahinter
* Theoretische Konzepte: CAP- und BASE-Theorem
* Verständnis für Key-Value Stores und Document Stores
* Einführung in MongoDB inkl. Modellierung, Queries und Transaktionen

---

## 1. NoSQL – Einführung

### Entstehung

* Web-2.0-Anwendungen (2000er Jahre): große Datenmengen, hohe Verfügbarkeit, horizontale Skalierung
* Problem: RDBMS = schwer skalierbar, Single Point of Failure

### Begriffsdefinition

* "NoSQL" = „Not only SQL“
* Merkmale:

  * Schemafrei, einfache APIs (REST/HTTP)
  * Optimiert für Skalierung, Verfügbarkeit
  * Häufig eventual consistency statt ACID
  * Cloud-/Cluster-orientiert, meist Open Source

---

## 2. NoSQL Kategorien

| Kategorie          | Beschreibung                            |
| ------------------ | --------------------------------------- |
| Key/Value Stores   | Hashmap-Struktur, sehr performant       |
| Document Stores    | Hierarchische JSON/BSON-Dokumente       |
| Graph Stores       | Knoten + Kanten mit Beziehungen         |
| Wide Column Stores | Tabellen mit flexiblen Spalten je Zeile |

---

## 3. Theorie: CAP & BASE

### CAP-Theorem (Eric Brewer, 2000)

* **C**onsistency: alle Replikate identisch
* **A**vailability: jede Anfrage bekommt Antwort
* **P**artition Tolerance: System funktioniert trotz Netzwerkproblemen

→ "Pick two":

* RDBMS: C + P
* NoSQL: A + P

### BASE-Modell

* **Basically Available**
* **Soft-State**
* **Eventually Consistent**

---

## 4. Key-Value Stores

### Eigenschaften

* Einfaches Modell: Key → Value (z. B. Strings, JSON, BLOBs)
* Beispiel: Redis, DynamoDB, PostgreSQL `hstore`

### Operationen

* Get/Put/Delete via Schlüssel
* Volltextsuche z. B. mit `kv -> 'key'` oder `kv @> 'key=>value'`

### Beispiele

* Redis (in-memory), Riak, Memcached, Project Voldemort

### Einsatzgebiete

* Caching, Sitzungsdaten, Benutzerprofile, Shopping Carts

### Einschränkungen

* Keine Joins, keine Multi-Key-Transaktionen
* Nicht geeignet bei stark verknüpften Daten

---

## 5. Document Stores

### Merkmale

* Speicherung strukturierter Daten (JSON/BSON)
* Flexibles, schemafreies Modell
* Beispiel: MongoDB, CouchDB

### Datenmodell in MongoDB

```json
{
  _id: ObjectId("..."),
  course: {code: "Dbs2", title: "Advanced DB"},
  students: ["Peter", "Manuel"],
  year: 2016
}
```

* Dokumente enthalten Arrays, Subdokumente etc.
* `_id` = Primärschlüssel (oft automatisch generiert via ObjectId)

---

## 6. MongoDB Grundlagen

| RDBMS       | MongoDB    |
| ----------- | ---------- |
| Table       | Collection |
| Row         | Document   |
| Column      | Field      |
| Primary Key | `_id`      |

### CRUD

* `db.collection.insert({...})`
* `db.collection.find({...})`
* `db.collection.update({...})`
* `db.collection.remove({...})`

---

## 7. MongoDB Abfragen & Joins

* Eigene Sprache (MQL), JSON-basiert

```js
db.orders.find({"customerId":"123"}, {orderId:1, orderDate:1})
```

* Joins via `$lookup` ab MongoDB 3.2:

```js
db.orders.aggregate([
  { $lookup: {
      from: "products",
      localField: "productId",
      foreignField: "_id",
      as: "productInfo"
  }}
])
```

---

## 8. Modellierung in MongoDB

### Embedding vs. Referencing

| Embedding                         | Referencing                     |
| --------------------------------- | ------------------------------- |
| One-to-One, One-to-Few            | Many-to-Many, große Hierarchien |
| Schnell beim Lesen                | Speicher- & Performance-sparend |
| Gefahr unkontrollierten Wachstums | Erfordert zusätzliche Abfragen  |

### Beispiel: Embedded

```json
{
  author: "Max",
  comments: ["OK", "Gut", "Mehr Details"]
}
```

### Beispiel: Referenced

```json
{
  _id: "Dbs2",
  coordinator: ObjectId("..."),
  guest_lecturer: ObjectId("...")
}
```

---

## 9. Indexe & Aggregation

### Indexe

* Automatisch auf `_id`
* Weitere Indexe mit `createIndex()`
* BTree-Struktur
* Negative Performance-Auswirkungen bei Schreiblast

### Aggregation

* Aggregation Pipeline (`$match`, `$group`, `$project`, `$sort`, …)

```js
db.orders.aggregate([
  { $match: { status: "shipped" } },
  { $group: { _id: "$customer", total: { $sum: "$amount" } } }
])
```

---

## 10. Schreib- & Lesekonzepte

### Write Concern

* `w: "majority"` → Schreiben gilt erst bei Mehrheit der Replikate

### Read Concern

* `local`, `majority`, `linearizable`
* Kombination aus Write/Read Concern definiert Konsistenzverhalten

---

## 11. Vor- und Nachteile von MongoDB

### Vorteile

* Schnell bei prototyping, JSON-freundlich
* Flexible Modellierung
* Sharding & Replikation für Skalierung
* Web-freundlich (REST APIs)

### Nachteile

* Keine echten Joins, begrenzte Transaktionen
* Schema-Validation muss durch Applikation erfolgen
* Default-Setup oft unsicher

---

## 12. Zusammenfassung

* NoSQL ist eine Reaktion auf moderne Anforderungen an Skalierung und Verfügbarkeit
* CAP & BASE liefern Theorierahmen
* Key/Value Stores = einfaches Modell (Redis etc.)
* Document Stores = flexible JSON-Daten (MongoDB)
* MongoDB: reichhaltige Features, aber vorsichtig bei Modellierungs- und Sicherheitsfragen
