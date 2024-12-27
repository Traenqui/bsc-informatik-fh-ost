# 📚 **Lecture Notes**

---

## 🗓️ **Course Details**

- **Course Title:** Web Engineering
- **Lecture Title:** AJAX and Promises
- **Lecturer Name:** Frieder Loch
- **Date:** 21.11.2024
- **Lecture Number:** Week 10

---

## 📝 **Key Topics Covered**

1. AJAX Overview
2. Asynchronous Programming Challenges
3. Promises in JavaScript
4. Fetch API
5. Error Handling with `catch()`
6. Async/Await Syntax
7. Practical Applications

---

## 🧠 **Learning Objectives**

- Describe AJAX and its components.
- Understand why AJAX requests are asynchronous and the programming challenges involved.
- Implement and manage Promises using `then`, `catch`, and `async/await`.
- Develop API calls with the Fetch API.
- Build a robust understanding of error handling in asynchronous code.

---

## 📖 **Detailed Notes**

### **1. AJAX Overview**

- **Definition:**
  - AJAX (Asynchronous JavaScript and XML) enables web applications to communicate with servers asynchronously without refreshing the page.
- **Core Idea:**

  - Send and retrieve data in the background.
  - Maintain uninterrupted user interaction.

- **Example Use Case:**
  - Fetching real-time weather updates.

---

### **2. Asynchronous Programming Challenges**

- Operations like server communication or file reading can take time, potentially freezing the UI.
- **Solution:** Use asynchronous patterns (callbacks, Promises, async/await) to handle operations without blocking.

---

### **3. Promises in JavaScript**

- **Definition:**

  - A Promise is a placeholder for a future result of an asynchronous operation.
  - States:
    1. **Pending:** Operation ongoing.
    2. **Fulfilled:** Operation successful, result available.
    3. **Rejected:** Operation failed, error available.

- **Creating Promises:**

```javascript
const promise = new Promise((resolve, reject) => {
  const success = true;
  if (success) resolve("Success!");
  else reject("Failure!");
});
```

- **Promise Methods:**
  - `then`: Called on fulfillment.
  - `catch`: Called on rejection.
  - `finally`: Executes regardless of success or failure.

---

### **4. Fetch API**

- **Purpose:**

  - Modern alternative to `XMLHttpRequest` for making HTTP requests.
  - Returns a Promise.

- **Basic Example:**

```javascript
fetch("https://restcountries.com/v3.1/name/liec")
  .then((response) => response.json())
  .then((data) => console.log(data))
  .catch((error) => console.error("Error:", error));
```

- **Options:**
  - Request method (`GET`, `POST`, etc.), headers, and body.

---

### **5. Error Handling with `catch()`**

- **Usage:**
  - Handle errors in Promises with `catch()`.
  - Prevent unhandled rejections.
- **Example:**

```javascript
fetch("https://example.com/api")
  .then((response) => {
    if (!response.ok) throw new Error("Request failed");
    return response.json();
  })
  .then((data) => console.log(data))
  .catch((error) => console.error("Error caught:", error));
```

---

### **6. Async/Await Syntax**

- **Purpose:**
  - Simplifies handling asynchronous code.
  - Makes asynchronous code look synchronous.
- **Example:**

```javascript
async function fetchData() {
  try {
    const response = await fetch("https://api.example.com/data");
    if (!response.ok) throw new Error("Failed to fetch");
    const data = await response.json();
    console.log(data);
  } catch (error) {
    console.error("Error:", error);
  }
}
```

---

### **7. Practical Applications**

#### **Exercise: Countries Using USD**

- **Task:**

  - Fetch a list of countries using USD as currency and display their names.

- **Implementation:**

```javascript
async function getCountriesUsingUSD() {
  try {
    const response = await fetch("https://restcountries.com/v3.1/all");
    const countries = await response.json();
    const usdCountries = countries.filter(
      (country) => country.currencies && country.currencies.USD,
    );
    console.log(usdCountries.map((c) => c.name.common));
  } catch (error) {
    console.error("Error fetching countries:", error);
  }
}
```

---

## ❓ **Questions Raised**

1. How do Promises compare to callbacks for managing complex workflows?
2. What are the performance impacts of large numbers of concurrent Fetch requests?

---

## 🔗 **Further Reading/Resources**

- [MDN Fetch API Documentation](https://developer.mozilla.org/en-US/docs/Web/API/Fetch_API)
- [JavaScript Promises](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Promise)
- [Async/Await](https://developer.mozilla.org/en-US/docs/Learn/JavaScript/Asynchronous/Promises)

---

## 📌 **Summary**

- **Main Takeaways:**
  - AJAX facilitates asynchronous web interactions without page reloads.
  - Promises and async/await streamline error handling and control flow in asynchronous operations.
  - The Fetch API is a modern, flexible tool for HTTP requests.
- **How This Links to Previous Content:**
  - Builds on JavaScript fundamentals and introduces practical asynchronous programming concepts.

---

## ✅ **Action Items**

- Extend the currency exercise to include other details like population and region.
- Create a small app using Fetch to retrieve and display real-time data.
- Compare performance of Promises vs. async/await in large-scale applications.

---

### **Lecture Review**

- **What I Learned:**
  - The difference between callbacks and Promises.
  - How async/await simplifies asynchronous JavaScript programming.
- **What Needs Clarification:**
  - Advanced error-handling strategies in nested Promises.
- **My Plan to Review This Material:**
  - Build a REST API client using Fetch and Promises to reinforce these concepts.
