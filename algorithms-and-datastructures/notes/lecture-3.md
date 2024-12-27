# 📚 **Lecture Notes**

---

## 🗓️ **Course Details**

- **Course Title:** Data Structures and Algorithms
- **Lecture Title:** Splay Trees
- **Lecturer Name:** Thomas Letsch
- **Date:** 02.10.2024
- **Lecture Number:** 3

---

## 📝 **Key Topics Covered**

1. Definition and Structure of Splay Trees
2. Splay Operation and Rotations
3. Use Cases of Splay Trees
4. Performance Analysis of Splay Trees

---

## 🧠 **Learning Objectives**

- Understand the concept and purpose of splay trees in dynamic data structures.
- Learn how the splay operation rebalances the tree during access.
- Analyze the efficiency of operations in splay trees.
- Explore practical applications of splay trees, including search and map operations.

---

## 📖 **Detailed Notes**

### **1. Definition and Structure of Splay Trees**

- **Definition:**

  - A splay tree is a self-adjusting binary search tree where recently accessed nodes are moved to the root.
  - Follows standard binary search tree rules:
    - Left subtree contains keys ≤ node’s key.
    - Right subtree contains keys ≥ node’s key.
  - An inorder traversal produces keys in sorted order.

- **Unique Property:**
  - After an operation (search, insert, delete), the target node is splayed (moved) to the root via rotations.

---

### **2. Splay Operation and Rotations**

- **Splay Operation:**

  - Performed to move a node `x` to the root using rotations.
  - **Types of Rotations:**
    1. **Zig-Zig (double rotation):** Occurs when `x` and its parent are both left or right children.
    2. **Zig-Zag (double rotation):** Occurs when `x` is a left child and its parent is a right child, or vice versa.
    3. **Zig (single rotation):** Used when `x` is a child of the root.
  - Example:
    - Searching for a node triggers rotations to bring it to the root.

- **Rotation Mechanics:**
  - **Right Rotation:** Moves the left child to the parent position.
  - **Left Rotation:** Moves the right child to the parent position.

---

### **3. Use Cases of Splay Trees**

- **Dynamic Set Operations:**

  - Frequently accessed elements are closer to the root.
  - Efficient for applications with non-uniform access patterns.

- **Examples:**
  1. **Search:** Brings the target node to the root.
  2. **Insert:** Newly inserted node is splayed to the root.
  3. **Delete:** Splays the node’s parent to the root after removing the node.

---

### **4. Performance Analysis**

- **Average Complexity:** $O(\log n)$
  - Frequently accessed elements remain near the root.
- **Worst-Case Complexity:** $O(n)$
  - Occurs if the tree degenerates into a linked list structure.
- **Amortized Cost:** $O(\log n)$

  - Over a sequence of operations, the cost of each operation is low.

- **Advantages:**

  - Simpler implementation than AVL or Red-Black Trees.
  - No need to store height or balance factors.

- **Disadvantages:**
  - No strict balance; relies on access frequency for efficiency.

---

## ❓ **Questions Raised**

- What are the specific scenarios where splay trees outperform other balanced search trees?
- How does the splay operation affect long-term tree structure and efficiency?

---

## 🔗 **Further Reading/Resources**

- [Introduction to Splay Trees](https://www.geeksforgeeks.org/splay-tree/)
- [Splay Trees on Wikipedia](https://en.wikipedia.org/wiki/Splay_tree)

---

## 📌 **Summary**

- **Main Takeaways:**
  - Splay trees dynamically adjust based on access patterns.
  - Rotations (zig-zig, zig-zag, zig) are key to rebalancing the tree.
  - Amortized $O(\log n)$ performance makes them suitable for dynamic workloads.
- **How This Links to Previous Content:**
  - Builds on the concept of binary search trees, extending functionality with self-adjusting properties.

---

## ✅ **Action Items**

- Implement a splay tree and test with operations like search, insert, and delete.
- Compare splay trees with AVL and Red-Black Trees for specific use cases.

---

### **Lecture Review**

- **What I Learned:**
  - Detailed understanding of splay operations and their impact on tree structure.
- **What Needs Clarification:**
  - Practical performance comparison with other self-balancing trees.
- **My Plan to Review This Material:**
  - Practice implementing splay trees and analyze performance with different data access patterns.
