# C# Grundlagen – Iteratoren

## Übersicht

- **Thema der Einheit:**
  `foreach`-Schleife, Iterator-Interfaces (`IEnumerable<T>`, `IEnumerator<T>`), Iterator-Methoden mit `yield`, spezifische Iteratoren, Extension Methods und Deferred Evaluation in C#.
- **Dozent:** Manuel Bauer
- **Lernziele:**
  - Prinzip der Iteratoren in C# verstehen
  - `IEnumerable<T>` und `IEnumerator<T>` anwenden und bei Bedarf selbst implementieren
  - Iterator-Methoden mit `yield return` / `yield break` schreiben
  - Extension-Methoden definieren und nutzen
  - Deferred Evaluation (verzögerte Ausführung) bei Iteratoren nachvollziehen

## 1. Einführung / Kontext

Viele C#-APIs arbeiten mit Sequenzen von Elementen: Arrays, Listen, eigene Collections oder LINQ-Abfragen. Das zentrale Muster zum Durchlaufen solcher Sequenzen ist der `foreach`-Loop. Hinter `foreach` steckt das Iteratoren-Konzept mit den Interfaces `IEnumerable` / `IEnumerable<T>` und `IEnumerator` / `IEnumerator<T>`.

Iterator-Methoden mit `yield` erlauben es, passende Enumerator-Klassen automatisch vom Compiler generieren zu lassen, statt sie mühsam selbst zu schreiben. In Kombination mit Extension Methods entstehen so LINQ-ähnliche, verkettbare Operationen, die dank **Deferred Evaluation** erst dann ausgeführt werden, wenn die Daten wirklich benötigt werden. Das spart Code und kann Performance und Speicherverbrauch deutlich verbessern.

## 2. Zentrale Begriffe und Definitionen

| Begriff                          | Definition                                                                                                                                                        |
| -------------------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `foreach`-Loop                   | Sprachkonstrukt zum sequentiellen Durchlaufen einer Collection; basiert auf `GetEnumerator()`, `MoveNext()` und `Current`.                                        |
| `IEnumerable` / `IEnumerable<T>` | Interface für aufzählbare Collections; deklariert `GetEnumerator()`. Generische Variante erbt von der nicht-generischen.                                          |
| `IEnumerator` / `IEnumerator<T>` | Interface für den Iterator selbst; deklariert `Current`, `MoveNext()`, `Reset()`; generische Variante erbt von `IEnumerator` und `IDisposable`.                   |
| Iterator                         | Objekt, das den aktuellen Stand einer Iteration über eine Collection kapselt (Position, aktuelles Element).                                                       |
| Iterator-Methode                 | Methode, die einen Iterator bereitstellt und mindestens ein `yield return` enthält; der Compiler erzeugt dazu die Enumerator-Klasse automatisch.                  |
| `yield return`                   | Liefert das nächste Element einer Sequenz an den Aufrufer zurück und merkt sich den Ausführungspunkt der Methode.                                                 |
| `yield break`                    | Beendet die Iteration vorzeitig; danach liefert der Iterator keine weiteren Elemente mehr.                                                                        |
| Spezifischer Iterator            | Iterator-Methode/-Property, die nur einen bestimmten Ausschnitt oder eine besondere Reihenfolge liefert (z.B. `Range`, `Reverse`).                                |
| Extension Method                 | Statische Methode, die sich syntaktisch so aufrufen lässt, als wäre sie Instanzmethode eines bestehenden Typs (`this`-Parameter).                                 |
| Deferred Evaluation              | Verzögerte Ausführung: Iterator-Logik wird erst beim Aufruf von `MoveNext()` (z.B. im `foreach`) ausgeführt, nicht beim Erzeugen des `IEnumerable`/`IEnumerator`. |

## 3. Hauptinhalte

### 3.1 `foreach`-Loop und Iterator-Grundkonzept

Ein klassischer `foreach` über eine Liste:

```csharp
List<int> list = new() { 1, 2, 3, 4, 5, 6 };

foreach (int i in list)
{
    if (i == 3) continue; // überspringt aktuelle Iteration
    if (i == 5) break;    // beendet gesamte Schleife
    Console.WriteLine(i);
}
// Ausgabe: 1, 2, 4
```

**Voraussetzungen für `collection` im `foreach`:**

- Implementiert `IEnumerable` oder `IEnumerable<T>` **oder**
- Besitzt eine Methode `GetEnumerator()`; deren Rückgabetyp hat:
  - Methode `bool MoveNext()`
  - Property `Current`

Der `foreach`-Loop ist ein reines Compiler-Feature. Der Compiler übersetzt ihn in etwa zu:

```csharp
IEnumerator enumerator = list.GetEnumerator();
try
{
    while (enumerator.MoveNext())
    {
        int i = (int)enumerator.Current;
        if (i == 3) continue;
        if (i == 5) break;
        Console.WriteLine(i);
    }
}
finally
{
    if (enumerator is IDisposable disposable)
        disposable.Dispose();
}
```

Das _Sequenzdiagramm auf Seite 8_ zeigt diesen Ablauf grafisch: Das Programm ruft `GetEnumerator()`, dann fortlaufend `MoveNext()` und liest jeweils `Current`, bis `MoveNext()` `false` zurückgibt.

**Visualisierung: `foreach`-Ablauf**

```mermaid
flowchart TD
  A[Start foreach] --> B[GetEnumerator()]
  B --> C{MoveNext()==true?}
  C -->|Nein| F[Schleife endet]
  C -->|Ja| D[elem = Current]
  D --> E[Loop-Body ausführen]
  E --> C
```

### 3.2 Iterator-Interfaces: `IEnumerable<T>` und `IEnumerator<T>`

Die Folien definieren die nicht-generischen und generischen Varianten:

```csharp
public interface IEnumerable
{
    IEnumerator GetEnumerator();
}

public interface IEnumerator
{
    object Current { get; }
    bool MoveNext();
    void Reset();
}

public interface IEnumerable<out T> : IEnumerable
{
    IEnumerator<T> GetEnumerator();
}

public interface IEnumerator<out T> :
    IDisposable, IEnumerator
{
    new T Current { get; }
}
```

**Wichtige Punkte:**

- Mehrere aktive Iteratoren gleichzeitig sind erlaubt – jedes Enumerator-Objekt muss seinen Zustand vollständig selbst halten.
- Während einer Iteration sollte die Collection nicht strukturell verändert werden, sonst kann es zu unerwarteten Effekten kommen.

**Implementationsbeispiele (klassisch, ohne `yield`):**

- Nicht-generisch: `MyList : IEnumerable` mit verschachtelter `MyEnumerator : IEnumerator`.
- Generisch: `MyIntList : IEnumerable<int>` mit `MyIntEnumerator : IEnumerator<int>`, plus expliziter Implementierung von `IEnumerable.GetEnumerator()`.

Fazit der Folien: Das ist relativ viel Boilerplate – Enter `yield`…

### 3.3 Iterator-Methoden mit `yield return` / `yield break`

Eine **Iterator-Methode** erkennt man daran, dass sie:

- `IEnumerator` oder `IEnumerator<T>` (oder typischerweise `IEnumerable<T>`) zurückgibt
- mindestens ein `yield return` (oder `yield break`) enthält

Beispiel:

```csharp
class MyIntList
{
    public IEnumerator<int> GetEnumerator()
    {
        yield return 1;
        yield return 3;
        yield break; // beendet die Sequenz
        yield return 6; // wird nie erreicht
    }
}
```

- `yield return expr;`
  - Pausiert die Methode und liefert `expr` als nächstes Element an den Aufrufer.

- `yield break;`
  - Beendet die Iteration; weitere `MoveNext()`-Aufrufe liefern `false`.

**Compiler-Output (vereinfacht, siehe _Seite 19_):**

Der Compiler erzeugt eine verschachtelte Klasse `__Enumerable1`, die `IEnumerable<int>` und `IEnumerator<int>` implementiert, mit Feldern für `__state` und `__current` sowie einer `MoveNext()`-State-Maschine. `Reset()` wirft `NotSupportedException`.

Damit reduziert sich der von Hand zu schreibende Code drastisch – die Logik bleibt im lesbaren `for`/`while` + `yield`-Code.

### 3.4 Spezifische Iteratoren: `Range` und `Reverse`

Iteratoren können mehr als nur die „Hauptiteration“ bereitstellen. Beispielklasse:

```csharp
class MyIntList
{
    private int[] _x = new int[10];

    // Standard-Iterator (für foreach über MyIntList)
    public IEnumerator<int> GetEnumerator()
    {
        for (int i = 0; i < _x.Length; i++)
            yield return _x[i];
    }

    // Spezifische Iterator-Methode
    public IEnumerable<int> Range(int from, int to)
    {
        for (int i = from; i < to; i++)
            yield return _x[i];
    }

    // Spezifisches Iterator-Property
    public IEnumerable<int> Reverse
    {
        get
        {
            for (int i = _x.Length - 1; i >= 0; i--)
                yield return _x[i];
        }
    }
}
```

**Verwendung:**

```csharp
MyIntList list = new();

// Standard
foreach (int elem in list) { /* ... */ }

// Spezifische Methode
foreach (int elem in list.Range(2, 7)) { /* ... */ }

// Spezifisches Property
foreach (int elem in list.Reverse) { /* ... */ }
```

- Rückgabewert von Range/Reverse ist `IEnumerable<int>` (nicht `IEnumerator<int>`), was sich gut mit LINQ & Extension Methods kombinieren lässt.

### 3.5 Extension Methods

Extension Methods wirken so, als würde man vorhandene Typen um Methoden erweitern, ohne ihre Definition zu verändern.

**Beispiel `ToStringSafe`:**

```csharp
public static class ExtensionMethods
{
    public static string ToStringSafe(this object obj)
    {
        return obj == null
            ? string.Empty
            : obj.ToString();
    }

    public static void Test()
    {
        int myInt = 0;
        object myObj = new();

        myInt.ToStringSafe(); // ok
        myObj = null;
        myObj.ToStringSafe(); // ok, gibt ""
    }
}
```

**Regeln:**

- Methode liegt in einer **statischen Klasse** und ist selbst `static`.
- Erster Parameter hat ein vorangestelltes `this` ⇒ gibt an, auf welchem Typ die Methode „erscheint“.
- Kein Zugriff auf `private`/`protected` Member des Zieltyps.
- Sichtbar nur, wenn der Namespace der statischen Klasse per `using` importiert ist.
- Bei Namenskollision gewinnt immer die echte Instanzmethode des Typs.
- Funktioniert für Klassen, Structs, Interfaces, Delegates, Arrays etc.

**Nur Compiler-Syntax:** Der Aufruf

```csharp
1.ToStringSafe();
```

wird zu

```csharp
ExtensionMethods.ToStringSafe(1);
```

übersetzt; der `object`-Typ selbst „kennt“ diese Methode gar nicht.

### 3.6 Deferred Evaluation

Iteratoren (insb. mit `yield`) werden **verzögert** ausgewertet: Weder der Aufruf von `GetEnumerator()` noch das Erzeugen eines `IEnumerable<T>` aus `Range` führt den Body der Iterator-Methode aus. Erst `MoveNext()` startet die Ausführung.

Beispiel aus den Folien:

```csharp
MyIntList list = new();

// Noch keine Ausführung
IEnumerator<int> e1 = list.GetEnumerator();
IEnumerable<int> e21 = list.Range(1, 10);
IEnumerator<int> e22 = e21.GetEnumerator();

// Jetzt Ausführung
e1.MoveNext();
int i1 = e1.Current;

e22.MoveNext();
int i2 = e22.Current;

// und natürlich im foreach
foreach (int i in e21) { /* ... */ }
```

Das _Diagramm auf Seite 31_ hebt hervor: erst `MoveNext()` im `while` (bzw. im syntaktischen Zucker `foreach`) durchläuft den Iterator-Code.

### 3.7 Extension Methods + Iteratoren = Query-Operatoren

Die Folien implementieren zwei LINQ-artige Operatoren: `OstWhere` und `OstOfType`.

```csharp
static class OstExtensions
{
    public static IEnumerable<T> OstWhere<T>(
        this IEnumerable<T> source,
        Predicate<T> predicate)
    {
        foreach (T item in source)
        {
            if (predicate(item))
                yield return item;
        }
    }

    public static IEnumerable<T> OstOfType<T>(
        this IEnumerable source)
    {
        foreach (object item in source)
        {
            if (item is T)
                yield return (T)item;
        }
    }
}
```

**Anwendung:**

```csharp
object[] list = { 4, 3.5, "abc", 3, 6 };

IEnumerable<int> res = list
    .OstOfType<int>()
    .OstWhere(k => k % 2 == 0);

foreach (int i in res)
    Console.WriteLine(i);
```

Der Code filtert erst alle `int`-Einträge heraus, dann nur die geraden. Die Folie zeigt auch die äquivalente Schreibweise ohne Erweiterungssyntax:

```csharp
IEnumerable<int> res =
    OstExtensions.OstWhere(
        OstExtensions.OstOfType<int>(list),
        k => k % 2 == 0);
```

Das _Diagramm auf Seite 34_ illustriert, wie `MoveNext()` des äußeren Enumerators die inneren Iteratoren kaskadenartig anstößt: Zuerst fragt der `Where`-Enumerator den `OfType`-Enumerator, der wiederum vom Array-Enumerator liest. Jedes Element durchläuft diese Pipeline nur, wenn es tatsächlich vom Client abgefragt wird – typische **Deferred Evaluation**.

### 3.8 Alternative Visualisierung (LaTeX)

Formal kann man die kombinierte OstOfType/OstWhere-Operation so auffassen:

```latex
\[
\mathrm{OstWhere}(\mathrm{OstOfType}_{\mathbb{Z}}(S),\ p)
= \{\, x \in S \mid x \in \mathbb{Z} \land p(x) \,\}
\]

\[
\text{mit } S = \{4, 3.5, "abc", 3, 6\},\
p(x) :\Leftrightarrow x \bmod 2 = 0
\]
```

Das Ergebnis ist die Menge aller geraden ganzen Zahlen aus `S`, also ({4, 6}).

## 4. Zusammenhänge und Interpretation

- `foreach` abstrahiert die eigentliche Logik von `GetEnumerator()`, `MoveNext()` und `Current` weg – solange ein Typ dem Muster von `IEnumerable`/`IEnumerator` entspricht, funktioniert er im `foreach`.
- Iterator-Methoden mit `yield` kapseln den Zustandsautomaten des Iterators im Compiler-Generat; der eigene Code konzentriert sich auf die logische Reihenfolge der Elemente.
- Spezifische Iteratoren (`Range`, `Reverse`) machen Collections flexibler, ohne zusätzliche Arrays oder Listen anlegen zu müssen.
- Extension Methods ermöglichen, generische Query-Operatoren auf `IEnumerable` aufzusetzen, ohne bestehende Types anfassen zu müssen.
- Deferred Evaluation sorgt dafür, dass diese Operatoren erst beim tatsächlichen Iterieren Arbeit leisten – so lassen sie sich effizient verketten und auf potenziell grosse Sequenzen anwenden.

## 5. Beispiele und Anwendungen

1. **Eigene Collection durchsuchen**
   - Erstelle eine Klasse `IntBuffer` mit interner `int[]`-Struktur und implementiere:
     - Standard-Iterator (alle Elemente),
     - `IEnumerable<int> Even()` (nur gerade Zahlen),
     - `IEnumerable<int> Skip(int n)`.

2. **Extension Method `Chunk`**
   - `IEnumerable<IEnumerable<T>> Chunk<T>(this IEnumerable<T> source, int size)`
   - Liefert die Sequenz in „Blöcken“ der angegebenen Grösse (Iterator-Methoden + `yield`).

3. **Sichere ToString-Varianten**
   - Ergänze `ToStringSafe` um eine generische Variante `ToStringSafe<T>(this T obj, string fallback)`.

4. **Deferred Evaluation beobachten**
   - Erzeuge eine Iterator-Methode mit `Console.WriteLine` im Body und prüfe, **wann** die Ausgabe im Vergleich zur Erstellung des `IEnumerable` erfolgt (nur bei `MoveNext()` / `foreach`).

5. **Eigene LINQ-artige Operatoren**
   - Implementiere `TakeWhile` und `SkipWhile` als Extension Methods auf `IEnumerable<T>` mit `yield` und teste sie mit Arrays und Listen.

## 6. Zusammenfassung / Takeaways

- `foreach` basiert auf dem Iterator-Pattern mit `IEnumerable` und `IEnumerator` – der Compiler übersetzt den Loop in eine `while`-Schleife mit Enumerator und `Dispose`.
- Eigene Enumerator-Klassen sind möglich, aber aufwändig; Iterator-Methoden mit `yield` nehmen einem die State-Machine-Arbeit ab.
- Spezifische Iteratoren (Methoden/Properties) liefern Ausschnitte oder alternative Traversierungen einer Collection, ohne zusätzliche Datenstrukturen.
- Extension Methods erlauben LINQ-ähnliche, verkettbare Abfragen auf beliebigen `IEnumerable`-Typen.
- Deferred Evaluation ist zentral: Iteratoren arbeiten „on demand“ und können so Speicher und Rechenzeit sparen, insbesondere bei langen Pipelines.

## 7. Lernhinweise

- Implementiere zunächst `IEnumerable<T>` / `IEnumerator<T>` **von Hand**, um das Muster zu verstehen – und ersetze danach alles durch `yield`-Iteratoren.
- Nutze den Debugger, um in eine Iterator-Methode hineinzuspringen und zu sehen, wie oft sie bei einem `foreach` tatsächlich betreten wird.
- Schreibe mehrere kleine Extension Methods auf `IEnumerable<T>` (z.B. `FirstOrDefaultSafe`, `CountIf`) und verkette sie; beobachte, wann sie ausgeführt werden.
- Schaue dir bei Interesse das im Foliensatz verlinkte Video zu Deferred Evaluation an (Seite 35) – dort werden Performance-Auswirkungen praktisch demonstriert.

## 8. Vertiefung / weiterführende Konzepte

- LINQ-Standardoperatoren (`Where`, `Select`, `OrderBy`, ...) und deren Implementierung mit `IEnumerable<T>` und `yield`.
- Asynchrone Iteratoren (`IAsyncEnumerable<T>`, `await foreach`) in neueren C#-Versionen.
- Performance-Themen: Materialisierung (`ToList`, `ToArray`) vs. reine Iteratoren; Mehrfachenumeration.
- Iteratoren im Zusammenspiel mit Streams und Datenbanken (Lazy Loading).

## 9. Quellen & Literatur (IEEE)

[1] M. Bauer, “C# Grundlagen – Iteratoren,” Foliensammlung, OST – Ostschweizer Fachhochschule, Departement Informatik, Rapperswil, 2025.

[2] Microsoft Corporation, “Custom Iterators with yield,” _MSDN Magazine_, 2017 (im Sequenzdiagramm auf Folie 8 referenziert).
