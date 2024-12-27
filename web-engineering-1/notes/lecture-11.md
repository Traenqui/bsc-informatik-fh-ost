# 📚 **Lecture Notes**

---

## 🗓️ **Course Details**

- **Course Title:** Web Engineering
- **Lecture Title:** REST and API Design
- **Lecturer Name:** Frieder Loch
- **Date:** 28.11.2024
- **Lecture Number:** Week 11

---

## 📝 **Key Topics Covered**

1. REST Principles and Components
2. Richardson’s Maturity Model
3. HTTP Methods and Resource Design
4. Resource-Oriented Architecture (ROA)
5. Mock APIs and `json-server`
6. API Design Best Practices

---

## 🧠 **Learning Objectives**

- Explain the purpose of REST in web services.
- Design a REST API for a given problem.
- Apply Richardson’s Maturity Model in API design.
- Utilize mock APIs for testing and development.
- Follow best practices for clean and efficient API design.

---

## 📖 **Detailed Notes**

### **1. REST Principles and Components**

- **Definition of REST:**

  - Representational State Transfer (REST) is an architectural style for building scalable web services.

- **Core Components of REST:**
  1. **Client-Server Architecture:**
     - Separation of concerns between client (user interface) and server (data storage).
  2. **Stateless Communication:**
     - Each request contains all the information needed for the server to process it.
  3. **Caching:**
     - Responses can be cached to improve performance.
  4. **Uniform Interface:**
     - A standardized way to interact with resources.
  5. **Layered System:**
     - Components operate independently.

---

### **2. Richardson’s Maturity Model**

- **Purpose:**

  - Measures the maturity of REST APIs.

- **Levels:**
  1. **Level 0: Swamp of POX**
     - Single endpoint with operations in the request body.
  2. **Level 1: Resources**
     - Endpoints represent resources (e.g., `/users`).
  3. **Level 2: HTTP Verbs**
     - Proper use of HTTP methods (`GET`, `POST`, etc.).
  4. **Level 3: Hypermedia Controls (HATEOAS)**
     - API responses include links to related actions/resources.

---

### **3. HTTP Methods and Resource Design**

#### **Common HTTP Methods:**

| Method | Purpose                          | Idempotent | Safe |
| ------ | -------------------------------- | ---------- | ---- |
| GET    | Retrieve resource representation | Yes        | Yes  |
| POST   | Create a new resource            | No         | No   |
| PUT    | Update/replace a resource        | Yes        | No   |
| DELETE | Remove a resource                | Yes        | No   |

#### **URI Design:**

- Intuitive and descriptive.
- Examples:
  - `/users/123`: Retrieve user with ID 123.
  - `/users/123/orders`: Retrieve orders for user 123.

#### **Resource Representation:**

- Use JSON as the preferred format for data representation.

---

### **4. Resource-Oriented Architecture (ROA)**

- **Concepts:**
  1. **Resource:** Anything important enough to be referenced independently.
  2. **Name:** Unique identifier (e.g., URI).
  3. **Representation:** Data format (e.g., JSON, XML).
  4. **Links:** Hyperlinks to related resources.
  5. **Interface:** Uniform interface for resource manipulation.

#### **Example:**

```json
{
  "orderId": 9876,
  "product": {
    "id": 33,
    "name": "SuperWidget",
    "amount": 10
  },
  "links": {
    "self": "/orders/9876",
    "product": "/products/33",
    "customer": "/customers/12345"
  }
}
```

---

### **5. Mock APIs and `json-server`**

- **Purpose:**

  - Simulate an API for testing without a full backend.

- **Using `json-server`:**

  1. Create a mock database (`db.json`):
     ```json
     {
       "posts": [{ "id": 1, "title": "Mock API", "author": "John Doe" }]
     }
     ```
  2. Install and run:
     ```bash
     npm install -g json-server
     json-server --watch db.json
     ```

- **Routes:**
  - `GET /posts`: Retrieve all posts.
  - `POST /posts`: Create a new post.

---

### **6. API Design Best Practices**

- Use nouns for resources (`/books`) instead of verbs (`/getBooks`).
- Ensure URIs are human-readable.
- Follow HTTP status code conventions:
  - `200 OK`, `201 Created`, `404 Not Found`, `500 Internal Server Error`.
- Return JSON, not XML, for compatibility.
- Use links (HATEOAS) to guide clients through the API.

#### **Example of a Good API:**

- **Request:**
  ```http
  POST /orders
  Content-Type: application/json
  {
    "productId": 33,
    "amount": 10
  }
  ```
- **Response:**
  ```http
  201 Created
  {
    "orderId": 9876,
    "links": {
      "self": "/orders/9876",
      "product": "/products/33"
    }
  }
  ```

---

## ❓ **Questions Raised**

1. How does HATEOAS improve API usability?
2. What are the limitations of mock APIs like `json-server`?

---

## 🔗 **Further Reading/Resources**

- [Richardson’s Maturity Model](https://martinfowler.com/articles/richardsonMaturityModel.html)
- [RESTful API Design](https://www.vinaysahni.com/best-practices-for-a-pragmatic-restful-api)
- [json-server Documentation](https://github.com/typicode/json-server)

---

## 📌 **Summary**

- **Main Takeaways:**
  - REST APIs emphasize simplicity, scalability, and consistency.
  - Richardson’s Maturity Model guides API development.
  - Mock APIs facilitate testing and prototyping.
- **How This Links to Previous Content:**
  - Builds on HTTP fundamentals and introduces practical API design concepts.

---

## ✅ **Action Items**

- Design a REST API using Richardson’s Maturity Model for a book management system.
- Experiment with `json-server` to mock an API for a to-do app.
- Implement HATEOAS in a sample API.

---

### **Lecture Review**

- **What I Learned:**
  - The core principles of REST and its role in web services.
  - Best practices for designing and documenting APIs.
- **What Needs Clarification:**
  - Practical scenarios where Level 3 maturity (HATEOAS) is essential.
- **My Plan to Review This Material:**
  - Develop a fully documented REST API with mock implementations for testing.
