# 📚 **Lecture Notes**

---

## 🗓️ **Course Details**

- **Course Title:** Web Engineering 1
- **Lecture Title:** Cascading Stylesheets (CSS)
- **Lecturer Name:** Prof. Frieder Loch
- **Date:** 2024-10-03
- **Lecture Number:** 3

---

## 📝 **Key Topics Covered**

1. Introduction to CSS
2. Selectors and the Cascade
3. Box Model and Display Properties
4. Layout Techniques with Flexbox
5. Debugging and Best Practices

---

## 🧠 **Learning Objectives**

- Explain the role of CSS in web applications.
- Apply basic and advanced CSS selectors.
- Use Flexbox, display properties, and the box model to create layouts.
- Resolve conflicts in CSS rules (cascade principle).
- Debug CSS using browser tools and understand layout dynamics.

---

## 📖 **Detailed Notes**

### **1. Introduction to CSS**

- **Definition**:
  - CSS (Cascading Style Sheets) adds styling (e.g., fonts, colors, spacing) to web documents.
- **Structure of a CSS Rule**:
  ```css
  selector {
    property: value;
  }
  ```
- **Example**:
  ```css
  body {
    background-color: lightblue;
  }
  ```

---

### **2. Selectors and the Cascade**

- **Selectors**:
  - Target HTML elements for styling:
    - Universal: `*`
    - Type: `p`, `h1`
    - Class: `.classname`
    - ID: `#idname`
    - Descendants: `div p`
    - Siblings: `.class + p`, `.class ~ p`
- **Cascade and Specificity**:
  - Rules are prioritized by:
    1. **Origin**: Browser defaults, user styles, author styles.
    2. **Specificity**: Weighted as `a, b, c`:
    - ID selectors (a): `#id`
    - Class selectors, attributes (b): `.class`, `[type="text"]`
    - Type selectors, pseudo-elements (c): `p`, `::before`
  - **Important Declarations**:
    - `!important` overrides other rules but should be used sparingly.

---

### **3. Box Model and Display Properties**

- **Box Model**:
  - Defines the structure of an element:
    - Content → Padding → Border → Margin.
  - Example:
    ```css
    div {
      width: 100px;
      padding: 10px;
      border: 5px solid black;
      margin: 20px;
    }
    ```
  - Total width = content width + padding + border + margin.
- **Display Properties**:
  - **Block**: Takes up full width.
  - **Inline**: Occupies only necessary space; no width/height adjustment.
  - **Inline-block**: Combines inline and block behaviors.

---

### **4. Layout Techniques with Flexbox**

- **What is Flexbox?**:
  - One-dimensional layout system for arranging elements in rows or columns.
- **Key Properties**:
  - `display: flex;` activates Flexbox.
  - **Main Axis Alignment** (`justify-content`):
    - `flex-start`, `center`, `space-between`, etc.
  - **Cross Axis Alignment** (`align-items`):
    - `stretch`, `baseline`, `center`, etc.
- **Flex-Direction**:
  - `row`: Main axis is horizontal.
  - `column`: Main axis is vertical.
- **Example**:
  ```css
  .container {
    display: flex;
    justify-content: space-between;
    align-items: center;
  }
  ```

---

### **5. Debugging and Best Practices**

- **Tools**:
  - Developer Tools in browsers (e.g., Chrome's "Inspect" feature) show computed styles and layout structures.
- **Common Issues**:
  - Margins collapsing in block elements.
  - Unexpected inheritance of properties.
  - Overlapping or unstyled elements.
- **Best Practices**:
  - Use semantic classes for clarity.
  - Avoid inline styles for scalability.
  - Test layouts across multiple browsers.

---

## ❓ **Questions Raised**

- How do modern grid systems compare to Flexbox in terms of usability and performance?
- What are the best debugging strategies for responsive design issues?

---

## 🔗 **Further Reading/Resources**

- [MDN Web Docs - CSS Basics](https://developer.mozilla.org/en-US/docs/Web/CSS)
- [CSS Flexbox Guide](https://css-tricks.com/snippets/css/a-guide-to-flexbox/)
- [Box Model Overview](https://developer.mozilla.org/en-US/docs/Web/CSS/CSS_Box_Model)

---

## 📌 **Summary**

- **Main Takeaways**:
  - CSS styles the visual appearance of web documents.
  - The cascade and specificity determine which styles apply.
  - Flexbox simplifies layout creation for rows and columns.
- **How This Links to Previous Content**:
  - Builds upon HTML basics to control web presentation and layout.

---

## ✅ **Action Items**

- Practice building layouts with Flexbox and test cascading styles.
- Explore browser developer tools for debugging CSS issues.
- Review and analyze a CSS file to identify potential inefficiencies.

---

### **Lecture Review**

- **What I Learned**:
  - CSS properties control element display and layout.
  - Specificity and cascade affect rule application order.
- **What Needs Clarification**:
  - Advanced uses of pseudo-classes and combinators.
- **My Plan to Review This Material**:
  - Create a project focusing on Flexbox-based layouts and debug using browser tools.
