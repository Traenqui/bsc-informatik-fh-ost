# 📚 **Lecture Notes**


## 🗓️ **Course Details**
- **Course Title:** Betriebssysteme 1
- **Lecture Title:** Kontrollfluss
- **Lecturer Name:** Felix Morgner
- **Date:** 17.09.2024
- **Lecture Number:** 6


## 📝 **Key Topics Covered**
1. Conditional and Unconditional Jumps in Assembly
2. Translation of C Control Structures to Assembly
3. Condition Flags and Their Usage
4. Loop Implementations in C and Assembly


## 🧠 **Learning Objectives**
- Describe the translation of comparison operators in C to assembly.
- Explain the use of conditional and unconditional jumps in assembly.
- Translate C control structures like if-statements and loops to assembly.


## 📖 **Detailed Notes**

### **1. Conditional and Unconditional Jumps**
- **Unconditional Jumps (`jmp`):**
  - Updates the instruction pointer (`RIP`) relative to its current value or to an absolute address.
  - Example:
    ```asm
    jmp target
    target:
    mov rax, rbx
    ```
- **Conditional Jumps (`jcc`):**
  - Execute based on condition codes (flags).
  - Example:
    ```asm
    cmp rax, rbx
    je equal
    ```


### **2. Translation of C Control Structures**
#### **If Statements**
- C Code:
  ```c
  if (x < 3) {
      // body
  }
  ```
- Assembly Equivalent:
  ```asm
  mov eax, [x]
  cmp eax, 3
  jge after_body
  ; body
  after_body:
  ```

#### **If-Else Statements**
- C Code:
  ```c
  if (x < 3) {
      // if-body
  } else {
      // else-body
  }
  ```
- Assembly Equivalent:
  ```asm
  mov eax, [x]
  cmp eax, 3
  jge else_body
  ; if-body
  jmp after_if
  else_body:
  ; else-body
  after_if:
  ```

#### **Loops**
1. **While Loop:**
   - C Code:
     ```c
     while (--i) {
         // body
     }
     ```
   - Assembly Equivalent:
     ```asm
     mov rcx, 23
     loop_start:
     dec rcx
     jz loop_end
     ; body
     jmp loop_start
     loop_end:
     ```
2. **Do-While Loop:**
   - Executes the body at least once.
   - C Code:
     ```c
     do {
         // body
     } while (--i);
     ```
   - Assembly Equivalent:
     ```asm
     mov rcx, 23
     loop_start:
     ; body
     dec rcx
     jnz loop_start
     ```
3. **For Loop:**
   - Combines initialization, condition, and iteration in one statement.
   - C Code:
     ```c
     for (int i = 0; i < 10; ++i) {
         // body
     }
     ```
   - Assembly Equivalent:
     ```asm
     mov ecx, 0
     for_condition:
     cmp ecx, 10
     jge for_end
     ; body
     inc ecx
     jmp for_condition
     for_end:
     ```


### **3. Condition Flags**
- **Key Flags:**
  - **Carry Flag (CF):** Indicates unsigned overflow.
  - **Overflow Flag (OF):** Indicates signed overflow.
  - **Zero Flag (ZF):** Indicates result is zero.
  - **Sign Flag (SF):** Reflects the most significant bit of the result.

- **Usage in Subtraction:**
  - Comparison via `cmp` sets these flags.
  - Example:
    ```asm
    cmp rax, rbx
    je equal
    ```
  - Conditions:
    - `ZF = 1`: `a == b`
    - `CF = 1`: `a < b` (unsigned).
    - `SF != OF`: `a < b` (signed).


### **4. Logical Operations**
- Logical operations in assembly correspond closely to C:
  - AND: `and rax, rbx`
  - OR: `or rax, rbx`
  - NOT: `not rax`

- Example: NAND in Assembly:
  ```asm
  mov rax, [x]
  mov rbx, [y]
  and rax, rbx
  not rax
  mov [z], rax
  ```


## ❓ **Questions Raised**
- How do modern compilers optimize jump conditions for nested loops?
- What are the trade-offs between conditional moves (`cmovcc`) and jumps (`jcc`)?


## 🔗 **Further Reading/Resources**
- [Intel Instruction Set Reference](https://www.intel.com/content/www/us/en/developer/articles/technical/intel-sdm.html)
- [Understanding Flags in Assembly](https://en.wikipedia.org/wiki/FLAGS_register)
- [Control Flow Statements in Assembly](https://www.tutorialspoint.com/assembly_programming/assembly_control_statements.htm)


## 📌 **Summary**
- **Main Takeaways:**
  - Control flow in assembly involves a combination of flags and conditional jumps.
  - C control structures translate directly into assembly patterns using `cmp` and `jmp`.
  - Loops in C map to backward jumps in assembly, maintaining efficiency.
- **How This Links to Previous Content:**
  - Builds on logical and arithmetic operations, emphasizing their integration into program flow.


## ✅ **Action Items**
- Write nested loops in C and observe their assembly translation.
- Experiment with condition flags using simple programs.
- Compare the performance of `cmovcc` vs `jcc` instructions.


### **Lecture Review**
- **What I Learned:**
  - Effective translation of C control structures to assembly.
  - Role of flags in enabling conditional logic in assembly.
- **What Needs Clarification:**
  - Optimization differences in compilers for control flow.
- **My Plan to Review This Material:**
  - Test various C control structures and analyze their assembly outputs.
