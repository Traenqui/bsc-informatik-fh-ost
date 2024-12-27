# 📚 **Lecture Notes**

---

## 🗓️ **Course Details**

- **Course Title:** Web Engineering 1
- **Lecture Title:** HTML
- **Lecturer Name:** Prof. Frieder Loch
- **Date:** 2024-09-26
- **Lecture Number:** 2

---

## 📝 **Key Topics Covered**

1. Fundamentals of HTML
2. Syntax vs. Semantics in HTML
3. Semantic HTML and Accessibility
4. Tools for HTML Validation
5. Best Practices for HTML Markup

---

## 🧠 **Learning Objectives**

- Describe the components of an HTML document.
- Create syntactically correct HTML documents and identify syntax errors.
- Understand the importance of semantic HTML for accessibility.
- Select and utilize semantically appropriate HTML elements for a given application.
- Analyze and review HTML markup for correctness and best practices.

---

## 📖 **Detailed Notes**

### **1. Fundamentals of HTML**

- **Key Points:**
  - HTML is not a programming language but a markup language.
  - It structures content on the web using elements enclosed in tags.
  - Core structure of an HTML document:
    ```html
    <!doctype html>
    <html lang="en">
      <head>
        <meta charset="UTF-8" />
        <title>Example</title>
      </head>
      <body>
        <h1>Hello World</h1>
      </body>
    </html>
    ```
  - Components:
    - **Tags**: Denote the beginning and end of an element.
    - **Attributes**: Provide additional information about elements.
    - **Content**: Visible information or nested elements.

---

### **2. Syntax vs. Semantics**

- **Syntax**: Rules that define how elements should be structured.
  - Example: `<img href="service.jpg">` is syntactically incorrect as `href` is not valid for `img`.
- **Semantics**: Assigning meaning to elements.
  - Example:
    ```html
    <div class="li">Milk</div>
    <!-- Less semantic -->
    <li>Milk</li>
    <!-- Proper semantic markup -->
    ```
- **Importance of Semantics**:
  - Enhances accessibility.
  - Improves SEO and machine-readability.
  - Facilitates maintainability and clarity in code.

---

### **3. Semantic HTML and Accessibility**

- **Principles** (WCAG - POUR criteria):
  - **Perceivable**: Content must be detectable by all users.
  - **Operable**: Interface must be usable via all input methods.
  - **Understandable**: Content and interactions should be clear.
  - **Robust**: Compatibility with various devices and assistive tools.
- **Examples**:
  - Use `<header>`, `<main>`, `<footer>` for page structure.
  - Avoid non-semantic tags like `<div>` for structural purposes.

---

### **4. Tools for HTML Validation**

- **W3C Validator**:
  - Validates syntax and structure of HTML documents.
  - Available at [validator.w3.org](https://validator.w3.org/).
- **Web Accessibility Evaluation Tools (WAVE)**:
  - Assesses accessibility issues in HTML.

---

### **5. Best Practices for HTML Markup**

- **Alt Attribute for Images**:
  - Provides alternative text for screen readers.
  - Guidelines:
    - Describe the image's purpose, not its appearance.
    - Avoid phrases like "image of…".
    - Example: `<img src="image.jpg" alt="Grace Hopper in a navy uniform.">`
- **Semantic Grouping**:
  - Use `<section>` for related content blocks.
  - Use `<article>` for independent, reusable content.
  - Example:
    ```html
    <main>
      <section id="news">
        <article>
          <h2>Headline</h2>
          <p>Content of the article.</p>
        </article>
      </section>
    </main>
    ```

---

## ❓ **Questions Raised**

- How can semantic HTML be applied in dynamic web applications using frameworks like React?
- What are some common pitfalls when using semantic elements incorrectly?

---

## 🔗 **Further Reading/Resources**

- [HTML Living Standard](https://html.spec.whatwg.org/)
- [WCAG Guidelines](https://www.w3.org/WAI/standards-guidelines/wcag/)
- [W3C Validator](https://validator.w3.org/)

---

## 📌 **Summary**

- **Main Takeaways:**
  - Syntax ensures correctness; semantics ensures meaningfulness.
  - Semantic HTML is crucial for accessibility and maintainability.
  - Use validation tools to maintain code quality.
- **How This Links to Previous Content:**
  - Builds on the foundational understanding of web application components.

---

## ✅ **Action Items**

- Practice creating and validating HTML documents.
- Use semantic elements to improve the accessibility of a sample web page.
- Explore the use of WAVE and W3C Validator for debugging HTML issues.

---

### **Lecture Review**

- **What I Learned:**
  - Difference between syntax and semantics in HTML.
  - Best practices for semantic markup and accessibility.
- **What Needs Clarification:**
  - Integration of semantic HTML with modern frontend frameworks.
- **My Plan to Review This Material:**
  - Apply learned concepts in small projects and validate using online tools.
