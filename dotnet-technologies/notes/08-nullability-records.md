# C# Grundlagen – Nullability & Record Types

## Übersicht

- **Thema der Einheit:**
  Umgang mit `null` in C#: Nullable Value Types, Nullable Reference Types, Nullability-Syntax & -Operatoren, sowie Record Types als immutable Datenträger.
- **Dozent:** Manuel Bauer
- **Lernziele:**
  - Wissen, wie Runtime und Compiler mit Nullable Types umgehen
  - Die im Zusammenhang mit `null` eingeführten Convenience-Features („Syntactic Sugar“) anwenden
  - Eigenschaften von Record Types verstehen und in einfachen Anwendungen einsetzen

## 1. Einführung / Kontext

Null-Referenzen gelten als „Billion-Dollar-Mistake“ (Tony Hoare), weil sie seit Jahrzehnten zu Abstürzen, Sicherheitslücken und schwer auffindbaren Bugs führen.

In .NET sind `null`-Referenzen ein grundlegendes Konzept:

- **Value Types** waren ursprünglich nie `null`,
- **Reference Types** konnten immer `null` sein und führten bei Zugriff zu `NullReferenceException`.

Seit C# 2 gibt es **Nullable Value Types** (`int?` usw.), seit C# 8 **Nullable Reference Types** als Compiler-Feature, um Zugriffe auf `null` statisch zu erkennen und zu vermeiden. Parallel dazu kamen Operatoren wie `?.`, `??`, `??=`, `is null`/`is not null` hinzu, die den Umgang mit `null` einfacher und sicherer machen. Record Types erleichtern vor allem die Arbeit mit **immutable** Daten und Nullable Reference Types.

## 2. Zentrale Begriffe und Definitionen

| Begriff                                  | Definition                                                                                                               |
| ---------------------------------------- | ------------------------------------------------------------------------------------------------------------------------ |
| Null Reference                           | Referenz, die auf kein Objekt zeigt; Zugriff führt bei Runtime zu `NullReferenceException`.                              |
| Default-Literal `default(T)` / `default` | Liefert Standardwert eines Typs: für Reference Types `null`, für Value Types z.B. `0`, `false`, `'\0'`.                  |
| Nullable Value Type                      | Value Type, der zusätzlich den Zustand `null` haben kann, technisch `System.Nullable<T>`.                                |
| `T?` (bei Value Types)                   | Kurzschreibweise für `Nullable<T>`, z.B. `int?` → `Nullable<int>`.                                                       |
| Nullable Reference Type                  | Referenztyp, der explizit als `T?` markiert ist und laut Compiler `null` sein darf (z.B. `string?`).                     |
| Non-Nullable Reference Type              | Referenztyp ohne `?` (z.B. `string`), den der Compiler als _nicht_ `null` behandelbar annimmt.                           |
| Null-Status-Analyse                      | Statische Analyse im Compiler, die anhand des Kontrollflusses ermittelt, ob eine Referenz `null` sein _kann_ (C# 8+).    |
| Null-forgiving Operator `!`              | Operator zur expliziten Unterdrückung von Nullability-Warnungen: `expr!`. Compiler nimmt an, `expr` sei nicht `null`.    |
| Null-Coalescing Operator `??`            | Gibt linken Operand zurück, falls nicht `null`, sonst rechten Operand.                                                   |
| Null-Coalescing Assignment `??=`         | Weist nur dann zu, wenn linke Seite `null` ist.                                                                          |
| Null-Conditional Operator `?.`           | Ruft Member nur auf, wenn linke Seite nicht `null` ist; sonst Ergebnis `default`.                                        |
| Record Type                              | Spezielle Klassen-/Struct-Variante mit Fokus auf Datenrepräsentation, Value Equality und immutablen Properties (`init`). |
| Nondestructive Mutation                  | Erzeugen leicht veränderter Kopien eines Records über `with`-Ausdruck.                                                   |

## 3. Hauptinhalte

### 3.1 Nullability – Überblick

**Historik & Trennung:**

- **Structs / Value Types**
  - hatten ursprünglich **kein** `null`; Defaultwert z.B. `0` für `int`, `false` für `bool`.
  - `default(T)` liefert diesen Standardwert.

- **Klassen / Reference Types**
  - konnten von Anfang an `null` sein.
  - Zugriff auf Member einer `null`-Referenz → `NullReferenceException`.

**Vergleich `x is null`:**

```csharp
// in generischer Methode:
T x1 = default;
// ...
if (x1 is null) { /* ... */ }
```

- Bei Reference Types ergibt `x is null` `true`, wenn `x` wirklich `null` ist.
- Bei Value Types ergibt `x is null` immer `false`; bei `where T : struct` ist `T x1 = null;` sogar Compilerfehler.

### 3.2 Nullable Value Types (Structs / Value Types)

#### `System.Nullable<T>`

Für Value Types existiert die generische Struct `Nullable<T>`:

```csharp
public struct Nullable<T> where T : struct
{
    public Nullable(T value);
    public bool HasValue { get; }
    public T Value { get; }
}
```

- `HasValue == false` → Zustand „null“.
- Zugriff auf `Value` in diesem Zustand → `InvalidOperationException`.

**Tabelle (vereinfacht):**

| Zustand    | `HasValue` | `Value`         |
| ---------- | ---------- | --------------- |
| `null`     | `false`    | nicht definiert |
| `not null` | `true`     | z.B. `123`      |

#### `T?`-Syntax

Kurzschreibweise, rein compilerseitig:

```csharp
int? x = 123;
int? y = null;

// Compiler-Output
System.Nullable<int> x = new System.Nullable<int>(123);
System.Nullable<int> y = new System.Nullable<int>();
```

→ bessere Lesbarkeit, kein Unterschied zur expliziten `Nullable<T>`-Schreibweise.

#### Sicheres Lesen & Casts

```csharp
int? x = null;

// klassisch
int x1 = x.HasValue ? x.Value : default;

// Methode
int x2 = x.GetValueOrDefault();
int x3 = x.GetValueOrDefault(-1);

// Umwandlung
int i = 123;
int? n = i;
int j = (int)n;        // Compiler expandiert zu j = n.Value;
```

### 3.3 Nullable Reference Types (Klassen)

#### Konzept & Aktivierung

Nullable Reference Types wurden mit C# 8 eingeführt und sind **nur ein Compiler-Feature**: die Runtime ändert sich nicht. :contentReference[oaicite:16]{index=16}

- Basieren auf „null-state analysis“ – einer statischen Flussanalyse.
- Ziel: **Warnungen** erzeugen, wenn potentieller Zugriff auf `null` erfolgt.
- Sanfter Ansatz, da nicht alle Libraries sofort umgestellt werden konnten:
  - Standardannahme: jede Referenz könnte `null` sein, **ausser**:
    - sie stammt aus einem Assembly, das bereits mit Nullable enabled kompiliert wurde, oder
    - sie wurde im eigenen Code bereits auf `null` geprüft.

**Aktivierung in `.csproj`:**

```xml
<PropertyGroup>
  <Nullable>enable</Nullable>  <!-- oder disable -->
</PropertyGroup>
```

**Aktivierung im Code:**

```csharp
#nullable enable   // aktiv
// ...
#nullable disable  // deaktiv
// ...
#nullable restore  // Projekt-Standard wiederherstellen
```

Gilt jeweils ab der Direktive nach „unten“ im File.

#### Syntax: `string` vs. `string?` & `!`

```csharp
string s1;   // Non-nullable
string? s2;  // Nullable

string? nameNull = null;
string name = nameNull;    // Warning

if (nameNull is null)
{
    name = nameNull!;      // OK für Compiler, evtl. falsch zur Laufzeit
}
else
{
    name = nameNull;       // OK, da im else-Teil nicht null
}
```

- `string` → soll im Null-State „nicht null“ sein.
- `string?` → darf `null` sein; Verwendung ohne vorherige Prüfung erzeugt Warnungen.
- `!` (Null-forgiving Operator) überschreibt die Analyse → nur sparsam verwenden.

#### Generische Constraints (Zusatz zu Generics)

Ergänzend zu normalen Constraints gibt es:

| Constraint          | Bedeutung                                                                                 |
| ------------------- | ----------------------------------------------------------------------------------------- |
| `where T : class?`  | `T` muss ein **nullable** Reference Type sein (inkl. Interface, Delegate).                |
| `where T : notnull` | `T` muss ein Non-Nullable Value oder Reference Type sein; `null` explizit ausgeschlossen. |

### 3.4 Syntactic Sugar rund um Nullability

#### `is null` / `is not null` – Pattern Matching

```csharp
int? x = null;
string s = null;

bool b1a = x is null;
bool b1b = x is not null;

bool b2a = s is null;
bool b2b = s is not null;
```

Der Compiler generiert abhängig vom Typ unterschiedlichen Code (siehe Diagramm auf _Seite 18_):

- **Value Types (Nullable<T>):** `x.HasValue` / `!x.HasValue`.
- **Reference Types:** `object.ReferenceEquals(x, null)` / Negation.

Warum nicht `== null`?
→ `==` kann überladen sein, dann wäre das Ergebnis nicht mehr reine Null-Prüfung.

#### Null-Coalescing `??`

```csharp
int? x = null;
int i = x ?? -1;

// Compiler (vereinfacht)
int i = x is not null
    ? x.GetValueOrDefault()
    : -1;
```

- Gibt linken Ausdruck zurück, wenn nicht `null`, sonst rechten.
- Auf der rechten Seite kann auch `throw` stehen (z.B. `?? throw new ArgumentNullException(...)`).

#### Null-Coalescing Assignment `??=`

```csharp
int? i = null;
i ??= -1;

// Compiler (vereinfacht)
if (i is null)
{
    i = -1;
}
```

Beliebt für „Initialisiere einmal, wenn noch nichts gesetzt wurde“.

#### Null-Conditional `?.`

```csharp
object o = null;
Action a = null;

string s = o?.ToString();
a?.Invoke();
```

Compilerexpansion (vereinfachte Logik, siehe _Seite 21_):

```csharp
string s = o is not null ? o.ToString() : default;

if (a is not null)
{
    a();
}
```

- Verhindert `NullReferenceException` beim Kettenzugriff: `obj?.Child?.Name`.
- Für Delegates sehr praktisch: `eventHandler?.Invoke(sender, args);`.

**Visualisierung: Verhalten von `?.`**

```mermaid
flowchart TD
  A[Ausdruck: x?.M()] --> B{x is null?}
  B -->|Ja| C[Ergebnis = default(TResult)]
  B -->|Nein| D[M() auf x aufrufen]
```

### 3.5 Record Types – Überblick

**Grundidee:** Records sind Klassen oder Structs, die hauptsächlich Daten repräsentieren sollen: wenig Logik, Fokus auf **immutable Properties** und **Value Equality**. Sie sind ein reines Compiler-Feature.

Beispiel (positional Syntax, _Seite 23/24_):

```csharp
public record class Person(
    int Id,
    string Name);
```

Der Compiler erzeugt u.a.:

- Konstruktor `Person(int Id, string Name)`
- Properties `Id` & `Name` mit `get; init;`
- `ToString()` mit guter Default-Darstellung
- `Equals`, `GetHashCode` & Operatoren `==`/`!=` für _Value Equality_
- Interface-Implementierung `IEquatable<Person>`

Die Grafik auf _Seite 24_ zeigt die vom Compiler erzeugte „normale“ Klasse mit diesen Members.

### 3.6 Record-Deklarationen

#### Vollständige Klassen-Syntax

Records können auch wie normale Klassen deklariert werden:

```csharp
public record Person
{
    public Person() : this(0, "") { }
    public Person(int id, string name)
    {
        Id = id;
        Name = name;
    }

    public int Id { get; init; }
    public string Name { get; init; }
}

// Anwendung
Person p1 = new();
Person p2 = new(1, "Mary");
```

- Nutzen begrenzt; Positional Syntax ist meist knapper.
- Value Equality & ToString werden trotzdem generiert.

#### Mixed Syntax & Init-only Setter

Positional Header + zusätzliche Members:

```csharp
public record Person(int Id)
{
    public string Name { get; init; }
    public void DoSomething() { }
}
```

- `Id` und `Name` sind `init`-only:
  - Nur im Konstruktor oder Objekt-Initializer setzbar, nicht mehr danach.

```csharp
Person p1 = new(0);
p1.Id = 0;        // Compilerfehler
p1.Name = "";     // Compilerfehler

Person p2 = new(0) { Name = "" }; // OK
```

**Hinweis:** Bei Non-Nullable-Properties ohne Initialwert warnt der Compiler:

> _Non-nullable property 'Name' must contain a non-null value when exiting constructor…_

→ Records motivieren zu **komplett initialisierten**, im Idealfall immutablen Objekten.

#### Vererbung mit Records

- Vererbung wird unterstützt, aber **Basistyp muss selbst Record sein**.

```csharp
public abstract record Person(int Id);

public record SpecialPerson(
    int Id,
    string Name) : Person(Id);

// Anwendung
SpecialPerson p1 = new(1, "Mary");
Person p2 = p1;
```

Basiskonstruktoren können hinter dem Record-Header aufgerufen werden (`: Person(Id)`, siehe _Seite 27_).

### 3.7 Value Equality & Records

Record Types vergleichen per Default **alle Properties** auf Gleichheit. Keine Reference Equality!

```csharp
public record Person(int Id, string Name);

Person p1 = new(0, "Mary");
Person p2 = new(0, "Mary");

bool eq1 = p1 == p2;             // true
bool eq2 = p1 != p2;             // false
bool eq3 = p1.Equals(p2);        // true
bool eq4 = ReferenceEquals(p1,p2); // false
```

- `==` / `Equals` → Wertgleichheit (Id & Name).
- `ReferenceEquals` → objektidentität, hier `false`.
- Vererbung wird bei Equality berücksichtigt: Properties von Basisklassen fliessen mit ein (siehe Hinweis auf _Seite 24/28_).

### 3.8 Nondestructive Mutation – `with`-Ausdruck

Für immutable Records braucht man oft „Kopie mit kleinen Änderungen“. `with` bietet genau das (siehe _Seite 29_):

```csharp
public record Person(int Id, string Name);

Person p1 = new(0, "Mary");
Person p2 = p1 with { Id = 1 };
bool eq2 = p1 == p2; // false

Person p3 = p1 with { };
bool eq3 = p1 == p3; // true
```

- `with` erstellt eine **flache Kopie** und wendet dann die im Initializer genannten Änderungen an.
- Ideal für z.B. „alte Version + 1 geändertes Feld“, ohne den ursprünglichen Datensatz zu verändern.

**Nondestructive Mutation**

```mermaid
flowchart TD
  A[Record p1] --> B[with { Id = 1 }]
  B --> C[neues Record-Objekt p2]
  A --> D[with { }]
  D --> E[p3 referenziert neue, aber wertgleiche Kopie]
```

## 4. Zusammenhänge und Interpretation

- **Nullable Value Types** erweitern Structs um einen `null`-Zustand.
- **Nullable Reference Types** sind ein Compiler-Feature, das _bestehende_ Null-Referenzen sicherer macht, ohne die Runtime zu ändern.
- Die Syntactic-Sugar-Operatoren (`is null`, `??`, `??=`, `?.`) bauen direkt auf Nullable-Mechanismen auf und verhindern viele typische `null`-Fehler – wenn man sie konsequent benutzt.
- **Record Types** passen hervorragend zu Nullable-Features, weil sie immutables, vollständig initialisiertes Datenmodell fördern – damit sinkt die Gefahr für vergessene Zuweisungen oder unerwartete `null`s.
- Value Equality von Records und `with`-Ausdrücke machen Records besonders geeignet für Domain-Modelle, DTOs und Konfigurationsobjekte, bei denen der Inhalt und nicht die Identität zählt.

## 5. Beispiele und Anwendungen

1. **Konfiguration mit Records & Nullable Reference Types**

   ```csharp
   public record DbConfig(
       string ConnectionString,
       string? User,
       string? Password);
   ```

   - `ConnectionString` muss gesetzt sein; `User`/`Password` optional.

2. **DTO mit Nondestructive Mutation**
   - `record Order(int Id, string Customer, decimal Amount);`
   - `var updated = order with { Amount = order.Amount * 1.1m };`

3. **Sichere Null-Behandlung in Services**

   ```csharp
   string? name = repo.GetName(id);
   string displayName = name ?? "<Unbekannt>";
   ```

4. **Null-Event-Aufruf**

   ```csharp
   public event EventHandler? Changed;
   protected void OnChanged()
       => Changed?.Invoke(this, EventArgs.Empty);
   ```

5. **Nullable-Constraints in Generics**

   ```csharp
   void EnsureNotNull<T>(T value) where T : notnull
   {
       if (value is null) throw new ArgumentNullException(nameof(value));
   }
   ```

## 6. Zusammenfassung / Takeaways

- `null` ist in .NET ein unveränderliches Laufzeitkonzept; C# versucht seit C# 2 (Nullable Value Types) und vor allem seit C# 8 (Nullable Reference Types) die Folgen zur **Compilezeit** abzufangen.
- Nullable Reference Types sind **opt-in** und erzeugen Warnungen statt Errors – sie erfordern aktives Mitmachen (Annotationen, `?`, `!`).
- `is null`, `??`, `??=`, `?.` vereinfachen Null-Prüfungen und sollten Standardwerkzeuge im täglichen Code sein.
- Record Types sind kompakte, immutability-freundliche Datenträger mit Value Equality und `with`-Unterstützung – ideal für Domain-Objekte und DTOs.

## 7. Lernhinweise

- Aktiviere `<Nullable>enable</Nullable>` in eigenen Projekten und behebe bewusst die entstehenden Warnungen.
- Übe die Null-Operatoren (`is null`, `??`, `??=`, `?.`) an kleinen Beispielen mit Listen, Events und Service-Aufrufen.
- Ersetze Schritt für Schritt klassische Datenklassen (`class` mit nur Properties) durch `record` und nutze `with`, Equality und `ToString()`.
- Achte bei Records auf vollständige Initialisierung – idealerweise keine `!`-Operatoren verwenden.

## 8. Vertiefung / weiterführende Konzepte

- Erweiterte Nullable-Annotations wie `[NotNull]`, `[MaybeNull]` etc. (Roslyn-Annotations).
- Kombination von Records mit Pattern Matching (z.B. `switch`-Expressions über Records).
- Immutable Collections (`ImmutableList<T>`) in Kombination mit Records und Nondestructive Mutation.
- Domain-Driven Design: Value Objects als Records mit Value Equality und Nullability-Regeln.

## 9. Quellen & Literatur (IEEE)

[1] M. Bauer, “C# Grundlagen – Nullability & Record Types,” Foliensammlung, OST – Ostschweizer Fachhochschule, Departement Informatik, Rapperswil, 2025.

[2] Microsoft Corporation, “Nullable reference types,” Online: Microsoft Learn, Zugriff: 2025.

[3] Microsoft Corporation, “Record types (C# reference),” Online: Microsoft Learn, Zugriff: 2025.
