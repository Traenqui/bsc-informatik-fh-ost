# 📚 **Lecture Notes**

## 🗓️ **Course Details**

- **Course Title:** Betriebssysteme 1
- **Lecture Title:** Virtueller Speicher Software
- **Lecturer Name:** Felix Morgner
- **Date:** 03.12.2024
- **Lecture Number:** 12

## 📝 **Key Topics Covered**

1. Paging and Threshing
2. Page Fetching Strategies
3. Cleaning Strategies
4. Replacement Strategies
5. Practical Implementations and Examples

## 🧠 **Learning Objectives**

- Describe how virtual memory software mechanisms improve memory utilization.
- Explain the concepts of paging, fetching, and cleaning strategies.
- Understand various page replacement strategies and their impacts.

## 📖 **Detailed Notes**

### **1. Paging**

- **Key Insights:**
  - Virtual memory divided into fixed-size pages (typically 4 KB).
  - MMU translates virtual addresses to physical addresses.
  - Present Bit (`P-Bit`): Indicates whether a page is in memory (1) or not (0).
- **When `P = 0`:**
  - OS determines location, fetches the page from secondary storage.
  - Errors like segmentation faults occur if page data is invalid.

### **2. Threshing**

- **Definition:**
  - Excessive paging activity due to:
    - Insufficient memory.
    - Too many processes.
- **Mitigation:**
  - Increase physical memory.
  - Limit active processes.
  - Optimize paging strategies.

### **3. Fetching Strategies**

#### **Demand Paging:**

- Pages loaded only when needed.
- **Advantages:** Minimal overhead.
- **Disadvantages:** High latency on first access.

#### **Prepaging:**

- Predicts required pages and loads them proactively.
- Utilizes static analysis or process tracking.
- Rarely used alone due to complexity.

#### **Demand Paging with Prepaging:**

- Combines both strategies.
- Loads adjacent pages based on locality principles.
- **Advantages:**
  - Fewer page faults.
  - Improved secondary storage efficiency.
- **Disadvantages:** May load unnecessary pages.

### **4. Cleaning Strategies**

#### **Demand Cleaning:**

- Pages are written back to disk only when reused.
- **Advantages:** Minimal effort.
- **Disadvantages:** Increased latency during reuse.

#### **Precleaning:**

- Modified pages are written back proactively.
- **Advantages:**
  - Reduced delays during page faults.
- **Disadvantages:**
  - Wasted effort if pages are modified again.

### **5. Replacement Strategies**

- **Key Goal:** Determine which page to evict when memory is full.

#### **FIFO (First-In-First-Out):**

- Replaces the oldest page.
- **Disadvantages:**
  - Suffers from Belady's anomaly (larger memory causing more faults).

#### **Second Chance:**

- Extends FIFO with a use check:
  - Pages not recently used (A-Bit = 0) are removed.
  - If used, page is marked and moved to the end of the queue.

#### **Clock:**

- Efficient implementation of Second Chance.
- Pages organized in a circular list (clock-like structure).

#### **Least Recently Used (LRU):**

- Evicts the least recently accessed page.
- **Challenges:**
  - Hardware overhead for tracking last access.

#### **Not Frequently Used (NFU):**

- Tracks access frequency over intervals.
- **Aging Enhancement:**
  - Weights recent accesses more heavily.

#### **Working Set:**

- Keeps pages used within a defined interval.
- **WSClock:** Optimized version using a clock structure.

### **6. Practical Examples**

#### **Demand Paging with Prepaging:**

- Fetches clusters of pages (e.g., 4–8 pages).
- Balances latency and prefetching overhead.

#### **FIFO Example:**

- Simple linked list tracks order of loading.
- Removes the oldest page during eviction.

#### **LRU Implementation:**

- Timestamp-based approach:
  - MMU records access time for each page.

## ❓ **Questions Raised**

- What are the performance implications of aging in NFU?
- How does prepaging balance proactive and reactive memory management?

## 🔗 **Further Reading/Resources**

- [Virtual Memory in Operating Systems](https://en.wikipedia.org/wiki/Virtual_memory)
- [Paging Strategies Overview](https://www.geeksforgeeks.org/paging-in-operating-system/)
- [Belady's Anomaly](https://www.sciencedirect.com/topics/computer-science/beladys-anomaly)

## 📌 **Summary**

- **Main Takeaways:**
  - Paging supports efficient memory management by breaking memory into manageable blocks.
  - Fetching and cleaning strategies directly impact system responsiveness.
  - Replacement strategies are crucial for maintaining performance under memory constraints.
- **How This Links to Previous Content:**
  - Expands on hardware-based memory management by exploring software-level optimizations.

## ✅ **Action Items**

- Simulate different replacement strategies and analyze performance.
- Experiment with varying page sizes and evaluate impacts on performance.
- Research real-world applications of WSClock in modern systems.

### **Lecture Review**

- **What I Learned:**
  - Deep understanding of how virtual memory operates at the software level.
  - Comparative analysis of different memory management strategies.
- **What Needs Clarification:**
  - Practical deployment of fetching strategies in dynamic workloads.
- **My Plan to Review This Material:**
  - Test fetching and replacement strategies using memory management simulators.
