# 📚 **Lecture Notes**


## 🗓️ **Course Details**
- **Course Title:** Betriebssysteme 1
- **Lecture Title:** Datentypen
- **Lecturer Name:** Felix Morgner
- **Date:** 05.11.2024
- **Lecture Number:** 8


## 📝 **Key Topics Covered**
1. Primitive and Complex Data Types in C
2. Memory Representation of Data Types
3. Pointers, Arrays, and Strings
4. Structs, Unions, and Memory Layout
5. Type Casting and Conversion


## 🧠 **Learning Objectives**
- Define arrays, strings, and structs and describe their memory layout.
- Utilize key functions for string manipulation.
- Pass arrays, strings, and structs as function parameters.


## 📖 **Detailed Notes**

### **1. Primitive Data Types**
- **Types in C:**
  - `char`: Single machine byte.
  - `int`: Natural bit width of the processor (signed by default).
  - `void *`: Machine word interpreted as an address.
- **Predefined Integer Aliases:**
  - `int8_t, int16_t, int32_t, int64_t`: Fixed-width integers.
  - `intptr_t`: Integer type capable of holding an address.
  - `size_t`: Unsigned integer large enough to represent the size of an object.


### **2. Memory Representation**
- **Assembly Perspective:**
  - Data types do not exist at the machine code level.
  - Memory is viewed as bits grouped into bytes.
- **Size of Data Types:**
  - `sizeof`: Compile-time operator to determine object or type size in bytes.
  - Example:
    ```c
    uint32_t a[] = {1, 2, 3};
    size_t n = sizeof a / sizeof a[0]; // Number of elements
    ```


### **3. Pointers and Arrays**
#### **Pointer Arithmetic:**
- Incrementing a pointer considers the size of the data type it points to.
  ```c
  uint64_t *p = 0xA00;
  ++p; // p == 0xA08
  ```
- Pointer difference accounts for type size:
  ```c
  int32_t *x = 120, *y = 100;
  ptrdiff_t diff = x - y; // diff == 5
  ```

#### **Arrays:**
- **Declaration:**
  ```c
  int a[10]; // Reserves space for 10 integers
  ```
- **Array as Pointer:**
  - Array labels are constant pointers.
  - Example:
    ```c
    int32_t *p = a; // Address of array's first element
    ```


### **4. Strings**
- **Null-Terminated Strings:**
  - Char arrays ending with `\0`.
  - Example:
    ```c
    char s[] = {'H', 'e', 'l', 'l', 'o', '\0'};
    ```
- **String Functions (from `<string.h>`):**
  - `strlen`: Length of a string.
    ```c
    size_t strlen(char const *str) {
        char const *p = str;
        while (*p) ++p;
        return p - str;
    }
    ```


### **5. Structs and Memory Layout**
#### **Structs:**
- **Definition:**
  ```c
  struct Point {
      int x;
      int y;
  };
  struct Point p = {10, 20};
  ```
- **Memory Alignment:**
  - Compiler may insert padding to align members.
  - Example:
    ```c
    struct {
        char c;  // Offset 0
        int x;   // Offset 4
    }; // sizeof == 8 (padding added)
    ```

#### **Unions:**
- **Definition:**
  - All members share the same memory location.
  - Example:
    ```c
    union Data {
        int i;
        float f;
    };
    ```
- **Use Case:**
  - Avoid type casting by interpreting memory differently.
  - Example:
    ```c
    union U {
        int kind;
        struct { int kind; char value[256]; } str;
    };
    ```


### **6. Type Casting**
- **Implicit Casting:**
  - Between compatible types (e.g., `int` to `float`).
- **Explicit Casting:**
  - Required for incompatible types.
  - Example:
    ```c
    int *p = (int *) 0xA00; // Cast address to integer pointer
    ```
- **Best Practices:**
  - Avoid casts unless necessary.
  - Document reasons for casting.


### **7. Best Practices and Pitfalls**
- **Avoid Using Uninitialized Variables:**
  - Local variables are not automatically initialized.
- **Be Cautious with Global Variables:**
  - Persist across function calls, leading to potential data corruption in recursion.
- **Understand Type Limits:**
  - Implicit conversions between `signed` and `unsigned` types can lead to unexpected results.


## ❓ **Questions Raised**
- What are the practical limitations of using unions for type interpretation?
- How does memory alignment affect performance and memory usage?


## 🔗 **Further Reading/Resources**
- [C Language Memory Layout](https://en.wikipedia.org/wiki/C_data_types)
- [String Handling in C](https://www.cplusplus.com/reference/cstring/)
- [Structs in C Programming](https://www.geeksforgeeks.org/structures-c/)


## 📌 **Summary**
- **Main Takeaways:**
  - C types are abstractions; their layout and size depend on hardware and compiler.
  - Arrays and pointers form the backbone of C's memory management.
  - Strings are simple null-terminated char arrays but require careful handling.
  - Structs and unions offer flexible ways to manage memory and data interpretation.
- **How This Links to Previous Content:**
  - Expands on memory management principles, introducing structured data types.


## ✅ **Action Items**
- Implement structs and unions in C programs to understand memory layout.
- Explore the effects of type casting and implicit conversions in complex expressions.
- Practice handling strings with built-in functions and custom logic.


### **Lecture Review**
- **What I Learned:**
  - Detailed understanding of data types, their memory layout, and usage in C.
- **What Needs Clarification:**
  - Advanced memory alignment strategies for performance optimization.
- **My Plan to Review This Material:**
  - Write small programs experimenting with structs, arrays, and type casting.
