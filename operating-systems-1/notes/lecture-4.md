# 📚 **Lecture Notes**


## 🗓️ **Course Details**
- **Course Title:** Betriebssysteme 1
- **Lecture Title:** Die C-Toolchain
- **Lecturer Name:** Felix Morgner
- **Date:** 08.10.2024
- **Lecture Number:** 4


## 📝 **Key Topics Covered**
1. Components of the C-Toolchain
2. The Role and Operation of the C Preprocessor
3. The Function of the C Compiler
4. Handling Variables in C and Assembler


## 🧠 **Learning Objectives**
- Describe and utilize the C-Toolchain for simple tasks.
- Explain the operation of the C Preprocessor.
- Understand the basic elements of a C program.
- Map global variables in C to labels in assembly.


## 📖 **Detailed Notes**

### **1. The C-Toolchain**
- **Components:**
  1. **C Preprocessor:** Processes directives like `#include` and `#define`.
  2. **C Compiler:** Converts preprocessed C code into assembly.
  3. **Assembler:** Translates assembly code into object files.
  4. **Linker:** Combines object files into an executable.
- **Workflow:**
  ```plaintext
  Source Code → Preprocessor → Compiler → Assembler → Linker → Executable
  ```
- **Modern Compilers:**
  - Often integrate all steps into a single tool.


### **2. The C Preprocessor**
- **Stages:**
  1. **Comment Removal and Line Joining:**
     - Example:
       ```c
       // Single-line comment
       /* Multi-line
       comment */
       puts("Hello \
       World");
       ```
       Output:
       ```c
       puts("Hello World");
       ```
  2. **Tokenization:**
     - Breaks code into tokens (e.g., identifiers, literals, operators).
  3. **Directive Execution:**
     - Examples:
       - `#include`: Inserts header files.
       - `#define`: Replaces macros.
       - `#if`, `#else`, `#endif`: Handles conditional compilation.


### **3. The C Compiler**
- **Role:**
  - Converts pure C code (output of preprocessor) into assembly language.
- **Translation Units:**
  - Includes all `#include` files and preprocessor expansions.
  - Contains global variables, functions, and type definitions.
- **Example Workflow:**
  - C Code:
    ```c
    int x = 5;
    void f() { if (x == 0) g(); }
    ```
  - Assembly Output:
    ```asm
    mov eax, x
    cmp eax, 0
    jne skip
    call g
    skip:
    ret
    ```


### **4. Handling Variables**
#### **Global Variables**
- In C:
  ```c
  int x = 5;
  ```
- In Assembler:
  ```asm
  global x
  x: dd 5
  ```
- Characteristics:
  - Always associated with a type and identifier.
  - Stored in memory with fixed size based on type.

#### **Static Variables**
- Not exported and are local to the file or function.
- C Example:
  ```c
  static int y = 10;
  ```
- Assembler Equivalent:
  ```asm
  y: dd 10
  ```

#### **Import/Export**
- `extern`: Declares an external variable.
- Example:
  - C:
    ```c
    extern int z;
    ```
  - Assembler:
    ```asm
    extern z
    ```

#### **Variable Initializations**
- Automatically zeroed if not explicitly initialized in C.
- Example:
  - C:
    ```c
    int a;
    int b = 10;
    ```
  - Assembler:
    ```asm
    a: dd 0
    b: dd 10
    ```


## ❓ **Questions Raised**
- How does the linker handle conflicting variable types across multiple object files?
- What is the performance impact of preprocessing large numbers of headers?


## 🔗 **Further Reading/Resources**
- [C Programming Language Documentation](https://en.cppreference.com/)
- [Clang Compiler Documentation](https://clang.llvm.org/docs/)
- [GNU Compiler Collection (GCC)](https://gcc.gnu.org/)
- [Introduction to Linkers](https://en.wikipedia.org/wiki/Linker_(computing))


## 📌 **Summary**
- **Main Takeaways:**
  - The C-Toolchain streamlines the process from source code to executable.
  - Preprocessors handle macros, includes, and conditional compilation.
  - Global variables in C directly map to labels in assembler.
- **How This Links to Previous Content:**
  - Builds upon assembler basics, showing how C integrates into low-level operations.

## ✅ **Action Items**
- Practice preprocessing, compiling, and linking simple programs.
- Explore the behavior of `#define` and `#include` with multiple files.
- Map C global and static variables to assembly to understand memory allocation.


### **Lecture Review**
- **What I Learned:**
  - The hierarchical process of the C-Toolchain.
  - How global variables are handled across C and assembler.
- **What Needs Clarification:**
  - The interaction between static and extern variables during linking.
- **My Plan to Review This Material:**
  - Compile small programs with GCC/Clang and analyze outputs at each stage.
