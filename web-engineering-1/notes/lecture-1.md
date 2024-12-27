# 📚 **Lecture Notes**

---

## 🗓️ **Course Details**

- **Course Title:** Web Engineering 1
- **Lecture Title:** Introduction to Web Development
- **Lecturer Name:** Prof. Frieder Loch
- **Date:** 2024-09-19
- **Lecture Number:** 1

---

## 📝 **Key Topics Covered**

1. Overview of Web Applications
2. Architecture of Web Applications
3. Practical Example: Ordering a Ball in a Smart Factory
4. Core Technologies (HTML, CSS, JavaScript)
5. Organizational and Logistical Information

---

## 🧠 **Learning Objectives**

- Understand the complexity of modern web applications.
- Learn the basic components of web application architecture (Frontend, Backend, Network).
- Gain insights into the technologies used for web development.
- Understand the course structure, workload, and expectations.

---

## 📖 **Detailed Notes**

### **1. Overview of Web Applications**

- **Key Points:**
  - Web applications consist of multiple layers.
  - Users typically interact only with the frontend (e.g., YouTube interface).
  - Backend processes (e.g., data storage) and network communication are invisible but essential.
  - Example questions:
    - Where does YouTube store videos?
    - How does Google locate webpages?
- **Important Concepts:**
  - Web applications rely on seamless interaction between visible (frontend) and invisible (backend) components.

---

### **2. Architecture of Web Applications**

- **Key Points:**
  - Main components:
    - **Frontend**: User Interface (UI) visible in the browser.
    - **Backend**: Business logic and data access.
    - **Network**: Communication using protocols like HTTP.
    - **External Systems (Umsysteme)**: Third-party integrations like payment gateways.
  - Example Architecture:
    - A user action triggers frontend logic (e.g., JavaScript function).
    - Network communication sends a request to the backend.
    - The backend processes the request, communicates with databases, and responds.
- **Diagram**:
  ```
  User → Frontend (Browser) → Network → Backend → Database/Services
  ```

---

### **3. Practical Example: Ordering a Ball**

- **Key Points:**
  - **Scenario**: A Unihockey ball-ordering app integrated with a Smart Factory.
  - Workflow:
    - User clicks a button in the browser.
    - The frontend sends an order request via network to the backend.
    - The backend coordinates with the Smart Factory to produce the ball.
    - Confirmation is sent back to the user.
  - **Code Snippet Example**:
    ```javascript
    onclick = "orderBall()";
    function orderBall() {
      sendOrderRequest();
    }
    ```

---

### **4. Core Technologies**

- **Frontend Technologies**:
  - HTML: Defines structure and content.
  - CSS: Handles design and layout.
  - JavaScript: Implements interactivity and event handling.
- **Backend Technologies**:
  - Common languages: Node.js, PHP, Java, C++.
  - Supports communication with databases and external systems.
- **Network Protocols**:
  - HTTP: Core protocol for web communication.
  - Examples include REST and RPC paradigms.

---

### **5. Organizational Information**

- **Course Structure**:
  - Weekly schedule: 2 hours lecture, 2 hours self-study, 2 hours exercises, 1 hour follow-up.
  - Topics: HTML, CSS, JavaScript, AJAX, REST, etc.
- **Assessment**:
  - Testat (practical assignment) required to take the exam.
  - Written exam: 120 minutes, allows personal notes (6 pages).
- **Study Tips**:
  - Complete preparation materials before lectures.
  - Utilize resources like JetBrains WebStorm and browser Developer Tools for debugging.

---

## ❓ **Questions Raised**

- How do modern frameworks like React or Angular fit into this architecture?
- What are the main challenges in scaling web applications for global users?

---

## 🔗 **Further Reading/Resources**

- [Smart Factory Overview](https://www.ost.ch/de/die-ost/organisation/medien/smart-factory-an-der-ost-volldigitalisierte-fertigung-fuer-die-zukunft)
- [HTTP Protocol Documentation](https://developer.mozilla.org/en-US/docs/Web/HTTP/Overview)
- [RFC2396: URI Syntax](https://datatracker.ietf.org/doc/html/rfc2396)

---

## 📌 **Summary**

- **Main Takeaways:**
  - Web applications are complex systems involving multiple layers.
  - Frontend, backend, and network layers must work cohesively.
  - Core web technologies (HTML, CSS, JavaScript) form the foundation for development.
- **How This Links to Previous Content:**
  - Lays the groundwork for understanding web development frameworks and tools.

---

## ✅ **Action Items**

- Set up a development environment (e.g., WebStorm IDE).
- Review preparation materials in Moodle.
- Experiment with basic HTML, CSS, and JavaScript projects.

---

### **Lecture Review**

- **What I Learned:**
  - The architecture and workflow of web applications.
  - The roles of frontend, backend, and network in a system.
- **What Needs Clarification:**
  - How external systems (Umsysteme) are integrated efficiently.
- **My Plan to Review This Material:**
  - Revisit code examples and experiment with network requests using tools like Postman.
