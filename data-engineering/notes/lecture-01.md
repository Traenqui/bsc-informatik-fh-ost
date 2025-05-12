# Data Engineering – O/R Mapping (Einführung)

**Dozenten:** Prof. Stefan Keller & Joël Schwab
**Fachsemester:** FS25
**Campus:** OST Rapperswil

---

## Lernziele

* Verstehen des Zwecks und Prinzips von O/R-Mapping
* Überblick über die **Jakarta Persistence API (JPA)** in Java
* Abbildung von Objektmodellen auf relationale Datenbanken
* Laden und Speichern von Entities in JPA
* Überblick über Mapping-Varianten, JPA-Architektur und Persistenzkonzepte

---

## Inhalte im Überblick

### 1. O/R-Mapping – Motivation & Grundidee

* Programme sind objektorientiert, Datenbanken relational → **"semantic gap"**
* O/R-Mapper bilden eine Brücke: Objekte ↔ Datenbank-Tabellen
* Aufgaben eines O/R-Mappers:

  * Abbildung von Datentypen (z.B. Collections)
  * Verwaltung von Beziehungen (Many-to-Many, Vererbung, etc.)
  * Object-ID-Management

---

### 2. Überblick O/R-Mapper

#### Java

* **JPA** (Jakarta Persistence API)

  * EclipseLink (Referenzimplementierung)
  * Hibernate (weit verbreitet)
* **Weitere Java-Optionen**: JDO, jOOQ, selbstgeschriebene Mapper

#### Andere Sprachen

* .NET: Entity Framework, NHibernate
* Python: SQLAlchemy, Django ORM
* JavaScript/TypeScript: TypeORM, Sequelize
* Ruby, Go, Rust: Diverse spezialisierte ORMs

---

## Jakarta Persistence API (JPA)

* Spezifikation, keine konkrete Implementation
* Unterstützt relationale Datenbanken via JDBC
* Nutzt Annotationen oder XML (`persistence.xml`)
* Nutzt **Entities** als POJOs für persistente Objekte

### JPA Stack

```text
Java Program
    ↑
JPA API
    ↑
JPA Provider (z. B. EclipseLink)
    ↑
JDBC API
    ↑
JDBC Driver
```

---

## Implementierung mit JPA (Kurz-Tour)

### 1. Entity-Klasse

```java
@Entity
public class BankAccount {
  @Id
  private long id;
  private String name;
}
```

### 2. Mapping zur Datenbank

* Standard: 1:1-Mapping von Feldern zu Spalten
* Optional: Feintuning via `@Column`, `@Table`, `@Temporal`, `@Enumerated`, `@Transient`

### 3. Konfiguration (`persistence.xml`)

```xml
<persistence-unit name="Bank">
  <provider>org.eclipse.persistence.jpa.PersistenceProvider</provider>
  <properties>
    <property name="javax.persistence.jdbc.url" value="jdbc:postgresql:jpatest"/>
    ...
  </properties>
</persistence-unit>
```

---

## Laden und Speichern von Entities

### Laden (JPQL):

```java
Query query = em.createQuery("SELECT a FROM BankAccount a");
List<BankAccount> accounts = query.getResultList();
```

### Speichern:

```java
em.getTransaction().begin();
em.persist(account);
em.getTransaction().commit();
```

### Update / Delete:

```java
BankAccount a = em.find(BankAccount.class, 1L);
a.setBalance(...);
em.remove(a);
```

---

## Beziehungen zwischen Entities

| Beziehungstyp | Annotation    | Beispiel                       |
| ------------- | ------------- | ------------------------------ |
| One-to-One    | `@OneToOne`   | `BankCustomer` ↔ `Address`     |
| Many-to-One   | `@ManyToOne`  | `BankAccount` → `BankCustomer` |
| One-to-Many   | `@OneToMany`  | `BankCustomer` → `Accounts[]`  |
| Many-to-Many  | `@ManyToMany` | `BankCustomer` ↔ `BankManager` |

> **Bidirektionale Beziehungen** erfordern `mappedBy` in der Inverse-Seite.

---

## Ladestrategien

* **Eager Loading** (sofort laden): Default bei `@OneToOne`, `@ManyToOne`
* **Lazy Loading** (bei Zugriff laden): Default bei `@OneToMany`, `@ManyToMany`
* Steuerung via `fetch = FetchType.LAZY/EAGER`

---

## Varianten des OR-Mappings

| Strategie           | Beschreibung                          |
| ------------------- | ------------------------------------- |
| Forward Engineering | Java-Code → DB                        |
| Bottom-Up           | DB → Java-Code (Reverse Engineering)  |
| Meet-in-the-Middle  | Beide existieren → Mapping definieren |
| Meta-Model          | Modell-getrieben (selten)             |

> In dieser Einführung wird **Forward Engineering** verwendet.

---

## Architekturbegriffe

### Persistence Unit

* Definiert durch `persistence.xml`
* Bündel von Entity-Klassen, DB-Config, Provider-Config

### Persistence Context

* Enthält alle aktuell **managed** Entities einer Transaktion

### EntityManager

* API für CRUD-Operationen
* Lifecycle: `persist()`, `find()`, `remove()`, `merge()`, `flush()`, `clear()`

---

## Entity-Lebenszyklus

| Zustand  | Beschreibung                            |
| -------- | --------------------------------------- |
| New      | Noch nicht gespeichert, ohne ID         |
| Managed  | Persistiert & aktiv im Context          |
| Detached | Persistiert, aber nicht mehr im Context |
| Removed  | Zum Löschen vorgemerkt                  |

---

## Fazit der Lektion

-  Grundlagen von O/R Mapping verstanden
-  JPA-Basics und Architekturkonzept erlernt
-  Mapping, Persistenz und Entitätsbeziehungen angewendet
- Nächste Lektion: Vererbung, JPQL, erweiterte Beziehungen, GenAI

---

## Weiterführende Links

* [Wikipedia – Jakarta Persistence](https://en.wikipedia.org/wiki/Jakarta_Persistence)
* [jOOQ (Java Object Oriented Querying)](https://www.jooq.org)
* [Spring & JPA Records Guide](https://www.baeldung.com/spring-jpa-java-records)
* [EclipseLink JPA Doku](https://www.eclipse.org/eclipselink/documentation/)
