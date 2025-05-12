# Data Engineering – Interne Ebene: Optimierung und Indexe (Fortsetzung)

**Dozenten:** Prof. Stefan Keller & Joël Schwab
**Semester:** FS25
**Ort:** OST Campus Rapperswil

---

## Lernziele

* Vertiefung der PostgreSQL-Indexstrukturen
* Verständnis von Join-Strategien
* Erkennen und Analysieren von Abfragekosten
* Anwendung von Statistiken und Selektivität in der Abfrageoptimierung
* Praktische Tipps zur Indexwahl und Tuning

---

## 1. Indexe in PostgreSQL

### Überblick der Indextypen

| Typ     | Beschreibung                                                             | Verwendung                   |
| ------- | ------------------------------------------------------------------------ | ---------------------------- |
| B-tree  | Standardtyp, universell einsetzbar (Vergleiche, LIKE, etc.)              | Default                      |
| Hash    | Nur für `=`-Vergleiche                                                   | Schnell bei Punktabfragen    |
| GiST    | Generalized Search Tree, für komplexe Datentypen (z. B. Text, Geometrie) | Textsuche, Overlap           |
| SP-GiST | Space-partitioned GiST, unterstützt k-d-Bäume, Quadtrees                 | Präfixsuche, CIDR            |
| GIN     | Generalized Inverted Index, ideal für Arrays, JSONB, hstore              | Dokumentartige Strukturen    |
| BRIN    | Block Range Index, speichert Min/Max je Block                            | Zeitliche Daten, sequentiell |
| Weitere | RUM (verbesserter GIN), Trigram, Bloom, pgvector                         | Spezifische Einsätze         |

---

## 2. Join-Strategien

* **Hash Join**: Hashtabelle auf kleinerer Tabelle, dann Lookup
* **Nested Loop Join**: Für kleine Tabellen und selektive Bedingungen
* **Merge Join**: Beide Tabellen sortiert → "zippen"

---

## 3. Abfrageoptimierung

### Ziel

* Reduktion der Gesamtkosten: Seitenzugriffe, CPU, Speicher

### Phasen

1. **Übersetzung**: Erstellung interner Darstellung (AST)
2. **Logische Optimierung**: Umformungen mit Heuristik
3. **Physische Optimierung**: konkrete Ausführungspläne mit Indexen, Algorithmen
4. **Kostenbasierte Auswahl**: Basierend auf Statistiken

---

## 4. Logische vs. Physische Optimierung

* **Logisch**: ohne Kenntnis von DB-Größe/Statistiken
* **Physisch**: unter Einbezug von Indexen und Systemstatistiken
* Ziel: Minimale **geschätzte Kosten**

---

## 5. Kostenanalyse

| Kostenart             | Beschreibung            |
| --------------------- | ----------------------- |
| Kommunikationskosten  | Datenübertragungsmenge  |
| CPU-Berechnungskosten | je nach Tupelgröße      |
| I/O-Kosten            | Seitenzugriffe          |
| Speicherkosten        | Nutzung von RAM, Puffer |

---

## 6. Selektivität und Dichte

### Selektivität:

* Anteil relevanter Tupel an Gesamtheit
* **Hohe Selektivität** (wenige Tupel): Index vorteilhaft
* **Tiefe Selektivität** (viele Tupel): Table Scan besser

### Dichte:

* Anteil Duplikate zu Distinct Values
* **Hohe Dichte**: wenig hilfreich für Index
* **Niedrige Dichte**: gute Index-Kandidaten

---

## 7. Statistiken im Optimizer

* PostgreSQL hält Statistiken in `pg_stats`
* Wichtige Werte:

  * `most_common_values`, `most_common_frequencies`
  * Histogramme: gleich breit vs. height-balanced
* Notwendig für realistische Kostenabschätzung
* Manuelle Aktualisierung: `ANALYZE`

---

## 8. Tipps zur Indexwahl

* Indexe nur bei hoher Selektivität (<10 %) sinnvoll

* Typische Indexkandidaten:

  * Primär-/Fremdschlüssel
  * JOIN- und WHERE-Bedingungen
  * Sortierungen und Aggregationen

* **Nicht geeignet** für:

  * selten verwendete Spalten
  * Spalten mit wenigen unterschiedlichen Werten (BOOLEAN, ENUM)
  * BLOBs

---

## 9. Tipps zur Abfrageoptimierung

* Verwende **JOIN-Syntax**, nicht Unterabfragen
* Vermeide `SELECT *`, stattdessen gezielte Projektion
* Nutze numerische Werte statt Textvergleiche
* Schnellere Filter zuerst formulieren
* Materialisierte Views und Partitionierung erwägen

---

## 10. Praktische Tools & Links

* [pgTune](https://pgtune.leopard.in.ua/) – Konfiguration anpassen
* [depesz EXPLAIN Visualizer](https://explain.depesz.com/) – Query-Pläne teilen
* [PostgreSQL Statistiken](https://www.postgresql.org/docs/current/sql-analyze.html)

---

## 11. Zusammenfassung

* Indexwahl, Statistiken und Selektivität sind zentral für Performance
* Der PostgreSQL-Optimizer wählt anhand von Histogrammen, Kardinalitäten und Dichte den Plan
* Performanceoptimierung benötigt aktuelle Statistiken und fundiertes Wissen über Datenstruktur und Zugriffsverhalten
* Abfrageoptimierung ist eine **iterative und datengetriebene Aufgabe**
