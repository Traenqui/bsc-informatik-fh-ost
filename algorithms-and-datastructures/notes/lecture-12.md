# 📚 **Lecture Notes**

---

## 🗓️ **Course Details**

- **Course Title:** Algorithms and Data Structures
- **Lecture Title:** Directed Graphs
- **Lecturer Name:** Thomas Letsch
- **Date:** 04.12.2024
- **Lecture Number:** 12

---

## 📝 **Key Topics Covered**

1. Definition and Applications of Directed Graphs (Digraphs)
2. Properties of Directed Graphs
3. Traversal Algorithms for Directed Graphs
4. Strong Connectivity in Directed Graphs
5. Transitive Closure and Floyd-Warshall Algorithm
6. Directed Acyclic Graphs (DAGs) and Topological Sorting

---

## 🧠 **Learning Objectives**

- Understand the structure and applications of directed graphs.
- Analyze key properties and connectivity of directed graphs.
- Implement traversal algorithms for directed graphs.
- Compute the transitive closure of a directed graph using Floyd-Warshall.
- Learn topological sorting for directed acyclic graphs (DAGs).

---

## 📖 **Detailed Notes**

### **1. Directed Graphs (Digraphs)**

- **Definition:**

  - A directed graph $G = (V, E)$ consists of vertices $V$ and directed edges $E$ where each edge $(u, v)$ points from $u$ to $v$.
  - Unlike undirected graphs, edges are one-way.

- **Applications:**
  - One-way streets in road networks.
  - Flight routes between airports.
  - Task scheduling and precedence relationships.

---

### **2. Properties of Directed Graphs**

- **Edge Directions:**
  - Edges $(u, v)$ indicate direction from $u$ to $v$; $(v, u)$ is distinct and may not exist.
- **Edge Constraints:**

  - For a simple graph, $m \leq n(n-1)$, where $n$ is the number of vertices and $m$ is the number of edges.

- **Adjacency Representation:**
  - Separate lists for incoming and outgoing edges enable efficient access.

---

### **3. Traversal Algorithms**

- **Directed Depth-First Search (DFS):**

  - Explores edges in their direction only.
  - Classifies edges into:
    - **Tree Edges:** Discovery edges forming the DFS forest.
    - **Back Edges:** Edges leading to an ancestor.
    - **Forward Edges:** Edges to a descendant in the tree.
    - **Cross Edges:** All other edges.

- **Reachability:**
  - A directed DFS from vertex $v$ identifies all vertices reachable from $v$.

---

### **4. Strong Connectivity**

- **Definition:**

  - A directed graph is strongly connected if every vertex can reach every other vertex.

- **Algorithm for Strong Connectivity:**

  1. Perform a DFS from an arbitrary vertex $v$ in $G$.
  2. Reverse the directions of all edges in $G$ (producing $G'$).
  3. Perform another DFS from $v$ in $G'$.

  - If all vertices are visited in both cases, the graph is strongly connected.
  - Complexity: $O(n + m)$.

- **Strongly Connected Components (SCCs):**
  - Maximal subgraphs where all vertices are mutually reachable.

---

### **5. Transitive Closure**

- **Definition:**

  - The transitive closure $G^\*$ of a directed graph $G$ adds a directed edge $(u, v)$ if $G$ has a directed path from $u$ to $v$.

- **Computation:**
  - **DFS-based Approach:**
    - Perform a DFS from each vertex.
    - Complexity: $O(n(n + m))$.
  - **Floyd-Warshall Algorithm:**
    - Iteratively considers paths through vertices $v_1, v_2, \dots, v_k$.
    - Complexity: $O(n^3)$ using adjacency matrix representation.

---

### **6. Directed Acyclic Graphs (DAGs)**

- **Definition:**

  - A DAG is a directed graph with no cycles.

- **Topological Sorting:**
  - Orders vertices $v_1, v_2, \dots, v_n$ such that for every edge $(v_i, v_j)$, $i < j$.
  - Applications:
    - Task scheduling where tasks depend on prior tasks.
- **Algorithms for Topological Sorting:**
  1. **Edge-Based Algorithm:**
     - Iteratively remove vertices with no outgoing edges.
     - Complexity: $O(n + m)$.
  2. **DFS-Based Algorithm:**
     - Perform a DFS and label vertices in reverse post-order.
     - Complexity: $O(n + m)$.

---

## ❓ **Questions Raised**

1. What is the practical impact of edge density on algorithm choice for directed graphs?
2. How can transitive closure computations be optimized for sparse graphs?
3. Can topological sorting handle dynamic changes (e.g., adding edges)?

---

## 🔗 **Further Reading/Resources**

- [Directed Graphs Overview](https://en.wikipedia.org/wiki/Directed_graph)
- [Floyd-Warshall Algorithm - GeeksforGeeks](https://www.geeksforgeeks.org/floyd-warshall-algorithm-dp-16/)
- [Topological Sorting Explanation](https://en.wikipedia.org/wiki/Topological_sorting)

---

## 📌 **Summary**

- **Main Takeaways:**
  - Directed graphs model directional relationships effectively.
  - Strong connectivity and transitive closure provide insights into graph reachability.
  - DAGs are key in scheduling problems and require efficient sorting algorithms.
- **How This Links to Previous Content:**
  - Builds on graph traversal and introduces directed-specific concepts.

---

## ✅ **Action Items**

- Implement DFS and Floyd-Warshall for directed graphs.
- Analyze real-world datasets for SCCs and transitive closures.
- Explore applications of DAGs in scheduling and project management.

---

### **Lecture Review**

- **What I Learned:**
  - How directed graphs model complex relationships.
  - Efficient methods for analyzing connectivity and sorting.
- **What Needs Clarification:**
  - Applications of SCCs in dynamic network analysis.
- **My Plan to Review This Material:**
  - Implement algorithms and test them on synthetic and real datasets.
