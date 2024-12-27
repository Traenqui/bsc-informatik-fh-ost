# 📚 **Lecture Notes**

---

## 🗓️ **Course Details**

- **Course Title:** Data Structures and Algorithms
- **Lecture Title:** Binary Search Trees (BSTs)
- **Lecturer Name:** Thomas Letsch
- **Date:** 18.09.2024
- **Lecture Number:** 1

---

## 📝 **Key Topics Covered**

1. Introduction to Binary Search Trees (BSTs)
2. Operations on Binary Search Trees (Search, Insert, Delete)
3. Performance Analysis
4. BST Implementation in Java

---

## 🧠 **Learning Objectives**

- Understand the structure and properties of binary search trees.
- Learn how to perform key operations: search, insert, and delete.
- Analyze the performance and height implications of BSTs.
- Understand Java implementation for BSTs.

---

## 📖 **Detailed Notes**

### **1. Introduction to Binary Search Trees (BSTs)**

- **Definition:**
  - A binary search tree is a binary tree where:
    - Keys are stored in internal nodes.
    - For each node `v`, keys in the left subtree are ≤ `key(v)`.
    - Keys in the right subtree are ≥ `key(v)`.
- **Traversal:**
  - Inorder traversal visits keys in non-decreasing order.
  - Leaf nodes (external nodes) do not store data.

---

### **2. Operations on Binary Search Trees**

#### **Search**

- **Algorithm:**
  - Start at the root.
  - Compare the target key `k` with the current node's key.
  - Traverse left if `k < key(v)` or right if `k > key(v)`.
  - Stop if `k = key(v)` or a leaf is reached.
- **Example:**
  - Searching for 4 in the BST involves traversing nodes 6 → 4.

#### **Insertion**

- **Procedure:**
  - Use the search operation to locate the appropriate leaf.
  - Replace the leaf with a new internal node containing the key.
- **Example:**
  - Inserting 5 expands the tree by adding a new node at the correct position.

#### **Deletion**

- **Cases:**
  1. **Node with two children:**
     - Replace the node with its inorder successor and delete the successor.
  2. **Node with one child:**
     - Remove the node and connect its parent directly to its child.
  3. **Leaf node:**
     - Simply remove the node.
- **Example:**
  - Removing node 3 involves replacing it with its inorder successor.

---

### **3. Performance Analysis**

- **Time Complexity:**
  - Space: $O(n)$ for `n` entries.
  - Operations (find, insert, remove):
    - $O(h)$, where $h$ is the height of the tree.
    - Best case: $O(\log n)$ (balanced tree).
    - Worst case: $O(n)$ (degenerate tree).
- **Height of BST:**
  - $O(\log n)$ for a balanced tree.
  - $O(n)$ for an unbalanced tree.

---

### **4. BST Implementation in Java**

#### **Node Class**

```java
public class Node {
    Node leftSon, rightSon;
    int key;

    Node(int key) {
        this.key = key;
    }

    public String toString() {
        return String.valueOf(key);
    }
}
```

#### **Tree Class**

- **Search Method:**

```java
Node search(Node root, int key) {
    if (root == null || root.key == key)
        return root;
    if (key < root.key)
        return search(root.leftSon, key);
    return search(root.rightSon, key);
}
```

- **Insert Method:**

```java
Node insert(Node root, int key) {
    if (root == null)
        return new Node(key);
    if (key < root.key)
        root.leftSon = insert(root.leftSon, key);
    else if (key > root.key)
        root.rightSon = insert(root.rightSon, key);
    return root;
}
```

- **Delete Method:**

```java
Node delete(Node root, int key) {
    if (root == null) return root;
    if (key < root.key)
        root.leftSon = delete(root.leftSon, key);
    else if (key > root.key)
        root.rightSon = delete(root.rightSon, key);
    else {
        if (root.leftSon == null) return root.rightSon;
        if (root.rightSon == null) return root.leftSon;
        Node successor = getInorderSuccessor(root.rightSon);
        root.key = successor.key;
        root.rightSon = delete(root.rightSon, successor.key);
    }
    return root;
}
```

---

## ❓ **Questions Raised**

- What are strategies to balance a BST to ensure $O(\log n)$ height?
- How does the BST performance compare to other search structures like hash tables?

---

## 🔗 **Further Reading/Resources**

- [Balanced Search Trees (AVL Trees)](https://en.wikipedia.org/wiki/AVL_tree)
- [Binary Search Trees on GeeksforGeeks](https://www.geeksforgeeks.org/binary-search-tree/)

---

## 📌 **Summary**

- **Main Takeaways:**
  - BSTs offer efficient search, insert, and delete operations.
  - Their performance depends on the height of the tree.
  - Proper balancing is crucial to maintaining optimal performance.
- **How This Links to Previous Content:**
  - Builds on knowledge of binary trees and sorting algorithms.

---

## ✅ **Action Items**

- Implement a BST and test all operations.
- Research tree balancing techniques like AVL or Red-Black Trees.

---

### **Lecture Review**

- **What I Learned:**
  - Clear understanding of BST structure and operations.
- **What Needs Clarification:**
  - Advanced balancing techniques for BSTs.
- **My Plan to Review This Material:**
  - Practice implementing a BST and study balancing algorithms.
