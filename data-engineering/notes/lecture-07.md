# Data Engineering – Interne Ebene: Optimierung und Indexe (Einführung)

**Dozenten:** Prof. Stefan Keller & Joël Schwab
**Semester:** FS25
**Ort:** OST Campus Rapperswil

---

## Lernziele

* Verständnis verschiedener **Query-Typen**
* Kenntnis der **Indexstrukturen** und deren Einsatzgebiete
* Überblick über den **PostgreSQL Query Planner**
* Grundlagen zur **Interpretation von EXPLAIN-Ausgabe**

---

## 1. Query-Arten

* **Equality Query**: Verwendung des `=` Operators; liefert oft ein einzelnes, aber evtl. auch mehrere Tupel.
* **Range Query**: Nutzung von `>`, `<`, `<=`, `>=`, `!=`, `BETWEEN`; liefert mehrere Tupel.
* **Point Query**: Genau ein Wert/Tupel wird mit `=` gesucht.
* **Join Query**: Abfragen mit `JOIN`.
* **Spezialfälle**: Präfix/Suffix-Suchen, Extremwertabfragen.

---

## 2. Index: Grundidee und Nutzen

* **Definition**: Separates Datenstruktur-Objekt zur Beschleunigung von Zugriffen.
* **Nutzen**: Schnellere Reads, speziell bei grossen Tabellen.
* **Kosten**: Mehr Speicherverbrauch, höhere Kosten bei Schreiboperationen.

---

## 3. Speichermedien

| Medium          | Zugriff     | Beispiel              | Zugriffsdauer |
| --------------- | ----------- | --------------------- | ------------- |
| Primärspeicher  | random      | RAM                   | 10–100 ns     |
| SSD             | random      | Solid State Drive     | >1 ms         |
| HDD             | random      | rotierende Festplatte | >10 ms        |
| Tertiärspeicher | sequentiell | Band, CD              | Sekunden      |

---

## 4. Datenorganisation

* **Page**: Kleinste Speicher-IO-Einheit (unsortierte Zeilen)
* **Heap**: Sammlung von Pages
* **Table Scan**: Vollständiges Scannen der Tabelle (langsam, aber bei grossen Resultsets effizienter als Index)
* **Indexziel**: Mapping von Werten auf Zeilen zur Beschleunigung

---

## 5. Arten von Indexstrukturen

* **B-Baum** / **B+-Baum**
* **Hash Index**
* **Bitmap Index**
* **Mehrdimensionale Indexe** (z. B. R-Tree)
* **PostgreSQL-spezifische Varianten**: GIST, SP-GIST, BRIN

---

## 6. Index-Definition und Verwaltung

```sql
CREATE INDEX <name> ON <table(column)> USING btree;
DROP INDEX <name>;
```

PostgreSQL nutzt standardmässig `btree`, `ASC`, `NULLS FIRST`.

---

## 7. Wichtige Indexbegriffe

| Begriff                  | Beschreibung                                              |
| ------------------------ | --------------------------------------------------------- |
| Primärindex              | Index auf dem Primärschlüssel (unique, not null)          |
| Clustered Index          | Daten physisch sortiert nach Index; nur einer pro Tabelle |
| Daten-integrierter Index | Enthält Daten direkt im Indexblatt                        |

---

## 8. B-Baum und B+-Baum

* B-Baum: Mehrweg-Baum, balanciert
* B+-Baum: Daten nur in Blättern, Blätter sind verkettet → effizient für Range-Queries

---

## 9. Hash Index

* Key-Value-Mapping über Hash-Funktion
* Vorteil: Schnelle Point Queries
* Nachteil: Unbrauchbar für Range Queries, aufwendig bei Überläufen

---

## 10. Bitmap Index

* Mapping diskreter Werte auf Bitmuster
* Ideal bei **niedriger Kardinalität** (z. B. Geschlecht)
* Schnell bei Kombinationen (AND/OR)
* Langsam bei Updates
* PostgreSQL erstellt interne **ad-hoc Bitmap Indexe** zur Optimierung

---

## 11. Weitere Indexvarianten

* **Mehrdimensionale Indexe**: z. B. R-Tree für GIS
* **Mehrstufige Indexe**: Grob- und Feinfilterung über zwei Stufen
* **Zusammengesetzter Index**: mehrere Spalten in einem Index
* **Index mit INCLUDE**: zusätzliche Spalten, nur zum Mitlesen
* **Partieller Index**: Index über Teilmenge der Tabelle (`WHERE`)
* **Funktionaler Index**: Index auf Ausdruck/Funktion (`LOWER(name)`)

---

## 12. Query-Planner in PostgreSQL

* Ziel: Wahl des **optimalen Ausführungsplans**
* Eingaben: SQL-Query, Statistiken aus Katalog
* PostgreSQL generiert Varianten und wählt Plan mit geringsten **geschätzten Kosten**

### Phasen

1. SQL → AST
2. AST → Pläne
3. Plan mit minimalen Kosten wird gewählt

---

## 13. Scan-Typen

| Typ              | Beschreibung                                               |
| ---------------- | ---------------------------------------------------------- |
| Seq Scan         | kompletter Tabellenscan                                    |
| Index Scan       | Index → Heap (random access)                               |
| Index Only Scan  | Nur Indexzugriff (bei vollständiger Information im Index)  |
| Bitmap Heap Scan | Kombination aus Bitmap-Erzeugung + selektivem Heap-Zugriff |

---

## 14. Join-Strategien

| Typ         | Beschreibung                                         |
| ----------- | ---------------------------------------------------- |
| Nested Loop | Einfach, gut für kleine Tabellen                     |
| Merge Join  | Sortiert beide Tabellen, dann „zippt“                |
| Hash Join   | Erst Hash-Tabelle, dann Lookup; nur für `=` geeignet |

---

## 15. EXPLAIN & EXPLAIN ANALYZE

```sql
EXPLAIN ANALYZE
SELECT * FROM angestellter WHERE abtnr = 2;
```

* `EXPLAIN`: zeigt geschätzte Kosten, aber keine Ausführung
* `EXPLAIN ANALYZE`: führt aus + misst reale Zeit
* Ausgabe:

  * `cost=start..end`: geschätzte Ausführungskosten
  * `rows`: erwartete Anzahl Tupel
  * `width`: erwartete Tupelbreite in Bytes
  * `Execution Time`: gemessene Laufzeit

---

## 16. Herausforderungen des Planners

* **Kombinatorische Explosion** bei Joins (z. B. 4 Tabellen → 15 Varianten)
* **Ungenaue Statistiken** führen zu schlechten Plänen
* Abhilfe: Manuelle Statistiken mit:

```sql
CREATE STATISTICS stat_name (ndistinct) ON col1, col2 FROM tabelle;
```

---

## Zusammenfassung

* Verschiedene Query-Typen beeinflussen Indexwahl
* Indexarten: B-Tree, Hash, Bitmap, Funktional, Partiell, etc.
* PostgreSQL-Planner wählt besten Plan basierend auf Statistiken
* `EXPLAIN` erlaubt tiefen Einblick in Ausführungsstrategien
