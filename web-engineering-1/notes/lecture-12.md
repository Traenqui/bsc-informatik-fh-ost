# 📚 **Lecture Notes**

---

## 🗓️ **Course Details**

- **Course Title:** Web Engineering
- **Lecture Title:** AJAX 2
- **Lecturer Name:** Frieder Loch
- **Date:** 05.12.2024
- **Lecture Number:** Week 12

---

## 📝 **Key Topics Covered**

1. Richardson’s Maturity Model
2. RESTful APIs
3. AJAX Challenges and Solutions
4. Handling Unreliable Backends
5. Debouncing and Throttling
6. Implementing Suspense States
7. Advanced AJAX Techniques

---

## 🧠 **Learning Objectives**

- Understand and apply Richardson’s Maturity Model in API design.
- Develop robust AJAX interactions using error handling and retries.
- Manage slow and unreliable APIs with debouncing, throttling, and abort controllers.
- Improve user experience with visible system statuses and suspense states.

---

## 📖 **Detailed Notes**

### **1. Richardson’s Maturity Model**

- **Definition:**

  - Measures the maturity of REST APIs in four levels:
    1. **Level 0:** Swamp of POX (Plain Old XML).
    2. **Level 1:** Resources are introduced (e.g., `/users`).
    3. **Level 2:** Proper use of HTTP methods (`GET`, `POST`, etc.).
    4. **Level 3:** Hypermedia Controls (HATEOAS).

- **API Design Process:**

  1. Identify resources.
  2. Define URIs.
  3. Specify representations, including links.
  4. Support appropriate HTTP methods.

- **Example (Book Management API):**
  - Level 0: Use a single POST request to perform operations:
    ```json
    { "function": "getOrders" }
    ```
  - Level 1: Separate URIs for resources:
    - `/orders`
  - Level 2: Use HTTP methods:
    - `GET /orders`, `POST /orders`, `DELETE /orders/1`
  - Level 3: Include links in responses:
    ```json
    {
      "orderId": 123,
      "links": {
        "delete": {
          "method": "DELETE",
          "url": "/orders/123"
        }
      }
    }
    ```

---

### **2. AJAX Challenges and Solutions**

#### **Challenges:**

1. **Slow API Services:**
   - Responses appear unexpectedly, causing user confusion.
2. **Unreliable Backends:**
   - Server errors (500), conflicts (409), or empty responses.

#### **Solutions:**

1. **Visibility of System Status:**
   - Indicate request progress with loaders or disabled buttons.
   - Example: Show "Loading..." until a response is received.
2. **Abort Controllers:**
   - Cancel a request if it exceeds a timeout.
   - Example:
     ```javascript
     const controller = new AbortController();
     setTimeout(() => controller.abort(), 5000);
     fetch(url, { signal: controller.signal });
     ```

---

### **3. Handling Unreliable Backends**

#### **Retry Mechanism:**

- Retry requests a limited number of times in case of errors.
- Example:
  ```javascript
  function getMemeRecursive(onSuccess, onError, retries = 3) {
    fetch(endpoint)
      .then((response) => {
        if (!response.ok) throw response.status;
        return response.json();
      })
      .then(onSuccess)
      .catch((error) => {
        if (retries > 0) {
          getMemeRecursive(onSuccess, onError, retries - 1);
        } else {
          onError("Failed after multiple attempts.");
        }
      });
  }
  ```

#### **Error Messages:**

- Provide meaningful feedback to users based on error codes.

---

### **4. Debouncing and Throttling**

- **Debouncing:**
  - Delays execution of a function until after a pause in user activity.
  - Prevents multiple rapid requests:
    ```javascript
    let timeout;
    function debounce(callback, delay) {
      clearTimeout(timeout);
      timeout = setTimeout(callback, delay);
    }
    ```
- **Throttling:**
  - Limits the number of function executions within a time frame.
- **Example Application: Auto-Complete Fields:**
  - Only send requests after the user stops typing for a short time.

---

### **5. Implementing Suspense States**

- **Purpose:**
  - Improve user experience during slow operations by showing clear feedback.
- **Example:**

  ```javascript
  function showSuspense() {
    button.disabled = true;
    const spinner = document.createElement("div");
    spinner.classList.add("spinner");
    document.body.appendChild(spinner);
    return () => {
      button.disabled = false;
      document.body.removeChild(spinner);
    };
  }

  const hideSuspense = showSuspense();
  fetch(url).then(hideSuspense).catch(hideSuspense);
  ```

---

### **6. Advanced AJAX Techniques**

- **AbortController for Preempting:**
  - Cancel ongoing requests when new ones are initiated.
  - Example:
    ```javascript
    const controller = new AbortController();
    if (currentController) currentController.abort();
    currentController = controller;
    fetch(url, { signal: controller.signal });
    ```

---

## ❓ **Questions Raised**

1. How can hypermedia controls (HATEOAS) improve API usability?
2. When should throttling be preferred over debouncing?

---

## 🔗 **Further Reading/Resources**

- [Richardson’s Maturity Model](https://martinfowler.com/articles/richardsonMaturityModel.html)
- [Debouncing and Throttling Techniques](https://css-tricks.com/debouncing-throttling-explained/)
- [AbortController Documentation](https://developer.mozilla.org/en-US/docs/Web/API/AbortController)

---

## 📌 **Summary**

- **Main Takeaways:**
  - Richardson’s Maturity Model guides API design towards better usability.
  - Debouncing, throttling, and suspense states enhance user experience.
  - Robust error handling and retries mitigate unreliable backend issues.
- **How This Links to Previous Content:**
  - Builds on AJAX basics and introduces advanced error handling and user feedback mechanisms.

---

## ✅ **Action Items**

- Implement a book management API with all levels of Richardson’s Model.
- Enhance auto-complete functionality with debouncing and request preemption.
- Experiment with various suspense state designs to improve application responsiveness.

---

### **Lecture Review**

- **What I Learned:**
  - Practical application of advanced AJAX patterns and API design principles.
  - Effective handling of slow and unreliable backends.
- **What Needs Clarification:**
  - Trade-offs between different error recovery techniques.
- **My Plan to Review This Material:**
  - Develop an application integrating all the discussed AJAX techniques.
