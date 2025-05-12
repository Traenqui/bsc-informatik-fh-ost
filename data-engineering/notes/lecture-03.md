# Data Engineering – Stored Procedures, PL/pgSQL und Cursors

**Dozenten:** Prof. Stefan Keller & Joël Schwab
**Semester:** FS25
**Ort:** OST Campus Rapperswil

---

## Lernziele

* Verständnis von **Stored Procedures (SP)**
* Anwendung der prozeduralen Sprache **PL/pgSQL**
* Einführung in das **Cursor-Konzept**
* Erweiterungsmöglichkeiten von PostgreSQL mit **SQL und Python**

---

## Einführung in Stored Procedures

### Was sind Stored Procedures?

* Subroutinen, die im DB-Server gespeichert und ausgeführt werden
* Auch bekannt als: **User Defined Functions**, **Methoden**, **Subprogramme**
* Zentralisieren Logik und reduzieren Netzwerkverkehr

### Vorteile:

1. Zentrale Geschäftslogik
2. Wiederverwendbarkeit
3. Performance-Optimierung
4. Wartbarkeit
5. Sicherheit (z. B. Schutz vor SQL-Injection)

### Nachteile:

* Komplexere Wartung
* DB-Spezifisch, erschwert Portierbarkeit
* Alternative: einfache Views/Subqueries oder O/R-Mapping

---

## PostgreSQL und PL/pgSQL

### PostgreSQL-Unterstützung

* Funktionen (`CREATE FUNCTION`)
* Prozeduren (`CREATE PROCEDURE`, ab Version 11)
* Verschiedene Sprachen: `plpgsql`, `plpythonu`, `pljava`, `sql`, `plv8` usw.

### PL/pgSQL = SQL/PSM (SQL:1999/2003)

* Blockstruktur wie Pascal/Ada
* Standardisiert, aber PostgreSQL-spezifisch erweitert

---

## Syntax-Beispiel: Einfache Funktion

```sql
CREATE FUNCTION helloworld()
RETURNS void AS $$
BEGIN
  RAISE NOTICE 'Hello World!';
END;
$$ LANGUAGE plpgsql;
```

---

## Parameterisierte Funktionen

```sql
CREATE FUNCTION power_modulo(bign bigint, n bigint, m bigint)
RETURNS bigint AS $$
BEGIN
  IF n = 0 THEN RETURN 1; END IF;
  DECLARE x bigint := bign % m;
  DECLARE xx bigint := (x * x) % m;
  IF n % 2 = 0 THEN
    RETURN power_modulo(xx, n/2, m);
  ELSE
    RETURN (x * power_modulo(xx, (n-1)/2, m)) % m;
  END IF;
END;
$$ LANGUAGE plpgsql;
```

---

## Blöcke, Deklarationen, Kommentare

* Blöcke bestehen aus `DECLARE`, `BEGIN`, `EXCEPTION`, `END`
* Variablenzuweisung: `var := expression;`
* Kommentare: `--`, `/* ... */`

---

## Kontrollstrukturen

* `IF` / `ELSIF` / `ELSE` / `END IF`
* `FOR-IN LOOP`
* `WHILE LOOP`
* `EXIT`, `CONTINUE`

---

## Fehlerbehandlung (EXCEPTION)

```sql
BEGIN
  SELECT ... INTO ...;
EXCEPTION
  WHEN NO_DATA_FOUND THEN ...
  WHEN TOO_MANY_ROWS THEN ...
  WHEN OTHERS THEN ...
END;
```

* Spezielle Variablen: `FOUND`, `ROW_COUNT`

---

## Dynamisches SQL

```sql
EXECUTE 'SELECT 1 + ' || i INTO result;
```

* Dynamisches SQL mit `EXECUTE`
* PERFORM für Funktionsaufrufe ohne Rückgabe

---

## Prozeduren vs. Funktionen

* Funktionen geben Werte zurück (`RETURNS ...`)
* Prozeduren (ab PostgreSQL 11) nutzen `CALL` und geben nichts zurück

Beispiel:

```sql
CREATE PROCEDURE salaererhoehung(angnr INTEGER, salincr DECIMAL)
AS $$
BEGIN
  IF salincr < 0 OR salincr > 2000 THEN
    RAISE EXCEPTION 'Ungültige Erhöhung';
  END IF;
  UPDATE angestellter SET salaer = salaer + salincr WHERE persnr = angnr;
END;
$$ LANGUAGE plpgsql;
```

---

## Rückgabe von Skalarwerten und Tabellen

* Skalarwert:

```sql
RETURNS DECIMAL
SELECT SUM(...) INTO var;
RETURN var;
```

* Tabelle:

```sql
RETURNS TABLE (col1 TYPE, col2 TYPE)
RETURN QUERY SELECT ...;
```

---

## Set Returning Functions (SRF)

```sql
RETURNS SETOF foo
FOR r IN SELECT * FROM foo LOOP
  RETURN NEXT r;
END LOOP;
```

---

## Cursor-Verarbeitung

### Ablauf:

1. DECLARE
2. OPEN
3. FETCH
4. LOOP / Verarbeitung
5. CLOSE

### Beispiel:

```sql
DECLARE
  angcursor CURSOR FOR SELECT ...;
BEGIN
  OPEN angcursor;
  LOOP
    FETCH angcursor INTO var;
    EXIT WHEN NOT FOUND;
  END LOOP;
  CLOSE angcursor;
END;
```

* Cursor auch mit Parametern und `FOR UPDATE` nutzbar

---

## Erweiterungen in PostgreSQL

### Offizielle Erweiterungen:

* `hstore`, `pg_trgm`, `tablefunc`
* Installation mit `CREATE EXTENSION name;`

### Community-Erweiterungen:

* z. B. `PostGIS`, `pg_stat_statements`, `TimescaleDB`

### Eigene Erweiterungen:

* Mit `CREATE EXTENSION`, `plpgsql`, `plpythonu`, C, etc.

---

## SQL-Funktion als Makro

```sql
CREATE FUNCTION array_sort(arr anyarray)
RETURNS anyarray AS $$
SELECT array(SELECT unnest(arr) ORDER BY 1)
$$ LANGUAGE sql;
```

---

## Python in PostgreSQL (PL/Python)

```sql
CREATE FUNCTION fnfileexists(afilename text)
RETURNS boolean AS $$
import os
return os.path.exists(afilename)
$$ LANGUAGE plpythonu;
```

* `plpythonu` ist untrusted (Superuser erforderlich)

---

## Zusammenfassung

* PL/pgSQL ist eine mächtige Erweiterung von SQL für prozedurale Verarbeitung
* Stored Procedures sind ideal zur Kapselung von Geschäftslogik in der Datenbank
* Cursor ermöglichen zeilenweise Verarbeitung, sind aber weniger effizient als SQL
* PostgreSQL ist durch Sprachen und Erweiterungen extrem flexibel

---

## Ressourcen

* PostgreSQL Doku: [https://www.postgresql.org/docs/current/](https://www.postgresql.org/docs/current/)
* Error Codes: [https://www.postgresql.org/docs/current/static/errcodes-appendix.html](https://www.postgresql.org/docs/current/static/errcodes-appendix.html)
* Tutorials:

  * [https://postgres.cz/wiki/PL/pgSQL\_(en)](https://postgres.cz/wiki/PL/pgSQL_%28en%29)
  * [https://www.enterprisedb.com/postgres-tutorials/10-examples-postgresql-stored-procedures](https://www.enterprisedb.com/postgres-tutorials/10-examples-postgresql-stored-procedures)
