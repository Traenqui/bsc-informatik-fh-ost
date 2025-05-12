# Data Engineering – Stored Procedures & PL/pgSQL (Fortsetzung)

**Dozenten:** Prof. Stefan Keller & Joël Schwab
**Semester:** FS25
**Ort:** OST Campus Rapperswil

---

## Lernziele

* Vertiefung der Anwendung von **PL/pgSQL**
* Verständnis des **Cursor-Konzepts**
* Kenntnis über **variadische**, **polymorphe** und **table-parameterisierte Funktionen**
* Einführung in **Best Practices**, Funktionsrückgaben, Aufrufmöglichkeiten (z. B. via JDBC, JPA)

---

## Wichtige Aspekte von PL/pgSQL

* Eng verknüpft mit SQL: direkte Einbindung von DML
* Nahtlose Integration von SQL + Kontrollstrukturen
* Unterstützung von Triggern, Cursors und komplexen Rückgabetypen
* Performancefreundlich (inkl. Inlining einfacher Funktionen)
* Ähnlichkeit zur Pascal-Syntax: leicht verständlich und strukturiert

---

## Stored Procedures (SP) in PostgreSQL

* SP sind vollwertige DB-Objekte mit eigenen Rechten
* Können von SQL, Triggern, anderen SPs oder Anwendungen (JPA, JDBC) aufgerufen werden
* SP vs. Function:

  | Merkmal                    | Function | Procedure  |
  | -------------------------- | -------- | ---------- |
  | Rückgabe durch Ausdruck    | ✓        | ✗          |
  | Rückgabe via OUT           | ✓        | ✓ (ab v14) |
  | Mehrere Resultsets         | ✗        | ✓          |
  | Transaktionen in SP selbst | ✗        | ✓          |
  | Aufruf                     | SELECT   | CALL       |

---

## Parameterarten

* `IN`, `OUT`, `INOUT` Parameter möglich
* Beispiel:

```sql
create or replace function mysum(
  in x real, in y real, out sum real)
returns real as $$
begin
  sum := x + y;
end;
$$ language plpgsql;
```

---

## Kontrollstrukturen

* `IF`, `CASE`, `LOOP`, `FOR`, `WHILE`, `EXIT`, `CONTINUE`
* Unterstützung für `CASE WHEN`, `ELSE`, `ELSIF`

---

## Cursor-Konzepte

* **Unbound Cursor**: Dynamische SQL-Ausführung
* **Bound Cursor**: Feste SQL-Query beim Deklarieren
* **Parametrisierte Cursor**: Cursor mit Eingabeparametern

### Beispiel:

```sql
declare
  angcursor cursor for
    select salaer, persnr from angestellter where abtnr = currabtnr;
...
fetch angcursor into ...
```

---

## PL/pgSQL – Rückgabetypen

* **SCALAR**: `text`, `integer`, `boolean`, etc.
* **RECORD**, **ROWTYPE**, **COMPOSITE**
* **CURSOR**: Referenz auf eine Abfrage
* **SETOF**, **TABLE**: Mehrere Zeilen zurückgeben
* **ARRAY**, **JSON**, **HSTORE** ebenfalls unterstützt

---

## Set-Returning Functions (SRF)

* Rückgabe einzelner oder mehrerer Zeilen
* Nutzung von `RETURN NEXT`, `RETURN QUERY`
* Unterschied zu Table Functions:

  | Merkmal      | SRF                    | Table Function      |
  | ------------ | ---------------------- | ------------------- |
  | Syntax       | `RETURNS SETOF`        | `RETURNS TABLE`     |
  | Flexibilität | Hoch                   | Niedriger           |
  | Lesbarkeit   | Gering bei Komplexität | Besser strukturiert |
  | Anwendung    | Dynamische Ergebnisse  | Feste Struktur      |

---

## Fortgeschrittene Parameterformen

### Variadische Parameter

```sql
create or replace function last_elem(variadic num_arr numeric[]) returns numeric ...
```

### Polymorphe Parameter

```sql
create or replace function polyfoo1(param1 anyelement) returns anyelement ...
```

### Parameter vom Typ `TABLE`

```sql
create or replace function id_as_text(_aka_record angestellter) returns text ...
```

---

## Aufrufmöglichkeiten

### JDBC

1. `Connection.prepareCall()`
2. Setzen von Input-/Output-Parametern
3. `CallableStatement.execute()`

[Dokumentation](https://jdbc.postgresql.org/documentation/80/callproc.html)

### JPA (ab 2.1)

```java
@NamedStoredProcedureQuery(
  name = "MySum",
  procedureName = "mysum",
  parameters = {
    @StoredProcedureParameter(mode = IN, name = "x", type = Double.class),
    @StoredProcedureParameter(mode = IN, name = "y", type = Double.class),
    @StoredProcedureParameter(mode = OUT, name = "sum", type = Double.class)
  }
)
```

Aufruf:

```java
StoredProcedureQuery query = em.createNamedStoredProcedureQuery("MySum");
query.setParameter("x", 1.0);
query.setParameter("y", 2.0);
query.execute();
Double sum = (Double) query.getOutputParameterValue("sum");
```

---

## Best Practices

1. Verwende `$$` als Delimiter
2. Nutze statisches SQL wenn möglich
3. Dokumentiere mit `COMMENT ON`
4. Fehlerbehandlung via `EXCEPTION`
5. Einheitlicher Stil und Formatierung
6. Nutze Tests (z. B. [pgTAP](https://pgtap.org))
7. Sei "postgresonic" (siehe unten)

---

## PostgreSQL Style Guide ("postgresonic")

* Verwende `snake_case` für Objektnamen
* Nutze `::` für Type Casts statt `typename`
* Operatoren bevorzugen (z. B. `+`, `-`)
* Vendor Features nutzen statt abstrahieren
* Moderne SQL-Features (JOINs, WINDOWs)

[Quelle: Twitter Thread von @reibitto](https://twitter.com/reibitto/status/1489678892785111040)

---

## Weiterführende Ressourcen

* Tutorial: [https://postgres.cz/index.php/PL/pgSQL\_(en)](https://postgres.cz/index.php/PL/pgSQL_%28en%29)
* SQL Tricks: [https://postgres.cz/index.php/PostgreSQL\_SQL\_Tricks](https://postgres.cz/index.php/PostgreSQL_SQL_Tricks)
* Snippets: [https://wiki.postgresql.org/wiki/Category\:Snippets](https://wiki.postgresql.org/wiki/Category:Snippets)

---

## Zusammenfassung

* Sie können PL/pgSQL professionell anwenden
* Sie kennen das Cursor-Konzept und dessen Einsatz
* Sie verstehen Best Practices zur robusten SP-Entwicklung
* SRF vs. Table Functions, polymorphe und variadische Funktionen wurden behandelt
