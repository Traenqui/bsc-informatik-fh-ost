# 📚 **Lecture Notes**

---

## 🗓️ **Course Details**

- **Course Title:** Web Engineering
- **Lecture Title:** Clean Code and Software Architecture
- **Lecturer Name:** Frieder Loch
- **Date:** 07.11.2024
- **Lecture Number:** Week 8

---

## 📝 **Key Topics Covered**

1. Clean Code Principles
2. Code Quality and Naming Conventions
3. DRY (Don’t Repeat Yourself) Principle
4. Single Responsibility Functions
5. MVC (Model-View-Controller) Design Pattern
6. Modularization and Component Architecture

---

## 🧠 **Learning Objectives**

- Explain the importance of clean code in software quality.
- Apply rules for naming conventions in HTML, CSS, and JavaScript.
- Understand and implement the DRY principle.
- Analyze and improve code quality using clean code practices.
- Structure single-page web applications using the MVC design pattern.

---

## 📖 **Detailed Notes**

### **1. Clean Code Principles**

- **Definition:**

  - Code that is easy to read, understand, and maintain.
  - Reflects the author's care and attention to detail.
  - Intuitively understandable with minimal effort.

- **Key Quote:**

  - "Clean code is code that is written by someone who cares." — Michael Feathers.

- **Relativity:**
  - Clean code practices vary across teams and programming languages.

---

### **2. Code Quality and Naming Conventions**

- **Rules for Good Naming:**

  - Use meaningful and descriptive identifiers.
  - Avoid abbreviations unless they are widely understood.
  - Reflect the purpose and scope of variables, functions, and classes.

- **Examples:**
  - **Bad Naming:**
    ```javascript
    function isTrue(tempBool) {
      return !tempBool;
    }
    ```
  - **Good Naming:**
    ```javascript
    function isFalsy(value) {
      return !value;
    }
    ```

---

### **3. DRY Principle**

- **Definition:**

  - "Don’t Repeat Yourself": Each piece of knowledge should have a single, unambiguous representation.

- **Example:**
  - **Redundant Code:**
    ```javascript
    function disableGameButtons() {
      button1.disabled = true;
      button2.disabled = true;
      // ...
    }
    ```
  - **DRY Approach:**
    ```javascript
    function setButtonsState(state) {
      buttons.forEach((button) => (button.disabled = state));
    }
    ```

---

### **4. Single Responsibility Functions**

- **Concept:**

  - Each function should perform one specific task.
  - Easier to debug, test, and maintain.

- **Example:**
  - **Refactored Code:**
    ```javascript
    function renderPage(pageData) {
      if (isTestPage(pageData)) {
        includeSetupAndTeardown(pageData);
      }
      return pageData.getHTML();
    }
    ```

---

### **5. MVC (Model-View-Controller) Design Pattern**

#### **Structure:**

1. **Model:**
   - Manages application state and logic.
   - Example: Tracks the current state of a traffic light.
2. **View:**
   - Handles the UI and displays data from the Model.
   - Registers event handlers for user interactions.
3. **Controller:**
   - Connects the Model and View.
   - Responds to user inputs by updating the Model and triggering View updates.

#### **Advantages:**

- Clear separation of concerns.
- Modular structure for maintainability and scalability.

#### **Example: Traffic Light Application**

- **Model:**
  ```javascript
  class TrafficLightModel {
    constructor() {
      this.state = 0;
    }
    nextState() {
      this.state = (this.state + 1) % 3;
    }
  }
  ```
- **View:**
  ```javascript
  class TrafficLightView {
    render(container) {
      container.innerHTML = `<div class="light"></div>`;
      this.lightElement = container.querySelector(".light");
    }
    update(state) {
      this.lightElement.className = `light state-${state}`;
    }
  }
  ```
- **Controller:**

  ```javascript
  const model = new TrafficLightModel();
  const view = new TrafficLightView();

  document.querySelector("#switch").addEventListener("click", () => {
    model.nextState();
    view.update(model.state);
  });
  ```

---

### **6. Modularization and Component Architecture**

- **Goal:**

  - Simplify complex systems by dividing them into smaller, reusable components.

- **MVC Components:**
  - **Model:** Encapsulates the state and logic.
  - **View:** Represents different visual presentations (e.g., vertical, horizontal).
  - **Controller:** Manages user interactions and ties components together.

#### **Traffic Light Modularization:**

- **Separate Logic:**
  - Sequential or random state changes.
- **Separate Views:**
  - Vertical, horizontal, or compact layouts.

---

## ❓ **Questions Raised**

1. How does MVC improve maintainability compared to monolithic applications?
2. What are best practices for modularizing large-scale applications?
3. How can clean code principles be enforced in teams?

---

## 🔗 **Further Reading/Resources**

- [Clean Code by Robert C. Martin](https://www.oreilly.com/library/view/clean-code/9780136083238/)
- [MVC Design Pattern](https://developer.mozilla.org/en-US/docs/Glossary/MVC)
- [DRY Principle](https://en.wikipedia.org/wiki/Don%27t_repeat_yourself)

---

## 📌 **Summary**

- **Main Takeaways:**
  - Clean code prioritizes readability, simplicity, and maintainability.
  - Adopting MVC ensures clear separation of concerns in applications.
  - DRY principles prevent redundancy and enhance code efficiency.
- **How This Links to Previous Content:**
  - Builds on JavaScript basics by introducing structured design patterns and clean coding practices.

---

## ✅ **Action Items**

- Refactor an existing project to follow clean code principles.
- Implement an application using the MVC design pattern.
- Use linters to identify and fix code quality issues.

---

### **Lecture Review**

- **What I Learned:**
  - How clean code practices simplify collaboration and debugging.
  - The utility of MVC in structuring modern web applications.
- **What Needs Clarification:**
  - Strategies for integrating MVC with existing monolithic codebases.
- **My Plan to Review This Material:**
  - Apply clean code and MVC principles to a small web project for practical understanding.
