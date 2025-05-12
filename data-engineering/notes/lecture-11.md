# Data Engineering – NoSQL: Graph & Column Family Stores

**Dozenten:** Prof. Stefan Keller & Joël Schwab
**Semester:** FS25
**Ort:** OST Campus Rapperswil

---

## Lernziele

* Verständnis von **Graph-Datenbanken** und **Triple Stores**
* Anwendung der Graph-Querysprache **Cypher**
* Architektur und Modellierung mit **Column Family Stores**
* Überblick über NoSQL-Systeme wie **Neo4j** und **Cassandra**

---

## Teil 1 – Graph Stores / Databases

### Was ist ein Graph?

* Strukturen bestehend aus **Knoten (Nodes)** und **Kanten (Edges)**
* Darstellung von Beziehungen in sozialen Netzwerken, Empfehlungen, Routen etc.

### Zwei Hauptmodelle:

1. **Labeled Property Graphs (LPG)**

   * Knoten & Kanten mit Typ (Label) und Eigenschaften (Properties)
   * Navigierbare Beziehungen
   * Abfragesprache: **Cypher**, SQL/PGQ

2. **RDF Triples (Resource Description Framework)**

   * Subjekt – Prädikat – Objekt
   * Standard im **Semantic Web**
   * Abfragesprache: **SPARQL**

### Beispiel: RDF Triples

```turtle
_:markus ex:vorname "Markus".
_:vreni ex:chef _:markus.
```

oder mit URIs:

```turtle
<http://example.org/Vreni> <http://example.org/chef> <http://example.org/Markus> .
```

---

## Neo4j & Cypher

### Eigenschaften von Neo4j

* Java-basiert, Open Source
* Disk-basiert mit Memory-Mapping
* Transaktionen via MVCC
* Skaliert auf Milliarden Knoten

### Graph erzeugen (Cypher)

```cypher
CREATE (alice:User {username:'Alice'}),
       (bob:User {username:'Bob'}),
       (alice)-[:ALIAS_OF]->(bob)
```

### Abfragen mit Cypher

```cypher
MATCH (u:User) WHERE u.name = "Bob" RETURN u
```

```cypher
MATCH (email:Email {id:'6'})
<-[:REPLY_TO*1..4]-(:Reply)<-[:SENT]-(replier)
RETURN replier.username, length(p)-1 AS depth
```

### Eigenschaften von Cypher

* Deklarativ
* Orientiert sich an SQL + SPARQL + JSONPath
* JOINs durch Pfadmuster

---

## Wann Graph Stores verwenden?

**Geeignet für:**

* Netzwerkbeziehungen (Social Graphs, Transport, Empfehlungssysteme)
* Wissensgraphen & semantische Netze
* Analyse tiefer Pfade in Datenstrukturen

**Nicht geeignet für:**

* Flache, tabellarische Daten
* Häufige Komplettabfragen
* Komplexe Aggregationen ohne Pfadbezug

---

## Probleme mit RDF

* Hoher Modellierungsaufwand (Tripel statt Objektmodell)
* Schwache Validierung (z. B. SHACL nicht vollständig integriert)
* Kaum Verbreitung (Marktnische < 0.5%)
* RDF-Star & Quads = Workarounds mit Mehr-Komplexität

---

## Teil 2 – Column Family Stores

### Grundlagen

* Auch "Wide Column Stores"
* Inspiriert von Google BigTable
* Speicherung in **Keyspace → Column Families → Rows**
* Row enthält gruppierte Key-Value-Paare

### Architektur

* Keyspace = logische Datenbank
* Node → Data Center → Cluster
* Partitionierung & Replikation über Hashring

### Produkte

| System           | Eigenschaften                        |
| ---------------- | ------------------------------------ |
| Apache Cassandra | Master-less, CQL, hohe Verfügbarkeit |
| Azure Cosmos DB  | Multi-API (Mongo, SQL, Cassandra)    |
| Apache HBase     | HDFS-basiert, stark konsistent       |
| ScyllaDB         | Cassandra-kompatibel, C++-basiert    |

---

## Cassandra – Datenmodell

```json
{
  "pramod-sadalage": {
    "2021-01-01": { "firstName": "Pramod", "lastName": "Sadalage" },
    "2023-06-30": { "location": "Pune" }
  }
}
```

* **Primary Key** = Partition Key + Clustering Key
* **Clustering Key**: Sortierung innerhalb der Partition
* Datenmodell ist **Query-Driven**, nicht normalisiert

---

## Cassandra Query Language (CQL)

```sql
CREATE TABLE Customer (
  id varchar PRIMARY KEY,
  name varchar,
  city varchar,
  web varchar
);

INSERT INTO Customer (id, name, city, web) VALUES
('mfowler', 'Martin Fowler', 'Boston', '...');

SELECT * FROM Customer;
```

### Indexing

```sql
CREATE INDEX ON Customer(city);
```

---

## Anwendungsfälle

* **Event Logging** (z. B. Metriken, Fehler)
* **CMS/Blogsysteme** mit Tags und Kommentaren
* **Web-Analytics** und Benutzertracking

### Einschränkungen

* Keine komplexen Aggregationen
* Keine ACID-Transaktionen über mehrere Zeilen
* Schema-Änderungen bevorzugt gegenüber Query-Anpassungen

---

## Zusammenfassung

* **Graph Stores** (Neo4j, Cypher) für stark vernetzte, relationale Daten
* **Column Family Stores** (Cassandra) für skalierbare, zeilenorientierte Key-Value-Daten
* Beide Systeme verfolgen **Query-Driven Design** statt relationaler Normalisierung
* Moderne Datenbanken kombinieren oft mehrere Modelle (Multi-Model DBMS)

---

## Weiterführende Literatur

* [Graph Databases Book (O'Reilly)](https://neo4j.com/graph-databases-book/)
* Sadalage & Fowler: *NoSQL Distilled*
* [https://db-engines.com/de/ranking](https://db-engines.com/de/ranking)
* [Neo4j Cypher Cheatsheet](https://neo4j.com/docs/cypher-cheat-sheet/)
