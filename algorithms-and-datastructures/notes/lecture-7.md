# 📚 **Lecture Notes**

---

## 🗓️ **Course Details**

- **Course Title:** Algorithms and Data Structures
- **Lecture Title:** Bucket-Sort and Radix-Sort
- **Lecturer Name:** Thomas Letsch
- **Date:** 30.10.2024
- **Lecture Number:** 7

---

## 📝 **Key Topics Covered**

1. Bucket-Sort Algorithm
2. Properties and Extensions of Bucket-Sort
3. Lexicographic Sorting
4. Radix-Sort Algorithm
5. Applications of Radix-Sort for Binary Numbers

---

## 🧠 **Learning Objectives**

- Understand the mechanics and applications of Bucket-Sort and Radix-Sort.
- Learn the use of Bucket-Sort for efficient sorting of numeric data.
- Explore lexicographic sorting for multi-dimensional data.
- Implement Radix-Sort for large datasets with integer and binary keys.

---

## 📖 **Detailed Notes**

### **1. Bucket-Sort**

#### **Definition:**

- **Input:** A sequence $S$ of $n$ key-value pairs, with keys in the range \([0, N-1]\).
- **Steps:**
  1. Use keys as indices to place items into buckets.
  2. Concatenate all buckets in order.

#### **Algorithm:**

```python
def bucketSort(S, N):
    B = [empty_sequence() for _ in range(N)]
    for item in S:
        key = item.key
        B[key].append(item)
    S = []
    for bucket in B:
        S.extend(bucket)
```

#### **Complexity:**

- **Time:**
  - Phase 1 (bucket allocation): $O(n)$
  - Phase 2 (bucket merging): $O(N + n)$
  - **Total:** $O(n + N)$.

---

### **2. Properties and Extensions of Bucket-Sort**

- **Key Features:**

  - Keys are treated as indices, requiring numeric keys.
  - **Stability:** Preserves the order of entries with equal keys.

- **Extensions:**
  - **Integer Keys in Range \([a, b]\):**
    - Shift keys into the range \([0, N-1]\).
  - **String Keys:**
    - Map each string to an index using a predefined sorted list.

---

### **3. Lexicographic Sorting**

#### **Definition:**

- Sorts $d$-dimensional tuples \((k_1, k_2, \dots, k_d)\) in lexicographic order.
- Compares dimensions sequentially:
  \[
  (x_1, x_2, \dots, x_d) < (y_1, y_2, \dots, y_d) \iff x_1 < y_1 \text{ or } (x_1 = y_1 \text{ and } (x_2, \dots, x_d) < (y_2, \dots, y_d)).
  \]

#### **Algorithm:**

```python
def lexicographicSort(S, d):
    for i in range(d, 0, -1):
        stableSort(S, Ci)
```

#### **Complexity:**

- $O(d \cdot T(n))$, where $T(n)$ is the complexity of the stable sort.

---

### **4. Radix-Sort**

#### **Definition:**

- A specialized lexicographic sort for integer tuples.
- Uses Bucket-Sort as the stable sorting algorithm.

#### **Steps:**

1. Sort tuples by the least significant dimension.
2. Progressively sort by higher dimensions.

#### **Algorithm:**

```python
def radixSort(S, N, d):
    for i in range(d, 0, -1):
        bucketSort(S, N, i)
```

#### **Complexity:**

- **Time:** $O(d \cdot (n + N))$.

---

### **5. Radix-Sort for Binary Numbers**

#### **Definition:**

- Sorts $b$-bit integers using Radix-Sort with $N = 2$.
- Represents each integer as a tuple of $b$ binary digits.

#### **Steps:**

1. Replace each integer with its binary representation.
2. Apply Radix-Sort on binary dimensions.

#### **Complexity:**

- $O(b \cdot n)$.

#### **Example:**

- Sorting a sequence of 4-bit integers:
  - Initial: \([1001, 0010, 1101, 0001, 1110]\)
  - Step-by-step sorting by each bit yields:
    - Final: \([0001, 0010, 1001, 1101, 1110]\).

---

## ❓ **Questions Raised**

1. How does Bucket-Sort perform on sparse datasets with large ranges?
2. What are the memory implications of Radix-Sort for high-dimensional data?
3. Can Radix-Sort be extended to support floating-point numbers?

---

## 🔗 **Further Reading/Resources**

- [Bucket-Sort Algorithm](https://en.wikipedia.org/wiki/Bucket_sort)
- [Radix-Sort Explanation](https://en.wikipedia.org/wiki/Radix_sort)
- [Lexicographic Sorting](https://en.wikipedia.org/wiki/Lexicographical_order)

---

## 📌 **Summary**

- **Main Takeaways:**
  - Bucket-Sort and Radix-Sort are efficient for sorting numeric and tuple data.
  - Radix-Sort achieves linear-time sorting under specific conditions.
  - Both algorithms leverage stability for multi-dimensional sorting.
- **How This Links to Previous Content:**
  - Extends foundational sorting concepts by introducing stable, key-based sorting mechanisms.

---

## ✅ **Action Items**

- Implement Bucket-Sort and Radix-Sort for sample datasets.
- Test performance on large datasets with varying key ranges.
- Explore applications in lexicographic ordering and binary data sorting.

---

### **Lecture Review**

- **What I Learned:**
  - The efficiency of Bucket-Sort and Radix-Sort for specific data types.
  - The utility of stability in sorting algorithms.
- **What Needs Clarification:**
  - Adapting Radix-Sort for variable-length keys.
- **My Plan to Review This Material:**
  - Solve practical problems using Bucket-Sort and Radix-Sort implementations.
