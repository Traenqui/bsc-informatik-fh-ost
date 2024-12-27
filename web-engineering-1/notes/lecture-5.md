# 📚 **Lecture Notes**

---

## 🗓️ **Course Details**

- **Course Title:** Web Engineering
- **Lecture Title:** Document Object Model (DOM)
- **Lecturer Name:** Frieder Loch
- **Date:** 17.10.2024
- **Lecture Number:** 5

---

## 📝 **Key Topics Covered**

1. Introduction to the DOM
2. DOM Tree and Nodes
3. Element Selection
4. DOM Manipulation
5. Event Handling
6. Event Bubbling
7. Best Practices in DOM Interaction

---

## 🧠 **Learning Objectives**

- Describe the function and structure of the DOM.
- Utilize JavaScript to select and manipulate DOM elements.
- Apply event handling techniques effectively within the DOM.
- Explain and use the concept of event bubbling in practical applications.

---

## 📖 **Detailed Notes**

### **1. Introduction to the DOM**

- **Definition:**

  - The DOM is a programming interface for HTML and XML documents.
  - Represents the structure of a document as a tree with nodes.
  - Allows dynamic access and updates to content, structure, and styles.

- **Components of Web Applications:**
  - **Frontend:** HTML, CSS, and JavaScript interact with the DOM.
  - **Backend:** Handles data and business logic.

---

### **2. DOM Tree and Nodes**

- **Structure:**

  - The document is represented as a hierarchical tree.
  - Node Types:
    - **Element Nodes:** Represent tags (e.g., `<div>`, `<p>`).
    - **Text Nodes:** Represent text content.
    - **Attribute Nodes:** Represent attributes of elements.
    - **Comment Nodes:** Represent comments in the document.

- **Example:**

```html
<!doctype html>
<html>
  <head>
    <title>Example</title>
  </head>
  <body>
    <h1>Title</h1>
    <p>Content here</p>
  </body>
</html>
```

- Tree Representation:
  - Root: `html`
  - Child nodes: `head`, `body`
  - Leaves: `title`, `h1`, `p`

---

### **3. Element Selection**

- **Methods:**
  - `getElementById(id)`: Select an element by its ID.
  - `querySelector(selector)`: Select the first matching element using CSS selectors.
  - `querySelectorAll(selector)`: Select all matching elements using CSS selectors.
  - **Recommendation:** Use `querySelector`/`querySelectorAll` for flexibility.

---

### **4. DOM Manipulation**

- **Modifying Content:**
  - `innerHTML`: Replaces the content of an element.
  - `textContent`: Sets or retrieves text content.
- **Creating Elements:**
  - `createElement(tag)`: Creates a new element.
  - `appendChild(node)`: Appends a node to a parent element.
- **Example:**

```javascript
let newElement = document.createElement("div");
newElement.textContent = "Hello World!";
document.body.appendChild(newElement);
```

---

### **5. Event Handling**

- **Concept:**
  - Use `addEventListener` to attach event handlers to DOM elements.
- **Example: Click Event:**

```html
<button id="click-btn">Click Me!</button>
<script>
  document.getElementById("click-btn").addEventListener("click", () => {
    alert("Button clicked!");
  });
</script>
```

---

### **6. Event Bubbling**

- **Phases of Events:**

  1. **Capture Phase:** Event moves from the root to the target.
  2. **Target Phase:** Event acts on the target element.
  3. **Bubble Phase:** Event propagates back to the root.

- **Practical Use:**
  - Register a single handler for dynamically changing elements.

```javascript
document.getElementById("container").addEventListener("click", (event) => {
  console.log("Clicked on", event.target.tagName);
});
```

---

### **7. Best Practices in DOM Interaction**

- Use `classList` for managing CSS classes:
  - `add`, `remove`, `toggle`, `contains`, `replace`.
- Minimize DOM updates for performance:
  - Use `createDocumentFragment` for batching changes.
- Avoid magic numbers; define constants for clarity.
- Optimize selectors for performance.

---

## ❓ **Questions Raised**

1. How does event delegation compare to direct event handling in terms of performance?
2. What are the limitations of `innerHTML` for content updates?
3. How can DOM manipulation be optimized for large-scale applications?

---

## 🔗 **Further Reading/Resources**

- [MDN: Document Object Model (DOM)](https://developer.mozilla.org/en-US/docs/Web/API/Document_Object_Model)
- [Event Handling in JavaScript](https://developer.mozilla.org/en-US/docs/Learn/JavaScript/Building_blocks/Events)
- [DOM Tree Visualization](https://software.hixie.ch/utilities/js/live-dom-viewer/)

---

## 📌 **Summary**

- **Main Takeaways:**
  - The DOM allows dynamic interaction with web documents through JavaScript.
  - Event bubbling simplifies handling dynamic elements.
  - Best practices like batching changes and avoiding redundant updates enhance performance.
- **How This Links to Previous Content:**
  - Builds on fundamental HTML and CSS concepts, introducing dynamic document interactions.

---

## ✅ **Action Items**

- Practice selecting and manipulating DOM elements with `querySelector`.
- Implement a dynamic todo list using event delegation and bubbling.
- Optimize a web page by batching DOM updates with `createDocumentFragment`.

---

### **Lecture Review**

- **What I Learned:**
  - The hierarchical structure of the DOM and its interaction model.
  - Efficient methods for event handling and dynamic content updates.
- **What Needs Clarification:**
  - Advanced use cases of `createDocumentFragment`.
- **My Plan to Review This Material:**
  - Build interactive components to reinforce event handling concepts.
