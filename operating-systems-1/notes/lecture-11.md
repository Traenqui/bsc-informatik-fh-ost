# 📚 **Lecture Notes**


## 🗓️ **Course Details**
- **Course Title:** Betriebssysteme 1
- **Lecture Title:** Virtueller Speicher Hardware
- **Lecturer Name:** Felix Morgner
- **Date:** 26.11.2024
- **Lecture Number:** 11


## 📝 **Key Topics Covered**
1. Virtual Memory and Process Isolation
2. Memory Management Unit (MMU)
3. Paging and Page Tables
4. Translation Lookaside Buffer (TLB)
5. Advanced Page Table Implementations


## 🧠 **Learning Objectives**
- Explain the mechanism of page-based virtual memory.
- Understand the purpose and working of the Memory Management Unit (MMU).
- Describe the different implementations of page tables and their trade-offs.


## 📖 **Detailed Notes**

### **1. Virtual Memory and Process Isolation**
- **Purpose:**
  - Isolate processes to prevent unauthorized memory access.
  - Map virtual addresses used by processes to physical addresses managed by the OS.
- **Protection:**
  - Prevents access to OS and other processes' memory.
  - Errors within a process remain isolated.


### **2. Memory Management Unit (MMU)**
- **Functionality:**
  - Translates virtual addresses to physical addresses.
  - Handles memory access protection.
- **Key Features:**
  - Virtual addresses are process-specific.
  - Uses a **Translation Lookaside Buffer (TLB)** for caching address translations.


### **3. Paging and Page Tables**
- **Paging Basics:**
  - Virtual memory is divided into fixed-size blocks called pages.
  - Corresponding blocks in physical memory are called page frames.
  - Standard page size: 4 KB.
- **Page Tables:**
  - Store mappings between pages and frames.
  - Each process has its own page table.
  - MMU accesses page tables to translate addresses.


### **4. Page Table Implementations**
#### **Single-Level Page Table:**
- **Structure:**
  - Array indexed by the virtual page number.
  - Contains frame number and status bits.
- **Advantages:**
  - Simple and fast lookup.
- **Disadvantages:**
  - Memory-intensive for large virtual address spaces.

#### **Two-Level Page Table:**
- **Structure:**
  - Splits the page number into two indices:
    - Directory index (points to page table).
    - Page table index (points to frame).
- **Advantages:**
  - Reduces memory requirements for unused pages.

#### **Multi-Level Page Table:**
- **Structure:**
  - Additional hierarchy for managing very large address spaces.
- **Applications:**
  - Used in modern x86-64 systems.

#### **Inverted Page Table:**
- **Structure:**
  - One entry per frame, shared across all processes.
- **Advantages:**
  - Scales well with physical memory size.
- **Disadvantages:**
  - Complex and slower lookups.

#### **Hashed Page Table:**
- **Structure:**
  - Hashes the virtual page number to an index.
  - Linked lists handle hash collisions.
- **Advantages:**
  - Efficient with TLB support.
- **Disadvantages:**
  - Slower for collision-heavy scenarios.


### **5. Translation Lookaside Buffer (TLB)**
- **Purpose:**
  - Cache recent address translations to speed up memory access.
- **Example:**
  - Intel i7 Skylake:
    - Instruction TLB: 128 entries, 8-way associative.
    - Data TLB: 64 entries, 4-way associative.
    - Second-level TLB: 1536 entries, 12-way associative.


### **6. Virtual Memory Benefits**
- **Memory Protection:**
  - Ensures processes do not interfere with each other.
- **Flexible Address Spaces:**
  - Processes can use virtual addresses independent of physical memory layout.
- **Efficient Use of Memory:**
  - OS can swap inactive pages to secondary storage.


## ❓ **Questions Raised**
- How does TLB miss handling affect performance in real-time systems?
- What are the practical trade-offs between single-level and multi-level page tables?


## 🔗 **Further Reading/Resources**
- [Paging and Virtual Memory](https://en.wikipedia.org/wiki/Paging)
- [Memory Management in x86](https://www.intel.com/content/www/us/en/developer/articles/technical/intel-sdm.html)
- [Virtual Memory Basics](https://www.geeksforgeeks.org/virtual-memory-in-operating-system/)


## 📌 **Summary**
- **Main Takeaways:**
  - Virtual memory isolates processes and provides flexible address space usage.
  - Page tables are essential for translating virtual addresses to physical ones.
  - The MMU, aided by TLB, ensures efficient memory translation and access.
- **How This Links to Previous Content:**
  - Builds on dynamic memory concepts, emphasizing hardware-supported memory management.


## ✅ **Action Items**
- Simulate address translation with different page table implementations.
- Analyze TLB performance in scenarios with frequent memory access patterns.
- Explore advanced memory management features in modern operating systems.


### **Lecture Review**
- **What I Learned:**
  - Comprehensive understanding of virtual memory mechanisms.
  - How hardware and OS collaborate to manage memory efficiently.
- **What Needs Clarification:**
  - Detailed workings of hashed page tables in multi-process environments.
- **My Plan to Review This Material:**
  - Test virtual memory management concepts in a simulated OS environment.

