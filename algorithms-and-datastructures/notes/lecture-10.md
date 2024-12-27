# 📚 **Lecture Notes**

---

## 🗓️ **Course Details**

- **Course Title:** Algorithms and Data Structures
- **Lecture Title:** Dynamic Programming
- **Lecturer Name:** Thomas Letsch
- **Date:** 21.10.2024
- **Lecture Number:** 10

---

## 📝 **Key Topics Covered**

1. Introduction to Dynamic Programming
2. Knapsack Problem
3. Longest Common Subsequence (LCS)
4. Characteristics and Requirements of Dynamic Programming

---

## 🧠 **Learning Objectives**

- Understand the principles of dynamic programming as an algorithm design paradigm.
- Apply dynamic programming to solve optimization problems efficiently.
- Explore examples such as the Knapsack Problem and Longest Common Subsequence.
- Learn the trade-offs of dynamic programming compared to brute force and greedy approaches.

---

## 📖 **Detailed Notes**

### **1. Introduction to Dynamic Programming**

- **Definition:**

  - A method for solving complex problems by breaking them down into simpler subproblems.
  - Stores solutions to subproblems to avoid redundant computations.

- **Key Characteristics:**
  - **Optimal Substructure:** The optimal solution of the problem can be constructed from optimal solutions of its subproblems.
  - **Overlapping Subproblems:** Subproblems recur multiple times.

---

### **2. Knapsack Problem**

#### **Problem Statement:**

- Given:
  - $n$ items, each with a weight $w_i$ and value $v_i$.
  - A knapsack with capacity $W$.
- Find:
  - A subset of items to maximize the total value without exceeding the weight limit.

#### **Brute Force Approach:**

- Enumerate all subsets of items.
- Complexity: $O(2^n)$.

#### **Greedy Algorithm:**

- Choose items with the highest $\text{value/weight}$ ratio.
- May lead to suboptimal solutions.

#### **Dynamic Programming Approach:**

- Define $dp[i][j]$: Maximum value attainable with the first $i$ items and weight limit $j$.
- Recurrence Relation:
  $$
  dp[i][j] =
  \begin{cases}
  dp[i-1][j] & \text{if } w_i > j \\
  \max(dp[i-1][j], dp[i-1][j-w_i] + v_i) & \text{otherwise}
  \end{cases}
  $$
- Complexity: $O(nW)$.

---

### **3. Longest Common Subsequence (LCS)**

#### **Problem Statement:**

- Given two strings $X$ and $Y$, find the longest subsequence common to both.

#### **Brute Force Approach:**

- Generate all subsequences of $X$, test for presence in $Y$.
- Complexity: $O(2^n)$.

#### **Dynamic Programming Approach:**

- Define $L[i][j]$: Length of LCS for substrings $X[0..i]$ and $Y[0..j]$.
- Recurrence Relation:
  $$
  L[i][j] =
  \begin{cases}
  L[i-1][j-1] + 1 & \text{if } X[i] = Y[j] \\
  \max(L[i-1][j], L[i][j-1]) & \text{otherwise}
  \end{cases}
  $$
- Complexity: $O(nm)$, where $n$ and $m$ are lengths of $X$ and $Y$.

---

### **4. Characteristics and Requirements**

- **Requirements for Applicability:**

  - Problem can be broken into subproblems.
  - Subproblems have overlapping computations.
  - Optimal solutions to subproblems lead to the global solution.

- **Advantages:**

  - Reduces exponential complexity to polynomial in many cases.

- **Disadvantages:**
  - Requires memory for storing intermediate results.
  - May not work well if subproblems are too numerous.

---

## ❓ **Questions Raised**

1. How can dynamic programming be adapted for problems with additional constraints?
2. What are the trade-offs between space and time complexity in dynamic programming?

---

## 🔗 **Further Reading/Resources**

- [Dynamic Programming Concepts](https://en.wikipedia.org/wiki/Dynamic_programming)
- [Knapsack Problem - GeeksforGeeks](https://www.geeksforgeeks.org/0-1-knapsack-problem-dp-10/)
- [Longest Common Subsequence](https://www.geeksforgeeks.org/longest-common-subsequence-dp-4/)

---

## 📌 **Summary**

- **Main Takeaways:**
  - Dynamic programming avoids recomputation by storing intermediate results.
  - Knapsack and LCS exemplify its utility in solving optimization and sequence alignment problems.
  - Key trade-offs include increased memory usage for substantial performance gains.
- **How This Links to Previous Content:**
  - Builds on recursion and introduces efficient tabulation and memoization techniques.

---

## ✅ **Action Items**

- Implement dynamic programming solutions for various problem classes.
- Explore space optimization techniques, such as rolling arrays.
- Apply dynamic programming to real-world optimization problems.

---

### **Lecture Review**

- **What I Learned:**
  - How dynamic programming transforms exponential problems into polynomial solutions.
  - Application of dynamic programming in solving optimization and sequence alignment tasks.
- **What Needs Clarification:**
  - Handling dynamic programming on sparse data structures.
- **My Plan to Review This Material:**
  - Solve diverse problems using dynamic programming to understand patterns and edge cases.
