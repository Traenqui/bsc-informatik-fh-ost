# 📚 **Lecture Notes**

---

## 🗓️ **Course Details**

- **Course Title:** Web Engineering
- **Lecture Title:** Application Development
- **Lecturer Name:** Frieder Loch
- **Date:** 24.10.2024
- **Lecture Number:** 6

---

## 📝 **Key Topics Covered**

1. Event Handling for Dynamic Child Elements
2. DOM Events and Event Phases
3. Event Bubbling
4. Practical Example: To-Do List
5. Tic Tac Toe Game Development
6. Using CSS for Styling and Layout

---

## 🧠 **Learning Objectives**

- Implement event handling for dynamic child elements in the DOM.
- Understand and utilize event bubbling and delegation.
- Build practical applications like a to-do list and Tic Tac Toe.
- Explore CSS and JavaScript integration for dynamic UI behavior.

---

## 📖 **Detailed Notes**

### **1. Event Handling for Dynamic Child Elements**

- **Scenario:**
  - Container with dynamic `<img>` elements that require individual event handling.
- **Problem:**
  - Adding event listeners to each `<img>` is inefficient when elements are dynamic.

#### **Solution: Event Delegation**

- Attach a single event listener to the parent element.
- Use the `event.target` property to identify the source of the event.

**Example:**

```javascript
document.getElementById("container").addEventListener("click", (event) => {
  if (event.target.tagName === "IMG") {
    console.log("Clicked image:", event.target);
  }
});
```

---

### **2. DOM Events and Event Phases**

- Events propagate through three phases:

  1. **Capture Phase:** Event travels from the root to the target.
  2. **Target Phase:** Event acts on the target element.
  3. **Bubble Phase:** Event travels back from the target to the root.

- Not all events bubble, but bubbling is useful for delegation.

**Example of `target` and `currentTarget`:**

```javascript
function handleClick(event) {
  console.log("Target:", event.target);
  console.log("Current Target:", event.currentTarget);
}
```

---

### **3. Event Bubbling**

- Register a single event handler on a container.
- Efficiently handle events for all children using the bubble phase.
- Benefits:
  - Simplifies code.
  - Reduces memory usage by avoiding multiple listeners.

**Practical Example:**

```html
<div id="container">
  <img src="image1.jpg" />
  <img src="image2.jpg" />
</div>
```

- **Handler:**

```javascript
document.getElementById("container").addEventListener("click", (event) => {
  if (event.target.tagName === "IMG") {
    alert(`Image clicked: ${event.target.src}`);
  }
});
```

---

### **4. Practical Example: To-Do List**

#### **Features:**

1. Add tasks:
   - Enter task text in an input field and press Enter.
   - Create a new `<li>` element and append it to the list.
2. Mark tasks as completed:
   - Clicking a task toggles its `completed` class.

#### **HTML Structure:**

```html
<input type="text" id="taskInput" placeholder="Add new task..." />
<ul id="taskList">
  <li>Example Task</li>
</ul>
```

**JavaScript:**

```javascript
document.getElementById("taskInput").addEventListener("keydown", (event) => {
  if (event.key === "Enter") {
    const taskText = event.target.value;
    const newTask = document.createElement("li");
    newTask.textContent = taskText;
    document.getElementById("taskList").appendChild(newTask);
    event.target.value = "";
  }
});

document.getElementById("taskList").addEventListener("click", (event) => {
  if (event.target.tagName === "LI") {
    event.target.classList.toggle("completed");
  }
});
```

---

### **5. Tic Tac Toe Game Development**

#### **HTML Structure:**

```html
<table id="game-board">
  <tr>
    <td data-field="0">-</td>
    <td data-field="1">-</td>
    <td data-field="2">-</td>
  </tr>
  <tr>
    <td data-field="3">-</td>
    <td data-field="4">-</td>
    <td data-field="5">-</td>
  </tr>
  <tr>
    <td data-field="6">-</td>
    <td data-field="7">-</td>
    <td data-field="8">-</td>
  </tr>
</table>
```

#### **CSS for Styling:**

```css
#game-board {
  width: 500px;
  height: 500px;
  display: flex;
  margin: auto;
}

#game-board td {
  background-color: #6a82fb;
  width: 166px;
  border: solid black;
  padding: 30px;
  font-size: 80px;
}
```

#### **JavaScript Logic:**

- Handle clicks on table cells.
- Toggle between "X" and "O" for players.

**Example:**

```javascript
const board = document.getElementById("game-board");
let currentPlayer = "X";

board.addEventListener("click", (event) => {
  const cell = event.target;
  if (cell.tagName === "TD" && cell.textContent === "-") {
    cell.textContent = currentPlayer;
    currentPlayer = currentPlayer === "X" ? "O" : "X";
  }
});
```

---

### **6. CSS Variables**

- Use `:root` for theming:

```css
:root {
  --primary-color: #6a82fb;
  --secondary-color: #fff;
  --border-radius: 10px;
}

#game-board td {
  background-color: var(--primary-color);
  border-radius: var(--border-radius);
  color: var(--secondary-color);
}
```

---

## ❓ **Questions Raised**

1. How can event delegation be extended for multi-level nesting?
2. What are the limitations of event bubbling for large DOM structures?

---

## 🔗 **Further Reading/Resources**

- [Event Bubbling and Delegation](https://developer.mozilla.org/en-US/docs/Web/API/Event/bubbling)
- [CSS Variables](https://developer.mozilla.org/en-US/docs/Web/CSS/Using_CSS_custom_properties)
- [Dynamic DOM Manipulation](https://developer.mozilla.org/en-US/docs/Web/API/Document_Object_Model)

---

## 📌 **Summary**

- **Main Takeaways:**
  - Event delegation simplifies handling for dynamic elements.
  - Bubbling phase is crucial for efficiently handling child events.
  - Practical projects like to-do lists and games illustrate DOM and CSS integration.
- **How This Links to Previous Content:**
  - Builds on DOM fundamentals and introduces advanced event handling techniques.

---

## ✅ **Action Items**

- Build and extend the to-do list application with edit and delete features.
- Develop Tic Tac Toe with win condition checks and animations.
- Experiment with CSS variables for theming and layout consistency.

---

### **Lecture Review**

- **What I Learned:**
  - Efficient event handling with delegation and bubbling.
  - Dynamic UI updates using JavaScript and CSS.
- **What Needs Clarification:**
  - Optimizing event delegation for deeply nested structures.
- **My Plan to Review This Material:**
  - Recreate the examples and extend them with additional features.
