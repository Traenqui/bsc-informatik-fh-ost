# 📚 **Lecture Notes**


## 🗓️ **Course Details**
- **Course Title:** Betriebssysteme 1
- **Lecture Title:** Dynamischer Speicher
- **Lecturer Name:** Felix Morgner
- **Date:** 19.11.2024
- **Lecture Number:** 10


## 📝 **Key Topics Covered**
1. Stack vs. Heap Memory
2. Allocation and Fragmentation
3. Dynamic Memory Management Techniques
4. Memory Management in Linux and Windows


## 🧠 **Learning Objectives**
- Differentiate between stack and heap memory and describe their use cases.
- Explain internal and external fragmentation.
- Compare various heap organization strategies and their trade-offs.
- Describe how memory management is implemented in Linux and Windows.


## 📖 **Detailed Notes**

### **1. Stack vs. Heap**
- **Stack:**
  - Fixed size and managed by the function call stack.
  - Data is automatically deallocated when the function returns.
  - Limitations:
    - Limited size.
    - Lifespan tied to the function scope.

- **Heap:**
  - Dynamically allocated memory managed by the operating system.
  - Allows allocation at runtime with flexible lifespans.
  - Requires explicit allocation (`malloc`) and deallocation (`free`).


### **2. Fragmentation**
- **Internal Fragmentation:**
  - Occurs when allocated memory blocks are larger than requested.
  - Unused portions of memory blocks cannot be utilized by other programs.
- **External Fragmentation:**
  - Arises from non-contiguous free memory blocks.
  - Can prevent allocation of larger memory requests despite sufficient total free memory.


### **3. Dynamic Memory Management**
#### **Allocation Techniques:**
1. **Static Allocation:**
   - Fixed-size arrays or buffers.
   - Issues: Wasted memory or insufficient capacity.
2. **Stack Allocation:**
   - Dynamically allocated via `alloca` or similar mechanisms.
   - Problems: Restricted scope, potential stack overflow.
3. **Heap Allocation:**
   - Flexible and widely used for dynamic memory needs.
   - Managed using OS-provided functions like `malloc` and `free`.

#### **Heap Organization Strategies:**
1. **Variable-Sized Blocks:**
   - Allocate exactly the requested size.
   - Prone to fragmentation.
2. **Fixed Block Sizes:**
   - Simplifies allocation but increases internal fragmentation.
3. **Buddy System:**
   - Allocates memory in power-of-2 block sizes.
   - Simplifies merging and splitting of blocks.

#### **Allocation Policies:**
- **First Fit:** Finds the first block large enough to satisfy the request.
- **Best Fit:** Searches all blocks for the smallest suitable size.
- **Worst Fit:** Allocates from the largest free block.


### **4. Practical Implementations**
- **malloc and free (C):**
  - `malloc`: Allocates a memory block of the specified size.
  - `free`: Releases a previously allocated block.
  - Risks:
    - Memory leaks from missing `free` calls.
    - Dangling pointers from repeated `free`.

#### **Garbage Collection:**
- Automated memory management used in environments like Java or .NET.
- **Advantages:**
  - Prevents direct memory leaks.
- **Disadvantages:**
  - Unpredictable deallocation timing.
  - Performance overhead.


### **5. Linux Memory Management**
- **Key Features:**
  - Buddy system for large blocks.
  - Slab allocator for fixed-size kernel objects.
  - `malloc` for user-level programs, with decentralized metadata for quick operations.
- **Advanced Allocators:**
  - `SLAB`: Original allocator, optimized for efficiency.
  - `SLUB`: Modern standard, simpler and faster.
  - `SLOB`: Lightweight for embedded systems.


### **6. Windows Memory Management**
- **Backend:**
  - Uses size classes and block sizes of 8 bytes.
  - Free memory tracked in linked lists and bitmaps.
- **Frontends:**
  - Look-Aside Lists: Quick allocations for frequently requested sizes.
  - Low-Fragmentation Heap: Reduces fragmentation and improves performance.
- **APIs:**
  - `HeapCreate`, `HeapAlloc`, `HeapFree`: Allows custom heap creation and management.


## ❓ **Questions Raised**
- How can developers minimize fragmentation in dynamic memory allocation?
- What are the performance trade-offs between different allocation policies?


## 🔗 **Further Reading/Resources**
- [Memory Allocation in C](https://www.geeksforgeeks.org/dynamic-memory-allocation-in-c-using-malloc-free-calloc-and-realloc/)
- [Linux Memory Management](https://linux.die.net/man/5/malloc)
- [Buddy System Allocation](https://en.wikipedia.org/wiki/Buddy_memory_allocation)


## 📌 **Summary**
- **Main Takeaways:**
  - Dynamic memory enables flexible and efficient use of resources but introduces complexity in management.
  - Fragmentation is a key challenge in memory management, requiring careful design of allocation strategies.
  - Linux and Windows implement robust systems tailored to their respective needs.
- **How This Links to Previous Content:**
  - Builds on memory hierarchy concepts, focusing on runtime management.


## ✅ **Action Items**
- Implement examples of `malloc` and `free` to understand usage patterns.
- Simulate fragmentation scenarios to evaluate different allocation strategies.
- Explore OS-specific memory management APIs for deeper insight.


### **Lecture Review**
- **What I Learned:**
  - The distinction and use cases for stack and heap memory.
  - Practical techniques for dynamic memory allocation and deallocation.
- **What Needs Clarification:**
  - Optimization techniques for large-scale applications.
- **My Plan to Review This Material:**
  - Write programs demonstrating fragmentation and its mitigation strategies.
