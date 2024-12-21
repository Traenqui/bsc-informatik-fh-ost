# 📚 **Lecture Notes**


## 🗓️ **Course Details**
- **Course Title:** Betriebssysteme 1
- **Lecture Title:** Hauptspeicher und Cache
- **Lecturer Name:** Felix Morgner
- **Date:** 12.11.2024
- **Lecture Number:** 9


## 📝 **Key Topics Covered**
1. Memory Hierarchy and Principles
2. Cache Concepts and Types
3. Cache Lookup and Replacement Strategies
4. Practical Examples of Cache Operations


## 🧠 **Learning Objectives**
- Explain the necessity of the memory hierarchy in modern systems.
- Use locality principles to write efficient programs.
- Describe the role and operation of caches in computer architecture.


## 📖 **Detailed Notes**

### **1. Memory Hierarchy**
- **Definition:**
  - A layered structure of memory types, balancing speed, cost, and capacity.
  - Includes:
    - Processor Registers
    - Cache (L1, L2, L3)
    - Main Memory (RAM)
    - Secondary Storage (HDD, SSD)
- **Key Insights:**
  - Volatile memory (e.g., cache and RAM) loses data without power.
  - Non-volatile memory (e.g., SSDs) retains data.


### **2. Locality Principles**
- **Temporal Locality:**
  - Data used recently is likely to be reused soon.
  - Example: Variables in a loop.
- **Spatial Locality:**
  - Data near recently accessed memory is likely to be accessed soon.
  - Example: Traversing arrays.
- **Applications:**
  - Efficient use of caches relies on maximizing temporal and spatial locality.


### **3. Cache Overview**
- **Definition:**
  - A small, fast memory layer between the processor and main memory.
- **Cache Metrics:**
  - **Hit:** Data is found in the cache.
  - **Miss:** Data must be fetched from slower memory.
  - **Hit Rate:** Ratio of cache hits to total accesses.
- **Access Time Formula:**
  - $\( E(T) = p_C \cdot T_C + (1 - p_C) \cdot T_M \)$
  - Example Calculation:
    - $\( T_C = 0.01 \cdot T_M, p_C = 0.95 \)$
    - $\( E(T) = 0.0595 \cdot T_M \)$


### **4. Cache Types**
#### **Fully Associative Cache:**
- **Structure:**
  - Any memory block can occupy any cache slot.
- **Advantages:**
  - Maximum flexibility, best locality exploitation.
- **Disadvantages:**
  - High complexity and cost.
- **Lookup Process:**
  - Compares the desired address with all stored addresses simultaneously.

#### **Direct-Mapped Cache:**
- **Structure:**
  - Each memory block maps to one specific cache slot.
- **Advantages:**
  - Simple and fast lookups.
- **Disadvantages:**
  - High collision probability (same slot for multiple blocks).

#### **Set-Associative Cache:**
- **Structure:**
  - Combines aspects of fully associative and direct-mapped caches.
  - Divides cache into "ways," allowing a block to occupy one of several slots.
- **Advantages:**
  - Balances flexibility and complexity.


### **5. Cache Lines**
- **Concept:**
  - Data is loaded into cache in blocks (e.g., 64 bytes).
- **Alignment:**
  - Cache lines start at addresses divisible by the block size.
- **Efficiency:**
  - Improves spatial locality by fetching adjacent data.


### **6. Practical Examples**
#### **Lookup Process:**
1. Split the address into:
   - **Tag:** Identifies the block.
   - **Index:** Determines the cache line.
   - **Offset:** Position within the block.
2. Compare the tag with stored tags.
3. Return data if the tag matches; otherwise, fetch from main memory.

#### **Replacement Policies:**
- **Least Recently Used (LRU):** Replaces the least recently accessed data.
- **Random:** Selects a random block to replace.
- **FIFO (First-In-First-Out):** Replaces the oldest block.


### **7. Multi-Level Caches**
- **Structure:**
  - Hierarchical caches (e.g., L1, L2, L3).
  - Closer to the processor → smaller, faster, but more expensive.
- **Example Configuration:**
  - **L1 Cache:**
    - 32 KB, 8-way set associative.
  - **L2 Cache:**
    - 256 KB, 4-way set associative.
  - **L3 Cache:**
    - 2 MB per core, 16-way set associative.


## ❓ **Questions Raised**
- How do compiler optimizations interact with cache management?
- What are the trade-offs between direct-mapped and fully associative caches?


## 🔗 **Further Reading/Resources**
- [Memory Hierarchy in Computer Architecture](https://en.wikipedia.org/wiki/Memory_hierarchy)
- [Cache Design and Performance](https://www.intel.com/content/www/us/en/developer/articles/technical/cpu-cache-and-memory-hierarchy.html)
- [Understanding Cache Replacement Policies](https://www.geeksforgeeks.org/cache-replacement-policies/)


## 📌 **Summary**
- **Main Takeaways:**
  - The memory hierarchy addresses speed, cost, and capacity limitations.
  - Locality principles guide efficient program design and hardware caching.
  - Caches dramatically improve performance by reducing main memory access frequency.
- **How This Links to Previous Content:**
  - Builds on memory management concepts, emphasizing practical performance optimizations.


## ✅ **Action Items**
- Write a program that demonstrates temporal and spatial locality effects.
- Experiment with different cache configurations in a simulator.
- Analyze how varying cache replacement policies affect performance.


### **Lecture Review**
- **What I Learned:**
  - The role and operation of caches in modern systems.
  - Key strategies to optimize program performance using locality.
- **What Needs Clarification:**
  - Practical implementation details of multi-level caches.
- **My Plan to Review This Material:**
  - Simulate cache operations with different data access patterns.

