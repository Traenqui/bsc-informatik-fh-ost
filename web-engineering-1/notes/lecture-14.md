# 📚 **Lecture Notes**

---

## 🗓️ **Course Details**

- **Course Title:** Web Engineering 1
- **Lecture Title:** Week 14 Summary
- **Lecturer Name:** Frieder Loch
- **Date:** 19.12.2024
- **Lecture Number:** Week 14

---

## 📝 **Key Topics Covered**

1. Exam Information and Structure
2. HTML and Semantics
3. CSS Fundamentals and Best Practices
4. JavaScript and the DOM
5. Clean Code Practices
6. HTTP and REST APIs
7. Usability and User Experience (UX)

---

## 🧠 **Learning Objectives**

- Prepare for the final examination by revisiting core topics in Web Engineering.
- Understand how semantic HTML and CSS are applied in frontend development.
- Develop a strong grasp of HTTP, REST, and modern API design.
- Utilize clean code principles for better software maintainability.
- Improve web application usability through design heuristics.

---

## 📖 **Detailed Notes**

### **1. Exam Information**

- **Date:** January 23, 2025
- **Time:** 14:50 - 16:50
- **Structure:**
  - 90 points total.
  - Allowed materials: 3 sheets of A4 paper (handwritten or printed).

---

### **2. HTML and Semantics**

#### **Key Principles:**

- Use **semantic HTML** to improve accessibility and SEO.
- Avoid "div-soup"; prefer semantic tags like `<header>`, `<footer>`, `<article>`, and `<section>`.
- Structure pages using meaningful elements:
  - Example:
    ```html
    <article>
      <h1>Weather forecast for Seattle</h1>
      <p>Heavy rain expected tomorrow.</p>
    </article>
    ```

#### **Attributes:**

- Use descriptive `alt` text for images to enhance accessibility.
- Example:
  ```html
  <img
    src="grace_hopper.jpg"
    alt="Grace Hopper, a pioneering computer scientist"
  />
  ```

---

### **3. CSS Fundamentals and Best Practices**

#### **Selectors:**

- Types:
  - **Class Selectors:** `.recent { color: blue; }`
  - **ID Selectors:** `#container { margin: 0; }`
  - **Pseudo-Classes:** `:hover`, `:nth-child(odd)`

#### **Flexbox:**

- One-dimensional layout model for rows or columns.
- Example:
  ```css
  .container {
    display: flex;
    justify-content: space-between;
    align-items: center;
  }
  ```

#### **Cascade and Specificity:**

- Styles are applied based on specificity and source order:
  - Inline styles > IDs > Classes > Elements.

---

### **4. JavaScript and the DOM**

#### **Event Handling:**

- Use `addEventListener` for registering event listeners.
- Example:
  ```javascript
  const btn = document.querySelector("#btnClickMe");
  btn.addEventListener("click", () => alert("Button clicked!"));
  ```

#### **Event Bubbling:**

- Events propagate from target element to the root.
- Example:
  ```javascript
  document.querySelector("#container").addEventListener("click", (event) => {
    console.log("Clicked element:", event.target);
  });
  ```

---

### **5. Clean Code Practices**

#### **Naming Conventions:**

- Use descriptive and intuitive names:
  - Bad: `int x;`
  - Good: `int elapsedTimeInDays;`

#### **Functions:**

- Should be short and focused on a single task.
- Example:
  ```javascript
  function calculateDiscount(price, discountRate) {
    return price * discountRate;
  }
  ```

---

### **6. HTTP and REST APIs**

#### **HTTP Basics:**

- Request methods:
  - `GET`: Retrieve data.
  - `POST`: Create resources.
  - `PUT`: Update resources.
  - `DELETE`: Remove resources.

#### **RESTful Design:**

- Use descriptive URLs:
  - `/users/123/orders` instead of `/getOrders?userId=123`.
- Include hypermedia links (HATEOAS):
  ```json
  {
    "orderId": 123,
    "links": {
      "self": "/orders/123",
      "cancel": "/orders/123/cancel"
    }
  }
  ```

---

### **7. Usability and UX**

#### **Heuristics (Nielsen’s 10):**

1. Visibility of system status.
2. Match between system and real world.
3. User control and freedom.
4. Consistency and standards.
5. Error prevention.
6. Recognition over recall.
7. Flexibility and efficiency of use.
8. Minimalist design.
9. Help users recognize and recover from errors.
10. Provide help and documentation.

#### **Gestalt Laws:**

- Use principles like similarity and proximity to group related elements.

#### **Accessibility:**

- Ensure sufficient color contrast (WCAG guidelines).
- Example: Use tools like [WebAIM](https://webaim.org/resources/contrastchecker/).

---

## ❓ **Questions Raised**

1. How can semantic HTML improve accessibility beyond screen readers?
2. What are the best practices for managing CSS specificity in large projects?

---

## 🔗 **Further Reading/Resources**

- [HTML Accessibility Guidelines](https://developer.mozilla.org/en-US/docs/Web/Accessibility)
- [CSS Flexbox Guide](https://css-tricks.com/snippets/css/a-guide-to-flexbox/)
- [Nielsen’s Usability Heuristics](https://www.nngroup.com/articles/ten-usability-heuristics/)

---

## 📌 **Summary**

- **Main Takeaways:**
  - Semantic HTML and CSS improve web performance and usability.
  - Clean code practices enhance readability and maintainability.
  - RESTful APIs and usability heuristics ensure a robust user experience.
- **How This Links to Previous Content:**
  - Consolidates all topics from the course into a holistic summary for exam preparation.

---

## ✅ **Action Items**

- Review past assignments and apply clean code principles.
- Practice creating semantic HTML and REST APIs.
- Test web pages for usability and accessibility using online tools.

---

### **Lecture Review**

- **What I Learned:**
  - Key exam topics and their importance.
  - The interconnectedness of web development concepts.
- **What Needs Clarification:**
  - Practical integration of REST APIs with complex frontend frameworks.
- **My Plan to Review This Material:**
  - Create a study guide summarizing each topic and practice with example problems.
