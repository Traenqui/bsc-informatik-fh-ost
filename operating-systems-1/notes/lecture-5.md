# 📚 **Lecture Notes**


## 🗓️ **Course Details**
- **Course Title:** Betriebssysteme 1
- **Lecture Title:** Variablen und Ausdrücke
- **Lecturer Name:** Felix Morgner
- **Date:** 15.10.2024
- **Lecture Number:** 5


## 📝 **Key Topics Covered**
1. Variables and Objects in C
2. C Types and Their Properties
3. Expressions and Operators in C
4. Arithmetic and Logical Operations in Assembly


## 🧠 **Learning Objectives**
- Explain the purpose of types in C.
- Translate arithmetic and logical expressions from C to assembler.


## 📖 **Detailed Notes**

### **1. Variables and Objects in C**
- **Definitions:**
  - **Object:** Contiguous memory block with interpretable content based on a type.
  - **Variable:** Named object, but not all objects are variables (e.g., return values).
- **Key Points:**
  - Memory size of an object depends on its type (`sizeof(T)`).
  - Variables in assembler correspond to labeled memory locations.


### **2. C Types**
- **Overview:**
  - **Base Types:** `char`, `int`, `float`, etc.
  - **Derived Types:** Arrays, pointers, structures, and unions.
  - **Enumerations:** Special type for named constants (not covered in depth).
- **Properties:**
  - Types exist only at the C language level; assembler deals purely with memory.
  - Type enforcement is weak in C but aids error detection.

- **Signed Integer Types:**
  | Type            | Minimum Size      |
  |-----------------|-------------------|
  | `signed char`   | ≥ 8 bits          |
  | `short int`     | ≥ 16 bits         |
  | `int`           | ≥ 16 bits         |
  | `long int`      | ≥ 32 bits         |
  | `long long int` | ≥ 64 bits         |

- **Unsigned Counterparts:** Same size as their signed equivalents.
- **Derived Types:**
  - **Pointers:** Address of an object.
  - **Structs/Unions:** Groups of elements in memory.


### **3. Expressions and Operators in C**
- **Integer Constants:**
  - Decimal: Start with non-zero digits (e.g., `123`).
  - Octal: Start with `0` (e.g., `0123`).
  - Hexadecimal: Start with `0x` (e.g., `0x1A3`).
- **Usage in Expressions:**
  - Example:
    ```c
    int x = 5;
    int y = x + 10;
    ```
    Translation to assembly:
    ```asm
    mov eax, [x]
    add eax, 10
    mov [y], eax
    ```
- **Bitwise Operators in C:**
  - `~` (NOT), `&` (AND), `|` (OR), `^` (XOR).
  - Equivalent to assembler operations (`not`, `and`, `or`, `xor`).


### **4. Arithmetic and Logical Operations in Assembly**
- **Logical Operations:**
  - Example: NAND in assembler
    ```asm
    mov rax, [x]
    mov rbx, [y]
    and rax, rbx
    not rax
    mov [z], rax
    ```
- **Arithmetic Operations:**
  - Addition: `add z, q`
  - Subtraction: `sub z, q`
  - Increment/Decrement: `inc z`, `dec z`
  - Example:
    ```asm
    add rax, rbx ; rax = rax + rbx
    ```

- **Shifts and Rotates:**
  - Left Shift (`shl z, i`): Multiply by `2^i`.
  - Right Shift (`shr z, i`): Divide by `2^i` (unsigned).
  - Arithmetic Right Shift (`sar z, i`): Preserve sign for signed division.

- **Multiplication:**
  - `mul z`: Unsigned, result in `RDX:RAX`.
  - Example:
    ```asm
    mul rbx ; RAX = RAX * RBX
    ```

- **Division:**
  - `div z`: Unsigned division, quotient in `RAX`, remainder in `RDX`.
  - Example:
    ```asm
    div rbx ; RAX = RAX / RBX, RDX = RAX % RBX
    ```


## ❓ **Questions Raised**
- How does the C compiler optimize multiplication and division for specific types?
- What are the limitations of type enforcement in C?


## 🔗 **Further Reading/Resources**
- [C Programming Standards](https://en.cppreference.com/)
- [Intel Instruction Set Reference](https://www.intel.com/content/www/us/en/developer/articles/technical/intel-sdm.html)
- [NAND Logic Basics](http://nandgame.com)


## 📌 **Summary**
- **Main Takeaways:**
  - Variables are named memory objects; their behavior depends on types.
  - Logical and arithmetic operations in C map closely to assembler instructions.
  - Shifts, rotates, and type conversions are critical for low-level optimizations.
- **How This Links to Previous Content:**
  - Builds on assembly basics, connecting them to C-level abstractions.


## ✅ **Action Items**
- Write a program that uses logical operators in C and translate it to assembler.
- Explore shift operations in assembly with non-power-of-2 values.
- Experiment with `mul` and `div` instructions to understand register interactions.


### **Lecture Review**
- **What I Learned:**
  - Translation of C expressions to assembler.
  - How assembler handles types implicitly.
- **What Needs Clarification:**
  - The performance impact of signed vs. unsigned operations.
- **My Plan to Review This Material:**
  - Analyze assembly outputs from different C compilers for the same expressions.
