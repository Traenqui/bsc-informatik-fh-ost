# 📚 **Lecture Notes**

---

## 🗓️ **Course Details**

- **Course Title:** Algorithms and Data Structures
- **Lecture Title 1:** Depth-First Search (DFS)
- **Lecture Title 2:** Breadth-First Search (BFS)
- **Lecturer Name:** Thomas Letsch
- **Date:** 27.11.2024
- **Lecture Numbers:** 11

---

## 📝 **Key Topics Covered**

### Depth-First Search (DFS)

1. Basic Concepts and Applications
2. DFS Algorithm and Implementation
3. Properties and Analysis
4. Specialized Applications (Path Finding, Cycle Detection)

### Breadth-First Search (BFS)

1. Basic Concepts and Applications
2. BFS Algorithm and Implementation
3. Properties and Analysis
4. BFS Applications and Comparisons to DFS

---

## 🧠 **Learning Objectives**

- Understand the mechanics of DFS and BFS and their traversal patterns.
- Learn how to apply DFS and BFS to solve common graph problems.
- Analyze the performance and limitations of both algorithms.
- Identify use cases for DFS vs. BFS and specialized extensions of each.

---

## 📖 **Detailed Notes**

### **1. Graph Basics**

#### **Definitions**

- **Graph**: $G = (V, E)$, where $V$ is a set of vertices, and $E$ is a set of edges connecting pairs of vertices.

  - **Directed Graph**: Edges have a direction ($(u, v)$).
  - **Undirected Graph**: Edges have no direction ($\{u, v\}$).

- **Path**: Sequence of vertices connected by edges.

  - **Simple Path**: No vertex is repeated.

- **Cycle**: Path that starts and ends at the same vertex.
  - **Simple Cycle**: No edge or vertex is repeated, except for the start/end vertex.

#### **Graph Representations**

- **Edge List**:
  - Stores all edges as pairs of vertices.
- **Adjacency List**:
  - Lists neighbors for each vertex.
  - Space: $O(n + m)$.
- **Adjacency Matrix**:
  - A 2D array indicating edge presence.
  - Space: $O(n^2)$.

#### **Properties**

- Degree: Number of edges incident to a vertex.
- Connected Graph: Path exists between any two vertices.
- Spanning Tree: Subgraph that includes all vertices and is a tree.

---

### **2. Depth-First Search (DFS)**

#### **Key Points**

- DFS explores as far as possible along a branch before backtracking.
- Visits all vertices and edges, determining connectivity and spanning forests.

#### **DFS Algorithm**

1. Start at a vertex $v$, mark it as visited.
2. Recursively visit all unvisited neighbors.
3. Use labels for vertices and edges:

   - **Discovery Edges:** Part of the DFS forest.
   - **Back Edges:** Lead to ancestors, indicating cycles.

   **Pseudocode:**

   ```python
   def DFS(G, v):
       mark v as VISITED
       for each edge (v, w) in G:
           if w is UNVISITED:
               mark (v, w) as DISCOVERY
               DFS(G, w)
           else:
               mark (v, w) as BACK
   ```

#### **Properties**

1. **Traversal Coverage:** Visits all vertices and edges in a component.
2. **Spanning Tree:** Forms a spanning forest for disconnected graphs.
3. **Time Complexity:** $O(n + m)$ for $n$ vertices and $m$ edges with adjacency lists.

#### **Applications**

- Path Finding:
  - Use DFS with a stack to track paths between vertices.
- Cycle Detection:
  - Identify cycles via back edges during traversal.

---

### **3. Breadth-First Search (BFS)**

#### **Key Points**

- BFS explores all neighbors at the current depth before moving deeper.
- Forms a level-order traversal.

#### **BFS Algorithm**

1. Initialize a queue with the starting vertex.
2. Process each vertex, enqueue its unvisited neighbors, and mark them as visited.
3. Label edges:

   - **Discovery Edges:** Connect levels.
   - **Cross Edges:** Between already visited vertices.

   **Pseudocode:**

   ```python
   def BFS(G, s):
       queue = [s]
       mark s as VISITED
       while queue is not empty:
           v = dequeue(queue)
           for each edge (v, w) in G:
               if w is UNVISITED:
                   mark (v, w) as DISCOVERY
                   enqueue(queue, w)
               else:
                   mark (v, w) as CROSS
   ```

#### **Properties**

1. **Traversal Coverage:** Visits all vertices and edges in the component.
2. **Shortest Path:** Guarantees the shortest path in terms of edges from the start vertex.
3. **Time Complexity:** $O(n + m)$ with adjacency lists.

#### **Applications**

- Shortest Path:
  - Efficiently finds paths with the minimum number of edges.
- Connected Components:
  - Identifies components in undirected graphs.

---

### **4. Comparison of DFS and BFS**

| Feature              | DFS                        | BFS                     |
| -------------------- | -------------------------- | ----------------------- |
| Traversal Pattern    | Deep first, then backtrack | Level by level          |
| Time Complexity      | $O(n + m)$                 | $O(n + m)$              |
| Shortest Path        | No                         | Yes (in terms of edges) |
| Spanning Tree/Forest | Yes                        | Yes                     |
| Cycle Detection      | Via back edges             | Less intuitive          |

---

## ❓ **Questions Raised**

1. When is DFS more efficient than BFS in practice?
2. How do edge densities affect DFS and BFS performance?
3. What are the practical limitations of DFS and BFS for large-scale graphs?

---

## 🔗 **Further Reading/Resources**

- [DFS Explanation](https://en.wikipedia.org/wiki/Depth-first_search)
- [BFS Explanation](https://en.wikipedia.org/wiki/Breadth-first_search)
- [Graph Traversal Comparisons](https://www.geeksforgeeks.org/graph-and-its-representations/)

---

## 📌 **Summary**

- **Main Takeaways:**
  - DFS dives deep into branches, useful for pathfinding and cycle detection.
  - BFS is ideal for finding shortest paths and layer-wise exploration.
  - Both algorithms are foundational tools for understanding graph structure.
- **How This Links to Previous Content:**
  - Builds on adjacency list and matrix representations for graphs.

---

## ✅ **Action Items**

- Practice implementing DFS and BFS for directed and undirected graphs.
- Solve real-world graph problems, such as social network analysis or routing.
- Compare the performance of DFS and BFS on different types of graphs.

---

### **Lecture Review**

- **What I Learned:**
  - How DFS and BFS systematically explore graphs.
  - The unique applications and limitations of each algorithm.
- **What Needs Clarification:**
  - Optimization techniques for large-scale graph traversal.
- **My Plan to Review This Material:**
  - Reimplement algorithms with edge cases and test on sample graphs.
