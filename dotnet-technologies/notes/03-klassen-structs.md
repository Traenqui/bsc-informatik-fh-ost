# C# Grundlagen – Klassen und Structs

## Übersicht

- **Thema der Einheit:**
  Klassen und Structs in C#: Speicherverhalten, Felder, Methoden & Parameter, Properties, Expression-bodied Members, Indexer, Konstruktoren, Operator-Überladung, partielle Klassen/Methoden, Destruktoren, Überblick über Operatoren.
- **Dozent:** Manuel Bauer
- **Lernziele:**
  - Konzept und Unterschiede von Klassen und Structs in C# erklären
  - Parameterübergabe-Mechanismen (`value`, `ref`, `out`, `params`, optionale & benannte Parameter) sicher anwenden
  - Properties (inkl. Auto-, field-backed, init-only) einsetzen
  - Nutzen von Indexern verstehen und implementieren
  - Operatoren sinnvoll überladen
  - Die Konzepte in praktischen Programmieraufgaben anwenden

## 1. Einführung / Kontext

Diese Einheit vertieft die C#-Grundlagen auf Typ-Ebene: Wie werden Objekte angelegt, wie sieht der Unterschied zwischen Klassen (Referenztypen) und Structs (Werttypen) aus, wie werden Daten gekapselt (Felder, Properties), wie ruft man Methoden mit verschiedenen Parameterarten auf, und wie können Operatoren und der Index-Zugriff überladen werden.
Abschliessend gibt es einen Überblick über Destruktoren und Operatoren (als Selbststudium), inklusive Reihenfolge und Überlaufverhalten.

## 2. Zentrale Begriffe und Definitionen

| Begriff                  | Definition                                                                                                                                                                               |
| ------------------------ | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Klasse                   | Referenztyp, liegt auf dem Heap; unterstützt Vererbung, kann Basisklasse sein und Interfaces implementieren. Instanzen werden mit `new` erzeugt.                                         |
| Struct                   | Werttyp, liegt auf dem Stack oder inline in einem anderen Objekt. Keine eigene Vererbungshierarchie (nur von `System.ValueType`), aber Interfaces möglich. Wird mit `new` initialisiert. |
| Feld                     | Variable in einem Typ (Instanz- oder statisch). Kann `const`, `readonly` oder frei beschreibbar sein.                                                                                    |
| `const`                  | Feld, dessen Wert zur Compilezeit feststehen muss und nicht geändert werden kann.                                                                                                        |
| `readonly`               | Feld, das nur in Deklaration oder im Konstruktor geschrieben werden darf; Wert muss nicht zur Compilezeit feststehen.                                                                    |
| Nested Type              | In einem anderen Typ geschachtelter Typ (Klasse, Struct, Interface, Enum, Delegate).                                                                                                     |
| Statische Klasse         | Klasse, die nur statische Member enthält, nicht instanziierbar und implizit `sealed`.                                                                                                    |
| Statisches `using`       | `using static` importiert statische Members und Nested Types einer Klasse/Enum, sodass man sie ohne Klassennamen verwenden kann.                                                         |
| Methode                  | Funktion oder Prozedur eines Typs, ggf. `static`. Kann überladen werden.                                                                                                                 |
| Parameterarten           | `value` (Standard), `ref`, `out`, `params`, optionale Parameter, benannte Parameter.                                                                                                     |
| Property                 | „Smartes Feld“ mit `get`/`set`-Zugriff; Compiler erzeugt passende Methoden. Ersetzt klassische Getter/Setter-Methoden.                                                                   |
| Auto-Property            | Kurzschreibweise, bei der das Backing Field vom Compiler erzeugt wird (`public int Length { get; set; }`).                                                                               |
| Field-backed Property    | Property, das ein implizites Feld über das Schlüsselwort `field` im `get`/`set` verwendet.                                                                                               |
| Init-only Property       | Property mit `init`-Setter, das nur bei Initialisierung (Konstruktor, Objekt-/`with`-Initializer) gesetzt werden darf.                                                                   |
| Expression-bodied Member | Member, das nur aus einem Ausdruck besteht, mit `=>` anstelle eines Blockes implementiert.                                                                                               |
| Konstruktor              | Spezielle Methode zur Initialisierung eines neuen Objekts/Structs; kann überladen, `static` oder privat sein.                                                                            |
| Primary Constructor      | Kurzschreibweise, bei der Konstruktor-Parameter der Klasse/Struct direkt im Typkopf deklariert werden und im Typ verwendbar sind.                                                        |
| Destruktor               | Finalizer einer Klasse (`~MyClass()`), der vom Garbage Collector aufgerufen wird, um Ressourcen freizugeben.                                                                             |
| Operator Overloading     | Überladen von Operatoren (`+`, `-`, `==`, …) als statische Methoden mit `operator`.                                                                                                      |
| Indexer                  | `this[...]`-Member, das einer Klasse Array-ähnlichen Zugriff verleiht; Compiler erzeugt `get_Item`/`set_Item`.                                                                           |
| Partielle Klasse/Methode | Typ/Methode, deren Implementierung auf mehrere Dateien aufgeteilt werden kann (`partial`).                                                                                               |

## 3. Hauptinhalte

### 3.1 Klassen vs. Structs

- **Klasse (Reference Type)**
  - Liegt auf dem Heap, Variable enthält eine Referenz.
  - Vererbung: von Basisklasse ableiten und selbst Basisklasse sein.
  - Interfaces implementieren möglich.
  - Instanziierung:

    ```csharp
    Stack s = new Stack(10);
    ```

- **Struct (Value Type)**
  - Liegt auf dem Stack oder inline als Teil eines anderen Objekts.
  - Keine eigene Vererbungshierarchie (außer implizit von `ValueType`), nicht als Basistyp nutzbar.
  - Interfaces implementierbar.
  - Instanziierung:

    ```csharp
    Point p = new Point(2, 3);
    struct Point
    {
        int _x, _y;
        public Point(int x, int y) { /* ... */ }
    }
    ```

**Wann Structs verwenden?** (Empfehlung der Folie)

- Repräsentiert _einen_ einzelnen Wert (z.B. `Point`, `Complex`, `Date`)
- Größe < 16 Byte
- _Immutable_ Design (keine verändernden Methoden / alle Felder readonly)
- Wird nicht häufig geboxt
- Kurzlebig oder meist in andere Objekte eingebettet
- In allen anderen Fällen → **Klasse** bevorzugen.

**Instanziierung – target-typed `new`**

```csharp
Stack s = new Stack(10); // klassisch
Stack s2 = new(10);      // Target-typed new
```

Der Typ ergibt sich hier von der Zielvariablen `Stack`.

### 3.2 Felder, statische Klassen & Nested Types

#### Felder, `const`, `readonly`

```csharp
class MyClass
{
    int _value = 0;
    const long Size = int.MaxValue / 3 + 1234;
    static readonly DateTime _date1 = DateTime.Now;
    readonly DateTime _date2;

    public MyClass()
    {
        _date2 = DateTime.Now;
    }

    public void DoSomething()
    {
        _value = 10;
        _date2 = DateTime.Now; // Compilerfehler
    }
}
```

- Felder werden in Deklarationsreihenfolge initialisiert.
- `const`: muss Compiletime-konstant sein; kann nie geändert werden.
- `readonly`: kann in Deklaration **oder** im Konstruktor gesetzt werden; danach unveränderlich.

#### Nested Types

- Innere Klasse hat Zugriff auf **private** Member der äußeren Klasse.
- Äußere Klasse sieht nur `public` Member der inneren.
- Fremde Klassen können die innere Klasse nutzen, wenn sie `public` ist:

```csharp
public class OuterClass
{
    private int _outerValue;
    InnerClass _innerInstance = new();

    public void OuterMethod()
    { _innerInstance.InnerMethod(this); }

    public class InnerClass
    {
        public void InnerMethod(OuterClass outerClass)
        {
            outerClass._outerValue = 123;
        }
    }
}
```

Unterschied zu Java: C#-Nested Types sind **nicht** fest an eine Instanz gebunden.

#### Statische Klassen & `using static`

```csharp
static class MyMath
{
    public const double Pi = 3.14159;
    public static double Sin(double x) { /* ... */ }
}
```

- Nur statische Member, nicht instanziierbar, `sealed`.
- Typische Einsatzzwecke: Hilfsfunktionen, Konstantensammlungen, Extension Methods.

**Statisches Using:**

```csharp
using static System.Console;
using static System.Math;
using static System.DayOfWeek;

WriteLine(Sqrt(3 * 3 + 4 * 4));
WriteLine(Friday - Monday);
```

→ Importiert statische Member und Nested Types; Namenskonflikte werden wie bei Overloads behandelt.

### 3.3 Methoden & Parameter

#### Statische vs. Instanzmethoden

```csharp
class MyClass
{
    public void Print() { }        // Instanz
    public int GetValue() { return 0; }

    public static void PrintStatic() { }      // statisch
    public static int GetValueStatic() => 0;
}
```

Aufruf:

```csharp
MyClass mc = new();
mc.Print();
MyClass.PrintStatic();
```

#### Parameter-Arten

1. **Value-Parameter (Standard)** – call by value

   ```csharp
   void IncVal(int x) { x = x + 1; }
   void Test()
   {
       int value = 3;
       IncVal(value);  // value bleibt 3
   }
   ```

2. **`ref`-Parameter** – call by reference

   ```csharp
   void IncRef(ref int x) { x = x + 1; }
   void Test()
   {
       int value = 3;
       IncRef(ref value); // value == 4
   }
   ```

3. **`out`-Parameter** – Ausgabe-/Initialisierungsparameter

   ```csharp
   void Init(out int a, out int b)
   {
       a = 1; b = 2;         // Müssen gesetzt werden
   }

   bool success = int.TryParse("123a", out int i1);
   bool success2 = int.TryParse("123a", out _); // Discard
   ```

4. **`params`-Array** – variable Argumentliste

   ```csharp
   void Sum(out int sum, params int[] values)
   {
       sum = 0;
       foreach (int i in values) sum += i;
   }

   Sum(out int s1);        // 0
   Sum(out int s2, 1, 2);  // 3
   ```

5. **Optionale Parameter** – Default-Werte

   ```csharp
   void Sort(int[] array, int from = 0, int to = -1,
             bool ascending = true, bool ignoreCase = false) { }

   Sort(a);                 // nur Pflichtparam.
   Sort(a, 0, -1);          // einige übersprungen
   ```

   Default-Werte müssen zur Compilezeit berechenbar sein (konstanter Ausdruck, `new MyStruct()` oder `default`).

6. **Benannte Parameter** – Aufruf per Namen

   ```csharp
   Sort(a, ascending: false);
   Sort(array: a, from: 2, to: 4, ignoreCase: true);
   ```

   Positionsparameter zuerst, Pflichtparameter müssen angegeben werden.

#### Überladen von Methoden & Konflikte

- Erlaubt: verschiedene Signaturen (Anzahl, Typ oder Art der Parameter).
- Nicht Unterscheidungsmerkmale:
  - Rückgabetyp
  - `params` vs. „normales“ Array
  - optionale Parameter (Default-Werte)

Beispiel Mehrdeutigkeit:

```csharp
void Test(int x, long y) { }
void Test(long x, int y) { }

short s = 0;
long l = 0;
Test(l, s);   // OK
Test(s, s);   // Compilerfehler: Mehrdeutig
```

### 3.4 Properties

#### Motivation & Grundsyntax

Properties ersetzen explizite `getX`/`setX`-Methoden:

```csharp
class MyClass
{
    private int _length;

    public int Length
    {
        get { return _length; }
        set { _length = value; }
    }
}
```

Aufruf:

```csharp
MyClass mc = new();
mc.Length = 12;
mc.Length += 5;
```

Der Compiler erzeugt intern `get_Length()` und `set_Length(int value)`.

#### Read-Only / Write-Only / Private Setter

```csharp
public int LengthReadOnly   // nur get
{
    get { return _length; }
}

public int LengthWriteOnly  // nur set
{
    set { _length = value; }
}

public int LengthPrivateSet // privater Setter
{
    get { return _length; }
    private set { _length = value; }
}
```

#### Auto-implemented Properties & Field-backed Properties

**Auto-Property:**

```csharp
public int LengthAuto { get; set; }
```

Der Compiler generiert ein verstecktes Backing Field.

**Field-backed Property:**

```csharp
public int LengthField
{
    get;
    set => field = value > 0 ? value : 0;
}
```

Hier ersetzt `field` das implizite Backing Field im Setter.

#### Objektinitialisierung & Init-only Setter

**Object Initializer:**

```csharp
MyClass mc = new()
{
    Length = 1,
    Width = 2
};
```

Compiler expandiert das zu: `var mc = new MyClass(); mc.Length = 1; ...`

**Init-only Property:**

```csharp
public int LengthInitOnly { get; init; }

MyClass mc = new()
{
    LengthInitOnly = 1
};

mc.LengthInitOnly = 2; // Compilerfehler
```

Init-only Properties können nur während der Initialisierung (Konstruktor, Object-/`with`-Initializer) gesetzt werden.

### 3.5 Expression-bodied Members

Für Member mit genau einem Ausdruck.

```csharp
public class Examples
{
    private int _value;

    // Konstruktor / Destruktor
    public Examples(int v) => _value = v;
    ~Examples() => _value = 0;

    // Methoden
    public int Sum(int x, int y) => x + y;
    public void Print() => Console.WriteLine("...");

    // Property
    public int Zero => 0;

    public int Value
    {
        get => _value;
        set => _value = value;
    }
}
```

Spart Klammern und Boilerplate bei einfachen Implementierungen.

### 3.6 Konstruktoren, Default-Werte & Initialisierungsreihenfolge

#### Instanz-Konstruktoren & Overloading

```csharp
class MyClass
{
    private int _x, _y;

    public MyClass() : this(0, 0) { }
    public MyClass(int x) : this(x, 0) { }

    public MyClass(int x, int y)
    {
        _x = x;
        _y = y;
    }
}
```

- Konstruktoren können sich über `this(...)` gegenseitig aufrufen.
- Basis-Klassen-Konstruktoren werden mit `base(...)` aufgerufen.

**Initialisierungs-Workflow (vereinfachte Klasse)**

```mermaid
flowchart TD
  A[new MyClass()] --> B[Feld-Initialisierung]
  B --> C[Instanz-Konstruktor Body]
  C --> D[Objekt fertig initialisiert]
```

#### Primary Constructors

```csharp
class Point(int x, int y)
{
    public int X { get; } = x;
    public int Y { get; } = y;

    public void Test()
        => Console.WriteLine($"Point: {x}/{y}");
}
```

- Parameter `x`/`y` stehen im ganzen Typ zur Verfügung (sollten aber wie Felder behandelt werden).
- Aufruf: `var p = new Point(1, 2);`

#### Klassen vs. Struct-Konstruktoren

- **Klasse:**
  - Parameterloser Konstruktor wird automatisch generiert, wenn keiner existiert.
  - Wird **nicht** generiert, sobald ein eigener (auch privater) Konstruktor definiert ist.

- **Struct:**
  - Parameterloser Konstruktor ist immer vorhanden (von der Laufzeit erzwungen).
  - Wird auch zusätzlich zum eigenen Konstruktor generiert.
  - Jeder benutzerdefinierte Konstruktor muss **alle** Felder initialisieren, sonst Compilerfehler.

#### Default-Werte & `default`-Literal

Die Tabelle auf _Seite 40_ listet Standardwerte, z.B.:

$$
\texttt{int}: 0,\quad \texttt{bool}: \text{false},\quad \texttt{class}: \text{null}
$$

Verwendung im Code:

```csharp
int x = default(int);
int y = default;      // Typ wird aus Kontext abgeleitet
```

#### Statische Konstruktoren & Initialisierungsreihenfolge

- Statische Konstruktoren:
  - immer parameterlos, keine Sichtbarkeit, max. einer pro Typ
  - werden **genau einmal** ausgeführt: bei erster Instanziierung oder beim ersten Zugriff auf ein statisches Member.

Die Diagramme auf den _Seiten 42–44_ zeigen die Reihenfolge:

1. Statische Felder eines Typs
2. Statischer Konstruktor
3. Instanzfelder
4. Instanz-Konstruktor

Bei Vererbung: zuerst statische Teile von abgeleiteten Typen, dann von Basistypen; bei Instanzierung: erst Basis-Klasse, dann Subklasse.

### 3.7 Operator Overloading

#### Regeln & Beispiel

- Methode muss `static` sein.
- Schlüsselwort `operator` + Operatorzeichen.
- Mindestens ein Parameter muss vom Typ der Klasse sein.
- Einige Operatoren müssen paarweise überladen werden (`==`/`!=`, `<`/`>`, `<=`/`>=`, `true`/`false`).

```csharp
class Point
{
    private int _x, _y;
    public Point(int x, int y)
    { _x = x; _y = y; }

    public static Point operator ~(Point a)
        => new(-a._x, -a._y);

    public static Point operator +(Point a, Point b)
        => new(a._x + b._x, a._y + b._y);
}
```

Verwendung:

```csharp
Point p1 = new(1, 2);
Point p2 = new(10, 20);
Point sum = p1 + p2;   // (11, 22)
Point neg = ~p1;       // (-1, -2)
```

Die Tabellen auf _Seiten 64–65_ geben einen Überblick, welche Operatoren überladen werden dürfen.

### 3.8 Indexer

Indexer „überladen“ den `[]`-Zugriff für eigene Klassen.

```csharp
class MyClass
{
    private string[] _arr = new string[10];

    public string this[int index]
    {
        get => _arr[index];
        set => _arr[index] = value;
    }

    public int this[string search]
    {
        get
        {
            for (int i = 0; i < _arr.Length; i++)
                if (_arr[i] == search) return i;
            return -1;
        }
    }
}
```

Verwendung:

```csharp
MyClass mc = new();
mc[0] = "Hello";
string value1 = mc[0];      // "Hello"
int index = mc["Hello"];    // 0
```

- Schlüsselwort `this` definiert einen Indexer.
- Parameterliste kann beliebige Typen und Dimensionen haben (z.B. `this[int i1, int i2]`).
- Compiler generiert `get_Item`/`set_Item`.

Die „NaiveArray“-Beispiele auf _Seite 54–55_ zeigen einen selbstgebauten Array-Typ, der intern mehrere Felder hat und über Indexer darauf zugreift.

### 3.9 Partielle Klassen & Methoden

#### Partielle Klassen

```csharp
// File1.cs
partial class MyClass
{
    public void Test1() { }
}

// File2.cs
partial class MyClass
{
    public void Test2() { }
}
```

- `partial` muss in **allen** Teilen angegeben werden.
- Sichtbarkeit (z.B. `public`) muss übereinstimmen.
- Angaben wie Basisklasse, Interfaces oder `sealed` gelten für den gesamten Typ und dürfen nicht widersprüchlich sein.

Typische Verwendung: Codegenerator erzeugt einen Teil, Entwickler ergänzt Logik im anderen File.

#### Partielle Methoden

```csharp
partial class MyClass
{
    public void Test1()
    {
        Test1Initialize();
        // ...
        Test1Cleanup();
    }

    partial void Test1Initialize();
    partial void Test1Cleanup();
}

// Andere Datei
partial class MyClass
{
    partial void Test1Initialize() { /* Hook */ }
}
```

- Müssen in einer `partial`-Klasse/Struct stehen.
- Rückgabewert **muss** `void` sein, implizit `private`.
- Können implementiert werden, müssen aber nicht:
  - Ohne Implementation werden Aufrufe beim Kompilieren entfernt (kein Overhead).

### 3.10 Destruktoren (optional)

Destruktoren sind Finalizer, die vom Garbage Collector aufgerufen werden.

```csharp
class MyClass
{
    ~MyClass()
    {
        // Freigabe von Handles, Streams, etc.
    }
}
```

- Nur in Klassen erlaubt, **nicht** in Structs.
- Parameterlos, keine Sichtbarkeit, nur **ein** Destruktor pro Typ.
- Wird von GC nicht-deterministisch aufgerufen → nicht für zeitkritische Aufräumarbeiten verwenden (stattdessen `IDisposable`/`using`-Pattern).

### 3.11 Operatoren – Überblick (Selbststudium)

Die Folien im letzten Teil geben einen systematischen Überblick über C#-Operatoren:

- Kategorien: arithmetisch, vergleichend, logisch, bitweise, Zuweisung, bedingter Operator `?:`, weitere (`is`, `as`, `await`, `sizeof`, `typeof`, …).
- Operatorpriorität (Präzedenz) – Tabellen auf _Seiten 66–67_.
- Arithmetische Operatoren führen zu einem Ergebnis im „kleinstmöglichen geeigneten Typ“, mindestens `int` (z.B. `short + short` ergibt `int`).
- Vergleichsoperatoren (`==`, `!=`) sind für alle Typen definierbar, `<`, `>` etc. nur für numerische, `char`, Enums.
- Logische Operatoren `&&`/`||` verwenden Short-Circuit-Evaluation; bitweise `&`/`\|`/`^` werten beide Seiten immer aus.
- Overflow-Verhalten: Ganzzahl-Überläufe werden standardmässig **nicht** geprüft, können aber mit `checked` erzwungen werden.
- `typeof` liefert `System.Type`, `sizeof` die Speichergröße eines Value Types (für Structs nur in `unsafe`-Code).

## 4. Zusammenhänge und Interpretation

- Klassen und Structs unterscheiden sich vor allem im Speicherlayout (Heap vs. Stack/inline) und im Vererbungsmodell; viele Sprachfeatures (Properties, Methoden, Konstruktoren, Operatoren) funktionieren aber für beide.
- Der Parametermechanismus (`value`, `ref`, `out`, `params`, optionale/benannte Parameter) gibt feine Kontrolle über Schnittstellen – wichtig für API-Design und Performance.
- Properties und Indexer sind reine Compilerkonstrukte, die intern in normale Methoden übersetzt werden, aber eine **feldartige** bzw. **arrayartige** Syntax erlauben.
- Konstruktoren (inkl. statisch, primary) und Initialisierungsreihenfolgen bestimmen, wann welche Felder gültige Werte besitzen – relevant für Bugs rund um „uninitialisierte“ Zustände.
- Operator Overloading, partielle Klassen & Methoden sind vor allem für gut lesbare Domänenmodelle und die Zusammenarbeit mit Codegeneratoren nützlich.

## 5. Beispiele und Anwendungen

1. **2D-Vektor als Struct**
   - Implementiere `struct Vector2` mit `X`, `Y`, `Length`-Property, `+`/`-`-Operatoren und `readonly`-Feldern.
   - Verwende `operator +` und Expression-bodied Members.

2. **Immutable Konfigurationsklasse mit Init-only Properties**

   ```csharp
   class AppConfig
   {
       public string ConnectionString { get; init; }
       public int MaxRetries { get; init; } = 3;
   }

   var cfg = new AppConfig { ConnectionString = "..." };
   ```

3. **Eigener „Dictionary-Light“-Typ mit Indexer**
   - Klasse mit internem Array von Key/Value-Paaren, Zugriff über `this[string key]`.

4. **Partielle Klasse für Codegenerator**
   - Eine Datei vom Generator (z.B. `Customer.g.cs`) mit Properties,
     eine zweite Datei mit `partial class Customer` für eigene Methoden.

5. **Methoden-API mit optionalen und benannten Parametern**
   - `void Log(string message, LogLevel level = LogLevel.Info, bool includeTimestamp = true)`
   - Aufruf in verschiedenen Varianten mit benannten Parametern.

## 6. Zusammenfassung / Takeaways

- **Klassen** sind Referenztypen mit Vererbung, **Structs** sind leichte Werttypen – Structs sparsam und gezielt einsetzen.
- Felder, `const` und `readonly` steuern, wann und wie Werte verändert werden dürfen.
- C#-Methoden unterstützen umfangreiche Parameterkonzepte (`ref`, `out`, `params`, optional, benannt) und Overloading.
- **Properties** und **Indexer** abstrahieren den Zugriff auf interne Daten, ohne die öffentliche API zu ändern.
- Expression-bodied Members vereinfachen den Code bei einzeiligen Implementierungen.
- Konstruktoren (inkl. Primary, statische Konstruktoren) und Initialisierungsreihenfolge sind zentral für korrekt initialisierte Objekte.
- Operator Overloading verbessert die Lesbarkeit, wenn sie intuitiv eingesetzt wird (z.B. für mathematische Typen).
- Partielle Klassen & Methoden trennen generierten und handgeschriebenen Code – wichtig in vielen Frameworks und Tools.

## 7. Lernhinweise

- Schreibe kleine Beispiele zu **jedem** Feature:
  - Klasse vs. Struct mit identischer API und beobachte das Verhalten bei Zuweisungen/Parameterübergabe.
  - Methoden mit `ref`/`out`/`params`/optional/benanntem Parameter.
  - Properties: erst als Auto-Property, dann in „voller“ Form mit Validation.

- Gehe die Initialisierungsreihenfolge anhand eigener Beispiele mit statischen/Instanzfeldern nach – evtl. Debug-Ausgaben im Konstruktor.
- Baue eine kleine Vektor-/Point-Library mit Operator Overloading und Indexern.
- Bearbeite die Selbststudium-Folien zu Operatoren (Rangfolge, Overflows, `checked`, `typeof`, `sizeof`) aktiv:
  - Rechne Beispiele per Hand nach und kontrolliere die Ausgabe im Debugger.

## 8. Vertiefung / weiterführende Konzepte

- **Record Types** und `with`-Expressions (nutzen init-only Properties und Value-based Equality).
- **Generics** und Constraints (`where T : struct/class`) im Zusammenspiel mit Klassen und Structs.
- **IDisposable** & `using`-Pattern als deterministische Alternative zu Destruktoren.
- **User-defined Conversions** (implizite/explizite Cast-Operatoren) als Ergänzung zum Operator Overloading.
- Erweiterungsmethoden in statischen Klassen und LINQ als praktische Anwendung vieler hier gezeigter Konzepte.

## 9. Quellen & Literatur (IEEE)

[1] M. Bauer, “C# Grundlagen – Klassen und Structs,” Foliensammlung, OST – Ostschweizer Fachhochschule, Departement Informatik, Rapperswil, 2025.

[2] Microsoft Corporation, “C# programming guide,” Online: Microsoft Learn, Zugriff: 2025.

[3] Microsoft Corporation, “Design guidelines for struct vs. class,” Online: Microsoft Learn, Zugriff: 2025.
