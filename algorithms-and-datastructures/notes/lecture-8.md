# 📚 **Lecture Notes**

---

## 🗓️ **Course Details**

- **Course Title:** Algorithms and Data Structures
- **Lecture Title:** Pattern Matching
- **Lecturer Name:** Thomas Letsch
- **Date:** 07.11.2024
- **Lecture Number:** 8

---

## 📝 **Key Topics Covered**

1. Strings and Substrings
2. Brute-Force Pattern Matching
3. Boyer-Moore Algorithm
4. Knuth-Morris-Pratt (KMP) Algorithm
5. Efficiency and Applications of Pattern Matching

---

## 🧠 **Learning Objectives**

- Understand the problem of pattern matching and its real-world applications.
- Learn and implement key algorithms for pattern matching.
- Analyze the time complexity of each approach.
- Apply efficient pattern matching techniques to practical scenarios.

---

## 📖 **Detailed Notes**

### **1. Strings and Substrings**

- **Definitions:**

  - **String:** A sequence of characters from a defined alphabet $\Sigma$.
  - **Substring:** A contiguous subsequence of a string.
  - **Prefix:** A substring starting at the first character.
  - **Suffix:** A substring ending at the last character.

- **Problem Statement:**

  - Given a text $T$ of length $n$ and a pattern $P$ of length $m$, find all starting indices in $T$ where $P$ matches.

- **Applications:**
  - Text editors and search engines.
  - DNA sequence analysis.
  - Source code comparison.

---

### **2. Brute-Force Pattern Matching**

- **Algorithm:**
  - Compare $P$ with every possible substring of $T$.
  - If all characters match, return the starting index.

**Pseudocode:**

```python
for i in range(0, n - m + 1):
    for j in range(0, m):
        if T[i + j] != P[j]:
            break
    else:
        return i  # Match found
return -1  # No match
```

- **Time Complexity:**
  - Worst case: $O(nm)$.

---

### **3. Boyer-Moore Algorithm**

- **Key Heuristics:**
  1. **Looking-Glass Heuristic:**
     - Compare $P$ with a substring of $T$, starting from the end of $P$.
  2. **Character-Jump Heuristic:**
     - If a mismatch occurs at $T[i]$:
       - Shift $P$ so that the last occurrence of $T[i]$ in $P$ aligns with $T[i]$.
       - If $T[i]$ is not in $P$, shift $P$ entirely past $T[i]$.

**Algorithm:**

```python
def BoyerMooreMatch(T, P):
    last = buildLastOccurrenceFunction(P)
    i = m - 1  # Index in T
    j = m - 1  # Index in P
    while i < n:
        if T[i] == P[j]:
            if j == 0:
                return i  # Match found
            else:
                i -= 1
                j -= 1
        else:
            i += m - min(j, 1 + last.get(T[i], -1))
            j = m - 1
    return -1  # No match
```

- **Preprocessing:**
  - Compute the "last occurrence" function $L(c)$: $O(m + |\Sigma|)$.
- **Time Complexity:**
  - Best case: $O(n/m)$.
  - Worst case: $O(nm)$, rare for typical text.

---

### **4. Knuth-Morris-Pratt (KMP) Algorithm**

- **Key Idea:**
  - Avoid unnecessary comparisons by leveraging the structure of $P$.
  - Use the "failure function" $F(j)$ to determine the longest prefix of $P[0..j]$ that is also a suffix of $P[1..j]$.

**Failure Function Construction:**

```python
def computeFailFunction(P):
    fail = [0] * len(P)
    j = 0
    for i in range(1, len(P)):
        if P[i] == P[j]:
            fail[i] = j + 1
            j += 1
        elif j > 0:
            j = fail[j - 1]
        else:
            fail[i] = 0
    return fail
```

**Algorithm:**

```python
def KMPMatch(T, P):
    fail = computeFailFunction(P)
    i = j = 0
    while i < len(T):
        if T[i] == P[j]:
            if j == len(P) - 1:
                return i - len(P) + 1  # Match found
            i += 1
            j += 1
        elif j > 0:
            j = fail[j - 1]
        else:
            i += 1
    return -1  # No match
```

- **Time Complexity:**
  - $O(n + m)$, linear for both preprocessing and matching.

---

### **5. Comparison of Algorithms**

| Algorithm   | Best Case Complexity | Worst Case Complexity | Characteristics                                    |
| ----------- | -------------------- | --------------------- | -------------------------------------------------- |
| Brute-Force | $O(m)$               | $O(nm)$               | Simple but inefficient for large texts.            |
| Boyer-Moore | $O(n/m)$             | $O(nm)$               | Efficient with long patterns, needs preprocessing. |
| KMP         | $O(n + m)$           | $O(n + m)$            | Linear time, works well for structured patterns.   |

---

## ❓ **Questions Raised**

1. When is Boyer-Moore faster than KMP?
2. How does text size and alphabet affect performance?
3. What are the limitations of pattern matching on dynamic text?

---

## 🔗 **Further Reading/Resources**

- [Boyer-Moore Algorithm](https://en.wikipedia.org/wiki/Boyer–Moore_string-search_algorithm)
- [Knuth-Morris-Pratt Algorithm](https://en.wikipedia.org/wiki/Knuth–Morris–Pratt_algorithm)
- [Pattern Matching Techniques](https://www.geeksforgeeks.org/pattern-searching/)

---

## 📌 **Summary**

- **Main Takeaways:**
  - Pattern matching is a cornerstone of text processing.
  - Algorithms like Boyer-Moore and KMP optimize matching by preprocessing $P$.
  - Choice of algorithm depends on text size, pattern length, and application context.
- **How This Links to Previous Content:**
  - Builds on basic string manipulation and introduces advanced preprocessing for efficiency.

---

## ✅ **Action Items**

- Implement and compare these algorithms on sample datasets.
- Explore real-world applications like DNA sequence alignment and document indexing.
- Investigate hybrid approaches combining multiple algorithms.

---

### **Lecture Review**

- **What I Learned:**
  - How preprocessing patterns can significantly optimize matching.
  - The differences between heuristic-based and prefix-based approaches.
- **What Needs Clarification:**
  - Adapting these algorithms for approximate matching.
- **My Plan to Review This Material:**
  - Test implementations on varied datasets to understand algorithm trade-offs.
