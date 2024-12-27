# 📚 **Lecture Notes**

---

## 🗓️ **Course Details**

- **Course Title:** Algorithms and Data Structures
- **Lecture Title:** Merge-Sort and Quick-Sort
- **Lecturer Name:** Thomas Letsch
- **Date:** 16.10.2024
- **Lecture Numbers:** 5

---

## 📝 **Key Topics Covered**

### Merge-Sort

1. Divide-and-Conquer Paradigm
2. Merge-Sort Algorithm
3. Time Complexity and Analysis
4. Non-Recursive Merge-Sort

### Quick-Sort

1. Divide-and-Conquer Paradigm
2. Quick-Sort Algorithm and Partitioning
3. Time Complexity: Best, Average, and Worst Case
4. In-Place Quick-Sort

---

## 🧠 **Learning Objectives**

- Understand the divide-and-conquer paradigm for sorting.
- Learn and implement Merge-Sort and Quick-Sort algorithms.
- Analyze the performance trade-offs of both sorting methods.
- Explore in-place optimizations for Quick-Sort.

---

## 📖 **Detailed Notes**

### **1. Merge-Sort**

#### **Algorithm:**

- **Divide:** Split the sequence into two halves.
- **Recur:** Recursively sort each half.
- **Conquer:** Merge the sorted halves into a single sorted sequence.

**Pseudocode:**

```python
def mergeSort(S):
    if len(S) > 1:
        mid = len(S) // 2
        S1 = S[:mid]
        S2 = S[mid:]
        mergeSort(S1)
        mergeSort(S2)
        merge(S1, S2, S)
```

#### **Merging Process:**

- Combine two sorted lists $A$ and $B$ into a single sorted list $S$ in $O(n)$.

**Pseudocode:**

```python
def merge(A, B, S):
    i = j = k = 0
    while i < len(A) and j < len(B):
        if A[i] < B[j]:
            S[k] = A[i]
            i += 1
        else:
            S[k] = B[j]
            j += 1
        k += 1
    while i < len(A):
        S[k] = A[i]
        i += 1
        k += 1
    while j < len(B):
        S[k] = B[j]
        j += 1
        k += 1
```

#### **Time Complexity:**

- Splitting: $O(\log n)$.
- Merging: $O(n)$.
- **Total:** $O(n \log n)$.

#### **Key Properties:**

- Stable sorting algorithm.
- Not in-place due to auxiliary space requirements.

#### **Non-Recursive Merge-Sort:**

- Uses iterative merging of subarrays of increasing size until the entire array is sorted.

---

### **2. Quick-Sort**

#### **Algorithm:**

- **Divide:** Select a pivot element and partition the sequence into:
  - $L$: Elements less than the pivot.
  - $E$: Elements equal to the pivot.
  - $G$: Elements greater than the pivot.
- **Recur:** Recursively sort $L$ and $G$.
- **Conquer:** Combine $L, E,$ and $G$.

**Pseudocode:**

```python
def quickSort(S):
    if len(S) < 2:
        return S
    pivot = S[0]
    L = [x for x in S if x < pivot]
    E = [x for x in S if x == pivot]
    G = [x for x in S if x > pivot]
    return quickSort(L) + E + quickSort(G)
```

#### **Partitioning:**

- Rearranges elements in-place, reducing memory usage.

**Pseudocode:**

```python
def partition(S, low, high):
    pivot = S[high]
    i = low - 1
    for j in range(low, high):
        if S[j] <= pivot:
            i += 1
            S[i], S[j] = S[j], S[i]
    S[i + 1], S[high] = S[high], S[i + 1]
    return i + 1
```

#### **Time Complexity:**

- **Best Case:** $O(n \log n)$ when partitions are balanced.
- **Worst Case:** $O(n^2)$ when one partition is empty.
- **Average Case:** $O(n \log n)$.

#### **Key Properties:**

- In-place and efficient for large datasets.
- Unstable due to potential reordering of equal elements.

---

## ❓ **Questions Raised**

1. How do pivot selection strategies affect Quick-Sort's performance?
2. What are the trade-offs between Merge-Sort and Quick-Sort for large datasets?

---

## 🔗 **Further Reading/Resources**

- [Merge-Sort Explanation](https://en.wikipedia.org/wiki/Merge_sort)
- [Quick-Sort Explanation](https://en.wikipedia.org/wiki/Quicksort)
- [Sorting Algorithm Comparisons](https://www.geeksforgeeks.org/sorting-algorithms/)

---

## 📌 **Summary**

- **Main Takeaways:**
  - Merge-Sort and Quick-Sort are efficient divide-and-conquer sorting algorithms.
  - Merge-Sort is stable and ideal for datasets requiring stability.
  - Quick-Sort is in-place and generally faster, but its performance depends on pivot selection.
- **How This Links to Previous Content:**
  - Builds on basic sorting techniques and introduces advanced recursive strategies.

---

## ✅ **Action Items**

- Implement Merge-Sort and Quick-Sort on different datasets.
- Explore hybrid approaches combining the strengths of both algorithms.
- Study variations of Quick-Sort with different pivot selection methods.

---

### **Lecture Review**

- **What I Learned:**
  - Divide-and-conquer simplifies complex sorting tasks.
  - Practical considerations, such as stability and space usage, guide algorithm choice.
- **What Needs Clarification:**
  - Performance trade-offs on highly unbalanced data.
- **My Plan to Review This Material:**
  - Experiment with recursive and iterative implementations to solidify understanding.
