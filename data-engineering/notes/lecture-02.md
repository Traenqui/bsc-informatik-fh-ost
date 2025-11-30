# O/R Mapping – Fortsetzung

**Modul:** Data Engineering
**Dozenten:** Prof. Stefan Keller & Joël Schwab
**Fachsemester:** FS25
**Ort:** OST Campus Rapperswil

---

## Lernziele

1. Verstehen von Entity-Identitäten und Vererbung in JPA
2. Überblick über JPQL (Java Persistence Query Language)
3. Anwendung von JPA in komplexeren Domänen
4. Kennen der Herausforderungen und Erweiterungen von O/R-Mapping

---

## Inhalt im Überblick

* Entity-Identität
* Verhalten und Zustände von Entities
* Vererbung in JPA
* Abfragen mit JPQL
* Anhang: Transaktionen, Optimistic Locking, Detached Entities

---

## Entity-Identität

* Jede Entity besitzt eine `@Id`, welche auf den Primärschlüssel in der Datenbank abgebildet wird.
* Automatische ID-Erzeugung mittels `@GeneratedValue` mit Strategien:

  * `AUTO`: vom Provider bestimmt
  * `IDENTITY`: auto-increment aus DB
  * `SEQUENCE`: über DB-Sequence
  * `TABLE`: über explizite Key-Tabelle

---

## Verhalten und Zustände von Entities

### Persistence Context

* Wird über `EntityManagerFactory` erzeugt
* Verwaltet geladenen Objektzustand (Cache, Change Tracking)
* Änderungen werden beim Commit synchronisiert

### Transitive Persistenz (Reachability)

* JPA persistiert Objekte nicht automatisch transitiv
* Möglich über:

  * Manuelle Allokation/Deallokation mit `persist()` / `remove()`
  * Annotationen mit `cascade = CascadeType.PERSIST / REMOVE`

### Aggregation und Komposition

* Abbildung über `@OneToMany`-Beziehungen mit verschiedenen Cascade-Typen
* Beispiel: Komposition von `BankCustomer` → `BankAccount`

---

## Bidirektionale Beziehungen

* Änderungen an beiden Seiten müssen manuell synchronisiert werden
* Beispiel: Methoden `setCustomer()` und `addAccount()` in beiden Klassen
* Schützt vor inkonsistenter Datenlage und Endlosrekursion

---

## Vererbung in JPA

### Strategien

1. **Single Table**

   * Eine Tabelle für alle Subtypen
   * Benötigt `@DiscriminatorColumn`
   * Einfach, aber viele NULL-Spalten

2. **Joined Table**

   * Super- und Subklassen in separaten Tabellen
   * Fremdschlüssel-Verknüpfung
   * Normalisierte Struktur

3. **Table per Class**

   * Eigene Tabelle je konkreter Klasse
   * Redundanz durch Vererbung der Felder
   * Kein `DiscriminatorColumn` nötig

4. **Mapped Superclass**

   * Nicht persistente Oberklasse
   * Gemeinsame Felder für Unterklassen

---

## JPQL – Java Persistence Query Language

* Abfragesprache auf dem **Entity-Modell**, nicht auf SQL-Tabellen
* Beispiel:

  ```java
  SELECT c FROM BankCustomer c JOIN c.accounts a
  ```

### Typen von Abfragen

* Selektion mit `WHERE`, `ORDER BY`, `GROUP BY`, `HAVING`
* Projektion: einzelne Felder oder Aggregate
* Join mit expliziten Beziehungen (`JOIN FETCH`)
* Subqueries möglich

### Parameter

* Positional: `?1`
* Named: `:name`
* Schutz vor SQL-Injection
* Auch Named Queries via Annotation `@NamedQuery`

---

## Ausblick

### Criteria API

* Alternative zu JPQL
* Typ-sichere, fluent-style Queries
* Weniger lesbar, aber compilezeitgeprüft

### N+1 Problem

* Tritt bei Lazy-Loading in OneToMany auf
* Führt zu vielen Einzelabfragen
* Lösungen:

  * `JOIN FETCH`
  * `FetchType.EAGER`
  * Entity Graphs, Caching

### Native SQL in JPA

* Direkte Ausführung von SQL möglich mit:

  * `createNativeQuery`
  * `@NamedNativeQuery`
  * JDBC-Zugriff via Unwrap

---

## JPA Transaktionen

* Transaktionen explizit via:

  ```java
  em.getTransaction().begin();
  ...
  em.getTransaction().commit();
  ```

* Isolation Level: standardmässig `READ_COMMITTED`

* Locking:

  * Pessimistic: `lock()` mit `LockModeType.PESSIMISTIC_WRITE`
  * Optimistic: `@Version` mit versionierter Validierung

---

## Detached Entities und Merge

* Detached: ausserhalb des Persistence Contexts
* Änderungen werden via `merge()` in neuen Context übertragen
* Wichtig: Version und ID nicht manuell ändern
* `merge()` gibt eine **managed copy** zurück

---

## Diskussion: Vor- und Nachteile von JPA/ORM

### Vorteile

* Erleichtert Domänenmodellierung
* Weniger manuelles SQL
* Schutz vor SQL-Injection
* Alternativen durch verschiedene JPA-Provider

### Nachteile

* Grosse Lernkurve (API, Konzepte, Verhalten)
* Native SQL manchmal dennoch nötig
* Boilerplate-Code (Abhilfe: Lombok)

---

## Fazit der Lektion

* Kenntnis verschiedener O/R-Mapping- und Vererbungsstrategien
* Anwendung von JPQL und Cascade-Typen
* Verständnis für Transaktionen, Locks und detaching
* ORM erfordert bewusste Modellierungsentscheidungen und Performanceverständnis
