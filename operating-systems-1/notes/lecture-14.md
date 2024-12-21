# 📚 **Lecture Notes**

---

## 🗓️ **Course Details**

- **Course Title:** Betriebssysteme 1 (Operating Systems 1)
- **Lecture Title:** Semesterabschluss (Semester Conclusion)
- **Lecturer Name:** Felix Morgner
- **Date:** 17.12.2024
- **Lecture Number:** 14

---

## 📝 **Key Topics Covered**

1. Semester Review
2. Exam Details
3. Preview of Next Semester Topics

---

## 🧠 **Learning Objectives**

- Review key concepts from the semester, including processor basics, memory management, and input/output.
- Prepare for the upcoming exam with an understanding of exam format and scope.
- Gain insight into the topics that will be covered in the next semester, such as OS APIs, file systems, and multithreading.

---

## 📖 **Detailed Notes**

### **1. Semester Review**

#### **Prozessorgrundlagen (Processor Basics)**

- Processors execute instructions sequentially from memory.
- Instructions are CPU-specific and must be translated to binary machine code.
- Key concepts:
  - Processors use internal flags to determine states (e.g., overflow, zero).
  - Communication with memory occurs via the memory bus.

#### **Hauptspeicher und Cache (Main Memory and Cache)**

- **Caches:** Store frequently used data to minimize latency due to slower main memory.
  - Types:
    - Fully Associative Cache (FAC)
    - Direct Mapped Cache (DMC)
    - Set Associative Cache (SAC)
- **Locality Principles:**
  - Temporal: Repeated use of the same data.
  - Spatial: Use of data stored close together.

#### **Virtueller Speicher (Virtual Memory)**

- Programs interact with virtual addresses; MMU translates to physical addresses.
- Concepts:
  - Pages and Frames: Pages reside in frames of equal size.
  - Strategies:
    - Single-Level Paging: Simple but inefficient.
    - Multi-Level Paging: Complex but space-efficient.

#### **Ein-/Ausgabe (Input/Output)**

- Communication types:
  - **Polling:** CPU checks device status regularly.
  - **Interrupts:** Device signals the CPU asynchronously.
  - **DMA:** Devices directly access main memory.

---

### **2. Exam Details**

- **Date:** 21.01.2025, 08:30
- **Locations:**
  - Rapperswil: Aula (monitored by Dominic)
  - Sankt Gallen: FZ.0132 (monitored by Felix)
- **Duration:** 2 hours
- **Permitted Materials:** One A4 sheet (front and back) of notes.
- Practice exams and old tests will be provided during this week’s exercise sessions.

---

### **3. Preview of Next Semester**

#### **Topics**

1. **OS API:**
   - Interaction between processes and OS using arguments, environment variables, and POSIX standards.
2. **File Systems:**
   - Logical: File descriptors, handles, and POSIX-C interactions.
   - Physical: ext2/ext4, journaling, and FAT file systems.
3. **Multithreading:**
   - Differences between processes and threads.
   - APIs like POSIX and thread synchronization tools.
4. **Scheduling:**
   - Cooperative vs. preemptive multitasking.
   - Scheduling metrics and strategies.
5. **Synchronization:**
   - Avoiding race conditions with semaphores and mutexes.
   - Addressing priority inversion.
6. **Interprocess Communication:**
   - Mechanisms like signals, message passing, and shared memory.
   - Networking basics, including sockets.

---

## ❓ **Questions Raised**

- How does multi-level paging improve memory efficiency compared to single-level paging?
- What are the practical trade-offs of cache types like FAC, DMC, and SAC?

---

## 📌 **Summary**

- **Main Takeaways:**
  - Consolidation of semester concepts including processor basics, I/O communication, and virtual memory.
  - Upcoming topics like synchronization and file systems will deepen OS understanding.
- **Connections to Previous Content:**
  - Builds on foundational concepts like memory management and CPU operations.

---

## ✅ **Action Items**

- Create a concise A4 exam sheet summarizing semester topics.
- Review key areas like DMA, caching strategies, and virtual memory management.
- Practice with old exams and exercises provided in this week’s sessions.

---

### **Lecture Review**

- **What I Learned:**
  - Detailed review of semester topics and introduction to advanced OS concepts for next semester.
- **What Needs Clarification:**
  - Deeper understanding of file system structures (ext4 vs. FAT) and journaling mechanisms.
- **My Plan to Review This Material:**
  - Dedicate time to solving practice exams and summarizing theoretical content into notes.
