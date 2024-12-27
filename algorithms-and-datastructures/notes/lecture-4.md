# 📚 **Lecture Notes**

---

## 🗓️ **Course Details**

- **Course Title:** Algorithms and Data Structures
- **Lecture Title:** Splay Trees
- **Lecturer Name:** Thomas Letsch
- **Date:** 09.10.2024
- **Lecture Number:** 4

---

## 📝 **Key Topics Covered**

1. Introduction to Splay Trees
2. Splay Operations (Rotations)
3. Splaying Examples
4. Time Complexity and Properties
5. Applications of Splay Trees

---

## 🧠 **Learning Objectives**

- Understand the structure and functionality of Splay Trees.
- Learn the splaying process with rotations for search, insert, and delete operations.
- Analyze the time complexity of splaying and the advantages it provides.
- Explore real-world applications and use cases of Splay Trees.

---

## 📖 **Detailed Notes**

### **1. Introduction to Splay Trees**

- **Definition:**

  - A splay tree is a self-adjusting binary search tree where frequently accessed elements are moved closer to the root using rotations.
  - Splay trees follow the binary search tree (BST) rules:
    - Keys in the left subtree are less than or equal to the root's key.
    - Keys in the right subtree are greater than or equal to the root's key.

- **Key Idea:**
  - After each access (search, insert, or delete), the accessed node is moved to the root using a process called "splaying."

---

### **2. Splay Operations (Rotations)**

#### **Right Rotation:**

- Moves the left child of a node $y$ to its parent position, making $y$ the right child of $x$.

#### **Left Rotation:**

- Moves the right child of a node $x$ to its parent position, making $x$ the left child of $y$.

#### **Splaying Process:**

- **Base Case:**
  - If the accessed node $x$ is the root, stop.
- **Steps:**
  1. **Zig Step:** If $x$ is the child of the root, perform a single rotation.
  2. **Zig-Zig Step:** If $x$ and its parent $y$ are both left (or right) children, perform two rotations in the same direction.
  3. **Zig-Zag Step:** If $x$ is a left child and $y$ is a right child (or vice versa), perform two rotations in opposite directions.

**Example Visualization:**

- **Zig-Zag Case:**
  1. Perform a left rotation on the parent $y$.
  2. Perform a right rotation on the grandparent $z$.

---

### **3. Splaying Examples**

#### **Example 1: Searching for Key $8$:**

1. Locate the node $8$ through a normal BST search.
2. Perform splaying:
   - If $8$ is a grandchild, perform zig-zag or zig-zig steps until $8$ becomes the root.

#### **Example 2: Inserting Key $40$:**

1. Insert $40$ into the tree as a BST.
2. Splay $40$ to the root.

#### **Example 3: Deleting Key $3$:**

1. Splay $3$ to the root.
2. Replace $3$ with its in-order successor or predecessor.

---

### **4. Time Complexity and Properties**

#### **Amortized Time Complexity:**

- The amortized time for a sequence of $m$ operations on a splay tree with $n$ nodes is $O(m \log n)$.
- **Why?**
  - Nodes frequently accessed move closer to the root, reducing future access times.

#### **Worst-Case Time Complexity:**

- A single splay operation may take $O(h)$, where $h$ is the height of the tree.

#### **Advantages:**

- Frequently accessed elements are faster to retrieve.
- No need for explicit rebalancing like AVL or Red-Black Trees.
- Works well for access patterns with locality.

---

### **5. Applications of Splay Trees**

- **Caching:** Efficiently maintains recently accessed elements at the root.
- **Multimaps and Priority Queues:** Handles duplicate keys and dynamically adjusts priorities.
- **Rope Data Structure:** Efficient for string manipulation.
- **Data Compression:** Used in algorithms like move-to-front encoding.

---

## ❓ **Questions Raised**

1. How does splaying affect performance in uniformly random access patterns?
2. Are there scenarios where AVL or Red-Black Trees outperform Splay Trees?
3. What are the space overheads of maintaining parent pointers for rotations?

---

## 🔗 **Further Reading/Resources**

- [Splay Tree Explanation](https://en.wikipedia.org/wiki/Splay_tree)
- [Splay Tree Visualization](https://www.cs.usfca.edu/~galles/visualization/SplayTree.html)
- [Amortized Analysis of Splay Trees](https://www.geeksforgeeks.org/splay-tree-set-1-insert/)

---

## 📌 **Summary**

- **Main Takeaways:**
  - Splay Trees provide efficient amortized $O(\log n)$ access time.
  - Splaying dynamically adjusts tree structure, improving performance for frequent accesses.
  - Unlike AVL or Red-Black Trees, Splay Trees don't require strict balancing.
- **How This Links to Previous Content:**
  - Builds on binary search trees and introduces self-adjusting mechanisms for dynamic workloads.

---

## ✅ **Action Items**

- Implement splay trees and test performance with different access patterns.
- Explore real-world datasets where splay trees outperform traditional BSTs.
- Compare splay trees with AVL and Red-Black Trees for mixed operations.

---

### **Lecture Review**

- **What I Learned:**
  - The mechanics of splaying and its impact on tree structure.
  - How self-adjusting properties optimize access patterns.
- **What Needs Clarification:**
  - Optimal scenarios for using Splay Trees over other balanced BSTs.
- **My Plan to Review This Material:**
  - Implement and visualize splaying for operations like search, insert, and delete.
