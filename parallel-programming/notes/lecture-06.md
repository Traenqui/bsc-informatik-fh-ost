# Parallel Programming – Week 6 Summary

**Topic:** Asynchronous Programming
**Instructor:** Mitra Purandare
**Institution:** OST – Ostschweizer Fachhochschule

---

## 1. Learning Goals

* Understand models of **asynchronous programming**
* Implement **non-blocking UI** patterns
* Apply the **C# `async`/`await`** programming model

---

## 2. Why Asynchronous Programming?

### Problems with Blocking

* Blocking operations (e.g. long calculations, I/O, database) waste CPU cycles.
* Caller thread is stalled unnecessarily.

### Solution: Asynchronous Execution

* Launch task using a separate thread:

```csharp
var task = Task.Run(() => LongOperation());
...
var result = task.Result; // Wait for result later
```

---

## 3. Types of Asynchrony

| Type           | Description                                           |
| -------------- | ----------------------------------------------------- |
| Caller-centric | Caller waits to get the result (e.g. `await`)         |
| Callee-centric | Task pushes result to a continuation (e.g. `.then()`) |

---

## 4. Task Continuations (C#)

### Sequential Continuations:

```csharp
Task.Run(() => step1())
  .ContinueWith(t => step2())
  .ContinueWith(t => step3());
```

### Parallel Continuations:

```csharp
Task.WhenAll(task1, task2)
  .ContinueWith(t => handleBoth());
Task.WhenAny(task1, task2)
  .ContinueWith(t => handleFirst());
```

### Exception Handling:

* Unhandled exceptions are ignored in fire-and-forget tasks.
* Handle via:

  * `task.Wait()`
  * `TaskScheduler.UnobservedTaskException`

---

## 5. Java: CompletableFuture

### Example:

```java
CompletableFuture.supplyAsync(() -> longOperation())
  .thenApplyAsync(result -> 2 * result)
  .thenAcceptAsync(System.out::println);
```

### Key Features:

* Asynchronous pipeline chaining
* Based on the `CompletionStage<T>` interface
* Replaces callback hell with fluent, reactive-style chains

---

## 6. Non-Blocking GUIs

### UI Thread Model:

* GUIs (Swing/.NET/Android) run on a **single UI thread**
* Only the UI thread may **access UI components**
* Long tasks must run on background threads
* Updates to the UI must be **dispatched** back to the UI thread

---

## 7. Java Swing Example

```java
button.addActionListener(event -> {
  var url = textField.getText();
  CompletableFuture.runAsync(() -> {
    var text = download(url);
    SwingUtilities.invokeLater(() -> textArea.setText(text));
  });
});
```

* `runAsync()` performs background work
* `invokeLater()` safely updates the GUI

---

## 8. .NET WPF Example

```csharp
void buttonClick(...) {
  var url = textBox.Text;
  Task.Run(() => {
    var text = Download(url);
    Dispatcher.InvokeAsync(() => {
      label.Content = text;
    });
  });
}
```

* Uses `Dispatcher.InvokeAsync()` to switch context to UI thread

---

## 9. `async` / `await` in C\#

### Benefits:

* Readable syntax for asynchronous flow
* Avoids callback chains
* Code appears linear

### Example:

```csharp
async void buttonClickAsync(...) {
  var url = textBox.Text;
  var text = await DownloadAsync(url);
  label.Content += text;
}
```

### Async Method Declaration:

```csharp
async Task<string> DownloadAsync(string url) {
  var client = new HttpClient();
  string result = await client.GetStringAsync(url);
  return result;
}
```

---

## 10. Execution Model

### General Flow:

* Method runs **synchronously** up to first `await`
* Remaining code is compiled as a **continuation**
* Continuation runs:

  * In worker thread (non-UI scenario)
  * In UI thread (UI scenario)

---

## 11. Async Method Behaviors

| Return Type | Behavior                                  |
| ----------- | ----------------------------------------- |
| `void`      | Fire-and-forget (only for event handlers) |
| `Task`      | No return, allows `await`                 |
| `Task<T>`   | Returns result of type `T`                |

### Special Rules:

* `await` only allowed in `async` methods
* If no `await` is used, the method runs synchronously

---

## 12. Async/Await Without `await`

### Problem:

```csharp
async Task<bool> IsPrimeAsync(long n) {
  for (...) {
    if (...) return false;
  }
  return true;
}
```

* Runs synchronously
* Causes compiler warning

### Fix:

```csharp
public async Task<bool> IsPrimeAsync(long number) {
  return await Task.Run(() => {
    for (...) {
      if (...) return false;
    }
    return true;
  });
}
```

---

## 13. Design Considerations

* Async methods often lead to a **“viral effect”** – caller must also be async.
* Complicates method signatures and debugging.
* Libraries often provide both **sync** and **async** versions.

---

## 14. Summary and Takeaways

* Asynchronous programming avoids blocking and enables responsive applications
* Continuation patterns allow chaining of asynchronous tasks
* `async`/`await` in C# simplifies readable asynchronous code
* GUI applications must offload long tasks and dispatch updates safely

---

## 15. Further Reading

* [Java CompletableFuture Overview (InfoQ)](https://www.infoq.com/articles/Functional-Style-Callbacks-Using-CompletableFuture)
* Goetz et al., *Java Concurrency in Practice*, Addison-Wesley – Chapter 9 (GUI Applications)
* Stephen Cleary, *Best Practices in Asynchronous Programming*, MSDN Magazine, 2013
* Stephen Toub, *Async Performance: Understanding the Costs of Async/Await*, MSDN Magazine, 2011
* Erik Meijer, *Your Mouse is a Database*, Communications of the ACM, May 2012
