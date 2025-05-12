# Data Engineering – Arrays, Dictionaries, Graphs, Trees & SQL/JSON

**Dozenten:** Prof. Stefan Keller & Joël Schwab
**Semester:** FS25
**Ort:** OST Campus Rapperswil

---

## Lernziele

* Verstehen und Anwenden von **Arrays**, **Dictionaries**, **Graphen**, **Bäumen**
* Modellierung und Nutzung semistrukturierter Daten mit **SQL/JSON**
* Kenntnis über **Datenstrukturen in SQL**, insbesondere PostgreSQL

---

## 1. Datentypen und Abstrakte Datentypen (ADT)

### Definitionen

* **Basisdatentypen**: Text, Ganzzahlen, Gleitkommazahlen, Boolean, Datum/Zeit
* **Datensätze (Records)**: Gruppe zusammengehöriger Felder
* **Abstrakter Datentyp (ADT)**:

  * Definiert durch erlaubte Operationen (Konstruktoren, Accessoren, CRUD)
  * Beispiel: Stack als Liste implementiert

### Bestandteile eines ADT

* Konstruktor, Accessor, Update-Funktion, Operatoren, Index

---

## 2. User-Defined Types in PostgreSQL

### Beispiele

```sql
CREATE DOMAIN contact_name AS varchar(255) NOT NULL CHECK (value !~ '\s');
CREATE TYPE easteregg AS (outer text, inner text);
CREATE TYPE traffic_light_t AS ENUM ('red', 'yellow', 'green');
```

---

## 3. Collections

### Definition

* Gruppierung mehrerer Elemente des gleichen oder eines verwandten Typs
* Beispiele: Arrays, Sets, Dictionaries, Graphs, Trees

### Kategorien

* **Lineare**: Listen, Arrays, Priority Queues
* **Assoziative**: Dictionaries, Sets
* **Strukturelle**: Graphs, Trees

---

## 4. Arrays

### Eigenschaften

* Homogene Elemente, feste oder variable Länge
* Nicht relational im Sinne der 1. Normalform
* Alternative: JSON, kommagetrennter Text, separate Tabelle

### Syntaxbeispiele

```sql
CREATE TABLE sal_emp (
  name text,
  pay_by_quarter integer[4],
  schedule text[][]
);

INSERT INTO sal_emp VALUES (
  'Bill',
  ARRAY[10000, 10000, 10000, 10000],
  ARRAY[['meeting', 'lunch'], ['training', 'presentation']]
);
```

### Abfragen

```sql
SELECT board[1][1] FROM tictactoe;
SELECT * FROM tictactoe WHERE 'z2 k2' = ANY(board);
```

### Operatoren

* `@>` enthält
* `<@` ist enthalten
* `&&` Überschneidung

### Funktionen

* `array_to_string()`, `unnest()`, `string_to_array()`, `array_agg()`

---

## 5. Dictionaries

### Begriffe & Modelle

* Auch: Associative Arrays, Maps, Hashes
* In relationalen DBs: **Entity-Attribute-Value (EAV)** Schema

### PostgreSQL: `hstore`

* Key-Value-Speicherung mit Typ `TEXT → TEXT`

```sql
SELECT 'a=>1,b=>2'::hstore -> 'b';  -- Ergebnis: 2
SELECT akeys('k1=>1, k2=>2'::hstore);  -- Ergebnis: {k1, k2}
```

* GIN/GIST Index möglich für schnelle Suche:

```sql
CREATE INDEX kvps_idx ON kvptable_hstore USING GIST (kvps);
```

---

## 6. Graphs (Graphen)

### Grundlagen

* G = (V, E) mit Knoten V und Kanten E
* Directed / Undirected, Cyclic / Acyclic
* Anwendungen: Navigation, Transport, Energie, GIS

### Implementierungen

* PostgreSQL mit `pgRouting` Erweiterung
* Alternativ: Neo4J, GraphHopper, OSMnx

---

## 7. Trees (Bäume)

### Eigenschaften

* Azyklischer Graph, hierarchische Struktur
* Begriffe: Root, Leaf, Internal Node, Level, Height

### Relationale Implementierungen

* **Adjazenzliste**
* **Nested Set Modell**
* **Materialisierter Pfad**
* **Selbstreferenzielle Tabellen**
* **PostgreSQL Extensions**: z. B. `ltree`

### Vergleich

| Kriterium         | Adjazenzliste | Nested Set  | Materialisierter Pfad |
| ----------------- | ------------- | ----------- | --------------------- |
| Nachfolger finden | Ineffizient   | Effizient   | Effizient             |
| Vorgänger finden  | Effizient     | Ineffizient | Effizient             |
| Kinder finden     | Effizient     | Ineffizient | Ineffizient           |

---

## 8. SQL/JSON in PostgreSQL

### JSON-Typen

* `json`: Text-Repräsentation
* `jsonb`: Binär-Repräsentation mit Indexsupport

### Operatoren

```sql
'{"k1":1,"k2":2}'::json ->> 'k2';   -- 2 (Text)
'{"k1":1,"k2":2}'::jsonb ? 'k2';   -- true
'{"k1":1}'::jsonb @> '{"k1":1}';   -- true
```

### Szenarien

* JSON-Feld in relationaler Tabelle
* Transformation relational ↔ JSON
* Aggregation via `json_agg()` und `json_build_object()`

### JSON Path (ab PG 12)

* Neue Möglichkeit zur präzisen Abfrage von JSON-Inhalten
* Syntax ähnlich zu XPath (aber für JSON)

---

## 9. Zusammenfassung

* Arrays, Dictionaries, Graphs, Trees sind zentrale Datenstrukturen auch in SQL
* PostgreSQL bietet starke native Unterstützung für:

  * Arrays mit Konstruktoren, Operatoren, Funktionen
  * Dictionaries über `hstore`
  * Graphen (z. B. via `pgRouting`)
  * Bäume mit mehreren relationalen Strategien
  * JSON / JSONB mit umfangreichen Operatoren und Indexen
