# 📚 **Lecture Notes**

---

## 🗓️ **Course Details**

- **Course Title:** Web Engineering
- **Lecture Title:** HTTP and Node.js
- **Lecturer Name:** Frieder Loch
- **Date:** 14.11.2024
- **Lecture Number:** Week 9

---

## 📝 **Key Topics Covered**

1. HTTP Protocol Overview
2. Client-Server Communication
3. HTTP Request and Response Structure
4. Web Servers with Node.js
5. Implementing API Servers
6. Practical Exercises: API Calculator and Book Database

---

## 🧠 **Learning Objectives**

- Explain the HTTP protocol and structure of requests and responses.
- Implement and describe the role of a web server.
- Develop basic API servers using Node.js.
- Apply concepts like SOP (Same-Origin Policy) and CORS (Cross-Origin Resource Sharing).

---

## 📖 **Detailed Notes**

### **1. HTTP Protocol Overview**

- **Definition:**
  - HTTP (Hypertext Transfer Protocol) is the foundation of web communication.
  - Facilitates the exchange of messages between clients and servers.
- **Components:**
  - **Request:** Sent by the client to the server.
  - **Response:** Sent by the server back to the client.

---

### **2. Client-Server Communication**

- **Flow:**

  1. Client sends an HTTP request to a server.
  2. Server processes the request and sends an HTTP response back.

- **Example:**
  - Client requests a webpage:
    - **Request:** `GET /index.html HTTP/1.1`
    - **Response:** HTML content of the page.

---

### **3. HTTP Request and Response Structure**

#### **Request:**

- **Methods:**

  - `GET`: Retrieve data.
  - `POST`: Submit data.
  - `PUT`: Update data.
  - `DELETE`: Remove data.

- **Structure:**
  ```
  GET /api/todos HTTP/1.1
  Host: example.com
  Content-Type: application/json
  Body: {"task": "New Task"}
  ```

#### **Response:**

- **Components:**
  - **Version:** HTTP/1.1.
  - **Status Code:**
    - `200`: OK.
    - `201`: Created.
    - `400`: Bad Request.
    - `500`: Internal Server Error.
  - **Headers:** Metadata about the response.
  - **Body:** Contains the requested data or error message.

---

### **4. Web Servers with Node.js**

- **Node.js Overview:**
  - JavaScript runtime environment for server-side programming.
  - Features non-blocking, asynchronous I/O operations.
- **Basic Web Server:**

```javascript
import http from "http";

const server = http.createServer((req, res) => {
  res.writeHead(200, { "Content-Type": "text/plain" });
  res.end("Hello, World!");
});

server.listen(3000, () =>
  console.log("Server running on http://localhost:3000"),
);
```

- **File Server:**
  - Serve different files based on requests:

```javascript
import { readFile } from "fs/promises";
import http from "http";

const server = http.createServer(async (req, res) => {
  try {
    const data = await readFile(`./public${req.url}`);
    res.writeHead(200, { "Content-Type": "text/html" });
    res.end(data);
  } catch (err) {
    res.writeHead(404, { "Content-Type": "text/plain" });
    res.end("File not found");
  }
});
```

---

### **5. Implementing API Servers**

- **Calculator API:**
  - Handles basic arithmetic operations (addition, subtraction, etc.).
  - Operands and operators are passed via URL parameters.

**Example API Endpoints:**

- Addition: `/api/calculate?op=add&n1=5&n2=10`
- Subtraction: `/api/calculate?op=subtract&n1=10&n2=5`

**Implementation:**

```javascript
const server = http.createServer((req, res) => {
  const url = new URL(req.url, `http://${req.headers.host}`);
  if (url.pathname === "/api/calculate") {
    const n1 = parseFloat(url.searchParams.get("n1"));
    const n2 = parseFloat(url.searchParams.get("n2"));
    const op = url.searchParams.get("op");
    let result;

    if (op === "add") result = n1 + n2;
    else if (op === "subtract") result = n1 - n2;

    res.writeHead(200, { "Content-Type": "application/json" });
    res.end(JSON.stringify({ result }));
  } else {
    res.writeHead(404, { "Content-Type": "text/plain" });
    res.end("Not Found");
  }
});
```

---

### **6. Practical Exercises**

#### **Book Database API:**

- **Endpoints:**

  1. `GET /api/books`: Retrieve a list of books.
  2. `POST /api/books`: Add a new book.

- **Implementation:**

  ```javascript
  let books = [{ id: 1, title: "Book 1" }];

  const server = http.createServer((req, res) => {
    if (req.method === "GET" && req.url === "/api/books") {
      res.writeHead(200, { "Content-Type": "application/json" });
      res.end(JSON.stringify(books));
    } else if (req.method === "POST" && req.url === "/api/books") {
      let body = "";
      req.on("data", (chunk) => (body += chunk));
      req.on("end", () => {
        const newBook = JSON.parse(body);
        newBook.id = books.length + 1;
        books.push(newBook);
        res.writeHead(201, { "Content-Type": "application/json" });
        res.end(JSON.stringify(newBook));
      });
    } else {
      res.writeHead(404, { "Content-Type": "text/plain" });
      res.end("Not Found");
    }
  });
  ```

---

## ❓ **Questions Raised**

1. How can performance be optimized for large-scale API servers?
2. What are the security considerations when handling user inputs?

---

## 🔗 **Further Reading/Resources**

- [MDN HTTP Overview](https://developer.mozilla.org/en-US/docs/Web/HTTP/Overview)
- [Node.js Documentation](https://nodejs.org/docs/latest/api/http.html)
- [REST API Design](https://restfulapi.net/)

---

## 📌 **Summary**

- **Main Takeaways:**
  - HTTP protocol enables structured client-server communication.
  - Node.js is powerful for building scalable and efficient web servers.
  - Practical exercises demonstrate API development and file serving.
- **How This Links to Previous Content:**
  - Builds on web development concepts and introduces backend server programming.

---

## ✅ **Action Items**

- Extend the Book Database API with update and delete functionalities.
- Build a real-time chat server using WebSockets in Node.js.
- Explore middleware frameworks like Express.js for simplifying server code.

---

### **Lecture Review**

- **What I Learned:**
  - The basics of HTTP and its role in web communication.
  - Building and managing a web server with Node.js.
- **What Needs Clarification:**
  - Handling concurrent requests in high-load environments.
- **My Plan to Review This Material:**
  - Develop a small project with RESTful APIs and file serving.
