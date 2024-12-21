# 📚 **Lecture Notes**


## 🗓️ **Course Details**
- **Course Title:** Betriebssysteme 1
- **Lecture Title:** Assembler
- **Lecturer Name:** Felix Morgner
- **Date:** 24.09.2024
- **Lecture Number:** 2


## 📝 **Key Topics Covered**
1. Understanding Machine Code
2. Role and Operation of Assemblers
3. Usage of Labels in Assembly Language
4. Differences Between Flat-Form Binaries and Object Files


## 🧠 **Learning Objectives**
- Explain how an assembler works.
- Understand the purpose and handling of labels in assembly code.
- Describe the role of object files and their usage.


## 📖 **Detailed Notes**

### **1. Machine Code**
- **Key Points:**
  - Machine code consists of binary instructions understood by the processor.
  - Different processors use different instruction sets (e.g., Intel 64 architecture).
  - Instructions are encoded as byte sequences, combining operations and operands.
- **Examples:**
  - Instruction: `Add 12345678h to Register 1` → Binary encoding: `81h C1h 78h 56h 34h 12h`.
- **Important Terms:**
  - **Opcode:** Operation code part of an instruction.
  - **Endianess:** Specifies byte order (Big-Endian vs. Little-Endian).


### **2. Assembler**
- **Key Points:**
  - The assembler converts human-readable assembly language into machine code.
  - Works line-by-line, translating text commands into binary instructions.
  - Assembly language is architecture-dependent (e.g., NASM for Intel 64-bit).
- **Examples:**
  - Assembly instruction: `mov rax, rbx` → Machine code: `48h 89h D8h`.
- **Assembler Modes:**
  - 16-bit, 32-bit (Legacy), and 64-bit modes, with `BITS` directive to set mode.


### **3. Labels in Assembly**
- **Key Points:**
  - Labels are markers for positions in code, not converted into machine code.
  - Labels simplify reference to memory addresses or offsets.
  - Arithmetic with labels is supported for advanced memory calculations.
- **Examples:**
  - Label usage: 
    ```asm
    my_text: db 'Betriebssysteme 1'
    length: dq after_text - my_text
    ```
- **Internal Handling:**
  - The assembler replaces label references with their offsets during compilation.


### **4. Output Files: Flat-Form Binaries vs. Object Files**
- **Key Points:**
  - **Flat-Form Binaries:**
    - Contain only the raw byte sequence of machine code.
    - No metadata (e.g., symbols or references).
  - **Object Files:**
    - Contain machine code with metadata like symbol tables.
    - Useful for linking and debugging.
- **Examples:**
  - NASM command for object file creation:
    ```bash
    nasm -f elf64 prog.asm -o prog.o
    ```
  - Inspecting object files with `objdump`:
    ```bash
    objdump -t -d -Mintel prog.o
    ```


## ❓ **Questions Raised**
- What advantages do object files provide over flat-form binaries?
- How does NASM handle label arithmetic internally?


## 🔗 **Further Reading/Resources**
- [NASM Documentation](https://www.nasm.us/xdoc/2.13.01/html/)
- [Understanding Endianness](https://en.wikipedia.org/wiki/Endianness)
- [ELF File Format](https://linux.die.net/man/5/elf)
- [Assembly Language Tutorial - TutorialsPoint](https://www.tutorialspoint.com/assembly_programming/index.htm)


## 📌 **Summary**
- **Main Takeaways:**
  - Assemblers translate textual commands into machine code efficiently.
  - Labels provide a user-friendly way to manage memory addresses.
  - Object files encapsulate additional information for linking and debugging.
- **How This Links to Previous Content:**
  - Builds on the understanding of machine code execution from the previous lecture on processors.


## ✅ **Action Items**
- Practice using NASM to assemble simple programs.
- Experiment with labels and offsets in assembly code.
- Explore object files using `objdump` or similar tools.


### **Lecture Review**
- **What I Learned:**
  - A deeper understanding of how assembly instructions are translated into machine code.
  - The practical usage of labels and their role in code organization.
- **What Needs Clarification:**
  - Handling of label arithmetic in more complex scenarios.
- **My Plan to Review This Material:**
  - Assemble and disassemble code snippets to observe label handling and binary output.
