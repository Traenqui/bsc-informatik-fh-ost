# 📚 **Lecture Notes**


## 🗓️ **Course Details**
- **Course Title:** Betriebssysteme 1
- **Lecture Title:** Variablen
- **Lecturer Name:** Felix Morgner
- **Date:** 01.10.2024
- **Lecture Number:** 3


## 📝 **Key Topics Covered**
1. Intel 64 Registers
2. Intel 64 Instructions
3. Memory Addressing Modes
4. Linker and Executable Creation
5. Basic "Hello World" in Assembler


## 🧠 **Learning Objectives**
- List and relate Intel 64 architecture registers.
- Explain and use addressing modes in Intel 64.
- Specify copy instructions in assembly.
- Utilize the linker to create executables.
- Explain the connection of variables and labels in assembly.
- Understand a basic "Hello World" program in assembly.


## 📖 **Detailed Notes**

### **1. Intel 64 Registers**
- **Key Points:**
  - **General Purpose Registers (GPRs):**
    - RAX, RCX, RDX, RBX, RSI, RDI, RSP, RBP, R8–R15.
    - Examples:
      - RAX: Accumulator for arithmetic.
      - RCX: Loop counter.
      - RSP: Stack pointer.
  - **Special Purpose Registers (SPRs):**
    - RIP (Instruction Pointer): Points to the next instruction.
    - RFLAGS: Holds flags like carry, zero, etc.
  - Registers are divided into sections:
    - **64-bit:** RAX.
    - **32-bit:** EAX.
    - **16-bit:** AX (can split into AL and AH).


### **2. Intel 64 Instructions**
- **Categories of Operations:**
  - Data Transfer: Move data between memory and registers.
    - Example: `mov rax, rbx` (Copies RBX to RAX).
  - Arithmetic/Logic: Perform calculations.
  - Program Flow: Branch and loop control.
  - String Operations: Operations on sequences of characters.
  - Device Communication: Interact with external hardware.
- **Instruction Length:**
  - Varies between 1–15 bytes, depending on operands.
- **Machine Code Translation:**
  - Example: `mov rax, rbx` → `48 89 D8`.


### **3. Memory Addressing Modes**
- **Types of Addressing:**
  - **Displacement:** Direct address (`[0x8000]`).
  - **Base:** Address in a register (`[rbx]`).
  - **Scaled Index:** Register multiplied by a scale factor (`[rcx * 8]`).
  - **Combined:** Any combination (`[0x2000 + rbx + rcx * 2]`).
- **Load Effective Address (LEA):**
  - Example: `lea rax, [0x2000 + rbx + rcx * 2]` calculates address without accessing memory.


### **4. Linker and Executable Creation**
- **Steps:**
  - Assembler translates assembly code into object files.
  - Linker combines object files into an executable.
  - Entry Point:
    - Default: `_start`.
    - Customizable using the `-e` flag (`ld -e main prog.o -o prog`).
- **Symbol Table in Object Files:**
  - Stores metadata like variable names and offsets.


### **5. Hello World in Assembler**
- **Program:**
  ```asm
  hello: db 'Hello OST', 13, 10
  hello_length: equ $ - hello

  extern _start
  _start:
      mov rax, 1          ; syscall write
      mov rdi, 1          ; target stdout
      mov rsi, hello      ; address of string
      mov rdx, hello_length ; length of string
      syscall

      mov rax, 60         ; syscall exit
      mov rdi, 0          ; exit code
      syscall
  ```
- **Syscall Mechanism:**
  - `rax`: Syscall number.
  - Parameters in: `rdi`, `rsi`, `rdx`, etc.
  - Example: `write` (code 1) writes to `stdout`.


## ❓ **Questions Raised**
- What are the practical applications of combining addressing modes?
- How does the linker handle symbol collisions between multiple object files?


## 🔗 **Further Reading/Resources**
- [Intel 64 and IA-32 Architectures Manual](https://www.intel.com/content/www/us/en/developer/articles/technical/intel-sdm.html)
- [NASM Documentation](https://www.nasm.us/xdoc/2.13.01/html/)
- [Introduction to x86 Assembly](https://cs.lmu.edu/~ray/notes/x86assembly/)


## 📌 **Summary**
- **Main Takeaways:**
  - Registers and memory addressing are central to assembly programming.
  - Linkers assemble multiple object files into a single executable.
  - Syscalls interface programs with the operating system.
- **How This Links to Previous Content:**
  - Builds on assembler knowledge and machine code execution.


## ✅ **Action Items**
- Practice defining and using various addressing modes in NASM.
- Compile and link a simple multi-file assembly program.
- Explore syscall documentation for additional OS functions.


### **Lecture Review**
- **What I Learned:**
  - The utility of registers and their subdivisions in assembly.
  - Various methods to address memory locations.
  - The critical role of the linker in executable creation.
- **What Needs Clarification:**
  - The interaction of syscalls with different OS architectures.
- **My Plan to Review This Material:**
  - Write and debug a custom assembly program using addressing modes and syscalls.
