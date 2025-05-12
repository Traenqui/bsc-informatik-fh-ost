# Data Engineering – Verteilte Datenbanksysteme

**Dozenten:** Prof. Stefan Keller & Joël Schwab
**Semester:** FS25
**Ort:** OST Campus Rapperswil

---

## Lernziele

* Grundverständnis verteilter Datenbanksysteme (DBMS)
* Unterschiede zwischen homogenen und heterogenen DBMS
* Datenverteilung: Partitionierung, Replikation, Allokation
* Verteilte Transaktionen, insbesondere 2-Phase Commit
* Optimierung verteilter Abfragen (z. B. Predicate Pushdown)

---

## 1. Was sind verteilte DBMS?

* Zusammenspiel autonomer Datenbanken auf vernetzten Rechnern (Nodes)
* Jeder Knoten kann lokal Anwendungen ausführen und global partizipieren
* Koordination zur Datenkonsistenz und Verfügbarkeit nötig

---

## 2. Vorteile & Nachteile

### Vorteile:

* Lokale Kontrolle, globale Zusammenarbeit
* Parallelisierung = bessere Performance
* Höhere Verfügbarkeit durch Replikation

### Nachteile:

* Erhöhte Komplexität
* Heterogene Technologien, Schemata, Middleware-Probleme

---

## 3. Anforderungen an verteilte DBMS

1. **Netzwerkzugriff** (z. B. Foreign Data Wrapper, SQL/MED)
2. **Verwaltung verteilter Daten** (Transparenz, Katalogführung)
3. **Transaktionsmanagement** (Atomarität, z. B. 2PC)
4. **Verteilte Ausführungsplanung** (globale Optimierung)

---

## 4. Homogen vs. Heterogen

| Merkmal        | Homogen         | Heterogen                        |
| -------------- | --------------- | -------------------------------- |
| Software       | Einheitlich     | Unterschiedlich                  |
| Schema         | Globales Schema | Unterschiedliche lokale Schemata |
| Zusammenarbeit | Eng integriert  | Föderiert oder lose gekoppelt    |

---

## 5. Verteilte Datenhaltung

### Partitionierung

* **Horizontal**: Zeilen werden aufgeteilt (Sharding)
* **Vertikal**: Spalten werden getrennt gespeichert

### Replikation

* Daten in mehreren Knoten redundant gespeichert
* Vorteile: Verfügbarkeit, schnellere lokale Abfragen
* Nachteile: Synchronisations- und Updatekosten

### Allokation

* Zuweisung von Fragmenten oder Replikaten an Knoten

---

## 6. Transparenz

* Benutzer sieht nur eine globale Sicht (Relation R)
* Versteckt Fragmentierung und Replikation
* Query wird zentral formuliert, verteilt ausgeführt

---

## 7. Partitionierung in der Praxis

* Strategien: Hash, Range, Composite, Reference
* Ziel: gleichmäßige Lastverteilung
* Einschränkungen: Shard-Key ist fix
* Beispiel (PostgreSQL):

```sql
CREATE TABLE payments (
  ...
) PARTITION BY HASH (payment_id);

CREATE TABLE payments_one PARTITION OF payments
  FOR VALUES WITH (modulus 2, remainder 1);
```

---

## 8. Verteilte Transaktionen

* Notwendig, wenn mehrere Datenbanken beteiligt sind
* Ziel: Globale Konsistenz durch **atomare Ausführung**

### Zwei-Phasen-Commit (2PC)

**Akteure:**

* TM = Transaction Manager (Koordinator)
* RM = Resource Manager (lokales DBMS)

#### Phase 1: Prepare

* TM fragt alle RM: „Bereit zum Commit?“
* RM loggt & antwortet mit `READY` oder `FAILED`

#### Phase 2: Commit

* Wenn alle `READY`, sendet TM `COMMIT`
* Bei Fehler: `ABORT` an alle
* RM loggen & bestätigen mit `ACK`

---

## 9. Fehlerbehandlung beim 2PC

* TM-Absturz vor `COMMIT` → globales `ABORT`
* RM-Absturz → Logauswertung beim Neustart
* Nachrichtenverlust → TIMEOUT-Handling, Wiederholungen

### Kritik am 2PC:

* Langsam
* Nicht fehlertolerant (Blockieren möglich)
* Alternative: **Paxos** oder **Raft**

---

## 10. Neue Konsensverfahren

### Paxos:

* Konsens durch Mehrheit
* Verbesserung der Fehlertoleranz

### Raft:

* Einfachere Implementation als Paxos
* Rollen: Leader, Follower, Candidate
* Mehrheitsentscheid für Konsens

---

## 11. Verteilte Anfrageverarbeitung

### Kosten

* Lokales DBMS: Disk-I/O
* Verteiltes DBMS: Netzwerk-I/O entscheidend
* Parallele Verarbeitung auf Knoten möglich

### Partitionierte Ausführung

* Horizontale Partition: lokale WHERE-Ausführung
* Vertikale Partition: Join über Identifier

---

## 12. Optimierung verteilter Abfragen

### Fetch-as-needed

* Nur benötigte Join-Daten werden übertragen

### Predicate Pushdown

* Filter-, Aggregat-, Join-Operationen werden **auf dem Remote-Knoten** ausgeführt

Beispiel PostgreSQL:

```sql
SELECT count(*), country_code
FROM remote.customer
GROUP BY country_code;
```

→ wird remote aggregiert

---

## 13. Parallel Processing

* Lokale Parallelisierung mit:

  * JIT (Just-in-Time Compilation)
  * Vectorized Execution (DuckDB)

---

## 14. Zusammenfassung

* Verteilte DBMS bieten **Skalierbarkeit**, **Fehlertoleranz** und **Flexibilität**
* Komplexität entsteht durch **Verteilung**, **Heterogenität** und **Koordination**
* Moderne Alternativen zu 2PC: **Paxos**, **Raft**
* Optimierungen wie **Predicate Pushdown** und **JIT** steigern Effizienz

---

## Weiterführende Quellen

* Kemper, Eickler: *Datenbanksysteme*, 8. Aufl., Oldenburg Verlag
* Silberschatz et al.: *Database System Concepts*, 6th Ed., McGraw-Hill
* PostgreSQL Foreign Data Wrappers: [FDW Übersicht](https://wiki.postgresql.org/wiki/Foreign_data_wrappers)
