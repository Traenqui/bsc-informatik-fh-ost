# 📚 **Lecture Notes**

---

## 🗓️ **Course Details**

- **Course Title:** Advanced JavaScript
- **Lecture Title:** JavaScript - Part 2
- **Lecturer Name:** Michael Gfeller
- **Date:** 31.10.2024
- **Lecture Number:** 7

---

## 📝 **Key Topics Covered**

1. Scope in JavaScript
2. Context (`this`) and its Usage
3. Strict Mode (`'use strict'`)
4. Arrow Functions and Object Hashing
5. JavaScript Classes and Modules
6. Modern JavaScript Features
7. Polyfills and Shims
8. JavaScript Style Guides

---

## 🧠 **Learning Objectives**

- Correctly use and debug scope and context in JavaScript.
- Activate and explain the benefits of strict mode.
- Define and use modern JavaScript classes and modules.
- Apply new JavaScript features and provide backward compatibility.
- Understand and follow JavaScript style guides.

---

## 📖 **Detailed Notes**

### **1. Scope in JavaScript**

- **Definition:**

  - Scope defines where variables and functions are accessible.
  - Types:
    - **Global Scope:** Accessible everywhere.
    - **Function Scope:** Local to a function.
    - **Block Scope:** Limited to `{}` blocks (using `let` and `const`).
    - **Module Scope:** File-based, created by ES6 modules.

- **Best Practices:**

  - Use `let` and `const` for block scoping.
  - Avoid polluting the global namespace.

- **Closures:**
  - Functions retain access to variables in their outer scope even after the outer function has returned.
  - Example:
    ```javascript
    function createClosure() {
      let value = 1;
      return () => value;
    }
    let closureFn = createClosure();
    console.log(closureFn()); // Outputs: 1
    ```

---

### **2. Context (`this`)**

- **Definition:**
  - `this` refers to the object that is the context of the execution.
- **Rules:**
  1. If called as a method: `this = object`.
  2. If called as a standalone function: `this = global object` (or `undefined` in strict mode).
  3. In an arrow function: `this` is lexically inherited.
  4. With `bind`, `call`, or `apply`: Explicitly set.

**Example with Arrow Function:**

```javascript
function Point(x, y) {
  this.x = x;
  this.y = y;
  this.area = () => this.x + this.y;
}
const areaFn = new Point(10, 20).area;
console.log(areaFn()); // Outputs: 30
```

---

### **3. Strict Mode**

- **Activation:**
  - Add `'use strict';` at the top of a script or function.
- **Advantages:**
  - Prevents silent errors (e.g., creating undeclared variables).
  - Improves security and optimizations.
- **Example:**
  ```javascript
  "use strict";
  function test() {
    undeclaredVar = 10; // Error: undeclaredVar is not defined
  }
  test();
  ```

---

### **4. Arrow Functions and Object Hashing**

- **Arrow Functions:**
  - Provide concise syntax for functions.
  - `this` is lexically scoped to the surrounding function.
- **Object Hashing:**
  - Objects behave as hash tables.
  - Keys are converted to strings:
    ```javascript
    const obj = { name: "John" };
    console.log(obj["name"]); // Outputs: John
    ```

---

### **5. JavaScript Classes and Modules**

#### **Classes:**

- **Features:**
  - Private properties (`#privateField`).
  - Inheritance with `extends` and `super`.
  - Example:
    ```javascript
    class Clock {
      #timer;
      constructor() {
        this.start();
      }
      start() {
        this.#timer = setInterval(() => {
          console.log(new Date());
        }, 1000);
      }
    }
    ```

#### **Modules:**

- **Definition:**
  - Modules provide functionality and isolate namespaces.
- **Example:**

  ```javascript
  // alarm.js
  export const alarm = (msg) => console.log(msg);

  // main.js
  import { alarm } from "./alarm.js";
  alarm("Wake up!");
  ```

---

### **6. Modern JavaScript Features**

#### **Spread Syntax:**

```javascript
const arr1 = [1, 2];
const arr2 = [3, 4];
const combined = [...arr1, ...arr2]; // [1, 2, 3, 4]
```

#### **Destructuring:**

```javascript
const [a, b] = [1, 2];
console.log(a); // 1
```

#### **Nullish Coalescing (`??`):**

```javascript
console.log(null ?? "default"); // Outputs: default
console.log(0 ?? "default"); // Outputs: 0
```

#### **Optional Chaining (`?.`):**

```javascript
const obj = { name: "Alice", cat: { name: "Dinah" } };
console.log(obj.cat?.name); // Outputs: Dinah
console.log(obj.dog?.name); // Outputs: undefined
```

---

### **7. Polyfills and Shims**

- **Polyfill:** Adds missing APIs to older environments.
- **Shim:** Provides alternative implementations.
- **Example:**
  - `Promise` polyfill for older browsers.

---

### **8. JavaScript Style Guides**

- **Recommendations:**
  - Use ESLint for code consistency.
  - Follow established guides like:
    - [Airbnb JavaScript Style Guide](https://github.com/airbnb/javascript)
    - [Google JavaScript Style Guide](https://google.github.io/styleguide/jsguide.html)

---

## ❓ **Questions Raised**

1. How do ES6 modules improve code organization?
2. When to use `nullish coalescing` vs. `||`?
3. What are the performance implications of closures?

---

## 🔗 **Further Reading/Resources**

- [JavaScript Modules](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Guide/Modules)
- [Closures in JavaScript](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Closures)
- [JavaScript Spread Operator](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Operators/Spread_syntax)

---

## 📌 **Summary**

- **Main Takeaways:**
  - JavaScript provides robust features for managing context, modularity, and compatibility.
  - Modern features enhance readability and performance.
- **How This Links to Previous Content:**
  - Builds on fundamental JavaScript programming concepts, introducing advanced tools.

---

## ✅ **Action Items**

- Implement a modular JavaScript project with ES6 modules.
- Practice using spread and destructuring for cleaner code.
- Compare arrow functions with regular functions in various scenarios.

---

### **Lecture Review**

- **What I Learned:**
  - Best practices for modern JavaScript development.
  - Advanced handling of scope and context.
- **What Needs Clarification:**
  - Real-world use cases for `??` vs. `||`.
- **My Plan to Review This Material:**
  - Build applications utilizing classes and modules for dynamic behavior.
