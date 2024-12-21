# 📚 **Lecture Notes**


## 🗓️ **Course Details**
- **Course Title:** Betriebssysteme 1
- **Lecture Title:** Funktionen
- **Lecturer Name:** Felix Morgner
- **Date:** 29.10.2024
- **Lecture Number:** 7


## 📝 **Key Topics Covered**
1. Stack Mechanics and Memory Management
2. Calling Conventions
3. Recursive Functions and Their Challenges
4. Function Prologues and Epilogues
5. Pointer and Function Interactions


## 🧠 **Learning Objectives**
- Describe the return mechanism at the assembly level.
- Explain stack frames and their role in function execution.
- Differentiate between global and local variables in C.
- Understand the limitations of global variables in recursion.


## 📖 **Detailed Notes**

### **1. Stack Mechanics**
- **Key Operations:**
  - **Push:** Adds data to the stack, adjusts the stack pointer (`rsp`).
    ```asm
    push rax  ; Equivalent to:
    sub rsp, 8
    mov [rsp], rax
    ```
  - **Pop:** Removes data from the stack, adjusts the stack pointer.
    ```asm
    pop rax   ; Equivalent to:
    mov rax, [rsp]
    add rsp, 8
    ```
- **Purpose:**
  - Temporarily store values such as:
    - Intermediate results
    - Function arguments
    - Return addresses


### **2. Calling Conventions**
- **Definition:**
  - A set of rules for how functions receive parameters and return results.
- **Components:**
  1. **Argument Passing:** Arguments passed in registers (e.g., `RDI`, `RSI`) or on the stack.
  2. **Return Values:** Typically stored in `RAX`.
  3. **Register Saving:**
     - **Caller-Saved:** The caller is responsible for saving registers before calling.
     - **Callee-Saved:** The function preserves certain registers.
- **Example:**
  ```c
  int f(int x, int y) {
      return x + y;
  }
  ```
  - Assembly Translation:
    ```asm
    mov eax, edi  ; Copy argument x
    add eax, esi  ; Add argument y
    ret
    ```


### **3. Recursive Functions**
- **Challenges:**
  - Each recursion requires:
    - Separate return addresses
    - Independent values for local variables
  - **Solution:** Use the stack for storing:
    - Local variables
    - Return addresses
- **Example:**
  ```c
  int sum(int n) {
      if (n == 0) return 0;
      return n + sum(n - 1);
  }
  ```
  - Assembly Translation:
    ```asm
    sum:
        test rdi, rdi
        jz done
        push rdi
        dec rdi
        call sum
        pop rsi
        add rax, rsi
    done:
        ret
    ```


### **4. Function Prologue and Epilogue**
- **Prologue:**
  - Sets up the stack frame for a function:
    ```asm
    push rbp
    mov rbp, rsp
    ```
- **Epilogue:**
  - Restores the stack frame before returning:
    ```asm
    mov rsp, rbp
    pop rbp
    ret
    ```


### **5. Pointer Interactions**
- **Function Pointers:**
  - Allow dynamic selection of functions.
  - Example:
    ```c
    int (*p)(int, int) = &f;
    int result = p(2, 3);
    ```
  - Assembly:
    ```asm
    mov rax, p
    call rax
    ```
- **Pointer as Arguments:**
  - Allows modification of data outside the function scope.
  - Example:
    ```c
    void increment(int *x) {
        (*x)++;
    }
    ```
  - Assembly:
    ```asm
    mov rax, [rdi]
    inc rax
    mov [rdi], rax
    ```


### **6. Printf and Variable Arguments**
- **Usage:**
  - Printf handles variable arguments by parsing the format string.
  - Example:
    ```c
    printf("%s %d", "Result:", 42);
    ```
- **Assembly Process:**
  - Arguments pushed onto the stack, format string parsed at runtime.


## ❓ **Questions Raised**
- How do different compilers implement calling conventions for optimized performance?
- What are the trade-offs between using global and local variables?


## 🔗 **Further Reading/Resources**
- [Intel x86-64 Calling Conventions](https://en.wikipedia.org/wiki/X86_calling_conventions)
- [Understanding Stack Frames](https://www.geeksforgeeks.org/stack-frame-in-c/)
- [Function Pointers in C](https://www.tutorialspoint.com/function-pointer-in-c)


## 📌 **Summary**
- **Main Takeaways:**
  - The stack is crucial for function execution, providing memory for variables and return addresses.
  - Calling conventions standardize parameter passing and register usage.
  - Recursive functions rely heavily on the stack to manage independent variables and execution flow.
- **How This Links to Previous Content:**
  - Builds upon memory management and control flow, emphasizing stack utilization.


## ✅ **Action Items**
- Write recursive functions and analyze their stack usage.
- Experiment with different calling conventions using assembly.
- Explore pointer arithmetic and its role in function parameter passing.


### **Lecture Review**
- **What I Learned:**
  - Detailed mechanisms of function execution at the assembly level.
  - Practical applications of stack frames in recursive calls.
- **What Needs Clarification:**
  - Efficiency considerations in custom calling conventions.
- **My Plan to Review This Material:**
  - Analyze compiler-generated assembly for complex functions.

