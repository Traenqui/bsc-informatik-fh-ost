# Data Engineering – Triggers, Views und Sicherheit in PostgreSQL

**Dozenten:** Prof. Stefan Keller & Joël Schwab
**Semester:** FS25
**Ort:** OST Campus Rapperswil

---

## Lernziele

* Einsatz und Verhalten von **Triggers** in PostgreSQL
* Verständnis von **updatable** und **materialized views**
* Anwendung von **instead of-triggers**
* Nutzung von **temporären Tabellen**
* Sicherheit durch **Stored Procedures**, **Views** und **Row-Level Security (RLS)**

---

## Triggers in PostgreSQL

### Verwendungszwecke

* Durchsetzung komplexer Konsistenzbedingungen
* Berechnung abgeleiteter Attribute
* Logging und Auditing
* Sicherheit (z. B. zeitlich eingeschränkte Änderungen)
* Unterstützung updatable Views

### Eigenschaften

* Werden durch Datenbank-Ereignisse ausgelöst: `INSERT`, `UPDATE`, `DELETE`, `TRUNCATE`
* Ausgeführt `BEFORE` oder `AFTER` der Aktion
* Für `EACH ROW` oder `EACH STATEMENT`
* Können **nicht direkt aufgerufen** werden
* Trigger-Funktionen müssen `RETURNS TRIGGER` haben

### Trigger-Funktion Beispiel

```sql
CREATE FUNCTION mytriggerfn()
RETURNS TRIGGER AS $$
BEGIN
  IF (TG_OP = 'INSERT') THEN
    NEW.creation_date := now();
  ELSIF (TG_OP = 'UPDATE') THEN
    NEW.modification_date := now();
  END IF;
  RETURN NEW;
END;
$$ LANGUAGE plpgsql;
```

---

## Trigger-Variablen (`TG_...`)

| Variable     | Bedeutung                    |
| ------------ | ---------------------------- |
| `TG_NAME`    | Name des Triggers            |
| `TG_WHEN`    | BEFORE / AFTER               |
| `TG_LEVEL`   | ROW / STATEMENT              |
| `TG_OP`      | INSERT, UPDATE, DELETE, etc. |
| `TG_ARGV[n]` | Parameter als TEXT           |
| `NEW`, `OLD` | Neuer / alter Record-Wert    |

---

## Trigger-Beispiele

* **Soft Delete:** Setze Flag statt physisch zu löschen
* **Audit Trigger:** Speichert Änderungen in Audit-Tabelle
* **Abgeleitete Attribute:** Aktualisiert z. B. `SalaerSumme` in Tabelle `Firma` bei Änderungen in `Angestellter`

---

## Updatable Views

* Views sind **virtuelle Tabellen**, kapseln Komplexität
* Manche Views sind **automatisch aktualisierbar**, z. B. bei einfacher SELECT-Anweisung
* Einschränkungen: keine Aggregationen, `GROUP BY`, `DISTINCT`, `UNION`, etc.
* Bei nicht-updatable Views: **Instead of-Trigger** verwenden

### Beispiel für nicht-updatable View:

```sql
CREATE VIEW ourview2 AS
SELECT abtnr, avg(salaer)::decimal(10,2) AS avg_salaer
FROM angestellter
GROUP BY abtnr;
```

### Lösung:

```sql
CREATE OR REPLACE FUNCTION ourview2triggerfn()
RETURNS TRIGGER AS $$
BEGIN
  UPDATE angestellter
  SET salaer = salaer + (NEW.avg_salaer - OLD.avg_salaer)
  WHERE abtnr = OLD.abtnr;
  RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER ourview2trigger
INSTEAD OF UPDATE ON ourview2
FOR EACH ROW
EXECUTE PROCEDURE ourview2triggerfn();
```

---

## Materialized Views

* **Persistente Abfrageergebnisse**
* Schneller Zugriff, aber **nicht automatisch aktuell**
* Muss via `REFRESH MATERIALIZED VIEW` aktualisiert werden

### Beispiel:

```sql
CREATE MATERIALIZED VIEW my_mat_view AS
SELECT * FROM mytable WHERE id <= 500000;
```

* `REFRESH MATERIALIZED VIEW my_mat_view;` aktualisiert die Daten
* **Vorteil**: sehr schnell lesbar
* **Nachteil**: bei Änderungen veraltet, manuelles Refresh nötig

---

## Temporäre Tabellen

* Temporär während einer Session oder Transaktion
* Anwendung: Zwischenergebnisse, temporäre Speicherung

```sql
CREATE TEMPORARY TABLE tmp AS
SELECT generate_series(1, 100000) AS id;
```

---

## Sicherheit in PostgreSQL

### Zugriffsschutz mit Stored Procedures

* Prozeduren kapseln Logik und Zugriffe
* Benutzer benötigt keine Rechte auf Basistabelle
* Prozeduren laufen mit Rechten des Erstellers (Definer-Rights)

```sql
GRANT EXEC ON SalaerErhoehung TO PersonalChef_R;
```

---

### Zugriffsschutz mit Views

* Erlaubt **horizontale oder vertikale Filterung**
* Benutzer hat Rechte nur auf die View, nicht auf die Basistabelle

```sql
GRANT SELECT ON Angestellter_V TO PUBLIC;
```

---

## Row-Level Security (RLS)

* RLS filtert Daten **abhängig vom Benutzerkontext**
* Benutzer sieht nur eigene Datenzeilen
* Aktivierung via:

```sql
ALTER TABLE tbl ENABLE ROW LEVEL SECURITY;
```

### Beispiel-Policy:

```sql
CREATE POLICY tbl_policy ON tbl TO public
USING (
  current_user = updater OR current_user = 'anonymous'
);
```

---

## RLS vs. Views

| Kriterium    | Views                                | Row-Level Security (RLS)                  |
| ------------ | ------------------------------------ | ----------------------------------------- |
| Sicherheit   | Hoch (bei fehlendem Tabellenzugriff) | Sehr hoch (serverseitig erzwungen)        |
| Flexibilität | Statisch                             | Dynamisch, benutzerkontextbasiert         |
| Performance  | Optimierbar                          | Geringere Performance durch Filtersysteme |
| Wartbarkeit  | Komplex bei vielen Views             | Zentralisierte Verwaltung durch Policies  |

---

## Zusammenfassung

* Triggers ermöglichen automatische Reaktionen auf Datenereignisse
* Updatable und materialized Views erlauben strukturierte Sichten auf Daten
* Sicherheit kann über Prozeduren, Views und RLS differenziert implementiert werden
* Materialized Views bieten Performancevorteile auf Kosten der Aktualität
